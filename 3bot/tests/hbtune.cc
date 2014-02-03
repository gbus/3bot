#include "../src/hbridgelib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <ncurses.h>
#include <string.h>

// GPIO output pins
#define GPIO_M1_IN1             17      // Right wheel
#define GPIO_M1_IN2             27
#define GPIO_M2_IN3             18      // Left wheel
#define GPIO_M2_IN4             23
// Motor speed control (pwm)
#define PWM_CH_M1_ENA           12
#define PWM_CH_M2_ENB           13


int main()
{       
	int lm,rm;
        HBridge hb(     GPIO_M1_IN1, GPIO_M1_IN2, GPIO_M2_IN3, GPIO_M2_IN4,
                        PWM_CH_M1_ENA, PWM_CH_M2_ENB );

        initscr();

	printw("enter value of left and right motors:"); scanw("%d %d",&lm,&rm); 
	printw("Set new PWM values: %d %d\n",lm,rm);
	hb.PWMtuning(FW, lm, rm);

        getch();                        /* Wait for user input */
	
	hb.stopPlatform();
        endwin();                       /* End curses mode                */

        return 0;
}

