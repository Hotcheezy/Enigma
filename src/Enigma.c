#include <pebble.h>
#include <string.h>

static Window *window;
static TextLayer *input_text_layer;
static TextLayer *input_message_layer;
static TextLayer *output_text_layer;

char *inputText[26] = {"A","B","C","D","E","F","G","H","I","J","K","L","M",                                   
                       "N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
char *inputMessage = ""; 

int textCounter = 0;

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(input_message_layer, strcat(inputMessage,inputText[textCounter-1]));
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(input_text_layer, "Up"); 
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(input_text_layer, inputText[textCounter]);
  textCounter++;
  if(textCounter == 26){
    textCounter = 0;
  }
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  GFont systems_font1 = fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK);
  GFont systems_font2 = fonts_get_system_font(FONT_KEY_GOTHIC_14);

  input_text_layer = text_layer_create((GRect) { .origin = { -45, 100 }, .size = { bounds.size.w, 110 } });
  input_message_layer = text_layer_create((GRect) { .origin = { 70, 80 }, .size = { bounds.size.w, 30 } });
  
  text_layer_set_text(input_text_layer, inputText[0]);

  text_layer_set_font(input_text_layer, systems_font1);
  text_layer_set_font(input_message_layer, systems_font2);
  text_layer_set_text_alignment(input_text_layer, GTextAlignmentCenter);

  layer_add_child(window_layer, text_layer_get_layer(input_text_layer));
  layer_add_child(window_layer, text_layer_get_layer(input_message_layer));

}

static void window_unload(Window *window) {
  text_layer_destroy(input_text_layer);
  text_layer_destroy(input_message_layer);
}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
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
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);
  // Enter the main event loop. This will block until the app is ready to exit.
  app_event_loop();
  // Do clean up here
  deinit();
}
