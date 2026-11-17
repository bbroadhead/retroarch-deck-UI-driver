/* RetroArch Deck UI: recent-content presentation model.
 * Stores only borrowed playlist entry IDs, never ROM data or save files.
 * GPL-3.0-or-later.
 */
#ifndef DECK_UI_RECENT_H
#define DECK_UI_RECENT_H
#include <stddef.h>
#include <string.h>
#define DECK_UI_RECENT_CAPACITY 12
#define DECK_UI_RECENT_ID_MAX 256

typedef struct deck_ui_recent
{
   char ids[DECK_UI_RECENT_CAPACITY][DECK_UI_RECENT_ID_MAX];
   size_t count;
} deck_ui_recent_t;

static inline void deck_ui_recent_init(deck_ui_recent_t *recent)
{
   if (recent)
      memset(recent, 0, sizeof(*recent));
}

/* Place a content identifier at the front, removing duplicates.
 * Callers supply a stable playlist/content identifier, not a title.
 */
static inline void deck_ui_recent_touch(deck_ui_recent_t *recent, const char *id)
{
   size_t i, old_index;
   if (!recent || !id || !*id || strlen(id) >= DECK_UI_RECENT_ID_MAX)
      return;
   old_index = recent->count;
   for (i = 0; i < recent->count; ++i)
      if (strcmp(recent->ids[i], id) == 0)
      {
         old_index = i;
         break;
      }
   if (old_index == recent->count && recent->count < DECK_UI_RECENT_CAPACITY)
      recent->count++;
   if (old_index >= recent->count)
      old_index = recent->count - 1;
   for (i = old_index; i > 0; --i)
      memcpy(recent->ids[i], recent->ids[i - 1], DECK_UI_RECENT_ID_MAX);
   strcpy(recent->ids[0], id);
}
#endif
