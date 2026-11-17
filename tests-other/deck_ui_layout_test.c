#include <assert.h>
#include "../menu/drivers/deck_ui_layout.h"
int main(void)
{
   deck_ui_layout_t deck = deck_ui_layout_home(1280, 800);
   deck_ui_layout_t small = deck_ui_layout_home(640, 400);
   deck_ui_layout_t zero = deck_ui_layout_home(0, 0);
   deck_ui_rect_t tabs = deck_ui_layout_achievement_tabs(1280, 800);
   assert(deck.scale == 1.0f);
   assert(deck.recent_columns == 5);
   assert(deck.header.width > 0);
   assert(deck.recent.y > deck.header.y + deck.header.height);
   assert(deck.collections.y > deck.recent.y + deck.recent.height);
   assert(deck.footer.y + deck.footer.height <= 800);
   assert(small.scale == 0.5f);
   assert(small.recent.width < deck.recent.width);
   assert(zero.scale == 0);
   assert(tabs.y == deck.header.y + deck.header.height);
   {
      deck_ui_rect_t all = deck_ui_layout_achievement_tab(1280, 800, 0);
      deck_ui_rect_t unlocked = deck_ui_layout_achievement_tab(1280, 800, 1);
      deck_ui_rect_t locked = deck_ui_layout_achievement_tab(1280, 800, 2);
      deck_ui_rect_t invalid = deck_ui_layout_achievement_tab(1280, 800, 3);
      assert(all.x == tabs.x);
      assert(all.width > 0);
      assert(unlocked.x > all.x + all.width);
      assert(locked.x > unlocked.x + unlocked.width);
      assert(locked.x + locked.width <= tabs.x + tabs.width);
      assert(invalid.width == 0);
   }
   return 0;
}
