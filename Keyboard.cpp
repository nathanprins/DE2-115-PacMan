/*
 * Keyboard.cpp
 *
 *  Created on: 2 May 2018
 *      Author: natha
 */

#include "Keyboard.h"

Keyboard::Keyboard(){
	this->PS2_dev = alt_up_ps2_open_dev ("/dev/PS2_Port");
	if (this->PS2_dev == NULL)
		printf("Error: could not open PS2 device\n");
	else
		printf("Opened PS2 device\n");

	alt_up_ps2_write_data_byte (this->PS2_dev, 0xFF);
	alt_up_ps2_enable_read_interrupt(this->PS2_dev);

	byte1 = 0, byte2 = 0, byte3 = 0;
};

void Keyboard::update(){
	while(alt_up_ps2_read_data_byte (PS2_dev, &PS2_data) == 0)
	{
		/* shift the next data byte into the display */
		byte1 = byte2;
		byte2 = byte3;
		byte3 = PS2_data;

		//printf("%d-%d-%d \n\r", byte1, byte2, byte3);
		if(byte2 == 224 && byte3 == 107)
			this->activeButton = BUTTON_LEFT;
		if(byte2 == 224 && byte3 == 117)
			this->activeButton = BUTTON_UP;
		if(byte2 == 224 && byte3 == 116)
			this->activeButton = BUTTON_RIGHT;
		if(byte2 == 224 && byte3 == 114)
			this->activeButton = BUTTON_DOWN;
//		if(byte2 == 41 && byte3 == 41) // SPACE
//			pm->setDir(DIR_NO_DIR);
	}
};
