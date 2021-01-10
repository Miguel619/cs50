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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    /* 
      [-1][0][1]    [-1][-2][-1]
    Gx[-2][0][2]  Gy[ 0][ 0][ 0]
      [-2][0][1]    [ 1][ 2][ 1]
      corner cases = 0
    **/
   // temp image we will store our edited pixels
    RGBTRIPLE temp[height][width];
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    // for every pixel in the pic
    for(int row = 0; row < height; row++){
        for(int col = 0; col < width; col++){
            int rowArray[] = {row-1, row, row + 1};
            int colArray[] = {col - 1, col, col +1};
            int redX = 0, greenX = 0, blueX = 0;
            int redY = 0, greenY = 0, blueY = 0;
            int r, g, b;
            // for every pixel in matrix
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    int curRow = rowArray[i];
                    int curCol = colArray[j];
                    int curGx = gx[i][j];
                    int curGy = gy[i][j];
                    RGBTRIPLE pix = image[curRow][curCol];
                    if(curRow < 0 || curRow >= height || curCol < 0 || curCol >= width){
                        redX += 0;
                        greenX += 0;
                        blueX += 0;
                        redY += 0;
                        greenY += 0;
                        blueY += 0;
                    }else{
                        redX += pix.rgbtRed * curGx;
                        greenX += pix.rgbtGreen * curGx;
                        blueX += pix.rgbtBlue * curGx;
                        redY += pix.rgbtRed * curGy;
                        greenY += pix.rgbtGreen * curGy;
                        blueY += pix.rgbtBlue * curGy;
                    }
                }
            }
            r = round(sqrt(pow(redX, 2.0) + pow(redY, 2.0)));
            temp[row][col].rgbtRed = check(r);
            g = round(sqrt(pow(greenX, 2.0) + pow(greenY, 2.0)));
            temp[row][col].rgbtGreen = check(g);
            b = round(sqrt(pow(blueX, 2.0) + pow(blueY,2.0)));
            temp[row][col].rgbtBlue = check(b);
        }
    }
    for(int r= 0; r < height; r++){
        for(int c = 0; c < width; c++){
            image[r][c] = temp[r][c];
        }
    }
    return;
}
