#include <stdio.h>

void pyrimid(int h, int t);

int main(){
    int h = 0;
    while (h < 1 || h > 8)
    {
        printf("Enter Height: ");
        scanf("%i",&h);
    }
    
    pyrimid(h, h);
}
//recursion
void pyrimid(int h, int t){
    if (h == 0){
        return;
    }
    pyrimid(h-1, t);
    // first pyrimid spaces first
    for(int i = 0; i < t-h; i++)
        printf(" ");
    // then first pyrimid
    for(int i = 0; i < h; i++)
        printf("#");
    printf("\n");
}