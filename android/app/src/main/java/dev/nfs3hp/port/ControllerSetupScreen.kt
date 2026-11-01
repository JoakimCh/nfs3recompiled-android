package dev.nfs3hp.port

import android.view.View
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.widthIn
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clipToBounds
import androidx.compose.ui.unit.dp
import androidx.compose.ui.viewinterop.AndroidView

/** Keep the native controller controls inside the launcher's shared page frame. */
fun showControllerSetup(activity: ComponentActivity, controls: View) {
    activity.enableEdgeToEdge()
    LauncherActivity.hideStatusBar(activity)
    activity.setContent {
        GameTheme {
            ScreenFrame("Gamepads", onBack = { activity.finish() }, scroll = false) {
                Box(Modifier.widthIn(max = 1000.dp).fillMaxWidth().weight(1f).clipToBounds()) {
                    AndroidView(factory = { controls }, modifier = Modifier.matchParentSize())
                }
            }
        }
    }
}
