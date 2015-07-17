//------------------------------------------------------------------------------------------
//
//  GeometricRecognizer.cpp
//
//  Created by Tong Tung Giang in 2015
//

#include "GeometricRecognizer.h"
#include <dirent.h>  // For reading files in a directory, using dirent-1.20.1
#include <fstream>
#include <string.h>

#define min(a, b) (a < b) ? a : b

namespace DollarRecognizer
{
	GeometricRecognizer::GeometricRecognizer(std::string path)
	{
		numPointsInGesture = 128;
		squareSize = 250;
		halfDiagonal = 0.5 * sqrt((250.0 * 250.0) + (250.0 * 250.0));
		setRotationInvariance(false);
		anglePrecision = 2.0;
		goldenRatio    = 0.5 * (-1.0 + sqrt(5.0));

		loadTemplates(path);
	}

	void GeometricRecognizer::loadTemplates(std::string path)
	{
		DIR *dir;
		struct dirent *ent;
		if ((dir = opendir(path.c_str())) != NULL)
		{
			while ((ent = readdir(dir)) != NULL)
			{
				if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
				{
					std::string fileName = TEMPLATE_PATH;
					fileName = fileName + ent->d_name;
					addTemplate(fileName.c_str());
				}
			}
			closedir(dir);
		}
		else
		{
			printf("Could not open the directory %s\n", path.c_str());
			exit(EXIT_FAILURE);
		}
	}

	void GeometricRecognizer::addTemplate(const char* fileName)
	{
		Path2D points;
		double x, y;
		char name[100];

		points.clear();

		ifstream ifs(fileName);

		if (!ifs)
		{
			std::cout << "Cannot open file " << fileName << std::endl;
			return;
		}

		ifs.getline(name, 100);
		while (ifs >> x >> y)
		{
			points.push_back(Point2D(x, y));
		}

		templates.push_back(GestureTemplate(name, points));
	}

	void GeometricRecognizer::addTemplate(string name, Path2D points)
	{
		points = normalizePath(points);

		templates.push_back(GestureTemplate(name, points));
	}

	Rectangle GeometricRecognizer::boundingBox(Path2D points)
	{
		double minX =  DBL_MAX;
		double maxX = -DBL_MAX;
		double minY =  DBL_MAX; 
		double maxY = -DBL_MAX;

		for (Path2DIterator i = points.begin(); i != points.end(); i++)
		{
			Point2D point = *i;
			if (point.x < minX)
				minX = point.x;
			if (point.x > maxX)
				maxX = point.x;
			if (point.y < minY)
				minY = point.y;
			if (point.y > maxY)
				maxY = point.y;
		}
		Rectangle bounds(minX, minY, (maxX - minX), (maxY - minY));
		return bounds;
	}

	Point2D GeometricRecognizer::centroid(Path2D points)
	{
		double x = 0.0, y = 0.0;
		for (Path2DIterator i = points.begin(); i != points.end(); i++)
		{
			Point2D point = *i;
			x += point.x;
			y += point.y;
		}
		x /= points.size();
		y /= points.size();
		return Point2D(x, y);
	}	

	double GeometricRecognizer::getDistance(Point2D p1, Point2D p2)
	{
		double dx = p2.x - p1.x;
		double dy = p2.y - p1.y;
		double distance = sqrt((dx * dx) + (dy * dy));
		return distance;
	}

	double GeometricRecognizer::distanceAtAngle(
		Path2D points, GestureTemplate aTemplate, double rotation)
	{
		Path2D newPoints = rotateBy(points, rotation);
		return pathDistance(newPoints, aTemplate.points);
	}	

	double GeometricRecognizer::distanceAtBestAngle(
		Path2D points, GestureTemplate aTemplate)
	{
		double startRange = -angleRange;
		double endRange   =  angleRange;
		double x1 = goldenRatio * startRange + (1.0 - goldenRatio) * endRange;
		double f1 = distanceAtAngle(points, aTemplate, x1);
		double x2 = (1.0 - goldenRatio) * startRange + goldenRatio * endRange;
		double f2 = distanceAtAngle(points, aTemplate, x2);
		while (abs(endRange - startRange) > anglePrecision)
		{
			if (f1 < f2)
			{
				endRange = x2;
				x2 = x1;
				f2 = f1;
				x1 = goldenRatio * startRange + (1.0 - goldenRatio) * endRange;
				f1 = distanceAtAngle(points, aTemplate, x1);
			}
			else
			{
				startRange = x1;
				x1 = x2;
				f1 = f2;
				x2 = (1.0 - goldenRatio) * startRange + goldenRatio * endRange;
				f2 = distanceAtAngle(points, aTemplate, x2);
			}
		}
		return min(f1, f2);
	}

