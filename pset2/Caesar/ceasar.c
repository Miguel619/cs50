#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX_LIMIT 500

int main(int argc, char *argv[]){
    // test for the second command line to be a number
    if( argc == 2 && isdigit(*argv[1])){
        int key = atoi(argv[1]);
        char text[MAX_LIMIT];
        char letter;
        printf("plaintext:  ");
        fgets(text, MAX_LIMIT, stdin);
        for(int i = 0; text[i]; i++){
            letter = text[i];
            if(isalpha(letter)){
                if(isupper(letter)){
                    
                    letter = letter % 65;
                    letter += key;
                    while (letter > 25)
                    {
                        letter -= 26;
                    }
                    
                    text[i] = letter + 65;

                }else if(islower(letter)){
                    letter = letter % 97;
                    letter += key;
                    while (letter > 25)
                    {
                        letter -= 26;
                    }
                    text[i] = letter + 97;
                }
            }
        }
        printf("ciphertext: %s", text);
    }else if(argc > 2){
        printf("Usage: ./caesar key\n");
    }else{
        printf("Usage: ./caesar key\n");
    }
}

