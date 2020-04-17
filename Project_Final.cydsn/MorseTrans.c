#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

const char *alpha[] = { ". -",   //A
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

const char *numbers[] = { "- - - - -", ". - - - -", ". . - - -", ". . . - -",
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

/*
int main(void) {
	char str[] = "SOS";
	int len = strlen(str);
	char *morse[len];
	for (int i = 0; i < len; ++i) {
		morse[i] = getMorse(str[i]);
		//rajouter un espace si necessaire
		printf("%s", getMorse(str[i]));
	}

	return EXIT_SUCCESS;
}
*/

