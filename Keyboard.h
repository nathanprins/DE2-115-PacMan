/*
 * Keyboard.h
 *
 *  Created on: 2 May 2018
 *      Author: natha
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "ControllerInterface.h"

#include "altera_up_avalon_ps2.h"
#include <stdio.h>

class Keyboard: public ControllerInterface {
	public:
		Keyboard();
		void update();

	private:
		alt_up_ps2_dev *PS2_dev;
		unsigned char byte1, byte2, byte3;
		unsigned char PS2_data;
};

#endif /* KEYBOARD_H_ */
