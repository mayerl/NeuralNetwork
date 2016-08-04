//
//  Util.hpp
//  ShapeRecognition
//
//  Created by Mayer Levy on 7/27/16.
//  Copyright © 2016 Mayer Levy. All rights reserved.
//

#ifndef Util_hpp
#define Util_hpp

#include <stdio.h>
#include <vector>
#include <string>

class Util {
public:
	
	static std::vector<std::string> split(std::string &s, char delim);
	static double maximum( double a, double b, double c );
	static void getdir (std::string dir, std::vector<std::string> &files);
	static double median(std::vector<double>::iterator begin, std::vector<double>::iterator end);
	static int getKey();
	
};

#endif /* Util_hpp */
