#include "helpers.h"
#include <math.h>

int check(int r);
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
// square blur is the worse
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    /*
    [ ][ ][ ]
    [ ][x][ ]
    [ ][ ][ ]
    **/
   // temp image
   RGBTRIPLE temp[height][width];
    // for every pixel
   for(int row = 0; row < height; row++){
       for(int col = 0; col < width; col++){
           // create dynamic square
            int allRow[] = {row-1, row, row + 1};
            int AllCol[] = {col-1, col, col+1};
            float r = 0, g = 0, b = 0;
            int count = 0;

            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    int curRow = allRow[i];
                    int curCol = AllCol[j];
                    if(curRow >= 0 && curRow < height && curCol >= 0 && curCol < width){
                        RGBTRIPLE pixel = image[curRow][curCol];
                        r += pixel.rgbtRed;
                        g += pixel.rgbtGreen;
                        b += pixel.rgbtBlue;
                        count++;
                    }
                    
                }
            }
            temp[row][col].rgbtRed = round(r / count);
            temp[row][col].rgbtGreen = round(g / count);
            temp[row][col].rgbtBlue = round(b / count);
       }
   }
   for(int a = 0; a < height; a++){
       for(int b = 0; b < width; b++){
           image[a][b] = temp[a][b];
       }
   }

    return;
}
