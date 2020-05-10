/* ========================================
 * ULB - Digital Electronic : Project 2020 
 * 
 * Mathias Hanquiniaux
 * Tanguy Snoeck
 * Vladimir Tulcinsky
 *
 * ========================================
*/

/*========================================
*
*	 Libraries Import
*
* ========================================
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "project.h"
#include "keypad.h"
#include "morse.h"
#include "semaphore.h"

/*========================================
*
*	 Variables initilization
*
* ========================================
*/

#define _LONG_SIGNAL_ '-'
#define _SHORT_SIGNAL_ '.'
#define _LETTER_SPACE_ '/'
#define _ELEMENT_SPACE_ ' '
#define _NEW_LINE_ '\n'

_Bool flag = 0;
_Bool pushSW4 = 0;
_Bool lightOn;
int clock = 0;
int i;
int32 adc_value;
float signal[100];
float adc_value_float;
char rxData;

/*========================================
*
* 		Methods declaration
*
* ========================================
*/

/*
* Interruption for Timer
* The sine wave is processed every 50 µs
*/
CY_ISR(Timer_Handler)  {
    float val = signal[i];
    VDAC_SetValue(val);
    i++;
    if (i == 100) i = 0;
    Timer_ReadStatusRegister();
}

/*
* Interruption for to detect when the user release button SW4
*/
CY_ISR(SW4_Handler) {
    flag =!flag;   
    SW4_ClearInterrupt();
}

/*
* Get the message to print on the first row of the LCD
*/
 void displayMessage(char** message) {
    LCD_Position(0,0);
    LCD_PrintString(*message);
}

/*
* Increment var 'clock' every 1 ms
*/
void checkTimerStatus() {
	if (Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC) clock++;
}

/*
* Get the state to light on or off all LEDs
*/
void ledsState(int state) {
    Led_1_Write(state);
    Led_2_Write(state);
    Led_3_Write(state);
    Led_4_Write(state);
}

/*
* Get time length and the state to start/stop sound and light on/off LEDs
*/
void activateSoundAndLEDS(int time, _Bool state) { 
    int actualClock = clock;
    if (state == 1) { // Start sound and light on LEDs
        Timer_Start();
    }
    do {
        checkTimerStatus();
        
        if (lightOn == 0 && state == 1) { // Start sound and light on LEDs
            ledsState(1);  
        }
        if (state == 0) { // Stop sound and light off LEDs
        	Timer_Stop();
        	ledsState(0);
        }
    } while(clock - actualClock < time); // For the period of time send to the method
}

/*
* Get the morse symbol to send to the computer by UART component in ASCII
*/
void UART_WriteChar(char symbol) { 
    switch (symbol)
    {
        case _SHORT_SIGNAL_: // .
            UART_PutChar(46);
            break;

        case _LONG_SIGNAL_: // -
            UART_PutChar(45);
            break;

        case _ELEMENT_SPACE_: // space between 2 elements of the same letter (only 1 space)
            UART_PutChar(32);
            break;
            
        case _LETTER_SPACE_: // space between 2 letters (3 spaces for a better visibility on Termite)
            for(int x = 0; x < 3; x++) {
                UART_PutChar(32);
            }
            break;
            
        case _NEW_LINE_: // \n (for a better visibility on Termite)
            UART_PutChar(10);
            break;
    }
}

/*
* Get the value to write/send 
*/
void switchMorseCode(char value) { 
    switch (value) {
        case _SHORT_SIGNAL_: 
        	activateSoundAndLEDS(250,1);
            UART_WriteChar(_SHORT_SIGNAL_);
            break;
            
        case _LONG_SIGNAL_:
            activateSoundAndLEDS(750,1);
            UART_WriteChar(_LONG_SIGNAL_);
            break;
            
        case _ELEMENT_SPACE_:
            activateSoundAndLEDS(250,0);   
            UART_WriteChar(_ELEMENT_SPACE_);
            break;
            
        case _LETTER_SPACE_:
            activateSoundAndLEDS(750,0);
            UART_WriteChar(_LETTER_SPACE_);
            break;
    }
}

/*
* Get all character from a morse code (dots,dashes and spaces) write it in ASCII
*/
void sendMorseToComputer(char value) { 
    Timer_1_Start();
   
    checkTimerStatus();
    
    char* morseCode = getMorse(value); // Get the signal duration for the given character
   UART_WriteChar(_NEW_LINE_);
    
    for (int x = 0; x < (int)strlen(morseCode); x++) { // Loop for the number of morse signal
        switchMorseCode(morseCode[x]); 
    }
    
    UART_WriteChar(_NEW_LINE_);
    ledsState(0);
    clock = 0;
}

