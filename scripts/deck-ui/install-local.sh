#!/usr/bin/env bash
# Copy an already-built RetroArch executable into an isolated test directory.
set -euo pipefail
SOURCE="${1:-}"
ROOT="${DECK_UI_ROOT:-$HOME/Applications/RetroArch-DeckUI}"
if [[ -z "$SOURCE" || ! -f "$SOURCE" ]]; then
  echo "Usage: $0 /path/to/built/retroarch" >&2
  exit 2
fi
mkdir -p "$ROOT"
install -m 0755 "$SOURCE" "$ROOT/retroarch"
echo "Installed experimental executable at $ROOT/retroarch"
echo "Launch using scripts/deck-ui/launch.sh safe"
