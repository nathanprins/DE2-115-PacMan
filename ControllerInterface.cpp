/*
 * Controller.cpp
 *
 *  Created on: 2 May 2018
 *      Author: natha
 */

#include "ControllerInterface.h"

ControllerInterface::ControllerInterface(){

};

button_t ControllerInterface::getActiveButton(){
	button_t temp = this->activeButton;
	this->activeButton = BUTTON_NO_BUTTON;
	return temp;
};
