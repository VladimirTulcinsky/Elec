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
#include "project.h"

static float alpha[26]; // a -> z
static float numbers[10]; // 0 -> 9

void createArray() {
    for(int x = 0; x < 26; x++) {
	alpha[x] = 1500 + ( x * 166.66); // 7500 - 1500 = 6000
    }                                // 6000 / 36 = 166.66 (36 = 26 char + 10 numbers)
    for(int y = 0; y < 10; y++) {
    	numbers[y] =  5833.33 + ( y * 166.66);
    }
}

float getSemaphore(char lettertoTranslate) {
   
	int position = lettertoTranslate - '0';

	if (position >= 0 && position <= 9)
		return numbers[position];
	else {
		position = tolower(lettertoTranslate) - 'a';
		return alpha[position];
	}
}


