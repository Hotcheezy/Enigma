//=======================================================================================================
// Project: Enigma 1.0v
// Description: Enigma Machine on Pebble Watch
// File: The rotatorSettings.c file
// Built using Pebble SDK 3.4v
// Date: October 25, 2015
//
// Programmer: Peter Leng, Kent Liu
// MIT Licence
// ======================================================================================================

// Libraries
#include "rotatorSettings.h"

// -------------------------------------------------------------------------------------------------------
//                                      Declare Variables
// -------------------------------------------------------------------------------------------------------

// Number of things to select in the menu
#define NUM_WINDOWS 2

// Windows and layer variables
static Window *menu_window;
static MenuLayer *menu_layer;


// -------------------------------------------------------------------------------------------------------
//                                      End: Declare Variables
// -------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------
//                                      Declare functions
// -------------------------------------------------------------------------------------------------------

// Returns the number of rows
static uint16_t get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *context) {
  return NUM_WINDOWS;
}

// The row names
static void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *context) {
  switch(cell_index->row) {
    case 0:
      menu_cell_basic_draw(ctx, cell_layer, "Change Settings", NULL, NULL);
      break;
    case 1:
      menu_cell_basic_draw(ctx, cell_layer, "Select Types", NULL, NULL);
      break;
    default:
      break;
  }
}

// returns the height of the cell
static int16_t get_cell_height_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context) {
  return 30;
}

// The row selector. It pushes to whichever window 
static void select_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context) {
  switch(cell_index->row) {
    case 0: 
      //rotator_settings_push();
      break;
    case 1:
      //plugboard_window_push();
      break;
    default:
      break;
  }
}

// Header
static void draw_header_callback(GContext *ctx, const Layer *cell_layer, uint16_t section_index, void *context) {
  menu_cell_basic_header_draw(ctx, cell_layer, "Rotator Settings");
}
// Returns the height of header
static int16_t get_header_height_callback(struct MenuLayer *menu_layer, uint16_t section_index, void *context) {
  return 20;
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

  menu_layer = menu_layer_create(bounds);
  menu_layer_set_click_config_onto_window(menu_layer, window);
  menu_layer_set_callbacks(menu_layer, NULL, (MenuLayerCallbacks) {
      .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback)get_num_rows_callback,
      .draw_row = (MenuLayerDrawRowCallback)draw_row_callback,
      .get_cell_height = (MenuLayerGetCellHeightCallback)get_cell_height_callback,
      .select_click = (MenuLayerSelectCallback)select_callback,
      .draw_header = (MenuLayerDrawHeaderCallback)draw_header_callback,
      .get_header_height = (MenuLayerGetHeaderHeightCallback)get_header_height_callback,
      .get_num_sections = (MenuLayerGetNumberOfSectionsCallback)get_num_sections_callback,
  });
  // Add menu to the windows layer
  layer_add_child(window_layer, menu_layer_get_layer(menu_layer));
}

static void window_unload(Window *window) {
  menu_layer_destroy(menu_layer);
  window_destroy(menu_window);
  // Makes sure to make this NULL othewise you cannot return here
  menu_window = NULL;
}

// -------------------------------------------------------------------------------------------------------
//                                     End:  Windows Load and Unload
// -------------------------------------------------------------------------------------------------------

// The public function
void rotator_settings_push() {
  if (!menu_window){
    menu_window = window_create();
    window_set_window_handlers(menu_window, (WindowHandlers) {
      .load = window_load,
      .unload = window_unload,
    });
    window_stack_push(menu_window, true);
  }
  
}


// -------------------------------------------------------------------------------------------------------
//                                      End: Functions
// -------------------------------------------------------------------------------------------------------

