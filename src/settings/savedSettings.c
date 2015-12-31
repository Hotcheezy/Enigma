//=======================================================================================================
// Project: Enigma 1.0v
// Description: Enigma Machine on Pebble Watch
// File: The savedSettings.c file
// Built using Pebble SDK 3.4v
// Date: October 25, 2015
//
// Programmer: Peter Leng, Kent Liu
// MIT Licence
// ======================================================================================================


// Libraries
#include "savedSettings.h"

// -------------------------------------------------------------------------------------------------------
//                                      Declare Variables
// -------------------------------------------------------------------------------------------------------

typedef enum {
  loadSetting, deleteSetting
} Save;

typedef struct {
  Save type;
} Context;



static Window *save_window;
static MenuLayer *save_layer;

static Save SavedSettings;
static ActionMenu *s_action_menu;
static ActionMenuLevel *s_root_level, *s_custom_level;

static char string_text[32];
static bool isEmpty = true; // status for if the number of saves if zero
static int count = 0; // a counter for how many saves
static int saves[8];

// -------------------------------------------------------------------------------------------------------
//                                      End: Declare Variables
// -------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------
//                                      Declare functions
// -------------------------------------------------------------------------------------------------------

static uint16_t get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *context) {
  return NUM_SAVE_WINDOWS_PLUG;
}

static void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *context) {
  // only draw the row if there are save data
  if(!isEmpty){
    snprintf(string_text, sizeof(string_text), "Save %i",saves[(int)cell_index->row]);
    menu_cell_basic_draw(ctx, cell_layer, string_text, NULL, NULL);
  }
}

static int16_t get_cell_height_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context) {
  return CHECKBOX_SAVE_WINDOW_CELL_HEIGHT;
}

static void draw_header_callback(GContext *ctx, const Layer *cell_layer, uint16_t section_index, void *context) { 
    menu_cell_basic_header_draw(ctx, cell_layer, "Saved Settings");
}

static int16_t get_header_height_callback(struct MenuLayer *menu_layer, uint16_t section_index, void *context) {
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static uint16_t get_num_sections_callback(struct MenuLayer *menu_layer, void *context) {
  return 1;
}

static void load_settings(){
  // get current selected meno row

  // load in rotor type

  // load in rotor shift

  // load in plugboard settings 

  // load in input message

  // laod in output message

}

static void delete_settings(){

  // Get the current selected menu row

  // delete this row 

  // recreate the menu 

  // update the save array by removing that number

  // reload the menu
  menu_layer_reload_data(save_layer);
}

static void action_performed_callback(ActionMenu *action_menu, const ActionMenuItem *action, void *context) {
  // An action was selected, determine which on
  // Get the action
  SavedSettings = (Save)action_menu_item_get_action_data(action);
  switch(SavedSettings) {
    case loadSetting:  load_settings();  break;
    case deleteSetting:  delete_settings();  break;
    default:
      break;
  }
}

static void init_empty_action_menu(){
  // Create the root level
  s_root_level = action_menu_level_create(NUM_SAVE_ACTIONS);

  // Set up the actions for this level, using action context to pass types
  action_menu_level_add_action(s_root_level, "Load", action_performed_callback, 
                              (void *) loadSetting);
  action_menu_level_add_action(s_root_level, "Delete", action_performed_callback, 
                              (void *) deleteSetting);
}

static void init_normal_action_menu(){
  // Create the root level
  s_root_level = action_menu_level_create(NUM_SAVE_ACTIONS);

  // Set up the actions for this level, using action context to pass types
  action_menu_level_add_action(s_root_level, "Save", action_performed_callback, 
                              (void *) loadSetting);
  action_menu_level_add_action(s_root_level, "Delete", action_performed_callback, 
                              (void *) deleteSetting);

}
static void action_menu_config_init(){

   ActionMenuConfig config = (ActionMenuConfig) {
    .root_level = s_root_level,
    .colors = {
      .background = GColorWindsorTan,
      .foreground = GColorBlack,
    },
    .align = ActionMenuAlignCenter
  };

  // Show the ActionMenu
  s_action_menu = action_menu_open(&config);
}
static void select(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context){
  // make sure to show the action menu only if there are saved settings
  if(!isEmpty){
    init_empty_action_menu(); // init the menu for each letter
    action_menu_config_init(); // config colors and opens the menu
  }  
  else{

  }
}

// -------------------------------------------------------------------------------------------------------
//                                      Windows Load and Unload
// -------------------------------------------------------------------------------------------------------
static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Letter layers

  save_layer = menu_layer_create(bounds);
  menu_layer_set_click_config_onto_window(save_layer, save_window);
  menu_layer_set_callbacks(save_layer, NULL, (MenuLayerCallbacks) {
      .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback)get_num_rows_callback,
      .draw_row = (MenuLayerDrawRowCallback)draw_row_callback,
      .get_cell_height = (MenuLayerGetCellHeightCallback)get_cell_height_callback,
      .draw_header = (MenuLayerDrawHeaderCallback)draw_header_callback,
      .get_header_height = (MenuLayerGetHeaderHeightCallback)get_header_height_callback,
      .get_num_sections = (MenuLayerGetNumberOfSectionsCallback)get_num_sections_callback,
      .select_click = (MenuLayerSelectCallback)select,
  });
  layer_add_child(window_layer, menu_layer_get_layer(save_layer));

}

static void window_unload(Window *window) {
  menu_layer_destroy(save_layer);
  save_window = NULL;
}

// -------------------------------------------------------------------------------------------------------
//                                     End:  Windows Load and Unload
// -------------------------------------------------------------------------------------------------------

// The public function
void savedSettings_window_push(){
  if (!save_window){
    save_window = window_create();
    window_set_window_handlers(save_window, (WindowHandlers) {
      .load = window_load,
      .unload = window_unload,
    });
    window_stack_push(save_window, true);
  }
  
}

// -------------------------------------------------------------------------------------------------------
//                                      End: Functions
// -------------------------------------------------------------------------------------------------------
