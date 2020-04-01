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
#include <math.h>
#include <stdio.h>

int static i;
float static signal[100];
int32 volatile static adc_value;

CY_ISR(Timer_1_Handler) {
    float val = signal[i] * (float)adc_value / 3311 + 128;
    VDAC_SetValue(val);
    VDAC_SetValue(signal[i] * 50 + 128);
    i++;
    if (i == 100) i = 0;
    Timer_ReadStatusRegister();
}


  // Function to turn on all LEDs when you press on SW1
 void appuiSW1()
    {
        
        if( SW1_Read() != 0)
        { // When the SW1 is press
            Led_1_Write(SW1_Read());
            Led_2_Write(SW1_Read());
            Led_3_Write(SW1_Read());
            Led_4_Write(SW1_Read());
        }
        else
        { //  When the SW1 isn't press
            Led_1_Write(SW1_Read());
            Led_2_Write(SW1_Read());
            Led_3_Write(SW1_Read());
            Led_4_Write(SW1_Read());
            
        }
    
    
    
    }
 

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    for (i = 0; i < 100; i++) {
        signal[i] = sin((i * 2 * M_PI) / 100);
    }
    
    i = 0;
    isr_StartEx(Timer_1_Handler);
    Timer_Start();
    
    VDAC_Start();
    VDAC_SetValue(0);

    
    
    for(;;)
    {
        
        //float val = signal[i] * (float)adc_value / 3311 + 128;
        //appuiSW1();
      
    }
}



/* [] END OF FILE */
