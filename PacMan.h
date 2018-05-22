/*
 * PacMan.h
 *
 *  Created on: 2 May 2018
 *      Author: natha
 */

#ifndef PACMAN_H_
#define PACMAN_H_

#include "ControllerInterface.h"

class PacMan {
	public:
		PacMan(ControllerInterface& control);
		void Loop();
	private:
		ControllerInterface& _control;
};

#endif /* PACMAN_H_ */
