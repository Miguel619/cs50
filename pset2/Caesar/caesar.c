#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX_LIMIT 500

char chipher(char letter, int key, int base);

int main(int argc, char *argv[]){
    // test for the second command line to be a number
    if( argc == 2 && isdigit(*argv[1])){
        // store key
        int key = atoi(argv[1]);
        char text[MAX_LIMIT];
        char letter;
        // print text
        printf("plaintext:  ");
        //store text
        fgets(text, MAX_LIMIT, stdin);
        for(int i = 0; text[i]; i++){
            // store char we are checking
            letter = text[i];
            // test for letter
            if(isalpha(letter)){
                // text for uppercase and use 65 as base
                if(isupper(letter)){
                    text[i] = chipher(letter, key, 65);
                // test lowercase and use 97 as base
                }else if(islower(letter)){
                    text[i] = chipher(letter, key, 97);
                }
            }
        }
        printf("ciphertext: %s", text);
    }else if(argc > 2){
        printf("Usage: ./caesar key\n");
        return 1;
    }else{
        printf("Usage: ./caesar key\n");
        return 1;
    }
}


char chipher(char letter, int key, int base){
    // index alphabet
    letter = letter % base;
    // add key
    letter += key;
    // reindex if goes out of range
    while (letter > 25)
    {
        letter -= 26;
    }
    // reindex to base
    return letter + base;
}