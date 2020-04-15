/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "project.h"
#include <stdio.h>
#include <stdlib.h>


char* translateToMorse(char caractere){

char* myReturn[20];
char *carac[40];

carac[0] = ". -";
carac[1] = "- . . .";
carac[2] = "- . - .";
carac[3] = "- . .";
carac[4] = ".";
carac[5] = ". . - .";
carac[6] = "- - .";
carac[7] = ". . . .";
carac[8] = ". .";
carac[9] = ". - - -";

carac[10] = "- . -";
carac[11] = "-. - . .";
carac[12] = "- -";
carac[13] = "- .";
carac[14] = "- - -";
carac[15] = ". - - .";
carac[16] = "- - . -";
carac[17] = ". - .";
carac[18] = ". . .";
carac[19] = "-";
carac[20] = ". . -";
carac[21] = ". . . -";
carac[22] = ". - -";
carac[23] = "- . . -";
carac[24] = "- . - -";
carac[25] = "- - . .";

carac[26]="- - - - -";
carac[27]=". - - - -";
carac[28]=". . - - -";
carac[29]=". . . - -";
carac[30]=". . . . -";
carac[31]=". . . . .";
carac[32]="- . . . .";
carac[33]="- - . . .";
carac[34]="- - - . .";
carac[35]="- - - - .";
carac[36] = ". - . - . -";
carac[37] = ". . - - . .";
carac[38] = "- . - . - -";
carac[39] = ". - - . - .";

switch (caractere)
{
    case 'a':
     return carac[0];
     ;
    case 'b':
     return carac[1];
     ;
    case 'c':
     return carac[2];
     ;
    case 'd':
     return carac[3];
     ;
    case 'e':
     return carac[4];
     ;
    case 'f':
     return carac[5];
     ;
    case 'g':
     return carac[6];
     ;
    case 'h':
     return carac[7];
     ;
    case 'i':
     return carac[8];
     ;
    case 'j':
     return carac[9];
     ;
    case 'k':
     return carac[10];
     ;
    case 'l':
     return carac[11];
     ;
    case 'm':
     return carac[12];
     ;
    case 'n':
     return carac[13];
     ;
    case 'o':
     return carac[14];
     ;
    case 'p':
     return carac[15];
     ;
    case 'q':
     return carac[16];
     ;
    case 'r':
     return carac[17];
     ;
    case 's':
     return carac[18];
     ;
    case 't':
     return carac[19];
     ;
    case 'u':
     return carac[20];
     ;
    case 'v':
     return carac[21];
     ;
    case 'w':
     return carac[22];
     ;
    case 'x':
     return carac[23];
     ;
    case 'y':
     return carac[24];
     ;
    case 'z':
     return carac[25];
     ;
    case '0':
     return carac[26];
     ;
    case '1':
     return carac[27];
     ;
    case '2':
     return carac[28];
     ;
    case '3':
     return carac[29];
     ;
    case '4':
     return carac[30];
     ;
    case '5':
     return carac[31];
     ;
    case '6':
     return carac[32];
     ;
    case '7':
     return carac[33];
     ;
    case '8':
     return carac[34];
     ;
    case '9':
     return carac[35];
     ;
    case '.':
     return carac[36];
     ;
    case '?':
     return carac[37];
     ;
    case '!':
     return carac[38];
     ;
    case '@':
     return carac[39];
     ;
}
    return 0;
}


/* [] END OF FILE */
