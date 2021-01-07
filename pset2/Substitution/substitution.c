#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_LIMIT 500

int main(int argc, char *argv[]){
    //get key
    if( argc == 2){
        //validate key
        if(strlen(argv[1]) == 26){
            char cipher[26];
            // save key
            for(int i = 0; argv[1][i]; i++){
                char letter = argv[1][i];
                if(isalpha(letter)){
                    if (strchr(cipher, letter) != NULL)
                    {
                        printf("Key must contain no repeated characters\n");
                        return 1;
                        // index cipher
                        
                    }else{
                        letter = toupper(letter) % 65;
                        letter = letter;
                        cipher[i] = letter;
                    }
                }else{
                    printf("Key must only contain alphabetic characters\n");
                    return 1;
                }
            }
            // get plan text
            char plain[MAX_LIMIT];
            printf("plaintext: ");
            fgets(plain, MAX_LIMIT, stdin);
            // encipher
            for(int i = 0; plain[i]; i++){
                // char we wanna change
                char cur = plain[i];
                // text for uppercase and use 65 as base
                if(isupper(cur)){
                    cur = cur % 65;
                    plain[i] = cipher[cur] + 65;
                // test lowercase and use 97 as base
                }else if(islower(cur)){
                    cur = cur % 97;
                    plain[i] = cipher[cur] + 97;
                }
            }
            // print ciphertext
            printf("ciphertext: %s", plain);
        }else{
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }else{
        printf("Usage: ./substitution key\n");
        return 1;
    }
}