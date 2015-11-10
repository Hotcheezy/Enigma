//=======================================================================================================
// Project: Enigma 1.0v
// Description: Enigma Machine on Pebble Watch
//
// Implementation file 
// Built using Pebble SDK 3.4v
// Date: October 15, 2015
//
// Programmer: Peter Leng, Kent Liu
// MIT Licence
// ======================================================================================================

// Global Variables
extern char rotatorText[3][2]; // this is the text for the rotator it has 3 letters and each on is in another array. so {"A", "A", "A"}
extern int rotorPostition[3]; // This is the rotor position for each individual rotor
extern int rotorTypePostition[3];
extern char rotorType[3][2]; // This will contain the type of rotor choosed. Each can contain a number from 1 to 8

extern char plugConnectLetters[26][2]; // The letters that corresponds to another letter
// For the enigma 
extern int selectRotor;
extern int selectType;