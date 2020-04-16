/* ========================================
 * ULB - Digital Electronic : Project 2020 
 * 
 * Mathias Hanquiniaux
 * Tanguy Snoeck
 * Vladimir Tulcinsky
 *
 * ========================================
*/

#include "project.h"
#include <stdio.h>
#include <stdlib.h>

  // Function to turn on all LEDs when you press on SW1
void pressSW1() {
    if (SW1_Read() != 0) { // When the SW1 is press
        Led_1_Write(SW1_Read());
        Led_2_Write(SW1_Read());
        Led_3_Write(SW1_Read());
        Led_4_Write(SW1_Read());
        Timer_Start();   
    } else { //  When the SW1 isn't press
        Led_1_Write(SW1_Read());
        Led_2_Write(SW1_Read());
        Led_3_Write(SW1_Read());
        Led_4_Write(SW1_Read());
        Timer_Stop();
    }
}

char* translateToMorse(char character){
    char* morse_alphabet[40] = {". -", "- . . .", "- . - .", "- . .", ".", ". . - .", "- - .", ". . . .", ". .", ". - - -",
        "- . -", "-. - . .", "- -", "- .", "- - -", ". - - .", "- - . -", ". - .", ". . .", "-", ". . -", ". . -",
        ". - -", "- . . -", "- . - -", "- - . .", "- - - - -", ". - - - -", ". . - - -", ". . . - -", ". . . . -",
        ". . . . .", "- . . . .", "- - . . .", "- - - . .", "- - - - .", ". - . - . -", ". . - - . .", "- . - . - -",
        "- . - . - -"};

    switch (character) {
        case 'a':
            return morse_alphabet[0];
            break;
        case 'b':
            return morse_alphabet[1];
            break;
        case 'c':
            return morse_alphabet[2];
            break;
        case 'd':
            return morse_alphabet[3];
            break;
        case 'e':
            return morse_alphabet[4];
            break;
        case 'f':
            return morse_alphabet[5];
            break;
        case 'g':
            return morse_alphabet[6];
            break;
        case 'h':
            return morse_alphabet[7];
            break;
        case 'i':
            return morse_alphabet[8];
            break;
        case 'j':
            return morse_alphabet[9];
            break;
        case 'k':
            return morse_alphabet[10];
            break;
        case 'l':
            return morse_alphabet[11];
            break;
        case 'm':
            return morse_alphabet[12];
            break;
        case 'n':
            return morse_alphabet[13];
            break;
        case 'o':
            return morse_alphabet[14];
            break;
        case 'p':
            return morse_alphabet[15];
            break;
        case 'q':
            return morse_alphabet[16];
            break;
        case 'r':
            return morse_alphabet[17];
            break;
        case 's':
            return morse_alphabet[18];
            break;
        case 't':
            return morse_alphabet[19];
            break;
        case 'u':
            return morse_alphabet[20];
            break;
        case 'v':
            return morse_alphabet[21];
            break;
        case 'w':
            return morse_alphabet[22];
            break;
        case 'x':
            return morse_alphabet[23];
            break;
        case 'y':
            return morse_alphabet[24];
            break;
        case 'z':
            return morse_alphabet[25];
            break;
        case '0':
            return morse_alphabet[26];
            break;
        case '1':
            return morse_alphabet[27];
            break;
        case '2':
            return morse_alphabet[28];
            break;
        case '3':
            return morse_alphabet[29];
            break;
        case '4':
            return morse_alphabet[30];
            break;
        case '5':
            return morse_alphabet[31];
            break;
        case '6':
            return morse_alphabet[32];
            break;
        case '7':
            return morse_alphabet[33];
            break;
        case '8':
            return morse_alphabet[34];
            break;
        case '9':
            return morse_alphabet[35];
            break;
        case '.':
            return morse_alphabet[36];
            break;
        case '?':
            return morse_alphabet[37];
            break;
        case '!':
            return morse_alphabet[38];
            break;
        case '@':
            return morse_alphabet[39];
            break;
    }
    
    return "";
}


/* [] END OF FILE */
