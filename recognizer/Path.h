//------------------------------------------------------------------------------------------
//
//  recognizer/Path.h
//
//  Created by Tong Tung Giang in 2015
//

#ifndef PATH_H
#define PATH_H

#include <vector>
#include <string>
#include "Point.h"
#include "Rectangle.h"

namespace recognizer
{
	class Path
	{

	private:

		std::string name;
		std::vector <Point> points;

	public:

		Path(std::string name, std::vector <Point> points);
		Path();

		Path resample(Path points, int n);

		void append(Path points, Point newPoint);
		Point calculateCentroid(Path points);
		Rectangle calculateBoundingBox(Path points);
		double pathLength(Path points);
		Path rotateBy(Path points, double angle);
		Path rotateByZero(Path points);
		Path scaleToSquare(Path points, int size);
		Path translateToOrigin(Path points);

		std::string getName();
		std::vector <Point> getPoints();

	};
}

#endif