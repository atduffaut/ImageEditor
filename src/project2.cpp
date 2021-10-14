#include <iostream>
#include <vector>
#include <fstream>
#include "header_object.h"
#include <sstream>
#include "pixel.h"
using namespace std;


vector <Pixel> multiply(vector <Pixel>& topLayer, vector <Pixel>& bottomLayer) {
	vector <Pixel> multiplied;
	Pixel pixel = Pixel();
	for (unsigned long int i = 0; i < topLayer.size(); i++) {
		pixel.blue = (topLayer[i].blue * bottomLayer[i].blue / 255.0f) + 0.5f;
		pixel.green = (topLayer[i].green * bottomLayer[i].green / 255.0f) + 0.5f;
		pixel.red = (topLayer[i].red * bottomLayer[i].red / 255.0f) + 0.5f;
		multiplied.push_back(pixel);
	}


	return multiplied;
}

vector <Pixel> subtract(vector <Pixel>& topLayer, vector <Pixel>& bottomLayer) {
	vector <Pixel> subtracted;
	Pixel pixel = Pixel();
	for (unsigned long int i = 0; i < topLayer.size(); i++) {
		if ((int)bottomLayer[i].blue - (int)topLayer[i].blue < 0) {
			pixel.blue = 0;
		}
		else {
			pixel.blue = bottomLayer[i].blue - topLayer[i].blue + 0.5f;
		}
		if ((int)bottomLayer[i].green - (int)topLayer[i].green < 0) {
			pixel.green = 0;
		}
		else {
			pixel.green = bottomLayer[i].green - topLayer[i].green + 0.5f;
		}
		if ((int)bottomLayer[i].red - (int)topLayer[i].red < 0) {
			pixel.red = 0;
		}
		else {
			pixel.red = bottomLayer[i].red - topLayer[i].red + 0.5f;
		}
		subtracted.push_back(pixel);
	}
	return subtracted;
}

vector <Pixel> screen(vector <Pixel>& topLayer, vector <Pixel>& bottomLayer) {
	vector <Pixel> screened;
	Pixel pixel = Pixel();
	for (unsigned long int i = 0; i < topLayer.size(); i++) {
		pixel.blue = 255.0f - ((255.0f - topLayer[i].blue) * (255.0f - bottomLayer[i].blue) / 255.0f) + 0.5f;
		pixel.green = 255.0f - ((255.0f - topLayer[i].green) * (255.0f - bottomLayer[i].green) / 255.0f) + 0.5f;
		pixel.red = 255.0f - ((255.0f - topLayer[i].red) * (255.0f - bottomLayer[i].red) / 255.0f) + 0.5f;
		screened.push_back(pixel);
	}
	return screened;
}

vector <Pixel> overlay(vector <Pixel>& topLayer, vector <Pixel>& bottomLayer) {
	vector <Pixel> overlayed;
	Pixel pixel = Pixel();
	for (unsigned long int i = 0; i < topLayer.size(); i++) {
		if (bottomLayer[i].blue <= 127.5f) {
			if (((2 * bottomLayer[i].blue * topLayer[i].blue) / 255.0f + 0.5f) > 255) {
				pixel.blue = 255;
			}
			else {
				pixel.blue = ((2 * bottomLayer[i].blue * topLayer[i].blue) / 255.0f + 0.5f);

			}
		}
		else {
			if ((255.0f - (2 * ((255 - topLayer[i].blue) * (255 - bottomLayer[i].blue) / 255.0f)) + 0.5f) < 0) {
				pixel.blue = 0;
			}
			else {
				pixel.blue = (255.0f - (2 * ((255 - topLayer[i].blue) * (255 - bottomLayer[i].blue) / 255.0f)) + 0.5f);
			}
		}
		if (bottomLayer[i].green <= 127.5f) {
			if (((2 * bottomLayer[i].green * topLayer[i].green) / 255.0f + 0.5f) > 255) {
				pixel.green = 255;
			}
			else {
				pixel.green = ((2 * bottomLayer[i].green * topLayer[i].green) / 255.0f + 0.5f);

			}
		}
		else {
			if ((255.0f - (2 * ((255 - topLayer[i].green) * (255 - bottomLayer[i].green) / 255.0f)) + 0.5f) < 0) {
				pixel.green = 0;
			}
			else {
				pixel.green = (255.0f - (2 * ((255 - topLayer[i].green) * (255 - bottomLayer[i].green) / 255.0f)) + 0.5f);

			}
		}
		if (bottomLayer[i].red <= 127.5f) {
			if (((2 * bottomLayer[i].red * topLayer[i].red + 0.5f)) / 255.0f > 255) {
				pixel.red = 255;
			}
			else {
				pixel.red = ((2 * bottomLayer[i].red * topLayer[i].red) / 255.0f + 0.5f);

			}
		}
		else {
			if ((255.0f - (2 * ((255 - topLayer[i].red) * (255 - bottomLayer[i].red) / 255.0f)) + 0.5f) < 0) {
				pixel.red = 0;
			}
			else {
				pixel.red = (255.0f - (2 * ((255 - topLayer[i].red) * (255 - bottomLayer[i].red) / 255.0f)) + 0.5f);

			}
		}
		overlayed.push_back(pixel);
	}
	return overlayed;
}

