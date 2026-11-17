# Steam Deck isolated testing

**Status:** the native Deck UI driver is not implemented. The launcher currently starts a separately built RetroArch in Ozone mode. Do not replace the Steam installation.

## Steps

1. Build RetroArch from the `deck-ui` branch on Linux or Steam Deck Desktop Mode. Do not overwrite the Steam-distributed executable.
2. Run `bash scripts/deck-ui/install-local.sh /absolute/path/to/built/retroarch`.
3. Run `bash scripts/deck-ui/launch.sh safe` to confirm the isolated build starts.
4. Add the launcher as a non-Steam game in Desktop Mode once it works; use `bash` as the target and the absolute path to `launch.sh` as the argument, or create a desktop entry.
5. Only after native driver integration and build validation, enable the `deck` menu driver in the isolated configuration.

## Isolation details

- Launcher sets an independent HOME and XDG config/data/cache root.
- RetroArch config points at separate core, assets, playlists, thumbnails, saves, states and BIOS paths.
- Existing ROM files may be used read-only; never share writable save/state directories during early testing.
- The launcher does **not** copy or migrate any Steam RetroArch data.
- To reset the experiment, remove the separate `~/Applications/RetroArch-DeckUI` directory after confirming it contains no data you wish to retain.
- Some user-customized paths and core-specific save locations may require further isolation checks before running content.
- Steam Cloud syncing is not configured for this test installation.

## Recovery

Use `bash scripts/deck-ui/launch.sh safe` to launch the separate build with the current safe default of Ozone. Safe mode generates a separate config that explicitly forces `menu_driver = "ozone"` without changing the regular experimental config.
