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
   return 0;
}
