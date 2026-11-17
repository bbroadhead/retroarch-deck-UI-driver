# Deck UI implementation status

## Implemented in source

- Opt-in `deck` menu driver registered with RetroArch.
- `HAVE_DECK_UI=1` in Makefile.common; requires `HAVE_OZONE=1`.
- Driver delegates to Ozone callbacks for initialization, rendering, playlist navigation and existing RetroAchievements menu support. This is a **temporary fallback**, not a new visual design.
- Separate `deck` and `safe` launcher modes, with safe mode forcing Ozone.
- Independent Deck UI navigation model and unit tests. The model is **not yet wired** to the native driver.

## Not implemented

- Custom rendered Home screen and recently played carousel.
- Custom per-console library and game detail pages.
- Custom RetroAchievements progress and badge interface.
- Full native renderer, artwork layout and controller focus integration.
- Verified end-to-end compilation, runtime and Steam Deck testing.

## Building an experimental test executable

The Makefile flag is opt-in: `make HAVE_DECK_UI=1 HAVE_OZONE=1` after configuring the repository for your system. This has **not been validated** against the current toolchain and is not an installation instruction for Steam RetroArch. Use a separate build and the isolated launcher.

## Next implementation steps

1. Compile and smoke-test driver selection and fallback.
2. Add Deck-specific rendering and input callbacks, initially a basic Home view.
3. Connect the navigation model to existing RetroArch playlist/history APIs.
4. Add a per-game RetroAchievements panel using RetroArch's existing cheevos runtime, preserving unlock behavior and account credentials.
5. Validate on a separate Steam Deck test installation.
