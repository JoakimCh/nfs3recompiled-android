# Launcher translations

The launcher uses Android string resources, with English as the fallback and
18 translated locales: `cs`, `de`, `el`, `es`, `fr`, `hr`, `hu`, `it`, `kk`,
`nl`, `pl`, `pt`, `ro`, `ru`, `sr`, `sv`, `tr` and `uk`.

English resources are in `android/app/src/main/res/values/`. Each translation
is in `android/app/src/main/res/values-<locale>/translations.xml`. There is no
automatic translation service or synchronization: wording changes need to be
carried into these files explicitly.

## Updating wording

- Put ordinary launcher wording in string resources, including Compose screens
  and Java-built views. Use `stringResource` in Compose and `getString` in Java.
- Update the same resource keys in all 18 locale files when their meaning changes.
  Reuse each locale's existing menu labels in instructions and navigation paths.
- Preserve format arguments such as `%1$s` and `%2$d`, paragraph breaks (`\n`),
  and any `<b>` markup. Escape XML characters (`&amp;`, `&lt;`) and Android string
  apostrophes (`\'`). Avoid translating file names such as `fedata` and `gamedata`.
- A missing translation falls back to English. Do not keep an obsolete answer
  that describes behavior the launcher no longer has.

The technical Advanced screen, diagnostic report contents and some input labels
remain English. Printed controller button names and names from the game's own
Controls menu are also kept recognizable. This is not a reason to mark ordinary
help or controller descriptions `translatable="false"`.

## Language selection

`language_names` and `language_tags` in `values/language.xml` are parallel arrays.
Each language names itself. The `system` entry follows Android's language;
other entries store a BCP-47 tag in `GamePreferences.UI_LANGUAGE`. These settings
affect the launcher; the imported game keeps its own language.

`LocaleHelper.wrap` applies the selected language to a context. Activities that
resolve launcher strings must wrap their base context, including the controller
setup activity. Background operations also need the localized application context.
Do not change Android's process-wide default locale to implement this preference.

When adding a language, add its resource directory and matching entries in both
language arrays. No external translation dependency is required.

When testing is authorized, cover selecting a language different from the system
language, switching back to System language, import/export messages, help text,
and long labels on phone and TV layouts. Source edits alone do not establish
layout fit or native-speaker quality; review translations on a device too.
