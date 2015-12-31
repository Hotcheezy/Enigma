//=======================================================================================================
// Project: Enigma 1.0v
// Description: Enigma Machine on Pebble Watch
// File: The savedSettings.h file
// Built using Pebble SDK 3.4v
// Date: October 25, 2015
//
// Programmer: Peter Leng, Kent Liu
// MIT Licence
// ======================================================================================================

#pragma once

#include <pebble.h>

// Def
#define NUM_SAVE_ACTIONS 2 // Number of things to select in the menu
#define CHECKBOX_SAVE_WINDOW_CELL_HEIGHT 47
#define NUM_SAVE_WINDOWS_PLUG 3 // number of windows for the plug window

// Pushed to the menu window
void savedSettings_window_push();