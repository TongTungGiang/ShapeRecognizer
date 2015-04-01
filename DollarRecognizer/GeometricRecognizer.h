//------------------------------------------------------------------------------------------
//
//  GeometricRecognizer.h
//
//  Created by Tong Tung Giang in 2015
//
#ifndef GEOMETRICRECOGNIZER_H
#define GEOMETRICRECOGNIZER_H

#define TEMPLATE_PATH "resources/templates/"

#include <limits>
#include <iostream>
#include "GeometricRecognizerTypes.h"
#include "GestureTemplate.h"

using namespace std;

namespace DollarRecognizer
{
	class GeometricRecognizer
	{
	private:

		double halfDiagonal;
		double angleRange;
		double anglePrecision;
		double goldenRatio;

		int numPointsInGesture;
		int squareSize;
		
		bool shouldIgnoreRotation;
		GestureTemplates templates;

	public:
		GeometricRecognizer(std::string path);

		void addTemplate(string name, Path2D points);
		void addTemplate(const char* fileName);

		DollarRecognizer::Rectangle boundingBox(Path2D points);
		Point2D centroid(Path2D points);
		double getDistance(Point2D p1, Point2D p2);
		bool   getRotationInvariance() { return shouldIgnoreRotation; }
		double distanceAtAngle(
			Path2D points, GestureTemplate aTemplate, double rotation);
		double distanceAtBestAngle(Path2D points, GestureTemplate T);
		Path2D normalizePath(Path2D points);
		double pathDistance(Path2D pts1, Path2D pts2);
		double pathLength(Path2D points);
		RecognitionResult recognize(Path2D points);
		Path2D resample(Path2D points);
		Path2D rotateBy(Path2D points, double rotation);
		Path2D rotateToZero(Path2D points);
		Path2D scaleToSquare(Path2D points);
		void   setRotationInvariance(bool ignoreRotation);
		Path2D translateToOrigin(Path2D points);

		void loadTemplates();
		void loadTemplates(std::string path);
	};
}

#endif