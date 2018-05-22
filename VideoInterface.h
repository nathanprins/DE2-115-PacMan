/*
 * VideoInterface.h
 *
 *  Created on: 21 May 2018
 *      Author: natha
 */

#ifndef VIDEOINTERFACE_H_
#define VIDEOINTERFACE_H_

#include <stdint.h>
#include <stdlib.h>
#include <math.h>

enum viLineAlg {
	DDA,
	BRESENHAM
};

class VideoInterface {
	public:
		VideoInterface(int width, int height, int scale);
		virtual void drawPixel(int x, int y) = 0;
		void setLineAlg(enum viLineAlg);
		void drawLine(int fx, int fy, int tx, int ty);
		void setColor(uint16_t color);
		void clear(uint16_t color);
	private:
		void _drawLineDDA(int x0, int y0, int x1, int y1);
		void _drawLineBRESENHAM(int x0, int y0, int x1, int y1);
		enum viLineAlg viLA;
	protected:
		uint16_t color;
		int width;
		int height;
		int scale;
};

#endif /* VIDEOINTERFACE_H_ */
