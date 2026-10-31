#!/system/bin/sh
# Run from an authorized local ADB shell, not an ordinary terminal app.
# Start a race first, then run this script and switch back within 15 seconds.
set -eu
profile_pkg=dev.nfs3hp.port.armv7tv
profile_process=dev.nfs3hp.port.armv7tv:game
profile_tool=/system/bin/simpleperf
if [ ! -x "$profile_tool" ]; then
    echo 'This phone does not expose /system/bin/simpleperf. Use System Tracing or Android Studio instead.' >&2
    exit 1
fi
profile_pid=$(pidof "$profile_process" || true)
case "$profile_pid" in
    ''|*[!0-9]*) echo 'Start one game session first, then run this script again.' >&2; exit 1 ;;
esac
profile_stamp=$(date +%Y%m%d-%H%M%S)
profile_output="/sdcard/Download/nfs3-${profile_stamp}.perf.data"
profile_local_dir=$(mktemp -d /data/local/tmp/nfs3-profile.XXXXXX)
profile_local="$profile_local_dir/perf.data"
echo "Backup recording location: $profile_local"
echo 'Switch back to your running race now. Sampling starts in 15 seconds and lasts 45 seconds.'
sleep 15
if [ "$(pidof "$profile_process" || true)" != "$profile_pid" ]; then
    echo 'The game process changed. Start a race and run the script again.' >&2
    exit 1
fi
"$profile_tool" record --app "$profile_pkg" -p "$profile_pid" -e cpu-clock:u -f 200 -g --duration 45 -o "$profile_local"
if [ ! -s "$profile_local" ]; then echo "ERROR: Empty recording: $profile_local" >&2; exit 2; fi
profile_magic=$(dd if="$profile_local" bs=8 count=1 2>/dev/null)
if [ "$profile_magic" != PERFILE2 ]; then echo "ERROR: Invalid header: $profile_local" >&2; exit 3; fi
cp "$profile_local" "$profile_output.partial"
if ! cmp -s "$profile_local" "$profile_output.partial"; then echo "ERROR: Export differs; backup: $profile_local" >&2; exit 4; fi
mv "$profile_output.partial" "$profile_output"
sync
if [ ! -s "$profile_output" ]; then echo "ERROR: Empty export; backup: $profile_local" >&2; exit 5; fi
profile_bytes=$(wc -c < "$profile_output" | tr -d '[:space:]')
echo "Verified recording complete: $profile_bytes bytes. Share: $profile_output"
echo "Backup retained: $profile_local"
