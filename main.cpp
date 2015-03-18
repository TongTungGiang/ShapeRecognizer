//------------------------------------------------------------------------------------------
//
//  main.cpp
//
//  Created by Tong Tung Giang in 2015
//
#include <iostream>

#include "recognizer\Recognizer.h"

int main()
{
	recognizer::Recognizer rec;
	recognizer::SampleGestures samp;

	rec.setCandidate(samp.getGestureDiamond());
	std::cout << rec.recognize().name;

	return 0;
}