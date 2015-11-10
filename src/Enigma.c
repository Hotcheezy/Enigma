//=======================================================================================================
// Project: Enigma 1.0v
// Description: Enigma Machine on Pebble Watch
//
// Built using Pebble SDK 3.4v
// Date: October 15, 2015
//
// Programmer: Peter Leng, Kent Liu
// MIT Licence
// ======================================================================================================

// Libraries
#include <pebble.h>
#include <string.h>
#include <time.h>
#include "Enigma.h"
#include "EnigmaAlgorithm.h"
#include "settings/Settings.h" // The settings file


//#include "EnigmaAlgorithm.h"

// -------------------------------------------------------------------------------------------------------
//                                      Declare Variables
// -------------------------------------------------------------------------------------------------------
//-----Config --------
#define DELAYTIME 2500 //time for logo splashscreen in milisecons

//-End-Config --------

// Windows 
static Window *window;
static Window *logoWindow;

// Textlayers 
static TextLayer *input_text_layer; 
static TextLayer *output_text_layer;   

static TextLayer *input_message_layer;
static TextLayer *output_message_layer;

// The output test for the rotator 
static TextLayer *rotatorText1_layer;
static TextLayer *rotatorText2_layer;
static TextLayer *rotatorText3_layer;                                                                                                             

// Image variables
static GBitmap *logo_bitmap; //GBitmap pointer
static BitmapLayer *logo_layer; //logo layer pointer

static GBitmap *frame_bitmap;
static BitmapLayer *frame_layer;



// List of the alphabet
char inputText[26] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};    
char outputText[26] = {"EKMFLGDQVZNTOWYHXUSPAIBRCJ"}; //Corresponding letter
// Temporary holders for the input and output
char inputHolder[2] = " ";
char outputHolder[2] = " ";

// Message holder for input and output    
char inputMessage[51] = "";
char outputMessage[51] = "";

// holder for the rotatorText
char rotatorText[3][2] = {"A","A","A"}; // the text that will be displayed on screen
char rotatorHolder[3][2] = {" "," "," "}; // A temp holder for transferring the rotator text

// Counter variable for cycling the alphabet
int textCounter = 0; 

// Global 
char *reflectors[] = {
    "EJMZALYXVBWFCRQUONTSPIKHGD",
    "YRUHQSLDPXNGOKMIEBFZCWVJAT",
    "FVPJIAOYEDRZXWGCTKUQSBNMHL"
};

struct Rotor {
    int             offset;
    int             turnnext;
    const char      *cipher;
    const char      *turnover;
    const char      *notch;
};

struct Enigma {
    int             numrotors;
    const char      *reflector;
    struct Rotor    rotors[8];
};




// -------------------------------------------------------------------------------------------------------
//                                      End: Declare Variables
// -------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------
//                                 The Main Screen: Set button map 
// -------------------------------------------------------------------------------------------------------

// When SELECT button is clicked
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
   // Change the text for each input and output
  // Add a char to input text
  unsigned int l = strlen(inputMessage);
  if(l<sizeof(inputMessage)-1) { // Check we have enough room left for an extra character
    inputMessage[l] = inputText[textCounter];
    inputMessage[l+1] = 0;
    text_layer_set_text(input_message_layer, inputMessage);
  }
  // Add a char to output text 
  unsigned int J = strlen(outputMessage); // Can remove if the the input and output buffer is the same length
  if(J<sizeof(outputMessage)-1) { // Check we have enough room left for an extra character
    outputMessage[J] = outputText[textCounter];
    outputMessage[J+1] = 0;
    text_layer_set_text(output_message_layer, outputMessage);
  }
  // A temp holder for the output text
  // using the calculate function in the Enigma Alg
  outputHolder[0] = calculate(inputText[textCounter]);
  // Update the output text layer with the output holder
  text_layer_set_text(output_text_layer, outputHolder);

}

// When UP button is clicked
static void up_click_handler(ClickRecognizerRef recognizer, void *context) { 
  // The input letter decrements with each up clicks therefore a counter
  textCounter--;
  // If the counter has reached the below zero
  if(textCounter < 0){
    // Set the counter to Z
    textCounter = 25;
  }
  // A temp holder for the input text
  inputHolder[0] = inputText[textCounter];
  // Update the input text layer with the holder
  text_layer_set_text(input_text_layer, inputHolder);
}

// When DOWN button is clicked
static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  // The input letter increments with each down clicks therefore a counter
  textCounter++;
  // If the counter has reached the end 
  if(textCounter >= 26){
    // Set the counter to A
    textCounter = 0;
  }
  // A temp holder for the input text
  inputHolder[0] = inputText[textCounter];
  // Update the input text layer with the holder
  text_layer_set_text(input_text_layer, inputHolder);
}
// When the back button is clicked remove the last character from input and output message
static void back_click_handler(ClickRecognizerRef recognizer, void *context) {
  // Get the current length
  unsigned int l = strlen(inputMessage);
  // Shorten the length by 1 and put the end string character 
  // If the length is not zero 
  if (l != 0){
    inputMessage[l-1] = '\0';
    outputMessage[l-1] = '\0';
  }
  // If the length is zero then just set that one to be end character
  else{
    inputMessage[l] = '\0';
    outputMessage[l] = '\0';
  }
  // Update the new text
  text_layer_set_text(input_message_layer, inputMessage);
  text_layer_set_text(output_message_layer, outputMessage);
}
// If the user long clicks or long clicks and release, go to the menu
static void select_long_click_handler(ClickRecognizerRef recognizer, void *context) {
  menu_push();
}
// This is the one for long click and release
static void select_long_click_release_handler(ClickRecognizerRef recognizer, void *context) {
  menu_push();
}

