//------------------------------------------------------------------------------------------
//
//  GestureTemplate.h
//
//  Created by Tong Tung Giang in 2015
//
#ifndef GESTURETEMPLATE_H
#define GESTURETEMPLATE_H

#include <string>

using namespace std;

namespace DollarRecognizer
{
class GestureTemplate
{
public:
	string name;
	Path2D points;
	
	GestureTemplate(string name, Path2D points)
	{
		this->name   = name;
		this->points = points;
	}
};

typedef vector<GestureTemplate> GestureTemplates;
}

#endif