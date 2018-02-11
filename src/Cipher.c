#include "hw1.h"
#include <stdlib.h>

#ifdef _STRING_H
#error "Do not #include <string.h>. You will get a ZERO."
#endif

#ifdef _STRINGS_H
#error "Do not #include <strings.h>. You will get a ZERO."
#endif

#ifdef _CTYPE_H
#error "Do not #include <ctype.h>. You will get a ZERO."
#endif


void findingCordinates(int c, int row, int col);
int  CheckingInKey(char c);
int lengthOfKey();
int runningPolybiusCipher(unsigned short findingRow,unsigned short findingCol);
int runningPolybiusDecryption(unsigned short findingRow,unsigned short findingCol);
void printingValue(int valuePoint);
int changeAsciiCode(char c);

int makePolybiusCipher(unsigned short mode){

    unsigned short checkDE= mode;
    unsigned short checkFP= mode;
    checkFP = checkFP >> 14;

    checkDE = checkDE & 0x2000;
    checkDE = checkDE >> 13;

// *** For Row
        unsigned short findingRow= mode;
        int makeRow = 0x00F0;
        findingRow = findingRow & makeRow;
        findingRow = findingRow >> 4;
        if(findingRow== 0){
            findingRow = 10;
        }else{
            // do nothing
        }

    // *** For Column
        unsigned short findingCol= mode;
        int makeCol = 0x000F;
        findingCol = findingCol & makeCol;

        if(findingCol == 0){
            findingCol = 10;
        }else{
            // do nothing
        }


    if(checkFP == 1){
        //printf("Morse Cipher\n");
        if(checkDE == 1){
            // Morse Decryption
            //printf("Morse Decryption\n");
            runMorseDecryption();
        }else
        {
            //printf("Morse Encryption\n");
            // Morse Encryption
            if(runMorseEncryption() == 1){
                return 1;
            }else{
                return 0;
            }
        }
    }

    else if(checkFP == 0){
        //printf("polybius Cipher\n");

        if(checkDE == 1){
            // Polybius Decryption
            runningPolybiusDecryption(findingRow,findingCol);

        }else
        {
            // Polybius Encryption
            runningPolybiusCipher(findingRow, findingCol);
        }

    }
    else{
        printf("Error in Valid Args\n");
        return 0;
    }

    return 0;
}

// Polybius Decryption
int runningPolybiusDecryption(unsigned short findingRow,unsigned short findingCol){
    char *table=polybius_alphabet;
    const char *keyValue= key;
    int i=0;
    int z=1;
    int row=findingRow;
    int col=findingCol;
    int val=0;
    int valuePoint=0;
    int a=0;
    if(keyValue){
        while ((a = getchar()) != EOF){
            if(a == '\n'){
                printf("\n");
            }else if(a==' '){
                printf(" ");
            }
            else{
                val = changeAsciiCode(a);
                if(z==1){
                    valuePoint = col*(val);
                    z++;
                }else{
                    valuePoint += (val+1);
                    printingValue(valuePoint);
                    //printf("%c",*(table+(valuePoint-1)));
                    z=1;
                    valuePoint = 0;
                }
            }
        }
    }
    else{
        while ((a = getchar()) != EOF){
            if(a == '\n'){
                printf("\n");
            }else if(a==' '){
                printf(" ");
            }
            else{
                val = changeAsciiCode(a);
                if(z==1){
                    valuePoint = col*(val);
                    z++;
                }else{
                    valuePoint += (val+1);
                    //printf("%d",valuePoint);
                    printf("%c",*(table+(valuePoint-1)));
                    z=1;
                    valuePoint = 0;
                }
            }

        }
    }
    return 0;
}

int changeAsciiCode(char c){
    int a = 0;
    if(c > '9'){
        a = c-'7';
    }
    else{
        a = c - '0';
    }
    return a;
 }

 void printingValue(int valuePoint){
    char *table=polybius_alphabet;
    const char *tableKey=key;
    int h=0;
    int m=0;
    if(valuePoint > lengthOfKey()){
       valuePoint= valuePoint - lengthOfKey();

        while(h!=valuePoint){
            if(CheckingInKey(*(table+m)) == -1){
                h++;
                m++;
            }else{
                m++;
            }
        }
        printf("%c",*(table+(m-1)));
    }else{
        printf("%c",*(tableKey+(valuePoint-1)));
    }
 }


// Polybius Cipher encryption ::
int runningPolybiusCipher(unsigned short findingRow,unsigned short findingCol)
{
    // getting the Key for the PolyBius Key
        const char *keyValue= key;    // Key if assigned
        char *table=polybius_alphabet;
        int i=0;
        int z=0;
        int a=0;
        int row=findingRow;     // Number of Row
        int col=findingCol;     // Number of Column

    if(keyValue){
        // Key Value is provided
        while ((a = getchar()) != EOF){
            if(a == '\n'){
                printf("\n");
            }else if(a ==' '){
                printf(" ");
            }
            else
            {
                int num = CheckingInKey(a);
                if(num == -1){
                    while((char)a != *(table+i)){
                        if(CheckingInKey(*(table+i)) == -1 ){
                            z++;
                        }else{
                            // do nothing
                        }
                        i++;
                    }
                    i = lengthOfKey() + z ;
                }else{
                    i = num;
                }
                findingCordinates(i,row,col);
                i=0;
                z=0;
            }
        }
    }
    else{
        // Key Value is not Provided
        while ((a = getchar()) != EOF){
            if(a == '\n'){
                printf("\n");
            }else if(a==' '){
                printf(" ");
            }
            else{
                while((char)a != *(table+i)){
                    i++;
                }
               findingCordinates(i,row,col);
               i=0;
            }
        }
    }
    return 0;
}


// Function to find the length of the Key
int lengthOfKey(){
    const char *tableKey=key;
    int z=0;
    while(*(tableKey+z) != '\0'){
       z++;
    }
    return z;
}

// Function to check if the char exist in the key
int CheckingInKey(char c){
    //char *key = "cse320";
    const char *tableKey=key;

    int z=0;
    while(c != *(tableKey+z)){
        if(*(tableKey+z) == '\0'){
            return -1;
        }
        else{
            z++;
        }
    }
    return z;
}

// Function to print the cordinates using row and column
void findingCordinates(int pos, int row, int col){
    int n= pos;
        int r,c;
        r = n /(col);    // row number
        if(r>9){
            printf("%c",r+'7');
        }else{
            printf("%c",r+'0');
        }
        c = n % (col);
        if(c>9){
            printf("%c",c+'7');
        }else{
            printf("%c",c+'0');
        }
}
