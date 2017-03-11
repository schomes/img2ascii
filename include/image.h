#ifndef IMAGE_H
#define IMAGE_H

#include <vector>

// TODO: use templates to accept any pixel type (char, double, etc.) and number of channels
// Pixel values are represented between 0 - 1
struct Pixel
{
	double r; 
	double g; 
	double b; 
};

class Image {
	public: 
		Image(); 
		~Image(); 
		
		void readImage(const char *path);

		// Returns the width of the image. 
		int getWidth() const {return numberOfColumns;}

		// Returns the height of the image. 
		int getHeight() const {return numberOfRows;}

		/**
		 * Returns the pixel at the specified coordinate.
		 * The top-left corner of the image is (0, 0).
		 * \param x The x-coordinate of the pixel.
		 * \param y The y-coordinate of the pixel.
		 */
		Pixel getPixel(int x, int y);

		/*
		 * Sets the color of the pixel at (x, y).
		 * The top-left corner of the image is (0, 0).
		 * \param x The x-coordinate of the pixel.
		 * \param y The y-coordinate of the pixel.
		 * \param pixel The pixel's new color. 
		 */ 
		void setPixel(int x, int y, Pixel pixel);

		/* 
		 * Converts an image from color to grayscale.
		 */
		void color2grayscale();

	private: 
		int numberOfRows; 
		int numberOfColumns; 
		double maxPixelValue; 
		std::vector<Pixel> pixels; 

		// Reads an image in PPM (P3) format
		void readImagePPM(const char *path);
};

#endif 