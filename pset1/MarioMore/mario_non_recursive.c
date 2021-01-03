#include <stdio.h>

void pyrimid(int h);

int main(){

    int n = 9;
    //check user input to be 1-8
    while(n < 1 || n > 8){
        printf("Height: ");
        scanf("%i", &n);
    }
    // non-recursive print
    pyrimid(n);

}

void pyrimid(int h){
    //reference point for spaces
    int num = h - 1;
    // for every height
    for(int i = 0; i < h; i++){
        // print spaces of height - 1
        for(int j = 0; j < num; j++){
            printf(" ");
        }
        // print pyrimid
        for(int k = 0; k < h - num; k++){
            printf("#");
        }
        // print space inbetween
        printf("  ");
        // print second pyrimid
        for(int k = 0; k < h - num; k++){
            printf("#");
        }
        // one less space next time
        num--;
        printf("\n");
    }
    

}