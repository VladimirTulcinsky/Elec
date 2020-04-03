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
#include "keypad.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int static i;
float static signal[100];
int32 volatile static adc_value;
int clock=0;
int clock2=0;

CY_ISR(Timer_Handler) 
{
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
    
 void resetLed()
{
        Led_1_Write(0);
        Led_2_Write(0);
        Led_3_Write(0);
        Led_4_Write(0);
}

void pointAllume(int length)
{
    int actualClock = clock;
    do{
        Timer_Start();
        if(Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC) clock++;
        Led_1_Write(1);
        Led_2_Write(1);
        Led_3_Write(1);
        Led_4_Write(1);   
    }while(clock - actualClock < length);
}

void pointEteint(int length)
{
    int actualClock = clock;
    do{
        if(Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC) clock++;  
        Timer_Stop();
        Led_1_Write(0);
        Led_2_Write(0);
        Led_3_Write(0);
        Led_4_Write(0);   
    }while(clock - actualClock < length);
}
void barre()
{
    pointAllume(750);
}

void espacementLettre()
{
   pointEteint(750); 
}

void espacementElement()
{
    pointEteint(250);   
}

void selectSignal(int value)
{   
   if(value == 0){
        pointAllume(250);    
    }else if(value == 1){
        barre();
    }else if(value == 2){
        espacementElement();
    }else if(value == 3){
        espacementLettre();
    }
}
 
void signalSOS()
{
        // ... --- ...
        // 0 = point
        // 1 = barre
        // 2 = espace entre deux éléments d'une même lettre (1 point)
        // 3 = espace entre deux lettres (3 points)  
    int arr[17] = {0,2,0,2,0,3,1,2,1,2,1,3,0,2,0,2,0};
    int f;
    Timer_1_Start();
   
    if(Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC) clock++;
    
    for(f = 0; f < 17; f ++)
    {
        selectSignal(arr[f]);
    }
    resetLed();
    clock = 0;
}

void signalBEAMS()
{
    //-... . .- -- ... 
    int arr[23] = {1,2,0,2,0,2,0,3,0,3,0,2,1,3,1,2,1,3,0,2,0,2,0};
    int f;
    Timer_1_Start();
   
    if(Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC) clock++;
    
    for(f = 0; f < 23; f ++)
    {
        selectSignal(arr[f]);
    }
    resetLed();
    clock = 0;
    
}
     // Function to turn on all LEDs when you press on SW2
  void appuiSW2()
    {
       if( SW2_Read() != 0)
        {
            Timer_1_Start();
           
            if(Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC) clock++;
            
            pointAllume(250);
            resetLed();
            clock = 0;
        }
    }
    
 void appuiSW3() /// When you press on SW3
    {
       if( SW3_Read() != 0)
        {
            Timer_1_Start();
           
            if(Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC) clock++;
            
            pointAllume(750);
            resetLed();
            clock = 0;
        }
    }
    
 void displayMessage(char** message)
{
    LCD_Position(0,0);
    LCD_PrintString(*message);
}
  
  void keyboard() // Keyboard function used to read 1,2 or *
{
    uint8_t  value = keypadScan();
    char* message;
    while (value == '1' || value == '*' || value == '2') 
    {
        uint8_t value2 = keypadScan();

        if ((value == '1' && value2 == '*') || (value == '*' && value2 == '1')) {
            message = (char*) malloc(strlen("SOS"));
            sprintf(message,"SOS");
            displayMessage(&message);
            signalSOS();
            
            break;
        }
         if ((value == '2' && value2 == '*') || (value == '*' && value2 == '2')) {
            message = (char*) malloc(strlen("BEAMS"));
            sprintf(message,"BEAMS");
            displayMessage(&message);
            signalBEAMS();
            
            break;
        }
    }
}


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    for (i = 0; i < 100; i++) {
        signal[i] = sin((i * 2 * M_PI) / 100);
    }
    i = 0;
    isr_StartEx(Timer_Handler);
    Timer_Stop();
    VDAC_Start();
    VDAC_SetValue(0);
    Led_1_Write(0);
    Led_2_Write(0);
    Led_3_Write(0);
    Led_4_Write(0);
    LCD_Start();
    LCD_ClearDisplay();
    for(;;)
    {  
        
                
        appuiSW1();
        appuiSW2();
        appuiSW3();   
        keyboard();
    }
}



/* [] END OF FILE */
