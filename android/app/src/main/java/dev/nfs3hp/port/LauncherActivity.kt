package dev.nfs3hp.port

import android.app.Activity
import android.content.ActivityNotFoundException
import android.content.Context
import android.content.Intent
import android.content.pm.ActivityInfo
import android.content.pm.PackageManager
import android.net.Uri
import android.os.Bundle
import android.provider.OpenableColumns
import android.util.Log
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.activity.result.ActivityResultLauncher
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.core.content.FileProvider
import androidx.documentfile.provider.DocumentFile
import java.io.File
import java.io.FileOutputStream
import java.io.IOException
import java.text.SimpleDateFormat
import java.util.Date
import java.util.Locale

/**
 * The launcher: Play, and every setting the game cannot ask for itself.  The
 * screens are Compose (LauncherScreens.kt) in the game's own colours
 * (LauncherTheme.kt); what they do -- imports, saves, the game's settings file
 * -- stays with the classes that always did it.  One screen is still a View:
 * the touch layout editor, which is the live overlay itself.
 */
class LauncherActivity : ComponentActivity() {

    enum class Screen {
        Main, Language, Data, GameData, DataSets, Saves, LauncherSettings,
        Controls, Touch, Editor, ControlsHelp,
        ForceFeedback, Faq, Display, Adjustment, Network, Advanced, Logs,
    }

    /** A question put to the player: a title, the question, and what the
     *  confirming button says and does.  Null `onConfirm`: only OK. */
    class Dialog(
        val title: String,
        val message: String,
        val confirm: String,
        val onConfirm: (() -> Unit)?,
        val onClose: (() -> Unit)? = null,
    )

    var screen by mutableStateOf(Screen.Main)
        private set
    /** An import, export or restore is running: the screens hold still. */
    var busy by mutableStateOf(false)
        private set
    /** How far it is, 0 to 100, or -1 while that is not known. */
    var importPercent by mutableIntStateOf(-1)
        private set
    var status by mutableStateOf("")
        private set
    var dataSets by mutableStateOf<List<DataSetManager.DataSet>>(emptyList())
        private set
    var activeSet by mutableStateOf<DataSetManager.DataSet?>(null)
        private set
    var dialog by mutableStateOf<Dialog?>(null)

    private var pickerOpen = false
    // Register in a fixed order on every creation, before the activity starts,
    // so AndroidX can deliver a pending result after recreation.
    private val folderPicker = registerPicker(REQUEST_PICK_FOLDER)
    private val zipPicker = registerPicker(REQUEST_PICK_ZIP)
    private val imagePicker = registerPicker(REQUEST_PICK_IMAGE)
    private val saveImportPicker = registerPicker(REQUEST_IMPORT_SAVES)
    private val saveExportPicker = registerPicker(REQUEST_EXPORT_SAVES)
    private val launcherImportPicker = registerPicker(REQUEST_IMPORT_LAUNCHER)
    private val launcherExportPicker = registerPicker(REQUEST_EXPORT_LAUNCHER)

    private var worker: Thread? = null
    private var dataSetManager: DataSetManager? = null
    /** The overlay drawn on the Touch screen or in the editor, while one is. */
    var touchPreview: TouchControlsOverlay? = null

    /* Language of the launcher, chosen on its own screen.  LocaleHelper
     * returns the context unchanged while the setting is "system". */
    override fun attachBaseContext(base: Context) {
        super.attachBaseContext(LocaleHelper.wrap(base))
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        AppLog.configure(this)
        /* On a desktop -- Samsung DeX -- the launcher is a window the player
         * sizes, so the orientation lock is let go: the task's window is made
         * to its shape, and the game that follows into it inherits it
         * (NFS3Activity.desktopWindow).  On a phone it lies as the Display
         * screen says, the same as the game. */
        requestedOrientation = launcherOrientation()
        enableEdgeToEdge()
        super.onCreate(savedInstanceState)
        pickerOpen = savedInstanceState?.getBoolean("document_picker_open") ?: false
        hideStatusBar(this)
        InputDeviceRoles.initialize(this)
        autoReplayPending = savedInstanceState == null && intent.getBooleanExtra("auto_replay", false)
        val preferences = GamePreferences.get(this)
        // Removed in 0.75: fixed/editable positions supersede this global offset.
        preferences.edit().remove("touch_raise_controls").apply()
        // 0.75: the pads' buttons mean one thing in a race and another in the
        // menus, and their racing set moved with it.
        TouchControlsOverlay.anchorLegacyPositions(this)
        try {
            dataSetManager = DataSetManager(this, dataRoot())
        } catch (e: IOException) {
            AppLog.e(TAG, "Could not initialize data sets", e)
            Toast.makeText(this, getString(R.string.data_error, e.message), Toast.LENGTH_LONG).show()
        }
        debugMode = DebugOptions.enabled(this)
        refreshDataSets()
        showScreens()
    }

