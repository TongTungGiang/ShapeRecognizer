//------------------------------------------------------------------------------------------
//
//  recognizer/Rectangle.cpp
//
//  Created by Tong Tung Giang in 2015
//
#include "Rectangle.h"

//------------------------------------------------------------------------------------------
// Class constructor
//
recognizer::Rectangle::Rectangle(Point _min, Point _max)
	: min(_min), max(_max)
{
	// empty body
}

//------------------------------------------------------------------------------------------
// Calculates the width of the rectangle
//
int recognizer::Rectangle::getWidth()
{
	return max.x - min.x;
}

//------------------------------------------------------------------------------------------
// Calculates the height of the rectangle
//
int recognizer::Rectangle::getHeight()
{
	return max.y - min.y;
}