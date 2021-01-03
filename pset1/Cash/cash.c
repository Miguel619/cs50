#include <stdio.h>
#include <math.h>

int calc(int c);

int main(){
    float change = 0;
    char ch;
    printf("Change owed: ");
    while(scanf("%f", &change) != 1 || change <= 0){
        printf("Change owed: ");
        while( (ch=getchar())!='\n' && ch!=EOF );
    }
    
    int cents = round(change * 100);
    int coins = calc(cents);
    printf("Coins: %i\n", coins);
}

// enter cents return coins
int calc(int cents){
    int coins;
    // 25
    coins = cents / 25;
    cents -= coins * 25;
    
    // 10
    coins += cents / 10;
    cents -= (cents/10) * 10;
    
    // 5
    coins += cents / 5;
    cents -= (cents/5) * 5;
    
    // 1
    coins += cents / 1;
    cents -= (cents/1) * 1;

    return coins;
}

