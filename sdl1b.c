#include <stdio.h>
#include <time.h> //include for random nums
#include <stdlib.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH   1024
#define SCREEN_HEIGHT  576

// Define the mighty cow as something drawable @ some x,y-coordinate:
typedef struct _koe_ {
	int x;
	int y;
} koe;

void process_input(koe *koetje);
void proper_shutdown(void);
void koe_offset(koe *array);//spawn 10 more cows
void onze_greta(koe array);//spawn greta


SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;


//offsets fast geleged voor greta

#define lijf_offset (SDL_Rect) {array.x, array.y, 32, 32}
#define kop_offset (SDL_Rect) {array.x + 8, array.y - 16, 16, 16}
#define staart_offset (SDL_Rect) {array.x + 14, array.y + 32, 4, 4}
#define linkervoorpoot_offset (SDL_Rect) {array.x - 6, array.y + 4, 6, 6}
#define rechtervoorpoot_offset (SDL_Rect) {array.x + 32, array.y + 4, 6, 6}
#define linkerachterpoot_offset (SDL_Rect) {array.x - 6, array.y + 24, 6, 6}
#define rechterachterpoot_offset (SDL_Rect) {array.x + 32, array.y + 24, 6, 6}



int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	srand(time(NULL));
	
	// Spawn Greta in the middle of the window:
	koe greta = {(SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2)};

	//een array van andere 10 nbc koeien
	koe koeien[10] = {{(SCREEN_WIDTH / 1.2),(SCREEN_HEIGHT / 8)},
					   {(SCREEN_WIDTH / 5),(SCREEN_HEIGHT / 4)},
					   {(SCREEN_WIDTH / 3),(SCREEN_HEIGHT / 2)},
					   {(SCREEN_WIDTH / 4),(SCREEN_HEIGHT / 1.2)},
					   {(SCREEN_WIDTH / 5),(SCREEN_HEIGHT / 1.4)},
					   {(SCREEN_WIDTH / 6),(SCREEN_HEIGHT / 1.5)},
					   {(SCREEN_WIDTH / 7),(SCREEN_HEIGHT / 1.7)},
					   {(SCREEN_WIDTH / 1.7),(SCREEN_HEIGHT / 8)},
					   {(SCREEN_WIDTH / 9),(SCREEN_HEIGHT / 3)},
					   {(SCREEN_WIDTH / 1.5),(SCREEN_HEIGHT / 6)}};
	
	
	unsigned int window_flags = 0;
	unsigned int renderer_flags = SDL_RENDERER_ACCELERATED;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	window = SDL_CreateWindow("All your grass are belong to Greta", SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 
		window_flags);
	if (window == NULL)
	{
		printf("Failed to create window -- Error: %s\n",
			SDL_GetError());
		exit(1);
	}
	
	renderer = SDL_CreateRenderer(window, -1, renderer_flags);
	if (renderer == NULL) // error handling:
	{
		printf("Failed to create renderer -- Error: %s\n",
			SDL_GetError());
		exit(1);
	}
	
	while (1)
	{
		// Refresh the backbuffer to its original state:
		// RGB (39, 174, 96) should be a green grass color
		SDL_SetRenderDrawColor(renderer, 39, 174, 96, 255);
		SDL_RenderClear(renderer);
		// Process selected inputs and pay close attention to moving
		// our freshly spawned cow:
		process_input(&greta);

		//spawn the rest of the cows:
		koe_offset(koeien);
		//spawn greta the great
		onze_greta(greta);

		
		// Render redrawn scene to front buffer, showing it in the 
		// actual window:
		SDL_RenderPresent(renderer);
		// Remember ~ 60 FPS of smooth Greta movements - PC Master Race!
		SDL_Delay(16);
	}

	return 0;
}

