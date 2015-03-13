//------------------------------------------------------------------------------------------
//
//  recognizer/Recognizer.h
//
//  Created by Tong Tung Giang in 2015
//
#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include "Path.h"
#include "SampleGestures.h"

namespace recognizer
{
	class RecognizerResult
	{
	public:

		std::string name;
		double score;

		RecognizerResult(std::string name, double score)
			: name(name), score(score)
		{
		}
	};

	class Recognizer
	{

	private:

		const int numPointsInGesture = 128;
		const int squareSize = 250;
		const double halfDiagonal = 0.5 * sqrt((squareSize * squareSize) + (squareSize * squareSize));

		Path candidate;
		std::vector <Path> templates;

	public:

		void addTemplate(Path temp);
		void loadTemplates();

		double distanceAtAngle(Path candidate, Path templates, double angle);
		double distanceAtBestAngle(Path candidate, Path templates, 
			double angleA = 45.0, double angleB = 45.0, double angleDelta = 2.0);
		double pathDistance(Path path1, Path path2);
		Path normalizePath(Path points);

		RecognizerResult recognize();

	};
}

#endif