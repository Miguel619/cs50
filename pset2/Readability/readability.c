#include <stdio.h>
#include <ctype.h>
#include <math.h>
#define MAX_LIMIT 500

int main(){
    //prompt user for text
    char text[MAX_LIMIT];
    printf("Text: ");
    //store text
    fgets(text, MAX_LIMIT, stdin);
    printf("-----[ Calculating]-------\n");
    int letters = 0, words = 0, sent = 0;
    for(int i = 0; text[i]; i++){
        if(isalpha(text[i])){
            letters++;
        }
        if(text[i] == '.' || text[i] == '?' || text[i] == '!'){
            words++;
            sent++;
            if(text[i+1] == ' '){
                i++;
            }
        }else if(text[i] == ' '){
            words++;
        }
    }


    //apply to formula and round
    printf("%i letter(s)\n", letters);
    printf("%i word(s)\n", words);
    printf("%i sentence(s)\n", sent);
    //print result
    printf("---[per 100 words]---\n");
    double L = ((double) letters / (double) words) * 100;
    printf("%.2f letters\n", L);
    double S = ((double) sent / (double) words) * 100;
    printf("%.2f sentances\n", S);
    printf("---[Coleman-Liau index]---\n");
    L = L * 0.0588;
    S = S * 0.296;
    int index = round(L - S - 15.8);
    if(index > 16){
        printf("Grade 16+\n");
    }else if (index < 1){
        printf("Before Grade 1\n");
    } else{
        printf("Grade %i\n", index);
    }
    

}