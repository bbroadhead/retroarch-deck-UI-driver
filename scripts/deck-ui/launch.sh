#!/usr/bin/env bash
# Launch an experimental RetroArch build without touching Steam RetroArch.
set -euo pipefail

ROOT="${DECK_UI_ROOT:-$HOME/Applications/RetroArch-DeckUI}"
BINARY="${DECK_UI_BINARY:-$ROOT/retroarch}"
MODE="${1:-deck}"
CONFIG="$ROOT/config/retroarch.cfg"

if [[ "$MODE" != "deck" && "$MODE" != "safe" ]]; then
  echo "Usage: $0 [deck|safe]" >&2
  exit 2
fi
if [[ ! -x "$BINARY" ]]; then
  echo "Experimental RetroArch binary not found or executable: $BINARY" >&2
  exit 1
fi
mkdir -p "$ROOT"/{config,config-home,assets,cores,playlists,thumbnails,saves,states,system,logs,downloads,remaps,overlays,shaders,autoconfig}
if [[ ! -f "$CONFIG" ]]; then
  cat > "$CONFIG" <<EOF
menu_driver = "ozone"
assets_directory = "$ROOT/assets"
libretro_directory = "$ROOT/cores"
playlist_directory = "$ROOT/playlists"
thumbnails_directory = "$ROOT/thumbnails"
savefile_directory = "$ROOT/saves"
savestate_directory = "$ROOT/states"
system_directory = "$ROOT/system"
log_dir = "$ROOT/logs"
rgui_config_directory = "$ROOT/config"
input_remapping_directory = "$ROOT/remaps"
overlay_directory = "$ROOT/overlays"
video_shader_dir = "$ROOT/shaders"
joypad_autoconfig_dir = "$ROOT/autoconfig"
core_options_path = "$ROOT/config/core-options.cfg"
content_database_path = "$ROOT/database"
EOF
fi

# Isolate HOME/XDG defaults as well as all explicit RetroArch paths.
# No Steam installation or Steam userdata files are modified.
export HOME="$ROOT/home"
export XDG_CONFIG_HOME="$ROOT/config-home"
export XDG_DATA_HOME="$ROOT/data-home"
export XDG_CACHE_HOME="$ROOT/cache-home"
mkdir -p "$HOME" "$XDG_CONFIG_HOME" "$XDG_DATA_HOME" "$XDG_CACHE_HOME"

# The deck driver is not yet compiled into RetroArch.
# Keep Ozone as the safe default until the native driver passes a smoke test.
if [[ "$MODE" == "deck" ]]; then
  echo "Deck UI driver is not yet integrated; launching isolated Ozone build." >&2
  exec "$BINARY" --config "$CONFIG" --menu
fi

# Safe mode forces Ozone regardless of the saved menu driver preference.
SAFE_CONFIG="$ROOT/config/retroarch-safe.cfg"
awk '
  /^[[:space:]]*menu_driver[[:space:]]*=/ { next }
  { print }
' "$CONFIG" > "$SAFE_CONFIG"
printf '\nmenu_driver = "ozone"\n' >> "$SAFE_CONFIG"
exec "$BINARY" --config "$SAFE_CONFIG" --menu
