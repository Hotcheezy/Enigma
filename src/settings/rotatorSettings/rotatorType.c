//=======================================================================================================
// Project: Enigma 1.0v
// Description: Enigma Machine on Pebble Watch
// File: The rotatorType.c file
// Built using Pebble SDK 3.4v
// Date: October 25, 2015
//
// Programmer: Peter Leng, Kent Liu
// MIT Licence
// ======================================================================================================

// Libraries
#include "rotatorType.h"
#include "../../layers/selection_layer.h"
#include "../../Enigma.h"
// -------------------------------------------------------------------------------------------------------
//                                      Declare Variables
// -------------------------------------------------------------------------------------------------------

// Windows and layer variables
static Window *type_window;

// The output test for the rotator 
static TextLayer *rotatorType_layer[3];   
// The label layer
static TextLayer *label;  

// create a selection object 
static Layer *selection;

// Alphabet that the rotor cycles through
char rotorTypeLetter[8][2] = {"1","2","3","4","5","6","7","8"};    
// Counter for each rotor for cycling the alphabet so we know where it's at 
// There will always be 3 rotors in use so we set the unused to 5
char unusedNumbers[5][2];
int rotorTypePostition[3] = {0,1,2};
// A temp holder for each of the rotor postitions
char typePositionHolder[3][2] = {" "," "," "};
char rotorType[3][2] = {"1","2","3"};




// -------------------------------------------------------------------------------------------------------
//                                      End: Declare Variables
// -------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------
//                                 The Main Screen: Set button map 
// -------------------------------------------------------------------------------------------------------

static void selection_handle_complete(void *context) {
}
static void selection_handle_inc(int index, uint8_t clicks, void *context) {
  // The rotor position letter increments with each up clicks 
  // The selectType variable is changed in the SelectionLayer file. Each time I
  // Press the select or back button the select rotor will increment or decrement, respecitively
  rotorTypePostition[selectType]++;
  // If the counter has reached the end 
  if(rotorTypePostition[selectType] >= 8){
    // Set the counter to A
    rotorTypePostition[selectType] = 0;
  }
  // A temp holder for the input text
  typePositionHolder[selectType][0] = rotorTypeLetter[rotorTypePostition[selectType]][0];
  rotorType[selectType][0] = typePositionHolder[selectType][0]; //Update the rotorType global variable
  // Update the input text layer with the holder
  text_layer_set_text(rotatorType_layer[selectType], typePositionHolder[selectType]);
}

static void selection_handle_dec(int index, uint8_t clicks, void *context) {
  // The rotor position letter decrements with each up clicks 
  // The selectType variable is changed in the SelectionLayer file. Each time I
  // Press the select or back button the select rotor will increment or decrement, respecitively
  rotorTypePostition[selectType]--;
  // If the counter has reached the below zero
  if(rotorTypePostition[selectType] < 0){
    // Set the counter to Z
    rotorTypePostition[selectType] = 7;
  }
  // A temp holder for the input text
  typePositionHolder[selectType][0] = rotorTypeLetter[rotorTypePostition[selectType]][0];
  rotorType[selectType][0] = typePositionHolder[selectType][0]; //Update the rotorType global variable
  // Update the input text layer with the holder
  text_layer_set_text(rotatorType_layer[selectType], typePositionHolder[selectType]);
}

// -------------------------------------------------------------------------------------------------------
//                                End: The Main Screen: set button map
// -------------------------------------------------------------------------------------------------------


