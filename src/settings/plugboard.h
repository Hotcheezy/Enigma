//=======================================================================================================
// Project: Enigma 1.0v
// Description: Enigma Machine on Pebble Watch
// File: The plugboard.h file
// Built using Pebble SDK 3.4v
// Date: October 25, 2015
//
// Programmer: Peter Leng, Kent Liu
// MIT Licence
// ======================================================================================================

#pragma once

#include <pebble.h>

// Def
#define NUM_WINDOWS_PLUG 26 // number of windows for the plug window
#define CHECKBOX_WINDOW_CELL_HEIGHT 30
#define DISTANCE_BETWEEN_LETTER 30
#define DISTANCE_BETWEEN_LABEL 5
#define NUM_LEVELS 27

// Pushed to the plugboard window
void plugboard_window_push();