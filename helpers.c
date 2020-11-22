#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = round(((float) image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaBlue;
    int sepiaGreen;
    int sepiaRed;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(.393 * (float) image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * (float) image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * (float) image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255)
                sepiaRed = 255;

           if (sepiaBlue > 255)
                sepiaBlue = 255;

            if (sepiaGreen > 255)
                sepiaGreen = 255;

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
    RGBTRIPLE tmp[width];

    for (int k = 0; k < height; k++)
    {
        for (int i = 0, j = width - 1; i < width; i++, j--)
        {
            tmp[j] = image[k][i];
        }

        for (int l = 0; l < width; l++)
        {
            image[k][l] = tmp[l];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                tmp[i][j].rgbtRed =   round(((float)image[i][j].rgbtRed   + image[i][j + 1].rgbtRed   + image[i + 1][j].rgbtRed   + image[i + 1][j + 1].rgbtRed) / 4);
                tmp[i][j].rgbtGreen = round(((float)image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 4);
                tmp[i][j].rgbtBlue =  round(((float)image[i][j].rgbtBlue  + image[i][j + 1].rgbtBlue  + image[i + 1][j].rgbtBlue  + image[i + 1][j + 1].rgbtBlue) / 4);
            }

            if (i == 0 && j != 0 && j != width - 1)
            {
                tmp[i][j].rgbtRed =   round(((float)image[i][j].rgbtRed   + image[i][j + 1].rgbtRed   + image[i + 1][j].rgbtRed   + image[i + 1][j + 1].rgbtRed   + image[i][j - 1].rgbtRed   + image[i + 1][j - 1].rgbtRed) / 6);
                tmp[i][j].rgbtGreen = round(((float)image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6);
                tmp[i][j].rgbtBlue =  round(((float)image[i][j].rgbtBlue  + image[i][j + 1].rgbtBlue  + image[i + 1][j].rgbtBlue  + image[i + 1][j + 1].rgbtBlue  + image[i][j - 1].rgbtBlue  + image[i + 1][j - 1].rgbtBlue) / 6);
            }

            if (i == 0 && j == width - 1)
            {
                tmp[i][j].rgbtRed =   round(((float)image[i][j].rgbtRed   + image[i + 1][j].rgbtRed   + image[i][j - 1].rgbtRed   + image[i + 1][j - 1].rgbtRed) / 4);
                tmp[i][j].rgbtGreen = round(((float)image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 4);
                tmp[i][j].rgbtBlue =  round(((float)image[i][j].rgbtBlue  + image[i + 1][j].rgbtBlue  + image[i][j - 1].rgbtBlue  + image[i + 1][j - 1].rgbtBlue) / 4);
            }

            if (i != 0 && i != height - 1 && j == 0)
            {
                tmp[i][j].rgbtRed =   round(((float)image[i][j].rgbtRed   + image[i][j + 1].rgbtRed   + image[i + 1][j].rgbtRed   + image[i + 1][j + 1].rgbtRed   + image[i - 1][j].rgbtRed   + image[i - 1][j + 1].rgbtRed) / 6);
                tmp[i][j].rgbtGreen = round(((float)image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6);
                tmp[i][j].rgbtBlue =  round(((float)image[i][j].rgbtBlue  + image[i][j + 1].rgbtBlue  + image[i + 1][j].rgbtBlue  + image[i + 1][j + 1].rgbtBlue  + image[i - 1][j].rgbtBlue  + image[i - 1][j + 1].rgbtBlue) / 6);
            }

            if (i != 0 && i != height - 1 && j == width - 1)
            {
                tmp[i][j].rgbtRed =   round(((float)image[i][j].rgbtRed   + image[i + 1][j].rgbtRed   + image[i][j - 1].rgbtRed   + image[i + 1][j - 1].rgbtRed   + image[i - 1][j - 1].rgbtRed   + image[i - 1][j].rgbtRed) / 6);
                tmp[i][j].rgbtGreen = round(((float)image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen) / 6);
                tmp[i][j].rgbtBlue =  round(((float)image[i][j].rgbtBlue  + image[i + 1][j].rgbtBlue  + image[i][j - 1].rgbtBlue  + image[i + 1][j - 1].rgbtBlue  + image[i - 1][j - 1].rgbtBlue  + image[i - 1][j].rgbtBlue) / 6);

            }

            if (i == height - 1 && j == 0)
            {
                tmp[i][j].rgbtRed =   round(((float)image[i][j].rgbtRed   + image[i][j + 1].rgbtRed   + image[i - 1][j].rgbtRed   + image[i - 1][j + 1].rgbtRed) / 4);
                tmp[i][j].rgbtGreen = round(((float)image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 4);
                tmp[i][j].rgbtBlue =  round(((float)image[i][j].rgbtBlue  + image[i][j + 1].rgbtBlue  + image[i - 1][j].rgbtBlue  + image[i - 1][j + 1].rgbtBlue) / 4);
            }

            if (i == height - 1 && j != 0 && j != width - 1)
            {
                tmp[i][j].rgbtRed =   round(((float)image[i][j].rgbtRed   + image[i][j + 1].rgbtRed   + image[i][j - 1].rgbtRed   + image[i - 1][j - 1].rgbtRed   + image[i - 1][j].rgbtRed   + image[i - 1][j + 1].rgbtRed) / 6);
                tmp[i][j].rgbtGreen = round(((float)image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6);
                tmp[i][j].rgbtBlue =  round(((float)image[i][j].rgbtBlue  + image[i][j + 1].rgbtBlue  + image[i][j - 1].rgbtBlue  + image[i - 1][j - 1].rgbtBlue  + image[i - 1][j].rgbtBlue  + image[i - 1][j + 1].rgbtBlue) / 6);

            }

            if (i == height - 1 && j == width - 1)
            {
                tmp[i][j].rgbtRed =   round(((float)image[i][j].rgbtRed   + image[i][j - 1].rgbtRed   + image[i - 1][j - 1].rgbtRed   + image[i - 1][j].rgbtRed) / 4);
                tmp[i][j].rgbtGreen = round(((float)image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen) / 4);
                tmp[i][j].rgbtBlue =  round(((float)image[i][j].rgbtBlue  + image[i][j - 1].rgbtBlue  + image[i - 1][j - 1].rgbtBlue  + image[i - 1][j].rgbtBlue) / 4);
            }

            if (i != 0 && i != height - 1 && j != 0 && j != width - 1)
            {
                tmp[i][j].rgbtRed =   round(((float)image[i][j].rgbtRed   + image[i][j + 1].rgbtRed   + image[i + 1][j].rgbtRed   + image[i + 1][j + 1].rgbtRed   + image[i][j - 1].rgbtRed   + image[i + 1][j - 1].rgbtRed   + image[i - 1][j - 1].rgbtRed   + image[i - 1][j].rgbtRed   + image[i - 1][j + 1].rgbtRed) / 9);
                tmp[i][j].rgbtGreen = round(((float)image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 9);
                tmp[i][j].rgbtBlue =  round(((float)image[i][j].rgbtBlue  + image[i][j + 1].rgbtBlue  + image[i + 1][j].rgbtBlue  + image[i + 1][j + 1].rgbtBlue  + image[i][j - 1].rgbtBlue  + image[i + 1][j - 1].rgbtBlue  + image[i - 1][j - 1].rgbtBlue  + image[i - 1][j].rgbtBlue  + image[i - 1][j + 1].rgbtBlue) / 9);
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }

    return;
}