    override fun onResume() {
        super.onResume()
        CrashReports.check(this)
        if (screen == Screen.Advanced) refreshBonusContent()
        if (autoReplayPending) {
            autoReplayPending = false
            startGame()
        }
    }

    fun launcherOrientation(): Int = orientationFor(this)

    /** Debug mode as the Advanced screen has it; the version under the menu
     *  says so. */
    var debugMode by mutableStateOf(false)

    private fun showScreens() {
        setContent { GameTheme { LauncherScreens(this) } }
    }

    fun dataRoot(): File =
        getExternalFilesDir(null) ?: throw IOException(getString(R.string.error_external_storage))

    fun refreshDataSets() {
        val manager = dataSetManager
        dataSets = manager?.list() ?: emptyList()
        activeSet = manager?.active()
    }

    /** Which build this is, under the menu: v0.78. */
    fun versionLabel(): String {
        val name = try {
            packageManager.getPackageInfo(packageName, 0).versionName ?: ""
        } catch (ignored: PackageManager.NameNotFoundException) {
            ""
        }
        val architecture = if (android.os.Process.is64Bit()) "ARMv8 (64-bit)" else "ARMv7 (32-bit)"
        return "v$name · $architecture"
    }

    fun go(next: Screen) {
        if (next == Screen.Advanced) refreshBonusContent()
        if (next == Screen.GameData || next == Screen.DataSets || next == Screen.Main)
            refreshDataSets()
        if (next != Screen.GameData && next != Screen.Saves && next != Screen.LauncherSettings && next != Screen.DataSets &&
            next != Screen.Logs)
            status = ""
        if (next == Screen.Touch)
            // The old wheel and tilt modes are gone: the buttons are what there is.
            GamePreferences.get(this).edit()
                .putString(GamePreferences.TOUCH_MODE, GamePreferences.TOUCH_MODE_BUTTONS).apply()
        screen = next
    }

    var bonusContent by mutableStateOf<BonusContent.State?>(null)
        private set
    var bonusContentMessage by mutableStateOf("")
        private set

    private fun refreshBonusContent() {
        bonusContent = null
        bonusContentMessage = ""
        if (busy || GameProcess.running(this)) {
            bonusContentMessage = "Close the game before changing bonus content."
            return
        }
        try {
            bonusContent = BonusContent.read(ControlProfile.settingsFile(dataRoot()))
        } catch (e: IOException) {
            bonusContentMessage = e.message ?: "Could not read game settings."
        }
    }

    fun setBonusContent(cars: Boolean? = null, track: Boolean? = null) =
        writeBonusContent { BonusContent.update(it, cars, track) }

    fun setBonusCar(index: Int, unlocked: Boolean) =
        writeBonusContent { BonusContent.updateCar(it, index, unlocked) }

    private fun writeBonusContent(change: (File?) -> BonusContent.State) {
        if (busy || GameProcess.running(this)) {
            refreshBonusContent()
            return
        }
        try {
            bonusContent = change(ControlProfile.settingsFile(dataRoot()))
            bonusContentMessage = ""
        } catch (e: IOException) {
            refreshBonusContent()
            bonusContentMessage = e.message ?: "Could not update bonus content."
        }
    }

    /* The editor is the overlay itself, laid out in a View: the screens step
     * aside for it and come back when it is done. */
    fun openEditor() {
        releasePreview()
        screen = Screen.Editor
        setContentView(R.layout.activity_touch_editor)
        val root = (findViewById<ViewGroup>(android.R.id.content)).getChildAt(0)
        root.setBackgroundColor(getColor(R.color.ui_background))
        val l = root.paddingLeft; val t = root.paddingTop; val r = root.paddingRight; val b = root.paddingBottom
        root.setOnApplyWindowInsetsListener { view, insets ->
            val safe = AndroidWindowCompat.safeInsets(insets)
            view.setPadding(l + safe.left, t + safe.top, r + safe.right, b + safe.bottom)
            insets
        }
        root.requestApplyInsets()
        touchPreview = TouchLayoutEditor.attach(this) { closeEditor() }
    }

