/* Standalone model smoke test:
 * cc -std=c99 -Wall -Wextra -Werror -pedantic -o /tmp/deck_ui_model_test tests-other/deck_ui_model_test.c
 * /tmp/deck_ui_model_test
 */
#include <assert.h>
#include "../menu/drivers/deck_ui_model.h"

int main(void)
{
   deck_ui_model_t model;
   deck_ui_model_init(&model);
   assert(model.screen == DECK_UI_HOME);
   deck_ui_model_move(&model, 1);
   assert(model.selected_item == 0);
   deck_ui_model_set_count(&model, 3);
   deck_ui_model_move(&model, 1);
   deck_ui_model_move(&model, 1);
   deck_ui_model_move(&model, 1);
   assert(model.selected_item == 2);
   deck_ui_model_set_count(&model, 1);
   assert(model.selected_item == 0);
   deck_ui_model_open(&model, DECK_UI_GAME_DETAILS);
   assert(model.screen == DECK_UI_GAME_DETAILS);
   assert(model.item_count == 0);
   deck_ui_model_back(&model);
   assert(model.screen == DECK_UI_HOME);
   deck_ui_model_set_count(&model, 0);
   deck_ui_model_move(&model, -1);
   assert(model.selected_item == 0);
   return 0;
}