	Path2D GeometricRecognizer::normalizePath(Path2D points)
	{
		/* Recognition algorithm from 
			http://faculty.washington.edu/wobbrock/pubs/uist-07.1.pdf
			Step 1: Resample the Point Path
			Step 2: Rotate Once Based on the "Indicative Angle"
			Step 3: Scale and Translate
			Step 4: Find the Optimal Angle for the Best Score
		*/
		points = resample(points);
		if (getRotationInvariance())
			points = rotateToZero(points);
		points = scaleToSquare(points);
		points = translateToOrigin(points);

		return points;
	}

	double GeometricRecognizer::pathDistance(Path2D pts1, Path2D pts2)
	{
		double distance = 0.0;
		for (int i = 0; i < (int)pts1.size(); i++) 
			distance += getDistance(pts1[i], pts2[i]);
		return (distance / pts1.size());
	}

	double GeometricRecognizer::pathLength(Path2D points)
	{
		double distance = 0;
		for (int i = 1; i < (int)points.size(); i++)
			distance += getDistance(points[i - 1], points[i]);
		return distance;
	}

	RecognitionResult GeometricRecognizer::recognize(Path2D points)
	{
		if (templates.empty())
		{
			std::cout << "No templates loaded so no symbols to match." << std::endl;
			return RecognitionResult("Unknown", NULL);
		}

		points = normalizePath(points);
	
		double bestDistance = DBL_MAX;
		int indexOfBestMatch = -1;

		for (int i = 0; i < (int)templates.size(); i++)
		{
			double distance = distanceAtBestAngle(points, templates[i]);
			if (distance < bestDistance)
			{
				bestDistance     = distance;
				indexOfBestMatch = i;
			}
		}

		double score = 1.0 - (bestDistance / halfDiagonal);

		if (-1 == indexOfBestMatch)
		{
			cout << "Couldn't find a good match." << endl;
			return RecognitionResult("Unknown", 1);
		}

		RecognitionResult bestMatch(templates[indexOfBestMatch].name, score);
		return bestMatch;
	};

	Path2D GeometricRecognizer::resample(Path2D points)
	{
		double interval = pathLength(points) / (numPointsInGesture - 1); // interval length
		double D = 0.0;
		Path2D newPoints;

		newPoints.push_back(points.front());
	    for(int i = 1; i < (int)points.size(); i++)
		{
			Point2D currentPoint  = points[i];
			Point2D previousPoint = points[i-1];
			double d = getDistance(previousPoint, currentPoint);
			if ((D + d) >= interval)
			{
				double qx = previousPoint.x + ((interval - D) / d) * (currentPoint.x - previousPoint.x);
				double qy = previousPoint.y + ((interval - D) / d) * (currentPoint.y - previousPoint.y);
				Point2D point(qx, qy);
				newPoints.push_back(point);
				points.insert(points.begin() + i, point);
				D = 0.0;
			}
			else D += d;
		}

		if (newPoints.size() == (numPointsInGesture - 1))
		{
			newPoints.push_back(points.back());
		}

		return newPoints;
	}

	Path2D GeometricRecognizer::rotateBy(Path2D points, double rotation) 
	{
		Point2D c     = centroid(points);
		double cosine = cos(rotation);	
		double sine   = sin(rotation);
		
		Path2D newPoints;
		for (Path2DIterator i = points.begin(); i != points.end(); i++)
		{
			Point2D point = *i;
			double qx = (point.x - c.x) * cosine - (point.y - c.y) * sine   + c.x;
			double qy = (point.x - c.x) * sine   + (point.y - c.y) * cosine + c.y;
			newPoints.push_back(Point2D(qx, qy));
		}
		return newPoints;
	}

	Path2D GeometricRecognizer::rotateToZero(Path2D points)
	{
		Point2D c = centroid(points);
		double rotation = atan2(c.y - points[0].y, c.x - points[0].x);
		return rotateBy(points, -rotation);
	}

	Path2D GeometricRecognizer::scaleToSquare(Path2D points)
	{
		DollarRecognizer::Rectangle box = boundingBox(points);
		Path2D newPoints;
		for (Path2DIterator i = points.begin(); i != points.end(); i++)
		{
			Point2D point = *i;
			double scaledX = point.x * (this->squareSize / box.width);
			double scaledY = point.y * (this->squareSize / box.height);
			newPoints.push_back(Point2D(scaledX, scaledY));
		}
		return newPoints;
	}

	void GeometricRecognizer::setRotationInvariance(bool ignoreRotation)
	{
		shouldIgnoreRotation = ignoreRotation;

		if (shouldIgnoreRotation)
		{
			angleRange = 45.0;
		}
		else
		{
			angleRange = 15.0;
		}
	}

	Path2D GeometricRecognizer::translateToOrigin(Path2D points)
	{
		Point2D c = centroid(points);
		Path2D newPoints;
		for (Path2DIterator i = points.begin(); i != points.end(); i++)
		{
			Point2D point = *i;
			double qx = point.x - c.x;
			double qy = point.y - c.y;
			newPoints.push_back(Point2D(qx, qy));
		}
		return newPoints;
	}
}