    private fun closeEditor() {
        releasePreview()
        screen = Screen.Touch
        showScreens()
    }

    fun releasePreview() {
        touchPreview?.releaseAll()
        touchPreview = null
    }

    fun switchDataSet(set: DataSetManager.DataSet) {
        try {
            dataSetManager?.activate(set.id)
            refreshDataSets()
        } catch (e: IOException) {
            showDataError(e)
        }
    }

    fun confirmDelete(set: DataSetManager.DataSet) {
        dialog = Dialog(
            getString(R.string.delete_data_title),
            getString(R.string.delete_game_files_message, set.name),
            getString(R.string.delete),
            {
                try {
                    dataSetManager?.delete(set.id)
                    refreshDataSets()
                } catch (e: IOException) {
                    showDataError(e)
                }
            },
        )
    }

    private fun showDataError(e: Exception) {
        AppLog.e(TAG, "Data-set operation failed", e)
        Toast.makeText(this, getString(R.string.data_error, e.message), Toast.LENGTH_LONG).show()
    }

    // ---- The system's file pickers, and what comes back from them ----

    private val logExportPicker = registerPicker(REQUEST_EXPORT_LOGS)

    private fun registerPicker(kind: Int) =
        registerForActivityResult(ActivityResultContracts.StartActivityForResult()) { result ->
            onDocumentResult(kind, result.resultCode, result.data)
        }

    private fun launchPicker(picker: ActivityResultLauncher<Intent>, intent: Intent) {
        pickerOpen = true
        try {
            picker.launch(intent)
        } catch (e: RuntimeException) {
            pickerOpen = false
            throw e
        }
    }

    override fun onSaveInstanceState(outState: Bundle) {
        outState.putBoolean("document_picker_open", pickerOpen)
        super.onSaveInstanceState(outState)
    }