// The button mapping for the main screen
static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_single_click_subscribe(BUTTON_ID_BACK, back_click_handler);
  // If up, select, or down button is pressed go to long click handler
  window_long_click_subscribe(BUTTON_ID_UP, 700, select_long_click_handler, select_long_click_release_handler);
  window_long_click_subscribe(BUTTON_ID_SELECT, 700, select_long_click_handler, select_long_click_release_handler);
  window_long_click_subscribe(BUTTON_ID_DOWN, 700, select_long_click_handler, select_long_click_release_handler);

}
// -------------------------------------------------------------------------------------------------------
//                                End: The Main Screen: set button map
// -------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------
//                               The Main Screen: Windows Load and unload
// -------------------------------------------------------------------------------------------------------
static void window_load(Window *window) {
  // Create Enigma instance
  struct Enigma machine = {}; // initialized to defaults
  int i, index;

  // Configure an enigma machine
  machine.reflector = reflectors[1];
  machine.rotors[0] = new_rotor(&machine, rotorTypePostition[0], rotorPostition[0]);
  machine.rotors[1] = new_rotor(&machine, rotorTypePostition[1], rotorPostition[1]);
  machine.rotors[2] = new_rotor(&machine, rotorTypePostition[2], rotorPostition[2]);




  // Set layer 
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  // Load the fonts

  GFont textFont = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD); //Font for Text input
  GFont messageFont = fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD); // Font for message input

  // Create layers for each and define the positions and size
  input_text_layer = text_layer_create((GRect) { .origin = { 14.5, 109 }, .size = { 28, 28 } }); 
  input_message_layer = text_layer_create((GRect) { .origin = { 60, 90 }, .size = { 85, 80 } });
  output_text_layer = text_layer_create((GRect) { .origin = { 14.5, 14 }, .size = { 28, 28 } });
  output_message_layer = text_layer_create((GRect) { .origin = { 60, 0 }, .size = { 85, 80 } });

  rotatorText1_layer = text_layer_create((GRect) { .origin = { 6.5, 70 }, .size = { 15, 15 } });
  rotatorText2_layer = text_layer_create((GRect) { .origin = { 21.5, 70 }, .size = { 15, 15 } });
  rotatorText3_layer = text_layer_create((GRect) { .origin = { 36.5, 70 }, .size = { 15, 15 } }); 
  //Setting fonts
  text_layer_set_font(input_text_layer, textFont);
  text_layer_set_font(input_message_layer, messageFont);
  text_layer_set_font(output_text_layer, textFont);
  text_layer_set_font(output_message_layer, messageFont);

  text_layer_set_font(rotatorText1_layer, messageFont);
  text_layer_set_font(rotatorText2_layer, messageFont);
  text_layer_set_font(rotatorText3_layer, messageFont);


  // Center the input and output text field
  text_layer_set_text_alignment(input_text_layer, GTextAlignmentCenter);
  text_layer_set_text_alignment(output_text_layer, GTextAlignmentCenter);

  text_layer_set_text_alignment(rotatorText1_layer, GTextAlignmentCenter);
  text_layer_set_text_alignment(rotatorText2_layer, GTextAlignmentCenter);
  text_layer_set_text_alignment(rotatorText3_layer, GTextAlignmentCenter);
   
  /* For debugging
  // Set the color for each field. Default is white 
  // Used for repostioning the layers. Since black is easy to see
  text_layer_set_background_color(input_text_layer, GColorBlack);
  text_layer_set_background_color(input_message_layer, GColorBlack);
  text_layer_set_background_color(output_text_layer, GColorBlack);
  text_layer_set_background_color(output_message_layer, GColorBlack);
  // The rotators
  text_layer_set_background_color(rotatorText1_layer, GColorBlack);
  text_layer_set_background_color(rotatorText2_layer, GColorBlack);
  text_layer_set_background_color(rotatorText3_layer, GColorBlack);
  */


  // Set the background to be transparent
  text_layer_set_background_color(input_text_layer, GColorClear);
  text_layer_set_background_color(input_message_layer, GColorClear);
  text_layer_set_background_color(output_text_layer, GColorClear);
  text_layer_set_background_color(output_message_layer, GColorClear);

  // Set inital text for input field as "A"
  inputHolder[0] = inputText[0];
  text_layer_set_text(input_text_layer, inputHolder);
  text_layer_set_text(input_message_layer,inputMessage);
  text_layer_set_text(output_message_layer,outputMessage);

  // Put the text into the temp holder 
  rotatorHolder[0][0] = rotatorText[0][0];
  rotatorHolder[1][0] = rotatorText[1][0]; 
  rotatorHolder[2][0] = rotatorText[2][0]; 

  // Set rotators to an initial state of 'A'
  text_layer_set_text(rotatorText1_layer, rotatorText[0]);
  text_layer_set_text(rotatorText2_layer, rotatorText[1]);
  text_layer_set_text(rotatorText3_layer, rotatorText[2]);



  // Set the frame image
  frame_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FRAME);
  // Add the layer for which the bitmap will say on top of
  // Also set the frame coordinates
  frame_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  // Set the outside of the image to be transparent
  bitmap_layer_set_compositing_mode(frame_layer, GCompOpSet);
  // Put the bitmap into the layer
  bitmap_layer_set_bitmap(frame_layer, frame_bitmap);




  // Add each layer to the window object
  layer_add_child(window_layer, bitmap_layer_get_layer(frame_layer));
  layer_add_child(window_layer, text_layer_get_layer(input_text_layer));
  layer_add_child(window_layer, text_layer_get_layer(input_message_layer));
  layer_add_child(window_layer, text_layer_get_layer(output_text_layer));
  layer_add_child(window_layer, text_layer_get_layer(output_message_layer));

  layer_add_child(window_layer, text_layer_get_layer(rotatorText1_layer));
  layer_add_child(window_layer, text_layer_get_layer(rotatorText2_layer));;
  layer_add_child(window_layer, text_layer_get_layer(rotatorText3_layer));


}

