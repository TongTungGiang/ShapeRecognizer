//------------------------------------------------------------------------------------------
//
//  main.cpp
//
//  Created by Tong Tung Giang in 2015
//
#include <iostream>

#include "DollarRecognizer\GeometricRecognizer.h"

int main()
{
	DollarRecognizer::SampleGestures samp;
	DollarRecognizer::GeometricRecognizer rec;

	std::cout << rec.recognize(samp.getGestureDiamond()).name << std::endl;

	return 0;
}