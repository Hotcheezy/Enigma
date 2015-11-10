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

typedef enum {
  A, B, C, D, E, F, G, H, I, J, K, L, M,
  N, O, P, Q, R, S, T, U, V, W, X, Y, Z, clear
} Alphabet;

typedef struct {
  Alphabet type;
} Context;



static Window *plug_window;
static MenuLayer *plug_layer;

static Alphabet current_letter;
static ActionMenu *s_action_menu;
static ActionMenuLevel *s_root_level, *s_custom_level;
static char string_text[32];
static char label[32];
static char max[4] = "Max";

// The letter connections on the right - by default it's left empty
char plugConnectLetters[26][2] = {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
                                  " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "};
 
// these letters display on the left
static char letters[26][2] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
                              "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

static int plugUsed = 0;

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
  // add the 
  snprintf(string_text, sizeof(string_text), "%*s%s", DISTANCE_BETWEEN_LETTER, "", plugConnectLetters[(int)cell_index->row]);
  menu_cell_basic_draw(ctx, cell_layer,  letters[(int)cell_index->row], NULL, NULL);
  menu_cell_basic_draw(ctx, cell_layer, string_text, NULL, NULL);
}

static int16_t get_cell_height_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context) {
  return CHECKBOX_WINDOW_CELL_HEIGHT;
}

static void draw_header_callback(GContext *ctx, const Layer *cell_layer, uint16_t section_index, void *context) {
  if (plugUsed +1 > 10){
    snprintf(label, sizeof(label), "Choose a letter%*sMax!", DISTANCE_BETWEEN_LABEL, "");
    menu_cell_basic_header_draw(ctx, cell_layer, label);
  }
  else{
    menu_cell_basic_header_draw(ctx, cell_layer, "Choose a letter");
  }
  
}

