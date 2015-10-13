// Libraries
#include <pebble.h>
#include <string.h>

// Define 
#define LAYER_1_PATH_COUNT 10



// Declare Variables --------------------------------------

// Windows 
static Window *window;
static Window *logoWindow;


static TextLayer *input_text_layer;
static TextLayer *input_message_layer;
static TextLayer *output_text_layer;   
static TextLayer *output_message_layer;

// List of the alphabet
char *inputText[27] = {"A","B","C","D","E","F","G","H","I","J","K","L","M",                                   
                       "N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};     

char *outputText[27] = {"A","Q","U","B","C","R","S","U","V","T","D","E","I",
                       "Y","Z","F","G","J","K","L","M","N","O","P","Q","W"}; 

// Message holder for input       
char *inputMessage = "";
char *outputMessage = "";
// Counter variable for cycling the alphabet
int textCounter = 0; 

// --------------------------------------------------------------

// When select button is clicked
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  // Change the text for each input and output 
  text_layer_set_text(input_message_layer,strcat(inputMessage,inputText[textCounter]));
  text_layer_set_text(output_message_layer,strcat(outputMessage,outputText[textCounter]));
  text_layer_set_text(output_text_layer, inputText[textCounter]);
}

// When up button is clicked
static void up_click_handler(ClickRecognizerRef recognizer, void *context) { 
}

// When down button is clicked
static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
// The input letter increments with each down clicks therefore a counter
  text_layer_set_text(input_text_layer, inputText[textCounter]);

  textCounter++;
  if(textCounter == 26 || textCounter > 26){
    // If letter is Z, reset to "A"
    textCounter = 0;
  }
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

// Main application window ---------------------------------------------------------------------------
static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  // Load the fonts
  GFont textFont = fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK);
  GFont messageFont = fonts_get_system_font(FONT_KEY_GOTHIC_14);

  // Create layers for each
  input_text_layer = text_layer_create((GRect) { .origin = { -40, 120 }, .size = { 130, 110 } });
  input_message_layer = text_layer_create((GRect) { .origin = { 60, 90 }, .size = { 85, 90 } });
  output_text_layer = text_layer_create((GRect) { .origin = { 0, 10 }, .size = { 50, 70 } });
  output_message_layer = text_layer_create((GRect) { .origin = { 60, 10 }, .size = { 80, 70 } });
 
  // Set inital text for input field as "A"
  text_layer_set_text(input_text_layer, inputText[0]);
  
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
  */ 
  //text_layer_set_background_color(output_message_layer, GColorBlack);

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

// -----------------------------------------------------------------------------------------------------



static void logoWindow_load(Window *logoWindow) {
  Layer *window_layer = window_get_root_layer(window);
}

static void logoWindow_unload(Window *logoWindow) {

}

static void logoInit(void) {
  logoWindow = window_create();
  //window_set_fullscreen(logoWindow, true);
  window_set_window_handlers(logoWindow, (WindowHandlers) {
    .load = logoWindow_load,
    .unload = logoWindow_unload,
  });
  //------------------------------



  //------------------------------
  window_destroy(window);
}
static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  //window_set_fullscreen(window, true); // Fullscreen - No status bar
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

// Main function 
int main(void) {
  // Do set up here
  logoInit();
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);
  // Enter the main event loop. This will block until the app is ready to exit.
  app_event_loop();
  // Do clean up here
  deinit();
}
