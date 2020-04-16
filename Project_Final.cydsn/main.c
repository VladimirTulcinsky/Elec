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
#include "keypad.h"
#include "morse.h"
#include "sw1.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define _LONG_SIGNAL_ '-'
#define _SHORT_SIGNAL_ '.'
#define _LETTER_SPACE_ ' '
#define _ELEMENT_SPACE_ '/'

int static i;
float static signal[100];
int clock=0;
int clock2=0;
_Bool flag = 0;
_Bool pressSW4 = 0;
_Bool lightOn;
char rxData;
//adc potentiometer
int32 volatile static adc_value;
float adc_value_float;


 void displayMessage(char** message) {
    LCD_Position(0,0);
    LCD_PrintString(*message);
}

CY_ISR(Timer_Handler)  {
    float val = signal[i] * (float)adc_value / 3311 + 128;
    VDAC_SetValue(val);
    VDAC_SetValue(signal[i] * 50 + 128);
    i++;
    
    if (i == 100) i = 0;
    
    Timer_ReadStatusRegister();
}

CY_ISR(SW4_Handler) {
    flag =!flag;   
    SW4_ClearInterrupt();
}

void resetLed() {
    Led_1_Write(0);
    Led_2_Write(0);
    Led_3_Write(0);
    Led_4_Write(0);
}

void turnLEDsOn(int length) { //cette fonction allume les leds? 
    int actualClock = clock;
    Timer_Start();
    
    do {
        if (Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC) clock++;
        
        if (lightOn == 1) {
            Led_1_Write(1);
            Led_2_Write(1);
            Led_3_Write(1);
            Led_4_Write(1);   
        }
    } while(clock - actualClock < length);
}

void turnLEDsOff(int length) { // cette fonction éteint les leds ?
    int actualClock = clock;
    
    do {
        if (Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC) clock++;  
        Timer_Stop();
        Led_1_Write(0);
        Led_2_Write(0);
        Led_3_Write(0);
        Led_4_Write(0);   
    } while(clock - actualClock < length);
}

// il y a surement moyen de fusionner les deux prochaines méthodes.

void sendMorseToComputer(char value) { // cette fonction envoie le signal morse vers le pc ?
    switch (value) {
        case _SHORT_SIGNAL_: 
            turnLEDsOn(250);
            UART_PutChar(46);
            break;
            
        case _LONG_SIGNAL_:
            turnLEDsOn(750);
            UART_PutChar(45); 
            break;
            
        case _ELEMENT_SPACE_:
            turnLEDsOff(250);   
            UART_PutChar(32);
            break;
            
        case _LETTER_SPACE_:
            turnLEDsOff(750); 
            UART_PutChar(32);
            UART_PutChar(32);
            UART_PutChar(32);
            break;
    }
}

void test(char value) { // test ? ça veut dire qu'on peut la supprimer ?
    Timer_1_Start();
   
    if (Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC) clock++;
    
    char* morseCode = translateToMorse(value);
    sendMorseToComputer(_ELEMENT_SPACE_);
    
    for (int x = 0; x < (int)strlen(morseCode); x++) {
        sendMorseToComputer(morseCode[x]);
    }
    
    sendMorseToComputer(_ELEMENT_SPACE_);
    resetLed();
    clock = 0;
}

void signalSOS() {
    // ... --- ...
    Timer_1_Start();
    char* morseCode = translateToMorse('s');
   
    if (Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC) clock++;
    
    for(int x = 0; x < (int)strlen(morseCode); x++) {
        sendMorseToComputer(morseCode[x]);
    }
    
    sendMorseToComputer(_LETTER_SPACE_);
    char* morseCode2 = translateToMorse('o');
    
    for(int x = 0; x < (int)strlen(morseCode2); x++) {
        sendMorseToComputer(morseCode2[x]);
    }
    sendMorseToComputer(_LETTER_SPACE_);
   
    for(int x = 0; x < (int) strlen(morseCode); x++)
    {
        sendMorseToComputer(morseCode[x]);
    }
    sendMorseToComputer(_LETTER_SPACE_);
    
    resetLed();
    clock = 0;
}

void signalBEAMS() {
    //-... . .- -- ... 
    int beams[23] = {_LONG_SIGNAL_,_LETTER_SPACE_,_SHORT_SIGNAL_,_LETTER_SPACE_,_SHORT_SIGNAL_,_LETTER_SPACE_,
        _SHORT_SIGNAL_,_ELEMENT_SPACE_,_SHORT_SIGNAL_,_ELEMENT_SPACE_,_SHORT_SIGNAL_,_LETTER_SPACE_,
        _LONG_SIGNAL_, _ELEMENT_SPACE_, _LONG_SIGNAL_, _LETTER_SPACE_, _LONG_SIGNAL_, _ELEMENT_SPACE_, _SHORT_SIGNAL_,
        _LETTER_SPACE_, _SHORT_SIGNAL_, _LETTER_SPACE_, _SHORT_SIGNAL_};
    int i;
    Timer_1_Start();
   
    if (Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC) clock++;
    
    for (i = 0; i < 23; i++) {
        sendMorseToComputer(beams[i]);
    }
    
    resetLed();
    clock = 0;
}

