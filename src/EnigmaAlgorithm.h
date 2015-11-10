//=======================================================================================================
// Project: Enigma 1.0v
// Description: Algorithm for the Enigma App for computing the rotators and plugboads
//
// Built using Pebble SDK 3.4v
// Date: October 14, 2015
//
// Programmer: Peter Leng, Kent Liu
// MIT Licence
// ======================================================================================================
#pragma once

#include <pebble.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ROTATE 26

char calculate(char inputChar);