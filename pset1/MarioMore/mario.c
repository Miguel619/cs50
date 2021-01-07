#include <stdio.h>

void pyrimid(int h, int tot);

int main(){

    int n = 9;
    //check user input to be 1-8
    while(n < 1 || n > 8){
        printf("Height: ");
        scanf("%i", &n);
    }
    // recursively print 
    pyrimid(n, n);
}
//(height for recursion and reference point for spaces)
void pyrimid(int h, int t){
    // base case
    if(h == 0){
        return;
    }
    // pyrimid recursion
    pyrimid(h-1, t);
    // first pyrimid spaces first
    for(int i = 0; i < t-h; i++)
        printf(" ");
    // then first pyrimid
    for(int i = 0; i < h; i++)
        printf("#");
    // space in between
    printf("  ");
    // second pyrimid
    for(int i = 0; i < h; i++)
        printf("#");
    printf("\n");

}