// Function to turn on all LEDs when you press on SW2
void pressSW2() {
    if (SW2_Read() != 0) {
        Timer_1_Start();

        if (Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC) clock++;

        turnLEDsOn(250);
        resetLed();
        clock = 0;
    }
}

// When you press on SW3
void pressSW3() {
    if (SW3_Read() != 0) {
        Timer_1_Start();

        if (Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC) clock++;

        turnLEDsOn(750);
        resetLed();
        clock = 0;
    }
}
    
void photoresistor() {
    if (ADC_IsEndConversion(ADC_RETURN_STATUS) != 0) {
        int32 value = ADC_GetResult32();
        
        if (value < 6500) { // pas de lumière 
           PWM_Stop();
           lightOn = 1;
        } else if(value > 6500) { // de la lumière 
           lightOn = 0;
           PWM_Start(); 
        }  
    }
}

// Keyboard function used to read 1,2 or *
void keyboard() { 
    uint8_t  value = keypadScan();
    char* message;
       
    while (value == '1' || value == '*' || value == '2')  {
        uint8_t value2 = keypadScan();
        AMux_FastSelect(0);
        photoresistor();

        if ((value == '1' && value2 == '*') || (value == '*' && value2 == '1')) {
            message = (char*) malloc(strlen("SOS"));
            sprintf(message, "SOS");
            displayMessage(&message);
            signalSOS();
            LCD_ClearDisplay();
            AMux_FastSelect(1);
            break;
        }
        
        if ((value == '2' && value2 == '*') || (value == '*' && value2 == '2')) {
            message = (char*) malloc(strlen("BEAMS"));
            sprintf(message, "BEAMS");
            displayMessage(&message);
            signalBEAMS();
            LCD_ClearDisplay();
            AMux_FastSelect(1);
            break;
        }
    }
}

void potentiometer() {
    if (ADC_IsEndConversion(ADC_RETURN_STATUS) > 0) {
        int32 value = ADC_GetResult32();
        float value_float = value / 7.9;
        
        if (flag == 0) {
            PWM_WriteCompare1(value_float);
        } else {
            PWM_WriteCompare2(value_float);
        }
    }
}

CY_ISR(UART_Handler) { 
    uint8_t status = 0;
    
    do { 
        // Checks if no UART Rx errors
        status = UART_ReadRxStatus(); 
        
        if ((status & UART_RX_STS_PAR_ERROR) | (status & UART_RX_STS_STOP_ERROR) | (status & UART_RX_STS_BREAK) | (status & UART_RX_STS_OVERRUN)) { // Parity , framing , break or overrun error 
            LCD_Position(1,0); 
            LCD_PrintString("UART err"); 
        } 
        
        // Check that rx buffer is not empty and get rx data 
        if ((status & UART_RX_STS_FIFO_NOTEMPTY) != 0) {
            rxData = UART_ReadRxData(); 
            LCD_Position(0,0);
            LCD_PrintString(&rxData);
        } 
    } while ((status & UART_RX_STS_FIFO_NOTEMPTY) != 0);
}



int main(void) {
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    for (i = 0; i < 100; i++) {
        signal[i] = sin((i * 2 * M_PI) / 100);
    }
    
    i = 0;
    isr_StartEx(Timer_Handler);
    pin_SW4_int_StartEx(SW4_Handler);
    isr1_StartEx(UART_Handler);
    Timer_Stop();
    
    UART_Start();
    UART_PutString("Start");
    UART_SetRxInterruptMode(UART_RX_STS_FIFO_NOTEMPTY);
    
    VDAC_Start();
    VDAC_SetValue(0);
    
    PWM_Start();
    PWM_WriteCompare1(7500);
    PWM_WriteCompare2(7500);
    
    ADC_Start();
    ADC_StartConvert();
    
    AMux_FastSelect(1);
    
    LCD_Start();
    
    resetLed();
    // reset servo
    
    CyDelay(1000);
    
    for (;;) {  
        if (rxData != _NULL){
            AMux_FastSelect(0);
            photoresistor();  
            test(rxData);  
            rxData = _NULL;
            LCD_ClearDisplay();
            AMux_FastSelect(1);  
        }
        
        pressSW1();
        pressSW2();
        pressSW3();  
        keyboard();
        potentiometer();
    }
}



/* [] END OF FILE */
