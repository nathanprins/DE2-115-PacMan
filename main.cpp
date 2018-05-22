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

//#include "PacMan.h"
//#include "Keyboard.h"
#include "VGA.h"

/* Definition of Task Stacks */
#define   TASK_STACKSIZE       2048
OS_STK    task1_stk[TASK_STACKSIZE];

/* Definition of Task Priorities */
#define TASK1_PRIORITY      1


void GameLoop(void* pdata);
void gfxLoop(void* pdata);

int main(void){

//	Keyboard Controls;
//	PacMan Game(&Controls);

	OSTaskCreate(gfxLoop,  (void*) 0, &task1_stk[TASK_STACKSIZE-1],  TASK1_PRIORITY);
//	OSTaskCreate(GameLoop,  (void*) 0, (void *)&task1_stk[TASK_STACKSIZE-1],  TASK1_PRIORITY);



	OSStart();
	return 0;
}

void gfxLoop(void* pdata){

	VGA vga((short*)0x08000000, 320, 240, 1);
	vga.clear(0);
	vga.setColor(0x187F);

	uint8_t clear = 0;

	while(1){
		vga.setColor(clear ? 0 : 0xFFFF);
		clear = clear ? 0 : 1;

		vga.drawLine(20, 100, 39, 100);
		OSTimeDlyHMSM(0, 0, 0, 100);
	}
}

//void GameLoop(void* pdata){
//	while (1){
//		Game.Loop();
//		OSTimeDlyHMSM(0, 0, 0, 100);
//	}
//}