static void window_unload(Window *window) {
  // Destroy the layers to clear memory
  text_layer_destroy(input_text_layer);
  text_layer_destroy(input_message_layer);
  text_layer_destroy(output_text_layer);
  text_layer_destroy(output_message_layer);
  text_layer_destroy(rotatorText1_layer);
  text_layer_destroy(rotatorText2_layer);
  text_layer_destroy(rotatorText3_layer);
}
// -------------------------------------------------------------------------------------------------------
//                           End: The Main Screen: Windows Load and Unload
// -------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------
//                                       The Logo Screen
// -------------------------------------------------------------------------------------------------------

// This is the timer
/**
* This is the function the timer call after the time is up. It will
* pop the window it is currently on. This is used for the splash screen.
* @param data
*/
static void timer_callback(void *data) {
  window_stack_pop(true);
}

// Load the logo window
static void logoWindow_load(Window *logoWindow) {

  // Set a 3000 millisecond to load the splash screen
  app_timer_register(DELAYTIME, (AppTimerCallback) timer_callback, NULL);
  // creat the layer
  Layer *window_layer = window_get_root_layer(logoWindow);
  // Match the bitmap with the image file
  logo_bitmap = gbitmap_create_with_resource(RESOURCE_ID_LOGO);
  // Add the layer for which the bitmap will say on top of
  // Also set the frame coordinates
  logo_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  // Set the outside of the image to be transparent
  bitmap_layer_set_compositing_mode(logo_layer, GCompOpSet);
  // Put the bitmap into the layer
  bitmap_layer_set_bitmap(logo_layer, logo_bitmap);



  // Add child
  layer_add_child(window_layer, bitmap_layer_get_layer(logo_layer));

}
// Unload the logo window
static void logoWindow_unload(Window *logoWindow) {
  // Destry them when exit logo windows
  gbitmap_destroy(logo_bitmap);
  bitmap_layer_destroy(logo_layer);
}

// -------------------------------------------------------------------------------------------------------
//                                       End: The Logo Screen
// -------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------
//                                       The Main Screen
// -------------------------------------------------------------------------------------------------------
static void mainInit(void) {
  //Create window for main screen
  window = window_create();
    // Create a window for logo screen
  logoWindow = window_create();
  // Tell which buttons settings to use for main screen
  window_set_click_config_provider(window, click_config_provider);

  // The windows handlers for the main window
  window_set_window_handlers(window, (WindowHandlers) {
    // These functions are to load and unload- Located above
    .load = window_load,
    .unload = window_unload,
  });

  // The window handlers for the logo windows
  window_set_window_handlers(logoWindow, (WindowHandlers) {
    // The two functions above
    .load = logoWindow_load,
    .unload = logoWindow_unload,
  });


  const bool animated = true;
  // Push the windows to the top
  window_stack_push(window, animated);
  // Push the logo Window to the top
  window_stack_push(logoWindow, true);
}


// To clean up the main screen
static void deinitMain(void) {
  // Destroy
  window_destroy(window);
}

// -------------------------------------------------------------------------------------------------------
//                                        End: The Main Screen
// -------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------
//                                        Main Function
// -------------------------------------------------------------------------------------------------------

// Main function 
int main(void) {
  // Do set up here
  // Go to the main screen 
  mainInit();
  // For debuggin
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);
  // Enter the main event loop. This will block until the app is ready to exit.
  app_event_loop();
  // Do clean up main screen
  deinitMain();
}

// -------------------------------------------------------------------------------------------------------
//                                        End: Main Function
// -------------------------------------------------------------------------------------------------------
