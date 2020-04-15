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
 void appuiSW1() 
{
    if( SW1_Read() != 0) { // When the SW1 is press
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

/* [] END OF FILE */
