//=======================================================================================================
// Project: Enigma 1.0v
// Description: Enigma Machine on Pebble Watch
// File: The plugboard.c file
// Built using Pebble SDK 3.4v
// Date: October 25, 2015
//
// Programmer: Peter Leng, Kent Liu
// MIT Licence
// ======================================================================================================



// Libraries
#include "plugboard.h"

// -------------------------------------------------------------------------------------------------------
//                                      Declare Variables
// -------------------------------------------------------------------------------------------------------
static Window *plug_window;
static MenuLayer *plug_layer;

char letters[26] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};    
char textHolder[2] = " ";

// -------------------------------------------------------------------------------------------------------
//                                      End: Declare Variables
// -------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------
//                                      Declare functions
// -------------------------------------------------------------------------------------------------------

static uint16_t get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *context) {
  return NUM_WINDOWS_PLUG;
}

static void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *context) {
  textHolder[0] = letters[(int)cell_index->row];
  menu_cell_basic_draw(ctx, cell_layer, textHolder, NULL, NULL);
}

static int16_t get_cell_height_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context) {
  return CHECKBOX_WINDOW_CELL_HEIGHT;
}

static void draw_header_callback(GContext *ctx, const Layer *cell_layer, uint16_t section_index, void *context) {
  menu_cell_basic_header_draw(ctx, cell_layer, "Choose a letter");
}

static int16_t get_header_height_callback(struct MenuLayer *menu_layer, uint16_t section_index, void *context) {
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static uint16_t get_num_sections_callback(struct MenuLayer *menu_layer, void *context) {
  return 1;
}


// -------------------------------------------------------------------------------------------------------
//                                      Windows Load and Unload
// -------------------------------------------------------------------------------------------------------
static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  plug_layer = menu_layer_create(bounds);
  menu_layer_set_click_config_onto_window(plug_layer, window);
  menu_layer_set_callbacks(plug_layer, NULL, (MenuLayerCallbacks) {
      .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback)get_num_rows_callback,
      .draw_row = (MenuLayerDrawRowCallback)draw_row_callback,
      .get_cell_height = (MenuLayerGetCellHeightCallback)get_cell_height_callback,
      .draw_header = (MenuLayerDrawHeaderCallback)draw_header_callback,
      .get_header_height = (MenuLayerGetHeaderHeightCallback)get_header_height_callback,
      .get_num_sections = (MenuLayerGetNumberOfSectionsCallback)get_num_sections_callback,
  });
  layer_add_child(window_layer, menu_layer_get_layer(plug_layer));
}

static void window_unload(Window *window) {
  menu_layer_destroy(plug_layer);
  plug_window = NULL;
}

// -------------------------------------------------------------------------------------------------------
//                                     End:  Windows Load and Unload
// -------------------------------------------------------------------------------------------------------

// The public function
void plugboard_window_push(){
  if (!plug_window){
    plug_window = window_create();
    window_set_window_handlers(plug_window, (WindowHandlers) {
      .load = window_load,
      .unload = window_unload,
    });
    window_stack_push(plug_window, true);
  }
  
}

// -------------------------------------------------------------------------------------------------------
//                                      End: Functions
// -------------------------------------------------------------------------------------------------------