void process_input(koe *koetje)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				proper_shutdown();
				exit(0);
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode)
				{
					case SDL_SCANCODE_ESCAPE:
						proper_shutdown();
						exit(0);
						break;
					case SDL_SCANCODE_RIGHT:
						koetje->x += 4;
						break;
					case SDL_SCANCODE_LEFT:
						koetje->x -= 4;
						break;
					case SDL_SCANCODE_UP:
						koetje->y -= 4;
						break;
					case SDL_SCANCODE_DOWN:
						koetje->y += 4;
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
}

void proper_shutdown(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//function die neemt de array van de 10 koeien als argument en spawned ze op de scherm:
void koe_offset(koe *array){

	int r = rand() % 255;  // Random value tussen 0 and 255 voor Red
    int g = rand() % 255;  // Random value tussen 0 and 255 for Green
    int b = rand() % 255;  // Random value tussen 0 and 255 for Blue


	for (int i = 0; i < 10; i++)
	{
		SDL_Rect lijf1 = {array[i].x, array[i].y, 32, 32};
		SDL_Rect kop1 = {array[i].x + 8, array[i].y - 16, 16, 16};
		SDL_Rect staart1 = {array[i].x + 14, array[i].y + 32, 4, 4};
		SDL_Rect linkervoorpoot1 = {array[i].x - 6, array[i].y + 4, 6, 6};
		SDL_Rect rechtervoorpoot1 = {array[i].x + 32, array[i].y + 4, 6, 6};
		SDL_Rect linkerachterpoot1 = {array[i].x - 6, array[i].y + 24, 6, 6};
		SDL_Rect rechterachterpoot1 = {array[i].x + 32, array[i].y + 24, 6, 6};

		// hier maak ik alle koeien RGB BECAUSE - PC Master Race!
		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		// Redraw alle 10 koeien in de backbuffer naar hun updated location:
		SDL_RenderFillRect(renderer, &lijf1);
		SDL_RenderFillRect(renderer, &kop1);
		SDL_RenderFillRect(renderer, &staart1);
		SDL_RenderFillRect(renderer, &linkervoorpoot1);
		SDL_RenderFillRect(renderer, &rechtervoorpoot1);
		SDL_RenderFillRect(renderer, &linkerachterpoot1);
		SDL_RenderFillRect(renderer, &rechterachterpoot1);
	}

}

void onze_greta(koe array){


	SDL_Rect lijf = lijf_offset;
	SDL_Rect kop = kop_offset;
	SDL_Rect staart = staart_offset;
	SDL_Rect linkervoorpoot = linkervoorpoot_offset;
	SDL_Rect rechtervoorpoot = rechtervoorpoot_offset;
	SDL_Rect linkerachterpoot = linkerachterpoot_offset;
	SDL_Rect rechterachterpoot = rechterachterpoot_offset;


				
	// RGB (135, 54, 0) should be a brown fur color for Greta
	SDL_SetRenderDrawColor(renderer, 135, 54, 0, 255);
	// Redraw Grata in the backbuffer to her updated location:
	SDL_RenderFillRect(renderer, &lijf);
	SDL_RenderFillRect(renderer, &kop);
	SDL_RenderFillRect(renderer, &staart);
	SDL_RenderFillRect(renderer, &linkervoorpoot);
	SDL_RenderFillRect(renderer, &rechtervoorpoot);
	SDL_RenderFillRect(renderer, &linkerachterpoot);
	SDL_RenderFillRect(renderer, &rechterachterpoot);

}


//===============================================================================================



/*

 * File:   main.c

 * Author: Sourav Gupta

 *

 * Created on 18 Dec 2018, 18:57

 */

 

/*

 * Configuration Related settings. Specific for microcontroller unit.

 */

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)

#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)

#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)

#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)

#pragma config LVP = OFF         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)

#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)

#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)

#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 20000000

/*

 * System Header files inclusions

 */

 

#include <xc.h>

//#include <string.h>

#include <stdlib.h>

#include "supporting c files/lcd.h"

 

#define Encoder_SW PORTDbits.RD2

#define Encoder_DT PORTDbits.RD3

#define Encoder_CLK PORTCbits.RC4

 

/*

 * Program flow related functions

 */

int counter; // It will hold the count of rotary encoder.

