/*
 * Controller.h
 *
 *  Created on: 2 May 2018
 *      Author: natha
 */

#ifndef CONTROLLERINTERFACE_H_
#define CONTROLLERINTERFACE_H_

class ControllerInterface {
	public:
		ControllerInterface();
		void getActiveButton();
		virtual void update() = 0;
	private:


};

#endif /* CONTROLLERINTERFACE_H_ */
