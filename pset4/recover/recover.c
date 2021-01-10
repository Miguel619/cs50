#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
    // check for only 1 argument 
    
    if(argc != 2){
        printf("Usage: ./recover image\n");
        return 1;
    }else{
        // open card
        FILE *file = fopen(argv[1], "r");
        if (file != NULL){
            int i = 0;
            int open = 0;
            FILE *img;
            fseek(file, 0, SEEK_END);          
            long filelen = ftell(file);            
            rewind(file);
            // buffer = size of 512
            unsigned char *buffer = (unsigned char*)malloc(sizeof(unsigned char)*512);
            char *filename = malloc(sizeof(char)*7);
            // repeat until end of card
            // read 512 bytes into buffer
            for(int j = 0; j < filelen; j++){
                int size = fread(buffer, 1, 512, file);
                if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff){
                    if((buffer[3] & 0xf0) == 0xe0){
                        if(i == 0){
                            sprintf(filename, "%03i.jpg", i);
                            img = fopen(filename, "w");
                            fwrite(buffer, 1, size, img);
                            open = 1;
                            i++;
                            
                        }else{
                            fclose(img);
                            sprintf(filename, "%03i.jpg", i);
                            img = fopen(filename, "w");
                            fwrite(buffer, 1, size, img);
                            open = 1;
                            i++;
                        }
                        
                    }
                    
                }else if(open == 1){
                    fwrite(buffer, 1, size, img);
                }
            }
            

            fclose(file);

            

            

        }
        
        
    }
 
}