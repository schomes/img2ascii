#include "image.h"
#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>

Image::Image() {

}

Image::~Image() {

}

void Image::readImage(const char *path) {
	readImagePPM(path);
}

void Image::readImagePPM(const char *path) {
	std::ifstream inputFile(path);
	if (inputFile.is_open()) {

		std::string line = "";

		// The first line of the PPM file must be "P3"; comments are
		// allowed on any subsequent line
		if (std::getline(inputFile, line)) {
			if (line.compare("P3") != 0) {
				std::cerr << "Incorrect format. Must be P3 PPM file." << std::endl;
				exit(EXIT_FAILURE); //TODO: use proper error handling instead
			}
		}

		// Get image width and height
		bool dimensionsRead = false;
		while (!dimensionsRead && std::getline(inputFile, line)) {
			// Ignore comments
			if (line.at(0) != '#') {
				std::stringstream dimensions(line); 
				dimensions >> numberOfColumns >> numberOfRows;
				dimensionsRead = true;
			}
		}  

		// Get max pixel value
		bool maxvalRead = false;
		while (!maxvalRead && std::getline(inputFile, line)) {
			// Ignore comments
			if (line.at(0) != '#') {
				maxPixelValue = std::stoi(line);
				maxvalRead = true;
			}
		} 

		// Read pixel data
		while (std::getline(inputFile, line)) {
			// Ignore comments
			if (line.at(0) != '#') {
				std::istringstream imageRow(line);
				Pixel px;
				int r, g, b;

				while (imageRow >> r >> g >> b) {
					// Map pixel values to the range 0 - 1
					px.r = r / maxPixelValue;
					px.g = g / maxPixelValue;
					px.b = b / maxPixelValue;
					pixels.push_back(px);
				}
			}
		}
	}
}

Pixel Image::getPixel(int x, int y) {
	int index = x + numberOfColumns * y;
	return pixels.at(index);
}

void Image::setPixel(int x, int y, Pixel pixel) {
	int index = x + numberOfColumns * y;
	pixels[index] = pixel;
}

/*
 * Images are converted from color to grayscale using the luminosity method
 * described in this article: 
 * https://www.johndcook.com/blog/2009/08/24/algorithms-convert-color-grayscale/
 */
void Image::color2grayscale() {
	for (int row = 0; row < numberOfRows; row++) {
		for (int column = 0; column < numberOfColumns; column++) {
			Pixel px = getPixel(column, row);
			double newPixelValue = (0.21 * px.r) + (0.72 * px.g) + (0.07 * px.b);
			px.r = newPixelValue;
			px.g = newPixelValue;
			px.b = newPixelValue;
			setPixel(column, row, px);
		}
		
	}
}