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
/* Rotator settings
Setting Wiring                      Notch   Window  Turnover
Base    ABCDEFGHIJKLMNOPQRSTUVWXYZ
I       EKMFLGDQVZNTOWYHXUSPAIBRCJ  Y       Q       R
II      AJDKSIRUXBLHWTMCQGZNPYFVOE  M       E       F
III     BDFHJLCPRTXVZNYEIWGAKMUSQO  D       V       W
IV      ESOVPZJAYQUIRHXLNFTGKDCMWB  R       J       K
V       VZBRGITYUPSDNHLXAWMJQOFECK  H       Z       A
VI      JPGVOUMFYQBENHZRDKASXLICTW  H/U     Z/M     A/N
VII     NZJHGRCXMYSWBOUFAIVLPEKQDT  H/U     Z/M     A/N
VIII    FKQHTLXOCBJSPDZRAMEWNIUYGV  H/U     Z/M     A/N
*/ 

// =======================================================================================================
// Libraries



// -------------------------------------------------------------------------------------------------------
//                                        Declare Variables
// -------------------------------------------------------------------------------------------------------
const char *rotor_ciphers[] = {
    "EKMFLGDQVZNTOWYHXUSPAIBRCJ", 
    "AJDKSIRUXBLHWTMCQGZNPYFVOE",
    "BDFHJLCPRTXVZNYEIWGAKMUSQO",
    "ESOVPZJAYQUIRHXLNFTGKDCMWB",
    "VZBRGITYUPSDNHLXAWMJQOFECK",
    "JPGVOUMFYQBENHZRDKASXLICTW",
    "NZJHGRCXMYSWBOUFAIVLPEKQDT",
    "FKQHTLXOCBJSPDZRAMEWNIUYGV"
};

// -------------------------------------------------------------------------------------------------------
//                                     End: Declare Variables
// -------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------
//                                         Public Function
// -------------------------------------------------------------------------------------------------------


// -------------------------------------------------------------------------------------------------------
//                                       End: Public Function
// -------------------------------------------------------------------------------------------------------


// -------------------------------------------------------------------------------------------------------
//                                        Private Function
// -------------------------------------------------------------------------------------------------------


// -------------------------------------------------------------------------------------------------------
//                                       End: Private Function
// -------------------------------------------------------------------------------------------------------
