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

	private:
		void _internalDrawPixel(int x, int y, uint16_t color);
		short* pbuffer;
};

#endif /* VGA_H_ */
