/* cc -std=c99 -Wall -Wextra -Werror -pedantic -o /tmp/deck_ui_recent_test tests-other/deck_ui_recent_test.c */
#include <assert.h>
#include <string.h>
#include "../menu/drivers/deck_ui_recent.h"
int main(void)
{
   deck_ui_recent_t r;
   size_t i;
   char id[32];
   deck_ui_recent_init(&r);
   deck_ui_recent_touch(&r, "");
   assert(r.count == 0);
   for (i = 0; i < 14; i++)
   {
      /* Avoid stdio dependencies in the production model. */
      id[0] = 'g';
      id[1] = (char)('A' + i);
      id[2] = '\0';
      deck_ui_recent_touch(&r, id);
   }
   assert(r.count == DECK_UI_RECENT_CAPACITY);
   assert(strcmp(r.ids[0], "gN") == 0);
   deck_ui_recent_touch(&r, "gE");
   assert(strcmp(r.ids[0], "gE") == 0);
   assert(r.count == DECK_UI_RECENT_CAPACITY);
   deck_ui_recent_touch(&r, "gE");
   assert(strcmp(r.ids[0], "gE") == 0);
   return 0;
}