vector <Pixel> addGreen(vector <Pixel>& pixels, int number) {
	vector <Pixel> added;
	Pixel pixel = Pixel();
	for (unsigned long int i = 0; i < pixels.size(); i++) {
		if ((int)pixels[i].green + number > 255) {
			pixel.blue = pixels[i].blue;
			pixel.green = 255;
			pixel.red = pixels[i].red;
		}
		else {
			pixel.blue = pixels[i].blue;
			pixel.green = pixels[i].green + number;
			pixel.red = pixels[i].red;
		}
		added.push_back(pixel);
	}
	return added;
}

vector <Pixel> scaleRed(vector <Pixel>& pixels, float scaleFactor) {
	vector <Pixel> scaled;
	Pixel pixel = Pixel();
	for (unsigned long int i = 0; i < pixels.size(); i++) {
		if (pixels[i].red * scaleFactor > 255) {
			pixel.blue = pixels[i].blue;
			pixel.green = pixels[i].green;
			pixel.red = 255;
		}
		else {
			pixel.blue = pixels[i].blue;
			pixel.green = pixels[i].green;
			pixel.red = pixels[i].red * scaleFactor + 0.5f;
		}
		scaled.push_back(pixel);
	}
	return scaled;
}

vector <Pixel> scaleBlue(vector <Pixel>& pixels, float scaleFactor) {
	vector <Pixel> scaled;
	Pixel pixel = Pixel();
	for (unsigned long int i = 0; i < pixels.size(); i++) {
		if (pixels[i].red * scaleFactor > 255) {
			pixel.blue = 255;
			pixel.green = pixels[i].green;
			pixel.red = pixels[i].red;
		}
		else {
			pixel.blue = pixels[i].blue * scaleFactor + 0.5f;
			pixel.green = pixels[i].green;
			pixel.red = pixels[i].red;
		}
		scaled.push_back(pixel);
	}
	return scaled;
}

vector <Pixel> combine(vector <Pixel>& blue, vector <Pixel>& green, vector <Pixel>& red) {
	vector <Pixel> combined;
	Pixel pixel = Pixel();
	for (unsigned long int i = 0; i < red.size(); i++) {
		pixel.blue = blue[i].blue;
		pixel.green = green[i].green;
		pixel.red = red[i].red;
		combined.push_back(pixel);
	}
	return combined;
}

vector <Pixel> flip(vector <Pixel>& pixels) {
	vector <Pixel> flipped;
	Pixel pixel = Pixel();
	for (unsigned long int i = 0; i < pixels.size(); i++) {
		pixel.blue = pixels[pixels.size() - 1 - i].blue;
		pixel.green = pixels[pixels.size() - 1 - i].green;
		pixel.red = pixels[pixels.size() - 1 - i].red;
		flipped.push_back(pixel);
	}
	return flipped;
}

