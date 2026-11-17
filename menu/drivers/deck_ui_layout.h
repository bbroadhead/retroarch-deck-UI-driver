/* Deck UI responsive geometry, independent of graphics backend. */
#ifndef DECK_UI_LAYOUT_H
#define DECK_UI_LAYOUT_H
#include <stddef.h>
typedef struct deck_ui_rect
{
   float x, y, width, height;
} deck_ui_rect_t;
typedef struct deck_ui_layout
{
   deck_ui_rect_t header;
   deck_ui_rect_t recent;
   deck_ui_rect_t collections;
   deck_ui_rect_t footer;
   float scale;
   unsigned recent_columns;
} deck_ui_layout_t;

/* Coordinates are logical pixels, scaled to the available viewport.
 * The 1280x800 Steam Deck screen is the design reference.
 */
static inline deck_ui_layout_t deck_ui_layout_home(
      unsigned width, unsigned height)
{
   deck_ui_layout_t out = {0};
   float w = (float)width, h = (float)height;
   float pad, gap, usable;
   if (!width || !height)
      return out;
   out.scale = w / 1280.0f;
   if (h / 800.0f < out.scale)
      out.scale = h / 800.0f;
   pad = 36.0f * out.scale;
   gap = 20.0f * out.scale;
   usable = w - 2.0f * pad;
   out.header = (deck_ui_rect_t){pad, 24.0f * out.scale,
      usable, 84.0f * out.scale};
   out.recent = (deck_ui_rect_t){pad, out.header.y + out.header.height + gap,
      usable, 300.0f * out.scale};
   out.collections = (deck_ui_rect_t){pad,
      out.recent.y + out.recent.height + gap,
      usable, 250.0f * out.scale};
   out.footer = (deck_ui_rect_t){pad, h - 56.0f * out.scale,
      usable, 36.0f * out.scale};
   out.recent_columns = usable >= 1000.0f * out.scale ? 5 : 3;
   return out;
}

static inline deck_ui_rect_t deck_ui_layout_achievement_tabs(
      unsigned width, unsigned height)
{
   deck_ui_layout_t base = deck_ui_layout_home(width, height);
   deck_ui_rect_t tabs = {base.header.x,
      base.header.y + base.header.height,
      base.header.width, 56.0f * base.scale};
   return tabs;
}

/* Geometry for one achievement tab; selected tab can be drawn with
 * a separate accent rectangle without changing focus state.
 */
static inline deck_ui_rect_t deck_ui_layout_achievement_tab(
      unsigned width, unsigned height, unsigned tab_index)
{
   deck_ui_rect_t bar = deck_ui_layout_achievement_tabs(width, height);
   float gap, tab_width;
   if (tab_index >= 3 || bar.width <= 0.0f)
      return (deck_ui_rect_t){0};
   gap = 8.0f * (bar.width / 1208.0f);
   tab_width = (bar.width - gap * 2.0f) / 3.0f;
   return (deck_ui_rect_t){
      bar.x + (float)tab_index * (tab_width + gap),
      bar.y, tab_width, bar.height
   };
}
#endif