    fun launchFolderPicker() {
        if (busy || pickerOpen) return
        val intent = Intent(Intent.ACTION_OPEN_DOCUMENT_TREE)
            .addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION or Intent.FLAG_GRANT_PERSISTABLE_URI_PERMISSION)
        launchPicker(folderPicker, intent)
    }

    fun launchZipPicker() {
        if (busy || pickerOpen) return
        val intent = Intent(Intent.ACTION_OPEN_DOCUMENT).addCategory(Intent.CATEGORY_OPENABLE)
            .setType("application/zip").addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION)
        launchPicker(zipPicker, intent)
    }

    /** A CD image: an .iso, or the .bin of a BIN/CUE pair (DataImporter.importFromDiscImage). */
    fun launchImagePicker() {
        if (busy || pickerOpen) return
        val intent = Intent(Intent.ACTION_OPEN_DOCUMENT).addCategory(Intent.CATEGORY_OPENABLE)
            // Any file: providers give .bin and .iso no one type; the importer
            // reads what it is from the file itself.
            .setType("*/*").addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION)
        launchPicker(imagePicker, intent)
    }

    fun launchSaveImport() {
        if (busy || pickerOpen) return
        val intent = Intent(Intent.ACTION_OPEN_DOCUMENT).addCategory(Intent.CATEGORY_OPENABLE)
            .setType("application/zip").addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION)
        launchPicker(saveImportPicker, intent)
    }

    fun launchSaveExport() {
        if (busy || pickerOpen) return
        val intent = Intent(Intent.ACTION_CREATE_DOCUMENT).addCategory(Intent.CATEGORY_OPENABLE)
            .setType("application/zip").putExtra(Intent.EXTRA_TITLE, "nfs3-saves-" + stamp() + ".zip")
            .addFlags(Intent.FLAG_GRANT_WRITE_URI_PERMISSION)
        launchPicker(saveExportPicker, intent)
    }

    fun launchLauncherImport() {
        if (busy || pickerOpen) return
        val intent = Intent(Intent.ACTION_OPEN_DOCUMENT).addCategory(Intent.CATEGORY_OPENABLE)
            .setType("*/*").addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION)
        launchPicker(launcherImportPicker, intent)
    }

    fun launchLauncherExport() {
        if (busy || pickerOpen) return
        val intent = Intent(Intent.ACTION_CREATE_DOCUMENT).addCategory(Intent.CATEGORY_OPENABLE)
            .setType("application/json").putExtra(Intent.EXTRA_TITLE, "nfs3-launcher-" + stamp() + ".json")
            .addFlags(Intent.FLAG_GRANT_WRITE_URI_PERMISSION)
        launchPicker(launcherExportPicker, intent)
    }

    fun launchLogExport() {
        if (busy || pickerOpen) return
        val intent = Intent(Intent.ACTION_CREATE_DOCUMENT).addCategory(Intent.CATEGORY_OPENABLE)
            .setType("application/zip").putExtra(Intent.EXTRA_TITLE, "nfs3-logs-" + stamp() + ".zip")
            .addFlags(Intent.FLAG_GRANT_WRITE_URI_PERMISSION)
        launchPicker(logExportPicker, intent)
    }

    /** The logs as a zip in the cache, handed to another app: the share menu,
     *  or, to the developer, a letter to the address in developer_email. */
    fun sendLogs(toDeveloper: Boolean) {
        startOperation(getString(R.string.logs_share_title)) {
            val folder = File(cacheDir, "logs")
            folder.listFiles()?.forEach { it.delete() }
            folder.mkdirs()
            val name = "nfs3-logs-" + stamp() + ".zip"
            val zip = File(folder, name)
            val count = FileOutputStream(zip).use { LogBundle.write(applicationContext, it) }
            val uri = FileProvider.getUriForFile(this, "$packageName.logs", zip)
            val send = Intent(Intent.ACTION_SEND).setType(if (toDeveloper) "message/rfc822" else "application/zip")
                .putExtra(Intent.EXTRA_STREAM, uri)
                .putExtra(Intent.EXTRA_SUBJECT, getString(R.string.logs_mail_subject, stamp()))
                .addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION)
            if (toDeveloper)
                send.putExtra(Intent.EXTRA_EMAIL, arrayOf(getString(R.string.developer_email)))
                    .putExtra(Intent.EXTRA_TEXT, getString(R.string.logs_mail_text))
            runOnUiThread {
                try {
                    startActivity(Intent.createChooser(send, getString(R.string.logs_share_title)))
                } catch (e: ActivityNotFoundException) {
                    Toast.makeText(this, getString(R.string.data_error, e.message), Toast.LENGTH_LONG).show()
                }
            }
            getString(R.string.logs_packed, count)
        }
    }

    fun confirmClearLogs() {
        if (GameProcess.running(this)) {
            Toast.makeText(this, R.string.logs_clear_game_running, Toast.LENGTH_LONG).show()
            return
        }
        dialog = Dialog(
            getString(R.string.logs_clear),
            getString(R.string.logs_clear_message),
            getString(R.string.logs_clear),
            {
                val cleared = LogBundle.clear(applicationContext)
                logsChanged++
                Toast.makeText(this, getString(R.string.logs_cleared, cleared), Toast.LENGTH_SHORT).show()
            },
        )
    }

    /** Counts what changed in the log files, so the Logs screen reads them anew. */
    var logsChanged by mutableIntStateOf(0)

    private fun stamp(): String = SimpleDateFormat("yyyyMMdd-HHmm", Locale.ROOT).format(Date())

    /* Read from the stored preference: the operation reports back after the
     * picker, whatever the screen shows by then. */
    private fun includeSettings(): Boolean =
        GamePreferences.get(this).getBoolean(GamePreferences.SAVES_INCLUDE_SETTINGS, false)

    private fun onDocumentResult(requestCode: Int, resultCode: Int, data: Intent?) {
        pickerOpen = false
        if (busy) return
        val uri = data?.data
        if (resultCode != Activity.RESULT_OK || uri == null)
            return
        when (requestCode) {
            REQUEST_PICK_FOLDER -> {
                try {
                    contentResolver.takePersistableUriPermission(uri, Intent.FLAG_GRANT_READ_URI_PERMISSION)
                } catch (e: SecurityException) {
                    AppLog.w(TAG, "Could not persist folder permission", e)
                }
                val name = DocumentFile.fromTreeUri(this, uri)?.name ?: getString(R.string.data_set_name_folder)
                startImport(name) { temporary ->
                    DataImporter.importFromTree(applicationContext, uri, temporary, progressListener())
                }
            }
            REQUEST_PICK_ZIP -> startImport(displayName(uri)) { temporary ->
                DataImporter.importFromZip(applicationContext, uri, temporary, progressListener())
            }
            REQUEST_PICK_IMAGE -> startImport(displayName(uri, getString(R.string.data_set_name_image))) { temporary ->
                DataImporter.importFromDiscImage(applicationContext, uri, temporary, progressListener())
            }
            REQUEST_IMPORT_SAVES -> {
                val withSettings = includeSettings()
                startOperation(getString(R.string.importing_saves)) {
                    val backup = SaveGameManager.importZip(applicationContext, uri, dataRoot(), withSettings)
                    if (backup.isEmpty()) getString(R.string.saves_import_complete_no_backup)
                    else getString(R.string.saves_import_complete, backup)
                }
            }
            REQUEST_EXPORT_SAVES -> {
                val withSettings = includeSettings()
                startOperation(getString(R.string.exporting_saves)) {
                    getString(R.string.saves_export_complete,
                        SaveGameManager.exportZip(applicationContext, uri, dataRoot(), withSettings))
                }
            }
            REQUEST_EXPORT_LOGS -> startOperation(getString(R.string.logs_export)) {
                val count = contentResolver.openOutputStream(uri)?.use { LogBundle.write(applicationContext, it) }
                    ?: throw IOException(getString(R.string.saves_open_failed))
                getString(R.string.logs_exported, count)
            }
            REQUEST_EXPORT_LAUNCHER -> startOperation(getString(R.string.exporting_launcher)) {
                LauncherSettings.export(applicationContext, uri)
                getString(R.string.launcher_backup_export_complete)
            }
            REQUEST_IMPORT_LAUNCHER -> startOperation(getString(R.string.importing_launcher)) {
                /* No recreate() afterwards: every screen reads these settings
                 * when it is shown, and the language is deliberately not
                 * carried, so nothing already on screen can go stale. */
                val backup = LauncherSettings.importFrom(applicationContext, uri, dataRoot())
                // A file from before may carry control positions the old way.
                TouchControlsOverlay.anchorLegacyPositions(this)
                if (backup.isEmpty()) getString(R.string.launcher_import_complete_no_backup)
                else getString(R.string.launcher_import_complete, backup)
            }
        }
    }

    private fun displayName(uri: Uri, fallback: String = getString(R.string.data_set_name_zip)): String {
        try {
            contentResolver.query(uri, arrayOf(OpenableColumns.DISPLAY_NAME), null, null, null)?.use { cursor ->
                if (cursor.moveToFirst())
                    return cursor.getString(0)
            }
        } catch (e: Exception) {
            AppLog.w(TAG, "Could not read document display name", e)
        }
        return fallback
    }

    private fun begin(message: String = getString(R.string.checking_game_data)) {
        busy = true
        importPercent = -1
        status = message
    }

    /** How far along an import is: the bar fills to the percentage and the
     *  text names the file; while the folder is still being measured the bar
     *  runs on its own and the text says so. */
    private fun progressListener(): DataImporter.ProgressListener {
        val running = Thread.currentThread()
        return DataImporter.ProgressListener { done, total, currentPath ->
            runOnUiThread {
                if (worker !== running || isDestroyed) return@runOnUiThread
                val percent = DataImporter.ProgressListener.percent(done, total)
                importPercent = percent
                status = importStatus(this, percent, currentPath)
            }
        }
    }

    private fun startOperation(message: String, operation: () -> String) {
        if (busy) return
        begin(message)
        val thread = Thread({
            val running = Thread.currentThread()
            try {
                val message = operation()
                runOnUiThread {
                    if (worker !== running || isDestroyed) return@runOnUiThread
                    worker = null
                    busy = false
                    status = ""
                    Toast.makeText(this, message, Toast.LENGTH_LONG).show()
                }
            } catch (failure: IOException) {
                AppLog.e(TAG, "Save operation failed", failure)
                runOnUiThread {
                    if (worker !== running || isDestroyed) return@runOnUiThread
                    worker = null
                    busy = false
                    status = getString(R.string.data_error, failure.message)
                    Toast.makeText(this, status, Toast.LENGTH_LONG).show()
                }
            }
        }, "nfs3-save-operation")
        worker = thread
        thread.start()
    }

    private fun startImport(displayName: String, operation: (File) -> Unit) {
        val manager = dataSetManager ?: return
        if (busy) return
        begin()
        val thread = Thread({
            val running = Thread.currentThread()
            try {
                manager.importDataSet(displayName) { temporary ->
                    operation(temporary)
                }
                runOnUiThread {
                    if (worker !== running || isDestroyed) return@runOnUiThread
                    worker = null
                    busy = false
                    status = ""
                    refreshDataSets()
                    Toast.makeText(this, R.string.import_complete, Toast.LENGTH_SHORT).show()
                }
            } catch (e: IOException) {
                if (running.isInterrupted) return@Thread
                AppLog.e(TAG, "Data import failed", e)
                runOnUiThread {
                    if (worker !== running || isDestroyed) return@runOnUiThread
                    worker = null
                    busy = false
                    status = getString(R.string.import_failed, e.message)
                    Toast.makeText(this, status, Toast.LENGTH_LONG).show()
                }
            }
        }, "nfs3-data-import")
        worker = thread
        thread.start()
    }

    /** Close the launcher; an independently running game keeps its own exit flow. */
    fun exitLauncher() {
        if (busy) return
        if (GameProcess.running(this)) finish() else finishAndRemoveTask()
    }

    private var autoReplayPending = false

    fun startGame() {
        if (dataSetManager?.active() == null)
            return
        /* Game data imported before the cop's map came as a minimap gets it
         * now, once -- while the game is not running to save over it. */
        if (!GameProcess.running(this)) {
            try {
                ControlProfile.copMinimapOnce(dataRoot())
            } catch (e: IOException) {
                AppLog.w(TAG, "No data root for the cop's minimap", e)
            }
        }
        val intent = Intent(this, NFS3Activity::class.java)
        getIntent()?.extras?.let { intent.putExtras(it) }
        startActivity(intent)
    }

    @Deprecated("Deprecated in Java")
    override fun onBackPressed() {
        if (busy) return
        if (dialog != null) {
            dialog = null
            return
        }
        when (screen) {
            Screen.Main -> {
                @Suppress("DEPRECATION")
                super.onBackPressed()
            }
            Screen.Editor -> closeEditor()
            Screen.Touch, Screen.ForceFeedback, Screen.ControlsHelp -> go(Screen.Controls)
            // The Data screens are a level deeper than the rest.
            Screen.GameData, Screen.Saves, Screen.LauncherSettings, Screen.Logs -> go(Screen.Data)
            Screen.DataSets -> go(Screen.GameData)
            // Screen adjustment sits under Display.
            Screen.Adjustment -> go(Screen.Display)
            else -> go(Screen.Main)
        }
    }

    override fun onDestroy() {
        val running = worker
        worker = null
        running?.interrupt()
        releasePreview()
        super.onDestroy()
    }

    companion object {
        private const val TAG = "NFS3Launcher"
        private const val REQUEST_PICK_FOLDER = 10
        private const val REQUEST_PICK_ZIP = 11
        private const val REQUEST_IMPORT_SAVES = 12
        private const val REQUEST_EXPORT_SAVES = 13
        private const val REQUEST_IMPORT_LAUNCHER = 14
        private const val REQUEST_EXPORT_LAUNCHER = 15
        private const val REQUEST_PICK_IMAGE = 16
        private const val REQUEST_EXPORT_LOGS = 17

        /** Full screen, as the theme asks, said to the window as well: with the
         *  status bar gone from the start, nothing arrives later to move the
         *  screen that was already drawn. */
        fun hideStatusBar(activity: Activity) {
            val controller = androidx.core.view.WindowCompat.getInsetsController(activity.window, activity.window.decorView)
            controller.hide(androidx.core.view.WindowInsetsCompat.Type.statusBars())
        }

        /** As the Display screen says, for the launcher as for the game: either
         *  way up turning with the phone while the system lets apps turn, or
         *  one way fixed (GamePreferences.screenOrientation).  A desktop
         *  window (DeX) takes whatever shape the player gives it. */
        fun orientationFor(context: Context): Int =
            if (DesktopMode.active(context)) ActivityInfo.SCREEN_ORIENTATION_UNSPECIFIED
            else GamePreferences.screenOrientation(GamePreferences.get(context))

        /** One step of an import, the same on the first run's screen and on
         *  Game data: the file it is on and how far, or that the folder is
         *  still being measured. */
        fun importStatus(context: Context, percent: Int, path: String): String {
            if (percent < 0)
                return context.getString(R.string.checking_game_data)
            val name = path.substring(path.lastIndexOf(File.separatorChar) + 1)
            return context.getString(R.string.importing_percent, name, percent)
        }

    }
}

