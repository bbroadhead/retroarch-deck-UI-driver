/* RetroArch Deck UI bootstrap driver.
 * Uses the proven Ozone callback implementation while Deck-specific
 * rendering and navigation are developed. This is NOT the final UI.
 * GPL-3.0-or-later.
 */
#include "../menu_driver.h"

#ifdef HAVE_DECK_UI
/* A distinct registered driver identity with the existing Ozone
 * implementation as a temporary, working rendering fallback.
 * Initialization occurs before the driver list is queried.
 */
menu_ctx_driver_t menu_ctx_deck;

void deck_menu_driver_bootstrap(void)
{
   menu_ctx_deck       = menu_ctx_ozone;
   menu_ctx_deck.ident = "deck";
}
#endif
