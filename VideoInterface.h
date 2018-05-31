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
		void drawPixel(int x, int y);
		void drawPixel(int x, int y, uint16_t color);
		void drawRect(int x, int y, int width, int height);
		void drawRect(int x, int y, int width, int height, uint16_t color);
		void setLineAlg(enum viLineAlg);
		void drawLine(int fx, int fy, int tx, int ty);
		void drawLine(int fx, int fy, int tx, int ty, uint16_t color);
		void setColor(uint16_t color);
		void clear(uint16_t color);
	private:
		virtual void _internalDrawPixel(int x, int y, uint16_t color) = 0;
		void _drawLineDDA(int x0, int y0, int x1, int y1, uint16_t color);
		void _drawLineBRESENHAM(int x0, int y0, int x1, int y1, uint16_t color);
		enum viLineAlg viLA;
	protected:
		uint16_t color;
		int width;
		int height;
		int scale;
};

#endif /* VIDEOINTERFACE_H_ */
