//------------------------------------------------------------------------------------------
//
//  recognizer/Point.cpp
//
//  Created by Tong Tung Giang in 2015
//
#include "Point.h"
#include <math.h>

//------------------------------------------------------------------------------------------
// Class constructor
//
recognizer::Point::Point(int _x, int _y)
{
	x = _x;
	y = _y;
}

//------------------------------------------------------------------------------------------
// Calculate the distance between current point and another point
//
double recognizer::Point::calculateDistance(Point anotherPoint)
{
	double deltaX = (x - anotherPoint.x);
	double deltaY = (y - anotherPoint.y);

	return sqrt(deltaX * deltaX + deltaY * deltaY);
}

//------------------------------------------------------------------------------------------
// Overload the () operator - for more convinient use
//
recognizer::Point recognizer::Point::operator () (int _x, int _y)
{
	x = _x;
	y = _y;

	return Point(x, y);
}