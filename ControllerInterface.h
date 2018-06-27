/*
 * Controller.h
 *
 *  Created on: 2 May 2018
 *      Author: natha
 */

#ifndef CONTROLLERINTERFACE_H_
#define CONTROLLERINTERFACE_H_

typedef enum {
	BUTTON_NO_BUTTON,
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_A,
	BUTTON_B,
	BUTTON_RESET,
	BUTTON_ENTER
} button_t;

class ControllerInterface {
	public:
		ControllerInterface();
		button_t getActiveButton();
		virtual void update() = 0;
	protected:
		button_t activeButton = BUTTON_NO_BUTTON;

};

#endif /* CONTROLLERINTERFACE_H_ */
