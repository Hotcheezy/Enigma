//=======================================================================================================
// Project: Enigma 1.0v
// Description: Enigma Machine on Pebble Watch
//
// Built using Pebble SDK 3.4v
// Date: October 14, 2015
//
// Programmer: Peter Leng, Kent Liu
// MIT Licence
// ======================================================================================================

// Libraries
#include <pebble.h>
#include <string.h>
#include <time.h>


// -------------------------------------------------------------------------------------------------------
//                                      Declare Variables
// -------------------------------------------------------------------------------------------------------
//-----Config --------
#define DELAYTIME 3000

//-End-Config --------

// Windows 
static Window *window;
static Window *logoWindow;

// Textlayers 
static TextLayer *input_text_layer; 
static TextLayer *output_text_layer;   
static TextLayer *input_message_layer;
static TextLayer *output_message_layer;

// Logo variables
static GBitmap *logo_bitmap; //GBitmap pointer
static BitmapLayer *logo_layer; //logo layer pointer
// List of the alphabet
char inputText[26] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};    
char outputText[26] = {"EKMFLGDQVZNTOWYHXUSPAIBRCJ"}; //Corresponding letter
// Temporary holders for the input and output
char inputHolder[2] = " ";
char outputHolder[2] = " ";

// Message holder for input and output    
char inputMessage[51] = "";
char outputMessage[51] = "";

// Counter variable for cycling the alphabet
int textCounter = 0; 


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
  outputHolder[0] = outputText[textCounter];
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
  inputMessage[l-1] = '\0';
  outputMessage[l-1] = '\0';
  // Update the new text
  text_layer_set_text(input_message_layer, inputMessage);
  text_layer_set_text(output_message_layer, outputMessage);
}

// The button mapping for the main screen
static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_single_click_subscribe(BUTTON_ID_BACK, back_click_handler);
}
// -------------------------------------------------------------------------------------------------------
//                                End: The Main Screen: set button map
// -------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------
//                               The Main Screen: Windows Load and unload
// -------------------------------------------------------------------------------------------------------
static void window_load(Window *window) {

  // Set layer 
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  // Load the fonts

  GFont textFont = fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK); //Font for Text input
  GFont messageFont = fonts_get_system_font(FONT_KEY_GOTHIC_14); // Font for message input

  // Create layers for each and define the positions and size
  input_text_layer = text_layer_create((GRect) { .origin = { -40, 120 }, .size = { 130, 110 } }); 
  input_message_layer = text_layer_create((GRect) { .origin = { 60, 90 }, .size = { 85, 90 } });
  output_text_layer = text_layer_create((GRect) { .origin = { 0, 10 }, .size = { 50, 70 } });
  output_message_layer = text_layer_create((GRect) { .origin = { 60, 10 }, .size = { 80, 70 } });

  //Setting fonts
  text_layer_set_font(input_text_layer, textFont);
  text_layer_set_font(input_message_layer, messageFont);
  text_layer_set_font(output_text_layer, textFont);
  text_layer_set_font(output_message_layer, messageFont);

  // Center the input and output text field
  text_layer_set_text_alignment(input_text_layer, GTextAlignmentCenter);
  text_layer_set_text_alignment(output_text_layer, GTextAlignmentCenter);

  /*   
  // Set the color for each field. Default is white
  text_layer_set_background_color(input_text_layer, GColorWhite);
  text_layer_set_background_color(input_message_layer, GColorWhite);
  text_layer_set_background_color(output_text_layer, GColorWhite);
  text_layer_set_background_color(output_message_layer, GColorBlack);
  */

  // Set inital text for input field as "A"
  inputHolder[0] = inputText[0];
  text_layer_set_text(input_text_layer, inputHolder);
  text_layer_set_text(input_message_layer,inputMessage);
  text_layer_set_text(output_message_layer,outputMessage);


  // Add each layer to the window object
  layer_add_child(window_layer, text_layer_get_layer(input_text_layer));
  layer_add_child(window_layer, text_layer_get_layer(input_message_layer));
  layer_add_child(window_layer, text_layer_get_layer(output_text_layer));
  layer_add_child(window_layer, text_layer_get_layer(output_message_layer));

}

static void window_unload(Window *window) {
  // Destroy the layers to clear memory
  text_layer_destroy(input_text_layer);
  text_layer_destroy(input_message_layer);
  text_layer_destroy(output_text_layer);
  text_layer_destroy(output_message_layer);
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
void timer_callback(void *data) {
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
  // Also set the frame points
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
