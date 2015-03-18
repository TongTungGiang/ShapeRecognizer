//------------------------------------------------------------------------------------------
//
//  recognizer/Path.cpp
//
//  Created by Tong Tung Giang in 2015
//
#include "Path.h"

//------------------------------------------------------------------------------------------
// Class constructor
//
recognizer::Path::Path(std::string _name, std::vector <Point> _points)
{
	name = _name;
	points = _points;
}

//------------------------------------------------------------------------------------------
// Class default constructor: everything is empty
//
recognizer::Path::Path()
{
	name = "";
	points.clear();
}

//------------------------------------------------------------------------------------------
// Returns current path's name
//
std::string recognizer::Path::getName()
{
	return name;
}

//------------------------------------------------------------------------------------------
// Returns current path's point set (points)
//
std::vector <recognizer::Point> recognizer::Path::getPoints()
{
	return points;
}

//------------------------------------------------------------------------------------------
// Calculates the length of the path 
//
double recognizer::Path::pathLength(Path points)
{
	int n = points.getPoints().size();
	double len = 0.0;
	for (int i = 0; i < n - 1; i++)
		len += points.getPoints().at(i).calculateDistance(points.getPoints().at(i + 1));

	return len;
}

//------------------------------------------------------------------------------------------
// Finds the centroid of the path 
//
recognizer::Point recognizer::Path::calculateCentroid(Path points)
{
	int centroidX = 0, centroidY = 0;
	int n = points.getPoints().size();

	for (int i = 0; i < n; i++)
	{
		centroidX += points.getPoints().at(i).x;
		centroidY += points.getPoints().at(i).y;
	}

	return Point(centroidX / n, centroidY / n);
}

//------------------------------------------------------------------------------------------
// Finds the bounding box of the path
//
recognizer::Rectangle recognizer::Path::calculateBoundingBox(Path points)
{
	int minX = points.getPoints().at(0).x;
	int minY = points.getPoints().at(0).y;
	int maxX = minX;
	int maxY = minY;
	int n = points.getPoints().size();

	for (int i = 1; i < n; i++)
	{
		int x = points.getPoints().at(i).x;
		int y = points.getPoints().at(i).y;

		if (x < minX)
			minX = x;
		if (x > maxX)
			maxX = x;

		if (y < minY)
			minY = y;
		if (y > maxY)
			maxY = y;
	}

	return Rectangle(Point(minX, minY), Point(maxX, maxY));
}

//------------------------------------------------------------------------------------------
// Adds a new point to the path
//
void recognizer::Path::append(Point newPoint)
{
	points.push_back(newPoint);
}

//------------------------------------------------------------------------------------------
// Rotates the path by an angle
//
recognizer::Path recognizer::Path::rotateBy(Path points, double angle)
{
	Point centroid = points.calculateCentroid(points);
	double cosine = cos(angle);
	double sine = sin(angle);
	int n = points.getPoints().size();

	Path newPoints;

	for (int i = 0; i < n; i++)
	{
		Point tmp = points.getPoints().at(i);
		double qx = 
			(tmp.x - centroid.x) * cosine -
			(tmp.y - centroid.y) * sine +
			centroid.x;
		double qy =
			(tmp.x - centroid.x) * sine +
			(tmp.y - centroid.y) * cosine +
			centroid.y;
		newPoints.append(Point((int) qx, (int) qy));
	}

	return newPoints;
}

//------------------------------------------------------------------------------------------
// Rotates the path so that the indicative angle is 0
//
recognizer::Path recognizer::Path::rotateByZero(Path points)
{
	Point centroid = points.calculateCentroid(points);
	int n = points.getPoints().size();

	double theta = atan2(
		(double) centroid.y - points.getPoints().at(0).y,
		(double) centroid.x - points.getPoints().at(0).x);

	return rotateBy(points, -theta);
}

//------------------------------------------------------------------------------------------
// Scales the path to the reference square
//
recognizer::Path recognizer::Path::scaleToSquare(Path points, int size)
{
	Path newPoints;

	Rectangle box = points.calculateBoundingBox(points);
	int n = points.getPoints().size();

	for (int i = 0; i < n; i++)
	{
		Point p = points.getPoints().at(i);
		int x = p.x * (size / box.getWidth());
		int y = p.y * (size / box.getHeight());
		Point q(x, y);

		newPoints.append(q);
	}

	return newPoints;
}

//------------------------------------------------------------------------------------------
// Translates the path to the origin
//
recognizer::Path recognizer::Path::translateToOrigin(Path points)
{
	Path newPoints;

	Point centroid = points.calculateCentroid(points);
	int n = points.getPoints().size();

	for (int i = 0; i < n; i++)
	{
		Point p = points.getPoints().at(i);
		Point q(p.x - centroid.x, p.y - centroid.y);
		newPoints.append(q);
	}

	return newPoints;
}

//------------------------------------------------------------------------------------------
// Resamples the path (pick n points from original path)
//
recognizer::Path recognizer::Path::resample(Path points, int n)
{
	double interval = pathLength(points) / (n - 1);
	double D = 0.0;
	int pointNumber = points.getPoints().size();

	// initializes the new path called newPoints which is the result of this function
	Path newPoints;
	newPoints.append(points.getPoints().front());

	for (int i = 1; i < pointNumber; i++)
	{
		Point current = points.getPoints()[i];
		Point prev = points.getPoints()[i - 1];
		double d = current.calculateDistance(prev);
		if ((D + d) >= interval)
		{
			double tmp = ((interval - D) / d);
			int qx = prev.x + (int)(tmp * (current.x - prev.x));
			int qy = prev.y + (int)(tmp * (current.y - prev.y));

			newPoints.append(Point(qx, qy));
			newPoints.getPoints().insert(points.getPoints().begin() + i,
				Point(qx, qy));
			D = 0.0;
	}	
		else D += d;
	}

	if (newPoints.getPoints().size() == (n - 1))
		newPoints.append(points.getPoints().back());

	return newPoints;
}