/*
* Get the letter or word to translate in ASCII 
* @param word : word to translate in morse code
*/
void sendSignal(char* word) {
	Timer_1_Start();

	checkTimerStatus();

   	char *str = word;
	int len = strlen(str); // get length of word
	char *morse[len]; // variable to store complete morse translation (eg: sos => ...---...)
	char dest[20];  // variable to store translation of one letter (eg: s => ...)
    float value[len];
    for (int h = 0; h < len; ++h) { // for each letter of the word (eg: sos) get corresponding morse translation
        // morse[0] holds ...
        // morse[1] holds --- etc ...
        morse[h] = getMorse(str[h]);
		
		strcpy(dest, morse[h]); // copy translation of one letter (eg s => ...) in dest variable for looping through individual symbols of morse string
		for (int var = 0; var < (int) strlen(dest); ++var) { // for each symbol (. or -) activate leds and write to UART
			switchMorseCode(dest[var]);
		}
		switchMorseCode(_LETTER_SPACE_); // between each letter we add 3 spaces
	}
    if ( lightOn == 1) {
    	for (int j = 0; j < len; j++) {
                value[j] = getSemaphore(str[j]);
                uint16 value2 = value[j];
                if (flag == 0) {
                  PWM_WriteCompare1(value2);
                } else {
                  PWM_WriteCompare2(value2);
                }
                CyDelay(500);
        } 
    }
    ledsState(0);
	clock = 0;
}

/*
* Start sound and light on LEDs when SW1 is pushed
*/
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

/*
* Start sound and turn on all LEDs when you press on SW2 for 250ms
*/
void pushSW2() {
    if (SW2_Read() != 0) {
        Timer_1_Start();

        checkTimerStatus();

        activateSoundAndLEDS(250,1);
        ledsState(0);
        clock = 0;
    }
}

/*
* Start sound and turn on all LEDs when you press on SW3 for 750ms
*/
void pushSW3() {
    if (SW3_Read() != 0) {
        Timer_1_Start();

        checkTimerStatus();

        activateSoundAndLEDS(750,1);
        ledsState(0);
        clock = 0;
    }
}

/*
* Get the value of the photoresistor and choose to use LEDs or Semaphor Code
*/    
void photoResistor() {
    if (ADC_IsEndConversion(ADC_RETURN_STATUS) != 0) {
        int32 value = ADC_GetResult32();
        
        if (value < 6500) { // There is no enough light
           lightOn = 0;
        } else if(value > 6500) { // There is enough light
           lightOn = 1;
        }  
    }
}

/*
* Used to read 1,2 or * from the keyboard and send appropriate message
*/
void keyboard() { 
    uint8_t  value = keypadScan(); // Get the value from the keyboard
    char* message; 
       
    while (value == '1' || value == '*' || value == '2')  { // Check if user pressed on those values
        uint8_t value2 = keypadScan(); // Get the new value from the keyboard
        AMux_FastSelect(0); // Use photoresistor value
        photoResistor();

        if ((value == '1' && value2 == '*') || (value == '*' && value2 == '1')) { 
            message = (char*) malloc(strlen("SOS"));
            sprintf(message, "SOS");
            displayMessage(&message);
            sendSignal("sos");
            LCD_ClearDisplay(); 
            break;
        }
        
        if ((value == '2' && value2 == '*') || (value == '*' && value2 == '2')) { 
            message = (char*) malloc(strlen("BEAMS"));
            sprintf(message, "BEAMS");
            displayMessage(&message);
            sendSignal("beams");
            LCD_ClearDisplay();
            break;
        }
    }
    AMux_FastSelect(1); // Use potentiometer value
}

/*
* Get the value from potentiometer and activate appropriate servo
*/
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

/*
* UART interruption and get data from computer
*/
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


/*========================================
*
* 		Main function
*
* ========================================
*/
int main(void) {
	/*
	* Enable interrupts
	*/
    CyGlobalIntEnable; 
    isr_StartEx(Timer_Handler); 
    pin_SW4_int_StartEx(SW4_Handler);
    isr1_StartEx(UART_Handler);
	/*
	* Start components
	*/
    UART_Start();
    VDAC_Start();
    PWM_Start();
 	ADC_Start();
    ADC_StartConvert();
    LCD_Start();
    /*
	* Initialization of components/variables
	*/
    AMux_FastSelect(1); // Use potentiometer value
    VDAC_SetValue(0);
    PWM_WriteCompare1(7500);
    CyDelay(1000);
    PWM_WriteCompare2(7500);
    ledsState(0); 
    Timer_Stop();
    UART_PutString("Start \n");
    createArray();
    /*
	* Fill a vector with a sound wave
	*/
    for (i = 0; i < 100; i++) {
        signal[i] = sin((i * 2 * M_PI) / 100);
    }
    i = 0;
    
    for (;;) {  
        if (rxData != _NULL){ // If no data receive from computer
            AMux_FastSelect(0); // Use photoresistor value
            photoResistor();  
            sendMorseToComputer(rxData);  
            rxData = _NULL;
            LCD_ClearDisplay();
            AMux_FastSelect(1);  // Get back to use potentiometer value
        }
        
        pushSW1();
        pushSW2();
        pushSW3();  
        keyboard();
        potentiometer();
    }
}

/* [] END OF FILE */