#include "helpers.h"
#include <math.h>
#include <stdio.h>

int check(int r);
int corner(int color, int a, int b, int c);
int row(int color, int a, int b, int c, int d, int e);
RGBTRIPLE all(int a, int b, RGBTRIPLE image[a][b]);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int r, g, b, average;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            r = image[i][j].rgbtRed;
            g = image[i][j].rgbtGreen;
            b = image[i][j].rgbtBlue;
            average = r+g+b;
            average = round(average/3.0);
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
    int r, g, b;
    int r2, g2, b2;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            r = image[i][j].rgbtRed;
            g = image[i][j].rgbtGreen;
            b = image[i][j].rgbtBlue;
            r2 = round((.393 * r) + (.769 * g) + (.189 * b));
            r2 = check(r2);
            g2 = round((.349 * r) + (.686 * g) + (.168 * b));
            g2 = check(g2);
            b2 = round((.272 * r) + (.534 * g) + (.131 * b));
            b2 = check(b2);
            image[i][j].rgbtRed = r2;
            image[i][j].rgbtGreen = g2;
            image[i][j].rgbtBlue = b2;
        }
    }
    return;
}

int check(int r){
    if(r > 255){
        return 255;
    }
    return r;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int last = width - 1;
    int r;
    int g;
    int b;
    for(int i = 0; i < height; i++){
        // [0][1][2][3][4]
        for(int j = 0; j < width/2; j++){
            r = image[i][last - j].rgbtRed;
            g = image[i][last - j].rgbtGreen;
            b = image[i][last - j].rgbtBlue;
            image[i][last - j].rgbtRed = image[i][j].rgbtRed;
            image[i][last - j].rgbtGreen = image[i][j].rgbtGreen;
            image[i][last - j].rgbtBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = r;
            image[i][j].rgbtGreen = g;
            image[i][j].rgbtBlue = b;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int last = width - 1;
    int bot = height - 1;
    int red = 0;
    int green = 0;
    int blue = 0;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            // check left corner
            if(i == 0 && j == 0){
                image[i][j].rgbtRed = 0;
                image[i][j].rgbtGreen = 0;
                image[i][j].rgbtBlue = 0;
                // top right corner
            }else if (i == 0 && j == last){
                image[i][j].rgbtRed = 0;
                image[i][j].rgbtGreen = 0;
                image[i][j].rgbtBlue = 0;
                // top row
            }else if(i == 0){
                image[i][j].rgbtRed = 0;
                image[i][j].rgbtGreen = 0;
                image[i][j].rgbtBlue = 0;
                //bottom left
            }else if (i == bot && j == 0)
            {
                image[i][j].rgbtRed = 0;
                image[i][j].rgbtGreen = 0;
                image[i][j].rgbtBlue = 0;
                // bottom right
            }else if(i == bot && j == last){
                image[i][j].rgbtRed = 0;
                image[i][j].rgbtGreen = 0;
                image[i][j].rgbtBlue = 0;
                // bottom row
            }else if (i == bot)
            {
                image[i][j].rgbtRed = 0;
                image[i][j].rgbtGreen = 0;
                image[i][j].rgbtBlue = 0;
                // left colm
            }else if (j == 0)
            {
                image[i][j].rgbtRed = 0;
                image[i][j].rgbtGreen = 0;
                image[i][j].rgbtBlue = 0;
                // right colm
            }else if (j == last)
            {
                image[i][j].rgbtRed = 0;
                image[i][j].rgbtGreen = 0;
                image[i][j].rgbtBlue = 0;
            }else
            {
                RGBTRIPLE topL = image[i-1][j-1];
                red += topL.rgbtRed;
                green += topL.rgbtGreen;
                blue += topL.rgbtBlue;
                RGBTRIPLE top = image[i][j-1];
                red += top.rgbtRed;
                green += top.rgbtGreen;
                blue += top.rgbtBlue;
                RGBTRIPLE topR = image[i+1][j-1];
                red += topR.rgbtRed;
                green += topR.rgbtGreen;
                blue += topR.rgbtBlue;
                RGBTRIPLE left = image[i-1][j];
                red += left.rgbtRed;
                green += left.rgbtGreen;
                blue += left.rgbtBlue;
                RGBTRIPLE right = image[i+1][j];
                red += right.rgbtRed;
                green += right.rgbtGreen;
                blue += right.rgbtBlue;
                RGBTRIPLE botL = image[i-1][j+1];
                red += botL.rgbtRed;
                green += botL.rgbtGreen;
                blue += botL.rgbtBlue;
                RGBTRIPLE bottom = image[i][j+1];
                red += bottom.rgbtRed;
                green += bottom.rgbtGreen;
                blue += bottom.rgbtBlue;
                RGBTRIPLE botR = image[i+1][j+1];
                red += botR.rgbtRed;
                green += botR.rgbtGreen;
                blue += botR.rgbtBlue;
                // last
                red += image[i][j].rgbtRed;
                green += image[i][j].rgbtGreen;
                blue += image[i][j].rgbtBlue;
                
                red = round(red/9);
                green = round(green/9);
                blue = round(blue/9);

                image[i][j].rgbtRed = red;
                image[i][j].rgbtGreen = green;
                image[i][j].rgbtBlue = blue;
            }

            
            
        }
    }
    return;
}


RGBTRIPLE all(int a, int b, RGBTRIPLE image[a][b]){
    int red = 0;
    int green = 0;
    int blue = 0;
    RGBTRIPLE topL = image[a-1][b-1];
    red += topL.rgbtRed;
    green += topL.rgbtGreen;
    blue += topL.rgbtBlue;
    RGBTRIPLE top = image[a][b-1];
    red += top.rgbtRed;
    green += top.rgbtGreen;
    blue += top.rgbtBlue;
    RGBTRIPLE topR = image[a+1][b-1];
    red += topR.rgbtRed;
    green += topR.rgbtGreen;
    blue += topR.rgbtBlue;
    RGBTRIPLE left = image[a-1][b];
    red += left.rgbtRed;
    green += left.rgbtGreen;
    blue += left.rgbtBlue;
    RGBTRIPLE right = image[a+1][b];
    red += right.rgbtRed;
    green += right.rgbtGreen;
    blue += right.rgbtBlue;
    RGBTRIPLE botL = image[a-1][b+1];
    red += botL.rgbtRed;
    green += botL.rgbtGreen;
    blue += botL.rgbtBlue;
    RGBTRIPLE bot = image[a][b+1];
    red += bot.rgbtRed;
    green += bot.rgbtGreen;
    blue += bot.rgbtBlue;
    RGBTRIPLE botR = image[a+1][b+1];
    red += botR.rgbtRed;
    green += botR.rgbtGreen;
    blue += botR.rgbtBlue;
    // last
    red += image[a][b].rgbtRed;
    green += image[a][b].rgbtGreen;
    blue += image[a][b].rgbtBlue;
    
    red = round(red/9);
    green = round(green/9);
    blue = round(blue/9);

    image[a][b].rgbtRed = red;
    image[a][b].rgbtGreen = green;
    image[a][b].rgbtBlue = blue;

    return image[a][b];
}