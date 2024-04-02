#include "bmp.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);

// makes calculations on the pixel based on the chosen kernal
void getKernalProduct(int i, int j,int height, int width, RGBTRIPLE originImage[height][width],INTRGB *pixel, int kernal[9]);