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
#include "MorseTrans.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define _LONG_SIGNAL_ '-'
#define _SHORT_SIGNAL_ '.'
#define _LETTER_SPACE_ '/'
#define _ELEMENT_SPACE_ ' '
#define _NEW_LINE_ '\n'

int static i;
float static signal[100];
int clock=0;
int clock2=0;
_Bool flag = 0;
_Bool pushSW4 = 0;
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

void ledsState(int state) {
    Led_1_Write(state);
    Led_2_Write(state);
    Led_3_Write(state);
    Led_4_Write(state);
}

void turnLEDsOn(int length) { //cette fonction allume les leds? 
    int actualClock = clock;
    Timer_Start();
    
    do {
        if (Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC) clock++;
        
        if (lightOn == 1) {
            ledsState(1);  
        }
    } while(clock - actualClock < length);
}

void turnLEDsOff(int length) { // cette fonction éteint les leds ?
    int actualClock = clock;
    
    do {
        if (Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC) clock++;  
        Timer_Stop();
        ledsState(0);  
    } while(clock - actualClock < length);
}


void UART_WriteChar(char symbol) {
    switch (symbol)
    {
        case _SHORT_SIGNAL_:
            UART_PutChar(46);
            break;

        case _LONG_SIGNAL_:
            UART_PutChar(45);
            break;

        case _ELEMENT_SPACE_:
            UART_PutChar(32);
            break;
            
        case _LETTER_SPACE_:
            for(int x = 0; x < 3; x++) {
                UART_PutChar(32);
            }
            break;
            
        case _NEW_LINE_:
            UART_PutChar(10);
            break;
    }
}
// il y a surement moyen de fusionner les deux prochaines méthodes.

void switchMorseCode(char value) { // cette fonction envoie le signal morse vers le pc ?
    switch (value) {
        case _SHORT_SIGNAL_: 
            turnLEDsOn(250);
            UART_WriteChar(_SHORT_SIGNAL_);
            break;
            
        case _LONG_SIGNAL_:
            turnLEDsOn(750);
            UART_WriteChar(_LONG_SIGNAL_);
            break;
            
        case _ELEMENT_SPACE_:
            turnLEDsOff(250);   
            UART_WriteChar(_ELEMENT_SPACE_);
            break;
            
        case _LETTER_SPACE_:
            turnLEDsOff(750); 
            UART_WriteChar(_LETTER_SPACE_);
            break;
    }
}

void sendMorseToComputer(char value) { 
    Timer_1_Start();
   
    if (Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC) clock++;
    
    char* morseCode = getMorse(value);
    UART_WriteChar(_NEW_LINE_);
    
    for (int x = 0; x < (int)strlen(morseCode); x++) {
        switchMorseCode(morseCode[x]);
    }
    
    UART_WriteChar(_NEW_LINE_);
    ledsState(0);
    clock = 0;
}

void sendSignal(char* word) {
	Timer_1_Start();

	if (Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC) clock++;

   	char *str = word;
	int len = strlen(str);
	char *morse[len];
	char dest[20];
	for (int i = 0; i < len; ++i) {
		morse[i] = getMorse(str[i]);
		strcpy(dest, morse[i]);
		for (int var = 0; var < (int) strlen(dest); ++var) {
			switchMorseCode(dest[var]);
		}
		switchMorseCode(_LETTER_SPACE_);

	}
    ledsState(0);
	clock = 0;
}

void pushSW1()
{
    if( SW1_Read() != 0) { // When the SW1 is pressed
        ledsState(1);
        Timer_Start();
    } else { //  When the SW1 isn't pressed
        ledsState(0);
        Timer_Stop();
    }
}

// Function to turn on all LEDs when you press on SW2
void pushSW2() {
    if (SW2_Read() != 0) {
        Timer_1_Start();

        if (Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC) clock++;

        turnLEDsOn(250);
        ledsState(0);
        clock = 0;
    }
}

// When you press on SW3
void pushSW3() {
    if (SW3_Read() != 0) {
        Timer_1_Start();

        if (Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC) clock++;

        turnLEDsOn(750);
        ledsState(0);
        clock = 0;
    }
}
    
void photoResistor() {
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
        photoResistor();

        if ((value == '1' && value2 == '*') || (value == '*' && value2 == '1')) {
            message = (char*) malloc(strlen("SOS"));
            sprintf(message, "SOS");
            displayMessage(&message);
            sendSignal("sos");
            LCD_ClearDisplay();
            AMux_FastSelect(1);
            break;
        }
        
        if ((value == '2' && value2 == '*') || (value == '*' && value2 == '2')) {
            message = (char*) malloc(strlen("BEAMS"));
            sprintf(message, "BEAMS");
            displayMessage(&message);
            sendSignal("beams");
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
    UART_PutString("Start \n");
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
    
    ledsState(0);
    // reset servo
    
    CyDelay(1000);
    
    for (;;) {  
        if (rxData != _NULL){
            AMux_FastSelect(0);
            photoResistor();  
            sendMorseToComputer(rxData);  
            rxData = _NULL;
            LCD_ClearDisplay();
            AMux_FastSelect(1);  
        }
        
        pushSW1();
        pushSW2();
        pushSW3();  
        keyboard();
        potentiometer();
    }
}



/* [] END OF FILE */