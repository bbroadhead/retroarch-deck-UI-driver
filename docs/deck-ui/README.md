# Deck UI — native RetroArch menu driver

Development branch: `deck-ui`. The `master` branch remains untouched.

## Vision

A distinct retro-modern, controller-first interface for the Steam Deck, inspired by SteamOS Gaming Mode's information architecture but not a visual clone.

- Home: recently played carousel, resume, favorites
- Library: per-console collections sourced from RetroArch playlists, artwork grids and filtering
- Game details: launch, core selection, metadata, play history
- RetroAchievements: per-game matching, progress, earned/locked badges, hardcore status, offline cache
- In-game overlay: quick menu, save states and achievements
- Preserve existing RetroArch core launching, settings and input handling

## Upstream integration points (verified in repository)

- `menu/menu_driver.c` and `menu/menu_driver.h`: driver lifecycle and registration
- `menu/menu_displaylist.c`: existing menu list generation
- `menu/drivers/ozone.c`: existing controller-friendly graphical driver reference
- `menu/drivers/xmb.c`: existing XMB driver reference
- `cheevos/`: existing RetroAchievements functionality; reuse authentication and runtime rather than duplicating unlock logic

## Implementation milestones

1. **Driver registration and compilation:** introduce `menu/drivers/deck.c`, register driver under a feature flag, update relevant build files, expose driver selection, retain fallback to Ozone. Do not claim this is complete until a Linux build succeeds.
2. **Home and library:** use existing playlists and history; controller navigation and cover-art rendering; support 1280×800 and scaling.
3. **Game detail page:** selected playlist entry, launch and per-game core settings.
4. **Achievements:** resolve content to RetroAchievements game IDs through existing integration; surface unlock status, progress, artwork and offline states. Do not infer identity from filename alone.
5. **Polish and QA:** responsive layout, custom assets, accessibility, Steam Deck gamepad testing, performance and regression testing.

## Design principles

- Original retro-futurist visual language: dark neutral base, restrained phosphor accents, subtle pixel motifs and optional scanline treatments.
- Artwork first; text readable on the Steam Deck's 7-inch display.
- No mandatory network connection to browse and launch games.
- Graceful handling of missing thumbnails, history and achievement data.
- No destructive modifications to the Steam-installed RetroArch binary during development.
- Respect RetroArch GPL licensing and attribution.

## Current status

Planning and source reconnaissance only. No native `deck` driver, compilation, or RetroAchievements UI integration has been implemented yet.
