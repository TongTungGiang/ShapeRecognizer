//------------------------------------------------------------------------------------------
//
//  recognizer/Rectangle.h
//
//  Created by Tong Tung Giang in 2015
//
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Point.h"

namespace recognizer
{
	class Rectangle
	{

	public:

		Point min;
		Point max;

	public:

		Rectangle(Point _min, Point _max);

		int getWidth();
		int getHeight();

	};
}

#endif