int position; // It will store the rotary encoder position.

void sw_delayms(unsigned int d);

int value[7];

 

/*

 * System Init Function

 */

 

void system_init ();

 

/* Main function single Thread*/

void main(void) {

    system_init();

    lcd_puts ("Circuit Digest");

    lcd_com(0xC0);

    counter = 0;

    while(1){

        lcd_com(0xC0);

        if (Encoder_SW == 0){

            sw_delayms(20);

            if (Encoder_SW == 0){

                //lcd_com(1);

                //lcd_com(0xC0);

                lcd_puts ("switch pressed");

//                itoa(counter, value, 10);

//                lcd_puts(value);

            }

        }                       

       if (Encoder_CLK != position){

            if (Encoder_DT != position){

               // lcd_com (0x01);

                counter++;

                lcd_com (0xC0);

                lcd_puts("                ");

                lcd_com (0xC0);

                lcd_bcd(1,counter);

            }

            else{

               // lcd_com (0x01);

                lcd_com (0xC0);

                counter--;

                lcd_puts("                ");

                lcd_com (0xC0);

                lcd_bcd(1,counter);

                //lcd_puts("Left");

            }           

        }

        position = Encoder_CLK;                

 

}

 

    return;

}

 

void sw_delayms(unsigned int d){

int x, y;

for(x=0;x<d;x++)

for(y=0;y<=1275;y++);

}

 

void system_init(){

    TRISB = 0x00; // PORT B as output, This port is used for LCD    

    TRISDbits.TRISD2 = 1;

    TRISDbits.TRISD3 = 1;

    TRISCbits.TRISC4 = 1;

    lcd_init(); // This will Initialize the LCD

    position = Encoder_CLK;// Sotred the CLK position on system init, before the while loop start.

}

//===============================================================================================================

#include <xc.h>

// Configuration settings for the PIC16F887
#pragma config FOSC = HS    // High-speed crystal oscillator
#pragma config WDTE = OFF   // Watchdog timer disabled
#pragma config PWRTE = OFF  // Power-up timer disabled
#pragma config BOREN = OFF  // Brown-out reset disabled
#pragma config LVP = OFF    // Low-voltage programming disabled
#pragma config CPD = OFF    // Data memory code protection disabled
#pragma config WRT = OFF    // Flash memory write protection disabled
#pragma config CP = OFF     // Flash memory code protection disabled

#define ENCODER_A RB4
#define ENCODER_B RB5

#define LED1 RA0
#define LED2 RA1
#define LED3 RA2
#define LED4 RA3

volatile unsigned char encoderValue = 0; // Encoder value
volatile unsigned char prevEncoderState = 0; // Previous encoder state

void main() {
    TRISB = 0b00110000; // Set RB4 and RB5 as inputs
    TRISA = 0b00000000; // Set all RA pins as outputs

    while (1) {
        // Read the current state of RB4 and RB5 (the encoder channels)
        unsigned char currentEncoderState = (PORTB >> 4) & 0x03;

        // Determine the direction of rotation
        if (currentEncoderState != prevEncoderState) {
            if ((prevEncoderState == 0x00 && currentEncoderState == 0x01) || (prevEncoderState == 0x03 && currentEncoderState == 0x02)) {
                encoderValue++;
            } else if ((prevEncoderState == 0x01 && currentEncoderState == 0x00) || (prevEncoderState == 0x02 && currentEncoderState == 0x03)) {
                encoderValue--;
            }
        }

        // Update the previous state
        prevEncoderState = currentEncoderState;

        // Control the LEDs based on the encoder value
        LED1 = (encoderValue & 0x01) ? 1 : 0;
        LED2 = (encoderValue & 0x02) ? 1 : 0;
        LED3 = (encoderValue & 0x04) ? 1 : 0;
        LED4 = (encoderValue & 0x08) ? 1 : 0;

        // Your main code here

        // You can use the LEDs (LED1, LED2, LED3, LED4) to display the encoder value or any other status.
    }
}
