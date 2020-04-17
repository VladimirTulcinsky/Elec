/* ========================================
 * ULB - Digital Electronic : Project 2020 
 * 
 * Mathias Hanquiniaux
 * Tanguy Snoeck
 * Vladimir Tulcinsky
 *
 * ========================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char *alpha[] = { ". -",   //A
		"- . . .", //B
		"- . - .", //C
		"- . .",  //D
		".",    //E
		". . - .", //F
		"- - .",  //G
		". . . .", //H
		". .",   //I
		". - - -", //J
		"- . -",  //K
		". - . .", //L
		"- -",   //M
		"- .",   //N
		"- - -",  //O
		". - - .", //P
		"- - . -", //Q
		". - .",  //R
		". . .",  //S
		"-",    //T
		". . -",  //U
		". . . -", //V
		". - -",  //W
		"- . . -", //X
		"- . - -", //Y
		"- - . .", //Z
		};

char *numbers[] = { "- - - - -", ". - - - -", ". . - - -", ". . . - -",
		". . . . -", ". . . . .", "- . . . .", "- - . . .", "- - - . .",
		"- - - - .", };

char* getMorse(char lettertoTranslate) {
	int position = lettertoTranslate - '0';

	if (position >= 0 && position <= 9)
		return numbers[position];
	else {
		position = tolower(lettertoTranslate) - 'a';
		return alpha[position];
	}
}


