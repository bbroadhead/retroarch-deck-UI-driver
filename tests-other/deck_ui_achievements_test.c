#include <assert.h>
#include <string.h>
#include "../menu/drivers/deck_ui_achievements.h"

int main(void)
{
   deck_ui_achievements_t view;
   const deck_ui_achievement_t *item;
   deck_ui_achievements_init(&view);
   assert(deck_ui_achievements_visible_count(&view) == 0);
   assert(deck_ui_achievements_at(&view, 0) == NULL);
   assert(deck_ui_achievements_add(&view, 1, "First", false, false));
   assert(deck_ui_achievements_add(&view, 2, "Second", true, false));
   assert(deck_ui_achievements_add(&view, 3, "Hardcore", false, true));
   assert(!deck_ui_achievements_add(&view, 3, "Duplicate", true, true));
   assert(view.count == 3);
   assert(deck_ui_achievements_tab_count(&view, DECK_UI_ACHIEVEMENT_ALL) == 3);
   assert(deck_ui_achievements_tab_count(&view, DECK_UI_ACHIEVEMENT_UNLOCKED) == 2);
   assert(deck_ui_achievements_tab_count(&view, DECK_UI_ACHIEVEMENT_LOCKED) == 1);
   assert(deck_ui_achievements_scroll_offset(&view, 2) == 0);
   assert(deck_ui_achievements_visible_count(&view) == 3);
   deck_ui_achievements_set_filter(&view, DECK_UI_ACHIEVEMENT_LOCKED);
   assert(deck_ui_achievements_visible_count(&view) == 1);
   item = deck_ui_achievements_at(&view, 0);
   assert(item && item->id == 1);
   deck_ui_achievements_move(&view, 1);
   assert(view.selected == 0);
   deck_ui_achievements_set_filter(&view, DECK_UI_ACHIEVEMENT_UNLOCKED);
   assert(deck_ui_achievements_visible_count(&view) == 2);
   deck_ui_achievements_move(&view, 1);
   assert(view.selected == 1);
   assert(deck_ui_achievements_scroll_offset(&view, 1) == 1);
   item = deck_ui_achievements_at(&view, view.selected);
   assert(item && item->id == 3 && item->hardcore_unlocked);
   deck_ui_achievements_set_filter(&view, DECK_UI_ACHIEVEMENT_ALL);
   assert(view.selected == 0);
   deck_ui_achievements_switch_tab(&view, 1);
   assert(view.filter == DECK_UI_ACHIEVEMENT_UNLOCKED);
   assert(view.selected == 1); /* restored per-tab selection */
   deck_ui_achievements_switch_tab(&view, 1);
   assert(view.filter == DECK_UI_ACHIEVEMENT_LOCKED);
   deck_ui_achievements_switch_tab(&view, 1);
   assert(view.filter == DECK_UI_ACHIEVEMENT_ALL);
   deck_ui_achievements_switch_tab(&view, -1);
   assert(view.filter == DECK_UI_ACHIEVEMENT_LOCKED);
   assert(deck_ui_achievements_at(&view, 3) == NULL);
   return 0;
}
