/*************************************************************************
* Copyright (c) 2004 Altera Corporation, San Jose, California, USA.      *
* All rights reserved. All use of this software and documentation is     *
* subject to the License Agreement located at the end of this file below.*
**************************************************************************
* Description:                                                           *
* The following is a simple hello world program running MicroC/OS-II.The * 
* purpose of the design is to be a very simple application that just     *
* demonstrates MicroC/OS-II running on NIOS II.The design doesn't account*
* for issues such as checking system call return codes. etc.             *
*                                                                        *
* Requirements:                                                          *
*   -Supported Example Hardware Platforms                                *
*     Standard                                                           *
*     Full Featured                                                      *
*     Low Cost                                                           *
*   -Supported Development Boards                                        *
*     Nios II Development Board, Stratix II Edition                      *
*     Nios Development Board, Stratix Professional Edition               *
*     Nios Development Board, Stratix Edition                            *
*     Nios Development Board, Cyclone Edition                            *
*   -System Library Settings                                             *
*     RTOS Type - MicroC/OS-II                                           *
*     Periodic System Timer                                              *
*   -Know Issues                                                         *
*     If this design is run on the ISS, terminal output will take several*
*     minutes per iteration.                                             *
**************************************************************************/


#include <stdio.h>
#include "includes.h"

#include "Game.h"
#include "Keyboard.h"
#include "PacMan.h"
#include "VGA.h"
#include "nios2_ctrl_reg_macros.h"
#include <string.h>

/* Definition of Task Stacks */
#define   TASK_STACKSIZE       4096
OS_STK    task1_stk[TASK_STACKSIZE];
OS_STK    task2_stk[TASK_STACKSIZE];
OS_STK    task3_stk[TASK_STACKSIZE];

/* Definition of Task Priorities */
#define TASK1_PRIORITY      1
#define TASK2_PRIORITY      2
#define TASK3_PRIORITY      3

void JTAG(const char* str)
{
	volatile int * JTAG_UART_ptr 	= (int *) 0x10001000;
	int control = *(JTAG_UART_ptr + 1);
	while(*(str)){
		if (control & 0xFFFF0000)
			*(JTAG_UART_ptr) = *(str++);
	}
}

void GameLoop(void* pdata);
void gfxLoop(void* pdata);
void inputLoop(void* pdata);

int main(void){
	JTAG("Starting App\r\n");

	VGA vga((short*)0x08000000, 320, 240, 1);
	Keyboard kb;
	Game game(&kb, &vga);

	OSTaskCreate(GameLoop, (void*) &game, &task3_stk[TASK_STACKSIZE-1],  TASK1_PRIORITY);
	OSTaskCreate(gfxLoop,  (void*) &game, &task1_stk[TASK_STACKSIZE-1],  TASK2_PRIORITY);
	OSTaskCreate(inputLoop,(void*) &kb, &task2_stk[TASK_STACKSIZE-1],  TASK3_PRIORITY);

	OSStart();
	return 0;
}

void gfxLoop(void* pdata){
	JTAG("GFX Started\r\n");

	Game* game = (Game*) pdata;
	while(1){
		game->draw();
		OSTimeDlyHMSM(0, 0, 0, 100);
	}
}

void inputLoop(void* pdata){
	JTAG("Input polling started \r\n");

	Keyboard* kb = (Keyboard*) pdata;


	while(1)
	{
		kb->update();
		OSTimeDlyHMSM(0, 0, 0, 100);
	}
}

void GameLoop(void* pdata){
	Game* game = (Game*) pdata;

	while (1)
	{
		game->update(100);
		OSTimeDlyHMSM(0, 0, 0, 100);
	}
}
