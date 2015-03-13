//------------------------------------------------------------------------------------------
//
//  recognizer/Recognizer.cpp
//
//  Created by Tong Tung Giang in 2015
//
#include "Recognizer.h"
#include <iostream>
#include <limits>

#define min(a, b) (a<b)?a:b

//------------------------------------------------------------------------------------------
// Calculats the path-distance between two paths
//
double recognizer::Recognizer::pathDistance(Path path1, Path path2)
{
	double distance = 0.0;
	int n = path1.getPoints().size();

	for (int i = 0; i < n; i++)
	{
		distance += path1.getPoints().at(i).calculateDistance(
			path2.getPoints().at(i));
	}

	return distance / n;
}

//------------------------------------------------------------------------------------------
// Calculats the path-distance between two paths at the angle "angle"
//
double recognizer::Recognizer::distanceAtAngle(
	Path candidate,
	Path templates, double angle)
{
	Path newPoints = candidate.rotateBy(candidate, angle);
	double distance = pathDistance(newPoints, templates);
	return distance;
}

//------------------------------------------------------------------------------------------
// Calculats the path-distance between two paths at the best angle possible
//
double recognizer::Recognizer::distanceAtBestAngle(
	Path candidate, Path templates, 
	double angleA, double angleB, double angleDelta
	)
{
	const double phi = 0.5 * (-1 + sqrt(5));
	double
		x1 = phi * angleA + (1 - phi) * angleB,
		f1 = distanceAtAngle(candidate, templates, x1),
		x2 = (1 - phi) * angleA + phi * angleB,
		f2 = distanceAtAngle(candidate, templates, x2);

	while (abs(angleB - angleA) > angleDelta)
	{
		if (f1 < f2)
		{
			angleB = x2;
			x2 = x1;
			f2 = f1;
			x1 = phi * angleA + (1 - phi) * angleB;
			f1 = distanceAtAngle(candidate, templates, x1);
		}
		else
		{
			angleA = x1;
			x1 = x2;
			f1 = f2;
			x2 = (1 - phi) * angleA + phi * angleB;
			f2 = distanceAtAngle(candidate, templates, x2);
		}
	}

	return min(f1, f2);
}

//------------------------------------------------------------------------------------------
// Normalizes the path: resamples it with N points from original M points, 
// scales it to the reference square, then rotates and translates
//
recognizer::Path recognizer::Recognizer::normalizePath(Path points)
{
	Path result = points.resample(points, numPointsInGesture);
	result = points.scaleToSquare(points, squareSize);
	result = points.rotateByZero(points);
	result = points.translateToOrigin(points);

	return result;
}

//------------------------------------------------------------------------------------------
// Recognizes
//
recognizer::RecognizerResult recognizer::Recognizer::recognize()
{
	if (templates.empty())
	{
		std::cout << "No templates!\n";
		return RecognizerResult("Unknown", NULL);
	}

	Path points = normalizePath(candidate);
	double bestDistance = DBL_MAX;
	int indexOfBestMatch = -1;

	for (int i = 0; i < templates.size(); i++)
	{
		double distance = distanceAtBestAngle(points, templates[i]);
		if (distance < bestDistance)
		{
			bestDistance = distance;
			indexOfBestMatch = i;
		}
	}

	double score = 1.0 - (bestDistance / halfDiagonal);
	if (-1 == indexOfBestMatch)
	{
		std::cout << "Couldn't find a good match.\n";
		return RecognizerResult("Unknown", 1);
	}

	RecognizerResult bestMatch(templates.at(indexOfBestMatch).getName(), score);
	return bestMatch;
}

//------------------------------------------------------------------------------------------
// Adds new template to current library
//
void recognizer::Recognizer::addTemplate(recognizer::Path newTemplate)
{
	newTemplate = normalizePath(newTemplate);
	templates.push_back(newTemplate);
}

//------------------------------------------------------------------------------------------
// Creates template library
//
void recognizer::Recognizer::loadTemplates()
{
	SampleGestures samples;

	addTemplate(samples.getGestureArrow());
	addTemplate(samples.getGestureCaret());
	addTemplate(samples.getGestureCheckMark());
	addTemplate(samples.getGestureCircle());
	addTemplate(samples.getGestureDelete());
	addTemplate(samples.getGestureDiamond());
	addTemplate(samples.getGestureLeftCurlyBrace());
	addTemplate(samples.getGestureLeftSquareBracket());
	addTemplate(samples.getGestureLeftToRightLine());
	addTemplate(samples.getGestureLineDownDiagonal());
	addTemplate(samples.getGesturePigtail());
	addTemplate(samples.getGestureQuestionMark());
	addTemplate(samples.getGestureRectangle());
	addTemplate(samples.getGestureRightCurlyBrace());
	addTemplate(samples.getGestureRightSquareBracket());
	addTemplate(samples.getGestureRightToLeftLine());
	addTemplate(samples.getGestureRightToLeftSlashDown());
	addTemplate(samples.getGestureSpiral());
	addTemplate(samples.getGestureStar());
	addTemplate(samples.getGestureTriangle());
	addTemplate(samples.getGestureV());
	addTemplate(samples.getGestureX());
}