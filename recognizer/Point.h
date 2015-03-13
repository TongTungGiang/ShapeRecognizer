//------------------------------------------------------------------------------------------
//
//  recognizer/Point.h
//
//  Created by Tong Tung Giang in 2015
//

#ifndef POINT_H
#define POINT_H

namespace recognizer
{
	class Point
	{

	public:

		int x;  // Coordinate of the point in x axis
		int y;  // Coordinate of the point in y axis

	public:

		Point(int _x, int _y);
		double calculateDistance(Point anotherPoint);

		Point operator () (int _x, int _y);

	};
}

#endif