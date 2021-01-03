#include <stdio.h>

void pyrimid(int h, int tot);

int main(){

    int n = 9;
    while(n < 1 || n > 8){
        printf("Height: ");
        scanf("%i", &n);
    }
    pyrimid(n, n);
}

void pyrimid(int h, int t){
    if(h == 0){
        return;
    }
    pyrimid(h-1, t);
    for(int i = 0; i < t-h; i++)
        printf(" ");

    for(int i = 0; i < h; i++)
        printf("#");
    printf("  ");
    for(int i = 0; i < h; i++)
        printf("#");
    printf("\n");

}