static int16_t get_header_height_callback(struct MenuLayer *menu_layer, uint16_t section_index, void *context) {
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static uint16_t get_num_sections_callback(struct MenuLayer *menu_layer, void *context) {
  return 1;
}

static void connect_letter(char selectLetter){
  // If we see that space sign it means we clear that letter 
  // Get the current index

  if(selectLetter == ' ' ){
    // If plugused is 0 or less then set it to 0 so we don't go over the bound

    if(plugUsed <= 0){
      plugUsed = 0;
    }
    // decrement
    else{
      plugUsed--;
    }

  }
  else{
    // If the plug used is over ten then tell the user that 10 is the limit
    if(plugUsed +1> 10){
        // -----   Show message -------
      selectLetter = ' ';
    } 
    // If if the plug used is not ten then keep incrementing
    else{
      plugUsed++;

    }
  }
  int index = menu_layer_get_selected_index(plug_layer).row;
  plugConnectLetters[index][0] = selectLetter;
  menu_layer_reload_data(plug_layer);


}

static void action_performed_callback(ActionMenu *action_menu, const ActionMenuItem *action, void *context) {
  // An action was selected, determine which on
  // Get the action
  current_letter = (Alphabet)action_menu_item_get_action_data(action);
  switch(current_letter) {
    case A:  connect_letter('A');  break;
    case B:  connect_letter('B');  break;
    case C:  connect_letter('C');  break;
    case D:  connect_letter('D');  break;
    case E:  connect_letter('E');  break;
    case F:  connect_letter('F');  break;
    case G:  connect_letter('G');  break;
    case H:  connect_letter('H');  break;
    case I:  connect_letter('I');  break;
    case J:  connect_letter('J');  break;
    case K:  connect_letter('K');  break;
    case L:  connect_letter('L');  break;
    case M:  connect_letter('M');  break;
    case N:  connect_letter('N');  break;
    case O:  connect_letter('O');  break;
    case P:  connect_letter('P');  break;
    case Q:  connect_letter('Q');  break;
    case R:  connect_letter('R');  break;
    case S:  connect_letter('S');  break;
    case T:  connect_letter('T');  break;
    case U:  connect_letter('U');  break;
    case V:  connect_letter('V');  break;
    case W:  connect_letter('W');  break;
    case X:  connect_letter('X');  break;
    case Y:  connect_letter('Y');  break;
    case Z:  connect_letter('Z');  break;
    case clear:  connect_letter(' ');  break; // This setting is for erasing the letter
    default:
      break;
  }
}

static void init_action_menu() {
  // Create the root level
  s_root_level = action_menu_level_create(27);

  // Set up the actions for this level, using action context to pass types
  action_menu_level_add_action(s_root_level, "Clear", action_performed_callback, 
                              (void *) clear);
  action_menu_level_add_action(s_root_level, "A", action_performed_callback, 
                              (void *) A);
  action_menu_level_add_action(s_root_level, "B", action_performed_callback, 
                              (void *) B);
  action_menu_level_add_action(s_root_level, "C", action_performed_callback, 
                              (void *) C);
  action_menu_level_add_action(s_root_level, "D", action_performed_callback, 
                              (void *) D);
  action_menu_level_add_action(s_root_level, "E", action_performed_callback, 
                              (void *) E);
  action_menu_level_add_action(s_root_level, "F", action_performed_callback, 
                              (void *) F);
  action_menu_level_add_action(s_root_level, "G", action_performed_callback, 
                              (void *) G);
  action_menu_level_add_action(s_root_level, "H", action_performed_callback, 
                              (void *) H);
  action_menu_level_add_action(s_root_level, "I", action_performed_callback, 
                              (void *) I);
  action_menu_level_add_action(s_root_level, "J", action_performed_callback, 
                              (void *) J);
  action_menu_level_add_action(s_root_level, "K", action_performed_callback, 
                              (void *) K);
  action_menu_level_add_action(s_root_level, "L", action_performed_callback, 
                              (void *) L);
  action_menu_level_add_action(s_root_level, "M", action_performed_callback, 
                              (void *) M);
  action_menu_level_add_action(s_root_level, "N", action_performed_callback, 
                              (void *) N);
  action_menu_level_add_action(s_root_level, "O", action_performed_callback, 
                              (void *) O);
  action_menu_level_add_action(s_root_level, "P", action_performed_callback, 
                              (void *) P);
  action_menu_level_add_action(s_root_level, "Q", action_performed_callback, 
                              (void *) Q);
  action_menu_level_add_action(s_root_level, "R", action_performed_callback, 
                              (void *) R);
  action_menu_level_add_action(s_root_level, "S", action_performed_callback, 
                              (void *) S);
  action_menu_level_add_action(s_root_level, "T", action_performed_callback, 
                              (void *) T);
  action_menu_level_add_action(s_root_level, "U", action_performed_callback, 
                              (void *) U);
  action_menu_level_add_action(s_root_level, "V", action_performed_callback, 
                              (void *) V);
  action_menu_level_add_action(s_root_level, "W", action_performed_callback, 
                              (void *) W);
  action_menu_level_add_action(s_root_level, "X", action_performed_callback, 
                              (void *) X);
  action_menu_level_add_action(s_root_level, "Y", action_performed_callback, 
                              (void *) Y);
  action_menu_level_add_action(s_root_level, "Z", action_performed_callback, 
                              (void *) Z);
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
    init_action_menu(); // init the menu for each letter
    action_menu_config_init(); // config colors and opens the menu
    
}

// -------------------------------------------------------------------------------------------------------
//                                      Windows Load and Unload
// -------------------------------------------------------------------------------------------------------
static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Letter layers

  plug_layer = menu_layer_create(bounds);
  menu_layer_set_click_config_onto_window(plug_layer, plug_window);
  menu_layer_set_callbacks(plug_layer, NULL, (MenuLayerCallbacks) {
      .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback)get_num_rows_callback,
      .draw_row = (MenuLayerDrawRowCallback)draw_row_callback,
      .get_cell_height = (MenuLayerGetCellHeightCallback)get_cell_height_callback,
      .draw_header = (MenuLayerDrawHeaderCallback)draw_header_callback,
      .get_header_height = (MenuLayerGetHeaderHeightCallback)get_header_height_callback,
      .get_num_sections = (MenuLayerGetNumberOfSectionsCallback)get_num_sections_callback,
      .select_click = (MenuLayerSelectCallback)select,
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
