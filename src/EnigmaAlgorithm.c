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

#include "EnigmaAlgorithm.h"
// -------------------------------------------------------------------------------------------------------
//                                        Declare Variables
// -------------------------------------------------------------------------------------------------------
// Global Variables
char rotatorText[3][2]; // this is the text for the rotator it has 3 letters and each on is in another array. so {"A", "A", "A"}
int rotorPostition[3]; // This is the rotor position for each individual rotor
int rotorTypePostition[3];
char rotorType[3][2]; // This will contain the type of rotor choosed. Each can contain a number from 1 to 8
char plugConnectLetters[26][2]; // The letters that corresponds to another letter

const char *alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
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

const char *rotor_notches[] = {"Q", "E", "V", "J", "Z", "ZM", "ZM", "ZM"};

const char *rotor_turnovers[] = {"R", "F", "W", "K", "A", "AN", "AN", "AN"};

extern char *reflectors[] = {
    "EJMZALYXVBWFCRQUONTSPIKHGD",
    "YRUHQSLDPXNGOKMIEBFZCWVJAT",
    "FVPJIAOYEDRZXWGCTKUQSBNMHL"
};

extern struct Rotor {
    int             offset;
    int             turnnext;
    const char      *cipher;
    const char      *turnover;
    const char      *notch;
};

extern struct Enigma {
    int             numrotors;
    const char      *reflector;
    struct Rotor    rotors[8];
};




// -------------------------------------------------------------------------------------------------------
//                                     End: Declare Variables
// -------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------
//                                         Private Function
// -------------------------------------------------------------------------------------------------------
/*
 * Produce a rotor object
 * Setup the correct offset, cipher set and turn overs.
 */
struct Rotor new_rotor(struct Enigma *machine, int rotornumber, int offset) {
    struct Rotor r;
    r.offset = offset;
    r.turnnext = 0;
    r.cipher = rotor_ciphers[rotornumber - 1];
    r.turnover = rotor_turnovers[rotornumber - 1];
    r.notch = rotor_notches[rotornumber - 1];
    machine->numrotors++;

    return r;
}
/*
 * Return the index position of a character inside a string
 * if not found then -1
 **/
int str_index(const char *str, int character) {
    char *pos;
    int index;
    pos = strchr(str, character);

    // pointer arithmetic
    if (pos){
        index = (int) (pos - str);
    } else {
        index = -1;
    }

    return index;
}

/*
 * Cycle a rotor's offset but keep it in the array.
 */
void rotor_cycle(struct Rotor *rotor) {
    rotor->offset++;
    rotor->offset = rotor->offset % ROTATE;

    // Check if the notch is active, if so trigger the turnnext
    if(str_index(rotor->turnover, alpha[rotor->offset]) >= 0) {
        rotor->turnnext = 1;
    }
}

/*
 * Pass through a rotor, right to left, cipher to alpha.
 * returns the exit index location.
 */
int rotor_forward(struct Rotor *rotor, int index) {

    // In the cipher side, out the alpha side
    index = (index + rotor->offset) % ROTATE;
    index = str_index(alpha, rotor->cipher[index]);
    index = (ROTATE + index - rotor->offset) % ROTATE;

    return index;
}

/*
 * Pass through a rotor, left to right, alpha to cipher.
 * returns the exit index location.
 */
int rotor_reverse(struct Rotor *rotor, int index) {

    // In the cipher side, out the alpha side
    index = (index + rotor->offset) % ROTATE;
    index = str_index(rotor->cipher, alpha[index]);
    index = (ROTATE + index - rotor->offset) % ROTATE;

    return index;

}


// -------------------------------------------------------------------------------------------------------
//                                       End: Private Function
// -------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------
//                                        Public Function
// -------------------------------------------------------------------------------------------------------

char calculate(char inputChar){

    index = str_index(alpha, inputChar);

    // Cycle first rotor before pushing through,
    rotor_cycle(&machine.rotors[0]);

    // Double step the rotor
        if(str_index(machine.rotors[1].notch,
                    alpha[machine.rotors[1].offset]) >= 0 ) {
            rotor_cycle(&machine.rotors[1]);
        }

        // Stepping the rotors
        for(i=0; i < machine.numrotors - 1; i++) {
            inputChar = alpha[machine.rotors[i].offset];

            if(machine.rotors[i].turnnext) {
                machine.rotors[i].turnnext = 0;
                rotor_cycle(&machine.rotors[i+1]);
            }
         }

        // Pass through all the rotors forward
        for(i=0; i < machine.numrotors; i++) {
            index = rotor_forward(&machine.rotors[i], index);
        }

        // Inbound
        character = machine.reflector[index];
        // Outbound
        index = str_index(alpha, inputChar);

        // Pass back through the rotors in reverse
        for(i = machine.numrotors - 1; i >= 0; i--) {
            index = rotor_reverse(&machine.rotors[i], index);
        }

        // Pass through Plugboard
        inputChar = alpha[index];

        return inputChar;

}

// -------------------------------------------------------------------------------------------------------
//                                       End: Public Function
// -------------------------------------------------------------------------------------------------------
