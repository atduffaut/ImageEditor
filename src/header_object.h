#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct headerObject {
	char IDlength;
	char colorMap;
	char imageType;

	short colorMapOrigin;
	short colorMapLength;
	char colorMapDepth;

	short x;
	short y;
	short width;
	short height;
	char pixelDepth;
	char imageDescriptor;
};