// -------------------------------------------------------------------------------------------------------
//                                       The Main Screen
// -------------------------------------------------------------------------------------------------------
static void rotateLoad(Window *window) { 

  // This variable will be initialized to 0 everythime the window loads;
  // If you do not do this the selectType variable will increment or decrement everytme selectionLayer file gets used
  int selectType = 0;
  // The windows layer
  Layer *window_layer = window_get_root_layer(type_window);
  GRect bounds = layer_get_bounds(window_layer);
  //Set the font
  GFont textFont = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD); //Font for Text input
  GFont labelFont = fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD); //Font for Text input

  // Set the position and the size of the layers
  rotatorType_layer[0] = text_layer_create((GRect) { .origin = { 13, 75 }, .size = { 30, 30 } });
  rotatorType_layer[1] = text_layer_create((GRect) { .origin = { 57, 75 }, .size = { 30, 30 } });
  rotatorType_layer[2] = text_layer_create((GRect) { .origin = { 100, 75 }, .size = { 30, 30 } }); 
  label = text_layer_create((GRect) { .origin = { 3, 0 }, .size = { 100, 40 } }); 

  // selection config
  // Create selection layer
  #ifdef PBL_SDK_3 // if it's the third version
    selection = selection_layer_create(GRect(8, 75, 128, 34), NUM_CELLS);
  #else
    selection = selection_layer_create(GRect(8, 60, 128, 34), NUM_CELLS);
  #endif

  for (int i = 0; i < NUM_CELLS; i++) {
    selection_layer_set_cell_width(selection, i, 40);
  }
    selection_layer_set_cell_padding(selection, 4);

  #ifdef PBL_COLOR
    selection_layer_set_active_bg_color(selection, GColorRed);
    selection_layer_set_inactive_bg_color(selection, GColorDarkGray);
  #endif
    selection_layer_set_click_config_onto_window(selection, type_window);
    selection_layer_set_callbacks(selection, type_window, (SelectionLayerCallbacks) {
      .complete = selection_handle_complete,
      .increment = selection_handle_inc,
      .decrement = selection_handle_dec,
    });
    
  // Set Font
  text_layer_set_font(rotatorType_layer[0], textFont);
  text_layer_set_font(rotatorType_layer[1], textFont);
  text_layer_set_font(rotatorType_layer[2], textFont);
  text_layer_set_font(label, labelFont);


  // Align them
  text_layer_set_text_alignment(rotatorType_layer[0], GTextAlignmentCenter);
  text_layer_set_text_alignment(rotatorType_layer[1], GTextAlignmentCenter);
  text_layer_set_text_alignment(rotatorType_layer[2], GTextAlignmentCenter);

  // Set them to an initial state of '1'
  text_layer_set_text(rotatorType_layer[0], rotorType[0]);
  text_layer_set_text(rotatorType_layer[1], rotorType[1]);
  text_layer_set_text(rotatorType_layer[2], rotorType[2]);

  // Set background color to transparent 
  text_layer_set_background_color(rotatorType_layer[0], GColorClear);
  text_layer_set_background_color(rotatorType_layer[1], GColorClear);
  text_layer_set_background_color(rotatorType_layer[2], GColorClear);
  // Set the label text
  text_layer_set_text(label, "Rotor Type Selection");

  // add the rotors to the windows layer
  layer_add_child(window_layer, selection);
  layer_add_child(window_layer, text_layer_get_layer(rotatorType_layer[0]));
  layer_add_child(window_layer, text_layer_get_layer(rotatorType_layer[1]));
  layer_add_child(window_layer, text_layer_get_layer(rotatorType_layer[2]));
  layer_add_child(window_layer, text_layer_get_layer(label));
  
}


// To clean up the main screen
static void rotateUnload(Window *window) {
  // Destroy
  window_destroy(type_window);
  text_layer_destroy(rotatorType_layer[0]);
  text_layer_destroy(rotatorType_layer[1]);
  text_layer_destroy(rotatorType_layer[2]);
  // Makes sure to make this NULL othewise you cannot return here
 type_window = NULL;
}

// -------------------------------------------------------------------------------------------------------
//                                        End: The Main Screen
// -------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------
//                                        Main Function
// -------------------------------------------------------------------------------------------------------

// public function 
void rotator_type_push() {
  if (!type_window){
  	//Create window for main screen
  	type_window = window_create();
  	// Tell which buttons settings to use for main screen
  	//window_set_click_config_provider(type_window, click_config_provider);

 	// The windows handlers for the main window
  	window_set_window_handlers(type_window, (WindowHandlers) {
    // These functions are to load and unload- Located above
    	.load = rotateLoad,
    	.unload = rotateUnload,
  	});

    window_stack_push(type_window, true);
  }
}

// -------------------------------------------------------------------------------------------------------
//                                        End: Main Function
// -------------------------------------------------------------------------------------------------------
