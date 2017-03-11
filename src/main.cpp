#include <iostream>
#include "image.h"

#define VERSION "0.0.1" 

int main(int argc, char *argv[]){

	if (argc < 3) {
		std::cout << "Version: " << argv[0] << " " << VERSION << std::endl; 
		std::cout << "Usage: img2ascii file file" << std::endl;
		std::cout << "The first file is the image to import. The second file is a text file to export to." << std::endl;
		std::cout << "Supported image formats: PPM" << std::endl; 
		return 0;
	}

	Image img;
	img.readImage(argv[1]);
	img.color2grayscale();

	for (int row = 0; row < img.getHeight(); row++) {
		for (int column = 0; column < img.getWidth(); column++) {
			Pixel p = img.getPixel(column, row);
			std::cout << p.r << " " << p.g << " " << p.b << " " << std::endl;
		}
	}

	// Convert to ascii textfile and export textfile
	// ascii(argv[2])

	// Delete image / cleanup

	return 0;
}