void testImages(vector <Pixel>& pixel1, vector <Pixel>& pixel2, string testname) {
	cout << "Testing images for " << testname << "..." << endl;
	for (unsigned long int i = 0; i < pixel1.size(); i++) {
		if (pixel1[i].blue != pixel2[i].blue) {
			cout << "Blues dont match here: " << i << endl;
			cout << "True blue: " << pixel2[i].blue << endl;
			cout << "My blue: " << pixel1[i].blue << endl;
		}
		if (pixel1[i].green != pixel2[i].green) {
			cout << "Greens don't match here: " << i << endl;
			cout << "True green: " << pixel2[i].green << endl;
			cout << "My green: " << pixel1[i].green << endl;
		}
		if (pixel1[i].red != pixel2[i].red) {
			cout << "Reds don't match here: " << i << endl;
			cout << "True red: " << pixel2[i].red << endl;
			cout << "My red: " << pixel1[i].red << endl;
		}
	}
	cout << "If you see no other messages, this test passed!" << endl;
}

void readFile(string filename, headerObject &header, vector <Pixel>& pixels) {
	ifstream inFile(filename, ios_base::binary);
	inFile.read(&header.IDlength, sizeof(header.IDlength));
	inFile.read(&header.colorMap, sizeof(header.colorMap));
	inFile.read(&header.imageType, sizeof(header.imageType));
	inFile.read((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
	inFile.read((char*)&header.colorMapLength, sizeof(header.colorMapLength));
	inFile.read(&header.colorMapDepth, sizeof(header.colorMapDepth));
	inFile.read((char*)&header.x, sizeof(header.x));
	inFile.read((char*)&header.y, sizeof(header.y));

	// we really only need width and height, the others don't matter
	inFile.read((char*)&header.width, sizeof(header.width));
	inFile.read((char*)&header.height, sizeof(header.height));


	inFile.read(&header.pixelDepth, sizeof(header.pixelDepth));
	inFile.read(&header.imageDescriptor, sizeof(header.imageDescriptor));

	
	//read byte data
	long arraySize;
	arraySize = header.width * header.height * 3;
	char* bytes = new char[arraySize];
	for (long i = 0; i < arraySize; i++) {
		inFile.read(&bytes[i], 1);
	}
	
	//convert byte data to pixel objects
	Pixel pixel = Pixel();
	for (long i = 0; i < arraySize; i+=3) {
		pixel.blue = bytes[i];
		pixel.green = bytes[i + 1];
		pixel.red = bytes[i + 2];
		pixels.push_back(pixel);
	}

	delete[] bytes;
}

void writeFile(string filename, headerObject& header, vector <Pixel>& pixels) {
	ofstream outfile(filename, ios_base::binary);
	outfile.write(&header.IDlength, sizeof(header.IDlength));
	outfile.write(&header.colorMap, sizeof(header.colorMap));
	outfile.write(&header.imageType, sizeof(header.imageType));
	outfile.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
	outfile.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
	outfile.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
	outfile.write((char*)&header.x, sizeof(header.x));
	outfile.write((char*)&header.y, sizeof(header.y));
	outfile.write((char*)&header.width, sizeof(header.width));
	outfile.write((char*)&header.height, sizeof(header.height));
	outfile.write(&header.pixelDepth, sizeof(header.pixelDepth));
	outfile.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

	// here we will write out the actual image data
	for (unsigned long int i = 0; i < pixels.size(); i++) {
		outfile.write((char*)&pixels[i].blue, 1);
		outfile.write((char*)&pixels[i].green, 1);
		outfile.write((char*)&pixels[i].red, 1);
	}
}

void writeRed(string filename, headerObject& header, vector <Pixel>& pixels) {
	ofstream outfile(filename, ios_base::binary);
	outfile.write(&header.IDlength, sizeof(header.IDlength));
	outfile.write(&header.colorMap, sizeof(header.colorMap));
	outfile.write(&header.imageType, sizeof(header.imageType));
	outfile.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
	outfile.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
	outfile.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
	outfile.write((char*)&header.x, sizeof(header.x));
	outfile.write((char*)&header.y, sizeof(header.y));
	outfile.write((char*)&header.width, sizeof(header.width));
	outfile.write((char*)&header.height, sizeof(header.height));
	outfile.write(&header.pixelDepth, sizeof(header.pixelDepth));
	outfile.write(&header.imageDescriptor, sizeof(header.imageDescriptor));


	//write out only the red channel of the image
	for (unsigned long int i = 0; i < pixels.size(); i++) {
		outfile.write((char*)&pixels[i].red, 1);
		outfile.write((char*)&pixels[i].red, 1);
		outfile.write((char*)&pixels[i].red, 1);
	}
}

void writeGreen(string filename, headerObject& header, vector <Pixel>& pixels) {
	ofstream outfile(filename, ios_base::binary);
	outfile.write(&header.IDlength, sizeof(header.IDlength));
	outfile.write(&header.colorMap, sizeof(header.colorMap));
	outfile.write(&header.imageType, sizeof(header.imageType));
	outfile.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
	outfile.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
	outfile.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
	outfile.write((char*)&header.x, sizeof(header.x));
	outfile.write((char*)&header.y, sizeof(header.y));
	outfile.write((char*)&header.width, sizeof(header.width));
	outfile.write((char*)&header.height, sizeof(header.height));
	outfile.write(&header.pixelDepth, sizeof(header.pixelDepth));
	outfile.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

	//write out only the green channel of the image
	for (unsigned long int i = 0; i < pixels.size(); i++) {
		outfile.write((char*)&pixels[i].green, 1);
		outfile.write((char*)&pixels[i].green, 1);
		outfile.write((char*)&pixels[i].green, 1);
	}
}

void writeBlue(string filename, headerObject& header, vector <Pixel>& pixels) {
	ofstream outfile(filename, ios_base::binary);
	outfile.write(&header.IDlength, sizeof(header.IDlength));
	outfile.write(&header.colorMap, sizeof(header.colorMap));
	outfile.write(&header.imageType, sizeof(header.imageType));
	outfile.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
	outfile.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
	outfile.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
	outfile.write((char*)&header.x, sizeof(header.x));
	outfile.write((char*)&header.y, sizeof(header.y));
	outfile.write((char*)&header.width, sizeof(header.width));
	outfile.write((char*)&header.height, sizeof(header.height));
	outfile.write(&header.pixelDepth, sizeof(header.pixelDepth));
	outfile.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

	//write out only the blue channel of the image
	for (unsigned long int i = 0; i < pixels.size(); i++) {
		outfile.write((char*)&pixels[i].blue, 1);
		outfile.write((char*)&pixels[i].blue, 1);
		outfile.write((char*)&pixels[i].blue, 1);
	}
}

int main() {
	headerObject header;

	// here we define all the pixel vectors for the input files
	vector <Pixel> car;
	vector <Pixel> circles;
	vector <Pixel> layer_blue;
	vector <Pixel> layer_green;
	vector <Pixel> layer_red;
	vector <Pixel> layer1;
	vector <Pixel> layer2;
	vector <Pixel> pattern1;
	vector <Pixel> pattern2;
	vector <Pixel> text;
	vector <Pixel> text2;

	// define all the output files pixel vectors
	vector <Pixel> part1;
	vector <Pixel> ex1;
	vector <Pixel> part2;
	vector <Pixel> ex2;
	vector <Pixel> part3;
	vector <Pixel> ex3;
	vector <Pixel> part4;
	vector <Pixel> ex4;
	vector <Pixel> part5;
	vector <Pixel> ex5;
	vector <Pixel> part6;
	vector <Pixel> ex6;
	vector <Pixel> part7;
	vector <Pixel> ex7;
	vector <Pixel> part8_r;
	vector <Pixel> part8_g;
	vector <Pixel> part8_b;
	vector <Pixel> ex8_r;
	vector <Pixel> ex8_g;
	vector <Pixel> ex8_b;
	vector <Pixel> part9;
	vector <Pixel> ex9;
	vector <Pixel> part10;
	vector <Pixel> ex10;
	
	// reading files into pixel vectors for part 1
	readFile("input/layer1.tga", header, layer1);
	readFile("input/pattern1.tga", header, pattern1);
	
	//perform desired operation on loaded files
	part1 = multiply(layer1, pattern1);
	
	// here we will write out the header data into tga files
	writeFile("output/part1.tga", header, part1);

	//test files for part 1:
	readFile("examples/EXAMPLE_part1.tga", header, ex1);
	testImages(part1, ex1, "Part 1");
	

	// now we read the files we need for part 2
	readFile("input/layer2.tga", header, layer2);
	readFile("input/car.tga", header, car);

	// perform desired operation on loaded files
	part2 = subtract(layer2, car);

	//write out file after operation
	writeFile("output/part2.tga", header, part2);

	//test files for part 2:
	readFile("examples/EXAMPLE_part2.tga", header, ex2);
	testImages(part2, ex2, "Part 2");

	//read files for part 3 (layer1 already loaded)
	readFile("input/pattern2.tga", header, pattern2);

	// perform desired operation on files
	part3 = multiply(layer1, pattern2);

	//read another file (part 2 of part3)
	readFile("input/text.tga", header, text);

	//perform another operation
	part3 = screen(text, part3);

	//write out final file
	writeFile("output/part3.tga", header, part3);

	//test files for part 3:
	readFile("examples/EXAMPLE_part3.tga", header, ex3);
	testImages(part3, ex3, "Part 3");


	// read the files needed for part 4
	readFile("input/circles.tga", header, circles);

	//perform desired operations
	part4 = multiply(layer2, circles);
	part4 = subtract(pattern2, part4);

	//write out final file
	writeFile("output/part4.tga", header, part4);

	//testing files for part 4:
	readFile("examples/EXAMPLE_part4.tga", header, ex4);
	testImages(part4, ex4, "Part 4");


	//read files needed for part 5
	//(they're already read)

	//perform the desired operations
	part5 = overlay(layer1, pattern1);

	//write out the new file
	writeFile("output/part5.tga", header, part5);

	//test files for part 5:
	readFile("examples/EXAMPLE_part5.tga", header, ex5);
	testImages(part5, ex5, "Part 5");


	//now read the files for part 6
	//(car is already loaded)

	//perform desired operations
	part6 = addGreen(car, 200);

	//write out the new file
	writeFile("output/part6.tga", header, part6);

	//test files for part 6:
	readFile("examples/EXAMPLE_part6.tga", header, ex6);
	testImages(part6, ex6, "Part 6");


	//read the files for part 7
	//(car is already loaded)

	//perform desired operations:
	part7 = scaleRed(car, 4);
	part7 = scaleBlue(part7, 0);

	//write out the new file
	writeFile("output/part7.tga", header, part7);

	//testing files for part 7
	readFile("examples/EXAMPLE_part7.tga", header, ex7);
	testImages(part7, ex7, "Part 7");


	//reading files for part 8
	//(car file is already loaded)

	//perform the desired operations:
	//this happens to be writing out all the desired files too

	writeRed("output/part8_r.tga", header, car);
	writeGreen("output/part8_g.tga", header, car);
	writeBlue("output/part8_b.tga", header, car);

	//test the files for part 8
	readFile("output/part8_r.tga", header, part8_r);
	readFile("output/part8_g.tga", header, part8_g);
	readFile("output/part8_b.tga", header, part8_b);
	readFile("examples/EXAMPLE_part8_r.tga", header, ex8_r);
	readFile("examples/EXAMPLE_part8_g.tga", header, ex8_g);
	readFile("examples/EXAMPLE_part8_b.tga", header, ex8_b);
	testImages(part8_r, ex8_r, "Part 8 Red");
	testImages(part8_g, ex8_g, "Part 8 Green");
	testImages(part8_b, ex8_b, "Part 8 Blue");


	//now load the files for part 9
	readFile("input/layer_blue.tga", header, layer_blue);
	readFile("input/layer_green.tga", header, layer_green);
	readFile("input/layer_red.tga", header, layer_red);

	//perform the desired operation
	part9 = combine(layer_blue, layer_green, layer_red);

	//write out the new file
	writeFile("output/part9.tga", header, part9);

	//test files for part 9:
	readFile("examples/EXAMPLE_part9.tga", header, ex9);
	testImages(part9, ex9, "Part 9");


	//load files for part 10
	readFile("input/text2.tga", header, text2);

	//perform desired operation:
	part10 = flip(text2);

	//write out new file
	writeFile("output/part10.tga", header, part10);

	//test images for part 10
	readFile("examples/EXAMPLE_part10.tga", header, ex10);
	testImages(part10, ex10, "Part 10");

}


