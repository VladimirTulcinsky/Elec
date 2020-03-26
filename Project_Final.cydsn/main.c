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

  // Function to turn on all LEDs when you press on SW1
 void appuiSW1()
    {
      Led_1_Write( SW1_Read() );
      Led_2_Write( SW1_Read() );
      Led_3_Write( SW1_Read() );
      Led_4_Write( SW1_Read() );
    }

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

  
   
    
    for(;;)
    {
        appuiSW1();
      
    }
}



/* [] END OF FILE */
