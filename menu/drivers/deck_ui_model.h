/* RetroArch Deck UI: controller-first navigation model.
 * GPL-3.0-or-later, consistent with RetroArch.
 * Independent of rendering and the menu driver lifecycle.
 */
#ifndef DECK_UI_MODEL_H
#define DECK_UI_MODEL_H
#include <stddef.h>

typedef enum deck_ui_screen
{
   DECK_UI_HOME = 0,
   DECK_UI_LIBRARY,
   DECK_UI_COLLECTIONS,
   DECK_UI_GAME_DETAILS,
   DECK_UI_ACHIEVEMENTS,
   DECK_UI_SETTINGS
} deck_ui_screen_t;

typedef struct deck_ui_model
{
   deck_ui_screen_t screen;
   deck_ui_screen_t previous_screen;
   size_t selected_item;
   size_t item_count;
} deck_ui_model_t;

static inline void deck_ui_model_init(deck_ui_model_t *model)
{
   if (!model)
      return;
   model->screen          = DECK_UI_HOME;
   model->previous_screen = DECK_UI_HOME;
   model->selected_item   = 0;
   model->item_count      = 0;
}

static inline void deck_ui_model_set_count(deck_ui_model_t *model, size_t count)
{
   if (!model)
      return;
   model->item_count = count;
   if (!count)
      model->selected_item = 0;
   else if (model->selected_item >= count)
      model->selected_item = count - 1;
}

static inline void deck_ui_model_move(deck_ui_model_t *model, int direction)
{
   if (!model || !model->item_count || !direction)
      return;
   if (direction > 0 && model->selected_item < model->item_count - 1)
      model->selected_item++;
   else if (direction < 0 && model->selected_item > 0)
      model->selected_item--;
}

static inline void deck_ui_model_open(deck_ui_model_t *model, deck_ui_screen_t screen)
{
   if (!model || screen < DECK_UI_HOME || screen > DECK_UI_SETTINGS)
      return;
   model->previous_screen = model->screen;
   model->screen          = screen;
   model->selected_item   = 0;
   model->item_count      = 0;
}

static inline void deck_ui_model_back(deck_ui_model_t *model)
{
   deck_ui_screen_t previous;
   if (!model || model->screen == DECK_UI_HOME)
      return;
   previous               = model->previous_screen;
   model->previous_screen = DECK_UI_HOME;
   model->screen          = previous;
   model->selected_item   = 0;
   model->item_count      = 0;
}
#endif
