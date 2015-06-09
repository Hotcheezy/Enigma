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

static GPath *s_my_path_ptr = NULL;

char *inputMessage = "";
char *outputMessage = "";
// Counter variable for cycling the alphabet
int textCounter = 0; 

// --------------------------------------------------------------

static const struct GPathInfo LAYER_1_PATHS[] = {
  { // [0] path 
    .num_points = 23,
    .points = (GPoint []) {
      {65, 38},
      {28, 49}, // CURVE CONVERTED
      {12, 58}, // CURVE CONVERTED
      {7, 64}, // CURVE CONVERTED
      {9, 74}, // CURVE CONVERTED
      {40, 91}, // CURVE CONVERTED
      {82, 96}, // CURVE CONVERTED
      {120, 86}, // CURVE CONVERTED
      {137, 61}, // CURVE CONVERTED
      {106, 44}, // CURVE CONVERTED
      {65, 38}, // CURVE CONVERTED
      {65, 38},
      {16, 62},
      {15, 74}, // CURVE CONVERTED
      {72, 92}, // CURVE CONVERTED
      {105, 86}, // CURVE CONVERTED
      {130, 73}, // CURVE CONVERTED
      {130, 62}, // CURVE CONVERTED
      {130, 62}, // CURVE CONVERTED
      {130, 62}, // CURVE CONVERTED
      {106, 48}, // CURVE CONVERTED
      {16, 62}, // CURVE CONVERTED
      {16, 62}
    }
  },
  { // [1] path 
    .num_points = 15,
    .points = (GPoint []) {
      {85, 88},
      {90, 87},
      {91, 51},
      {94, 58}, // CURVE CONVERTED
      {93, 67}, // CURVE CONVERTED
      {93, 87}, // CURVE CONVERTED
      {97, 86},
      {98, 54},
      {101, 68}, // CURVE CONVERTED
      {100, 85}, // CURVE CONVERTED
      {105, 83},
      {106, 55},
      {98, 49}, // CURVE CONVERTED
      {86, 46}, // CURVE CONVERTED
      {85, 88}
    }
  },
  { // [2] path 
    .num_points = 19,
    .points = (GPoint []) {
      {83, 67},
      {73, 67},
      {72, 71},
      {78, 71},
      {78, 85}, // CURVE CONVERTED
      {70, 85}, // CURVE CONVERTED
      {70, 51},
      {75, 49}, // CURVE CONVERTED
      {78, 53}, // CURVE CONVERTED
      {83, 54},
      {82, 48}, // CURVE CONVERTED
      {66, 48}, // CURVE CONVERTED
      {65, 61}, // CURVE CONVERTED
      {65, 75}, // CURVE CONVERTED
      {66, 88}, // CURVE CONVERTED
      {78, 90}, // CURVE CONVERTED
      {83, 81}, // CURVE CONVERTED
      {83, 67}, // CURVE CONVERTED
      {83, 67}
    }
  },
  { // [3] path 
    .num_points = 12,
    .points = (GPoint []) {
      {38, 82},
      {40, 83},
      {42, 84}, // CURVE CONVERTED
      {42, 55}, // CURVE CONVERTED
      {48, 70}, // CURVE CONVERTED
      {48, 86}, // CURVE CONVERTED
      {53, 87},
      {53, 55}, // CURVE CONVERTED
      {39, 53}, // CURVE CONVERTED
      {37, 61}, // CURVE CONVERTED
      {38, 82}, // CURVE CONVERTED
      {38, 82}
    }
  },
  { // [4] path 
    .num_points = 11,
    .points = (GPoint []) {
      {107, 82},
      {112, 81},
      {112, 74},
      {117, 72},
      {117, 78},
      {122, 76}, // CURVE CONVERTED
      {123, 59},
      {113, 55}, // CURVE CONVERTED
      {108, 66}, // CURVE CONVERTED
      {107, 82}, // CURVE CONVERTED
      {107, 82}
    }
  },
  { // [5] path 
    .num_points = 6,
    .points = (GPoint []) {
      {56, 48},
      {56, 88},
      {61, 89},
      {61, 46},
      {56, 48}, // CURVE CONVERTED
      {56, 48}
    }
  },
  { // [6] path 
    .num_points = 15,
    .points = (GPoint []) {
      {22, 76},
      {36, 82}, // CURVE CONVERTED
      {35, 77},
      {26, 73}, // CURVE CONVERTED
      {26, 70},
      {32, 70},
      {32, 67},
      {26, 67},
      {29, 62}, // CURVE CONVERTED
      {35, 59}, // CURVE CONVERTED
      {35, 54},
      {24, 61}, // CURVE CONVERTED
      {21, 67}, // CURVE CONVERTED
      {22, 76}, // CURVE CONVERTED
      {22, 76}
    }
  },
  { // [7] path 
    .num_points = 6,
    .points = (GPoint []) {
      {13, 70},
      {16, 68}, // CURVE CONVERTED
      {13, 65}, // CURVE CONVERTED
      {10, 68}, // CURVE CONVERTED
      {13, 70}, // CURVE CONVERTED
      {13, 70}
    }
  },
  { // [8] path 
    .num_points = 6,
    .points = (GPoint []) {
      {133, 70},
      {136, 68}, // CURVE CONVERTED
      {133, 65}, // CURVE CONVERTED
      {130, 68}, // CURVE CONVERTED
      {133, 70}, // CURVE CONVERTED
      {133, 70}
    }
  },
  { // [9] path 
    .num_points = 5,
    .points = (GPoint []) {
      {112, 69},
      {117, 68},
      {114, 59}, // CURVE CONVERTED
      {112, 69}, // CURVE CONVERTED
      {112, 69}
    }
  }
};

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
  s_my_path_ptr = gpath_create(&LAYER_1_PATHS);
}

static void logoWindow_unload(Window *logoWindow) {

}

static void logoInit(void) {
  logoWindow = window_create();
  window_set_fullscreen(logoWindow, true);
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
  window_set_fullscreen(window, true); // Fullscreen - No status bar
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
