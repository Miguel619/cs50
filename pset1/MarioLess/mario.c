#include <stdio.h>

void pyrimid(int h);

int main(){
    int h;
    printf("Enter Height: ");
    scanf("%i",&h);
    pyrimid(h);
}
//recursion
void pyrimid(int h){
    if (h == 0){
        return;
    }
    pyrimid(h-1);
    for(int i = 0; i < h; i++)
        printf("#");
    printf("\n");
}