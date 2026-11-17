/* Deck UI achievement view model. Data is provided by RetroArch cheevos.
 * This module never contacts RetroAchievements servers.
 */
#ifndef DECK_UI_ACHIEVEMENTS_H
#define DECK_UI_ACHIEVEMENTS_H
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#define DECK_UI_ACHIEVEMENT_CAPACITY 512
#define DECK_UI_ACHIEVEMENT_TITLE_MAX 128

typedef enum deck_ui_achievement_filter
{
   DECK_UI_ACHIEVEMENT_ALL = 0,
   DECK_UI_ACHIEVEMENT_LOCKED,
   DECK_UI_ACHIEVEMENT_UNLOCKED
} deck_ui_achievement_filter_t;

typedef struct deck_ui_achievement
{
   unsigned id;
   char title[DECK_UI_ACHIEVEMENT_TITLE_MAX];
   bool unlocked;
   bool hardcore_unlocked;
} deck_ui_achievement_t;

typedef struct deck_ui_achievements
{
   deck_ui_achievement_t items[DECK_UI_ACHIEVEMENT_CAPACITY];
   size_t count;
   size_t selected;
   deck_ui_achievement_filter_t filter;
} deck_ui_achievements_t;

static inline void deck_ui_achievements_init(deck_ui_achievements_t *view)
{
   if (view)
      memset(view, 0, sizeof(*view));
}

static inline bool deck_ui_achievements_add(
      deck_ui_achievements_t *view, unsigned id, const char *title,
      bool unlocked, bool hardcore_unlocked)
{
   deck_ui_achievement_t *item;
   size_t i;
   if (!view || !title || !*title ||
       strlen(title) >= DECK_UI_ACHIEVEMENT_TITLE_MAX)
      return false;
   for (i = 0; i < view->count; i++)
      if (view->items[i].id == id)
         return false;
   if (view->count == DECK_UI_ACHIEVEMENT_CAPACITY)
      return false;
   item = &view->items[view->count++];
   item->id = id;
   strcpy(item->title, title);
   item->unlocked = unlocked || hardcore_unlocked;
   item->hardcore_unlocked = hardcore_unlocked;
   return true;
}

static inline bool deck_ui_achievement_visible(
      const deck_ui_achievements_t *view, size_t index)
{
   if (!view || index >= view->count)
      return false;
   if (view->filter == DECK_UI_ACHIEVEMENT_UNLOCKED)
      return view->items[index].unlocked;
   if (view->filter == DECK_UI_ACHIEVEMENT_LOCKED)
      return !view->items[index].unlocked;
   return true;
}

static inline size_t deck_ui_achievements_visible_count(
      const deck_ui_achievements_t *view)
{
   size_t i, total = 0;
   if (!view)
      return 0;
   for (i = 0; i < view->count; i++)
      if (deck_ui_achievement_visible(view, i))
         total++;
   return total;
}

/* Select by visible row rather than backing-array index. */
static inline const deck_ui_achievement_t *deck_ui_achievements_at(
      const deck_ui_achievements_t *view, size_t row)
{
   size_t i;
   if (!view)
      return NULL;
   for (i = 0; i < view->count; i++)
      if (deck_ui_achievement_visible(view, i))
      {
         if (!row)
            return &view->items[i];
         row--;
      }
   return NULL;
}

static inline void deck_ui_achievements_set_filter(
      deck_ui_achievements_t *view, deck_ui_achievement_filter_t filter)
{
   if (!view || filter < DECK_UI_ACHIEVEMENT_ALL ||
       filter > DECK_UI_ACHIEVEMENT_UNLOCKED)
      return;
   view->filter = filter;
   view->selected = 0;
}

static inline void deck_ui_achievements_move(
      deck_ui_achievements_t *view, int direction)
{
   size_t count;
   if (!view || !direction)
      return;
   count = deck_ui_achievements_visible_count(view);
   if (!count)
   {
      view->selected = 0;
      return;
   }
   if (direction > 0 && view->selected < count - 1)
      view->selected++;
   else if (direction < 0 && view->selected > 0)
      view->selected--;
}
#endif
