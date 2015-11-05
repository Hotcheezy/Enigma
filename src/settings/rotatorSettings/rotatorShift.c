//=======================================================================================================
// Project: Enigma 1.0v
// Description: Enigma Machine on Pebble Watch
// File: The rotatorShift.c file
// Built using Pebble SDK 3.4v
// Date: October 25, 2015
//
// Programmer: Peter Leng, Kent Liu
// MIT Licence
// ======================================================================================================

// Libraries
#include "rotatorShift.h"

// -------------------------------------------------------------------------------------------------------
//                                      Declare Variables
// -------------------------------------------------------------------------------------------------------

// Windows and layer variables
static Window *rotator_window;

// The output test for the rotator 
static TextLayer *rotatorText1_layer;
static TextLayer *rotatorText2_layer;
static TextLayer *rotatorText3_layer;     

<<<<<<< HEAD
static TextLayer *label;  

// Gear animation
=======
//Gear animation
>>>>>>> b008f22a437228eb4b98757dcfbf4e2131e71a70
/*
static GBitmapSequence *gear_sequence;
static GBitmap *gear_bitmap;
*/
// -------------------------------------------------------------------------------------------------------
//                                      End: Declare Variables
// -------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------
//                                 The Main Screen: Set button map 
// -------------------------------------------------------------------------------------------------------

// When SELECT button is clicked
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
}

// When UP button is clicked
static void up_click_handler(ClickRecognizerRef recognizer, void *context) { 

}

// When DOWN button is clicked
static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  
}


// The button mapping for the main screen
static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}
// -------------------------------------------------------------------------------------------------------
//                                End: The Main Screen: set button map
// -------------------------------------------------------------------------------------------------------


// -------------------------------------------------------------------------------------------------------
//                                       The Main Screen
// -------------------------------------------------------------------------------------------------------
static void rotateLoad(Window *window) { 
  // The windows layer
  Layer *window_layer = window_get_root_layer(rotator_window);
  GRect bounds = layer_get_bounds(window_layer);
  //Set the font
  GFont textFont = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD); //Font for Text input
  GFont labelFont = fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD); //Font for Text input

  rotatorText1_layer = text_layer_create((GRect) { .origin = { 5, 70 }, .size = { 30, 30 } });
  rotatorText2_layer = text_layer_create((GRect) { .origin = { 45, 70 }, .size = { 30, 30 } });
  rotatorText3_layer = text_layer_create((GRect) { .origin = { 85, 70 }, .size = { 30, 30 } }); 

  label = text_layer_create((GRect) { .origin = { 0, 0 }, .size = { 100, 40 } }); 

  // Set Font
  text_layer_set_font(rotatorText1_layer, textFont);
  text_layer_set_font(rotatorText2_layer, textFont);
  text_layer_set_font(rotatorText3_layer, textFont);

  text_layer_set_font(label, labelFont);


  // Align them
  text_layer_set_text_alignment(rotatorText1_layer, GTextAlignmentCenter);
  text_layer_set_text_alignment(rotatorText2_layer, GTextAlignmentCenter);
  text_layer_set_text_alignment(rotatorText3_layer, GTextAlignmentCenter);
  text_layer_set_text_alignment(label, GTextAlignmentCenter);

  // Set them to an initial state of 'A'
  text_layer_set_text(rotatorText1_layer, "A");
  text_layer_set_text(rotatorText2_layer, "A");
  text_layer_set_text(rotatorText3_layer, "A");

  // Set the label text
  text_layer_set_text(label, "Shift Rotors");

  // add the rotors to the windows layer
  layer_add_child(window_layer, text_layer_get_layer(rotatorText1_layer));
  layer_add_child(window_layer, text_layer_get_layer(rotatorText2_layer));
  layer_add_child(window_layer, text_layer_get_layer(rotatorText3_layer));
  layer_add_child(window_layer, text_layer_get_layer(label));
}


// To clean up the main screen
static void rotateUnload(Window *window) {
  // Destroy
  window_destroy(rotator_window);
  text_layer_destroy(rotatorText1_layer);
  text_layer_destroy(rotatorText2_layer);
  text_layer_destroy(rotatorText3_layer);
  // Makes sure to make this NULL othewise you cannot return here
  rotator_window = NULL;
}

// -------------------------------------------------------------------------------------------------------
//                                        End: The Main Screen
// -------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------
//                                        Main Function
// -------------------------------------------------------------------------------------------------------

// public function 
void rotator_shift_push() {
  if (!rotator_window){
  	//Create window for main screen
  	rotator_window = window_create();
  	// Tell which buttons settings to use for main screen
  	window_set_click_config_provider(rotator_window, click_config_provider);

 	// The windows handlers for the main window
  	window_set_window_handlers(rotator_window, (WindowHandlers) {
    // These functions are to load and unload- Located above
    	.load = rotateLoad,
    	.unload = rotateUnload,
  	});

    window_stack_push(rotator_window, true);
  }
}

// -------------------------------------------------------------------------------------------------------
//                                        End: Main Function
// -------------------------------------------------------------------------------------------------------
