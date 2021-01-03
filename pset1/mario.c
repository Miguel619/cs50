#include <stdio.h>

void pyrimid(int h);

int main(){

    int n;
    printf("Height: ");
    scanf("%i", &n);
    pyrimid(n);

}

void pyrimid(int h){
    int num = h - 1;
    for(int i = 0; i < h; i++){
        for(int j = 0; j < num; j++){
            printf(" ");
        }
        for(int k = 0; k < h - num; k++){
            printf("#");
        }
        printf("  ");
        for(int k = 0; k < h - num; k++){
            printf("#");
        }
        num--;
        printf("\n");
    }
    

}