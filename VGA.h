/*
 * VGA.h
 *
 *  Created on: 21 May 2018
 *      Author: natha
 */

#ifndef VGA_H_
#define VGA_H_

#include "VideoInterface.h"

class VGA: public VideoInterface {
	public:
		VGA(short* pixel_buffer, int width, int height, int scale);
		void drawPixel(int x, int y);

	private:
		short* pbuffer;
};

#endif /* VGA_H_ */
