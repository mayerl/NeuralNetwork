//
//  Util.cpp
//  ShapeRecognition
//
//  Created by Mayer Levy on 7/27/16.
//  Copyright © 2016 Mayer Levy. All rights reserved.
//

#include "Util.hpp"

#include <sstream>
#include <iostream>
#include <cmath>
#include <iterator>


double Util::maximum( double a, double b, double c )
{
	double max = ( a < b ) ? b : a;
	return ( ( max < c ) ? c : max );
}

double Util::median(std::vector<double>::iterator begin, std::vector<double>::iterator end) {
	
	int size = (int)std::distance(begin, end);
	double med = 0;
	if (size % 2 == 0) {
		std::advance(begin, (int)size/2 - 1);
		std::advance(end, -((int)size/2 - 1));
		med = (*begin + *end) / 2;
	} else {
		std::advance(begin, (int)floor(size/2));
		med = *begin;
	}
	
	return med;
	
}


std::vector<std::string> Util::split(std::string &s, char delim) {
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> tokens;
	while (std::getline(ss, item, delim)) {
		tokens.push_back(item);
	}
	return tokens;
}

#ifdef _WIN32

#include <windows.h>
#include <conio.h>

int Util::getdir(std::string dir, std::vector<std::string> &files)
{
	std::string search_path = dir + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				files.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	
	return 0;
}

int Util::getKey() {
	int key;
	key = _getch();
	return key;
}

#else

#include <dirent.h>
#include <unistd.h>
#include <termios.h>

int Util::getdir (std::string dir, std::vector<std::string> &files)
{
	DIR *dp;
	struct dirent *dirp;
	if((dp  = opendir(dir.c_str())) == NULL) {
		std::cout << "Error(" << errno << ") opening " << dir << std::endl;
		return errno;
	}
	
	while ((dirp = readdir(dp)) != NULL) {
		files.push_back(std::string(dirp->d_name));
	}
	closedir(dp);
	
	return 0;
}

int Util::getKey() {
	int key;
	struct termios oldt, newt;
	tcgetattr(STDIN_FILENO, &oldt); // 1473
	memcpy((void *)&newt, (void *)&oldt, sizeof(struct termios));
	newt.c_lflag &= ~(ICANON);  // Reset ICANON
	newt.c_lflag &= ~(ECHO);    // Echo off, after these two .c_lflag = 1217
	tcsetattr(STDIN_FILENO, TCSANOW, &newt); // 1217
	key = getchar(); // works like "getch()"
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return key;
}

#endif