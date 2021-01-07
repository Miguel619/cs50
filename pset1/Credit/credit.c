#include <stdio.h>
#include <math.h>

int auth(long card, int digits);

int main(){
    long num;
    char ch;
    int code;
    printf("Number: ");
    while(scanf("%ld", &num) != 1){
        printf("Number: ");
        while((ch=getchar())!='\n' && ch!=EOF);
    }
    //16
    if(num >= pow(10,15)){
        int fd = (num % (long)pow(10,16))/pow(10,15);
        // mc
        if(fd == 5){
            int sd = (num % (long)pow(10,15))/pow(10,14);
            if (sd == 1 || sd == 2 || sd == 3 || sd == 4 || sd == 5){
                code = auth(num, 16);
                if(code % 10 == 0){
                    printf("MASTERCARD\n");
                    return 0;
                }
                
            }
        }// visa
        else if(fd == 4){
            code = auth(num, 16);
            if(code % 10 == 0){
                printf("VISA\n");
                return 0;
            }
        }
    }//15 AE
    else if(num >= pow(10,14)){
        int fd = (num % (long)pow(10,15))/pow(10,14);
        if(fd == 3){
            int sd = (num % (long)pow(10,14))/pow(10,13);
            if (sd == 4 || sd == 7){
                code = auth(num, 15);
                if(code % 10 == 0){
                    printf("AMEX\n");
                    return 0;
                }
                
            }
        }
    }//13
    else if(num >= pow(10,12)){
        int fd = (num % (long)pow(10,13))/pow(10,12);
        if(fd == 4){
            code = auth(num, 13);
            if(code % 10 == 0){
                printf("VISA\n");
                return 0;
            }
        }
    }
    printf("INVALID\n");
    return 0;

}

int auth(long card, int digits){
    int sum = 0;
    int holder;
    // add every 2 * 2
    
    for(int i = 2; i <= digits; i+=2){
        holder = ((card % (long)pow(10,i))/pow(10,i-1));
        holder = holder*2;
        // add each digit for double digit numbers
        if(holder>9){
            sum += (holder%100)/10;
            sum += holder%10;
        }else{
            sum += holder;
            
        }
    }
    
    for(int i = 1; i <= digits; i+=2){
        holder = (card % (long)pow(10,i))/pow(10,i-1);
        // add each digit for double digit numbers
        sum += holder;
    }
    return sum;

}