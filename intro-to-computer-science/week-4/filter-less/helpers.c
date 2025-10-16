#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
  // Loop over all pixles
  for (int i =0; i < height; i++) {
    for (int j = 0; j < width; j++){
      int red = image[i][j].rgbtRed;
      int green = image[i][j].rgbtGreen;
      int blue = image[i][j].rgbtBlue;

      // Take average of red, green, blue and round it.
      int average = round((red + green + blue) / 3.0);

      // Update pixel values.
      image[i][j].rgbtRed = average;
      image[i][j].rgbtGreen = average;
      image[i][j].rgbtBlue = average;
    }
  }
  return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
  // Loop over all pixles
  for (int i =0; i < height; i++) {
    for (int j = 0; j < width; j++){
      int originalRed = image[i][j].rgbtRed;
      int originalGreen = image[i][j].rgbtGreen;
      int originalBlue = image[i][j].rgbtBlue;

      // Comput sepia values
      float sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue; 
      float sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
      float sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;

      // Round the values
      sepiaRed = round(sepiaRed);
      sepiaGreen = round(sepiaGreen);
      sepiaBlue = round(sepiaBlue);
      
      // Check if the value is greater than 255, if so set it to 255
      if (sepiaRed > 255) {
        sepiaRed = 255;
      }
      if (sepiaGreen > 255) {
        sepiaGreen = 255;
      }
      if (sepiaBlue > 255) {
        sepiaBlue = 255;
      } 

      // Update pixel values.
      image[i][j].rgbtRed = sepiaRed;
      image[i][j].rgbtGreen = sepiaGreen;
      image[i][j].rgbtBlue = sepiaBlue;
    }
  }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
  // Loop over all pixels
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      // For each row, swap pixels horizontally from left to right
      // Only loop until the middle of the row to avoid double swapping
      // Use a temporary variable to store one pixel during the swap
      // Swap the pixel at position j with the pixel at position (width - 1 - j)
      if (j >= width /2) {
        break;
      }
      RGBTRIPLE temp = image[i][j];
      image[i][j] = image[i][width - 1 - j];
      image[i][width - 1 - j] = temp;
    }
  }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
  // Create a copy of image
  RGBTRIPLE copy[height][width];

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      // Copy each pixel from the original image to the copy
      copy[i][j] = image[i][j];
    }
  }
  
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      // For each pixel, calculate the average color values of the pixel and its neighboring pixels
      int redTotal = 0;
      int greenTotal = 0;
      int blueTotal = 0;
      int count = 0;

      for (int di = -1; di <= 1; di++)
      {
        for (int dj = -1; dj <= 1; dj++)
        {
          // Make sure to handle edge and corner pixels by checking boundaries
          int ni = i + di;
          int nj = j + dj;

          if (ni >= 0 && ni < height && nj >= 0 && nj < width)
          {
            redTotal += copy[ni][nj].rgbtRed;
            greenTotal += copy[ni][nj].rgbtGreen;
            blueTotal += copy[ni][nj].rgbtBlue;
            count++;
          }
        }
      }
      // Calculate the average color values by dividing the total by the count of valid pixels
      int averageRed = round((float)redTotal / count);
      int averageGreen = round((float)greenTotal / count);
      int averageBlue = round((float)blueTotal / count);

      // Assign the averaged color values to the corresponding pixel in the original image
      image[i][j].rgbtRed = averageRed;
      image[i][j].rgbtGreen = averageGreen;
      image[i][j].rgbtBlue = averageBlue;

    }
  }
  return;
}
