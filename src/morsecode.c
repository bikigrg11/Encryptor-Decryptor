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

int lengthOfKey(char *charCount);
int numprint(int n);
int CheckingInKey(char c);
char* createKeyWord();
int compareWithFraction(char *set);
void printMorseEncryption(int n);
int runMorseDecryption();
int checkExistence(char *str);
void printdecryption(char *here);
int countCompareSize(char *a, const char *b);
int countSize(char *a);
int constCountSize(const char *a);
int checkValidEncode(char ch);

int checkExistence(char *str){
    char *ptrStr= str;
    int i=0;
    int flagCheck=0;
    while(*(morse_table+i) != '\0')
    {
        int z=0;
        flagCheck=0;
        int n= countCompareSize(ptrStr,*(morse_table+i));
        if(n == 1)
        {
            while((*(ptrStr+z)) != '\0')
            {
                if(*(ptrStr+z) == *(*(morse_table+i)+z))
                {
                    z++;
                    flagCheck = 1;
                }else
                {
                    flagCheck = 0;
                    break;
                }
            }
        }

        if(flagCheck == 1)
        {
            return i;       // Return value of correct !! here
        }
        i++;
    }
    return -1;
}

int countCompareSize(char *a, const char *b){
    if(countSize(a) ==  constCountSize(b)){
        return 1;
    }else{
        return 0;
    }
}

int constCountSize(const char *a){
    const char *table=a;
    int z=0;
    while(*(table+z) != '\0'){
       z++;
    }
    return z;
}

int countSize(char *a){
    char *table=a;
    int z=0;
    while(*(table+z) != '\0'){
       z++;
    }
    return z;
}


int runMorseDecryption(){
    int charInput=0;
    long spaceMorse=0;
    char *createBuffer= (char*)&spaceMorse;
    int BufferCounter=0;
    int count=0;
    int charInput2;
    int countSpace = 0;


    while ((charInput = getchar()) != EOF+1){

            if(countSpace == 1){
                if(charInput == EOF){
                    if(count == 0)
                    {
                        *(createBuffer+BufferCounter)='\0';
                        int p = checkExistence(createBuffer);
                        char c = '!'+p;
                        printf("%c",c);     // Print Statement for the char
                        BufferCounter=0;
                        printf("\n");
                        break;
                    }else{
                        // do nothing
                        break;
                    }
                }
                else{
                    printf("\n");
                    countSpace = 0;
                }
            }

           // if(charInput == EOF){
           //      if(count == 0)
           //      {
           //          *(createBuffer+BufferCounter)='\0';
           //          int p = checkExistence(createBuffer);
           //          char c = '!'+p;
           //          printf("%c",c);     // Print Statement for the char
           //          BufferCounter=0;
           //          printf("\n");
           //          break;
           //      }else{
           //          break;
           //      }
           //  }

        if(charInput == '\n'){
            countSpace = 1;
            //printf("\n");
        }else{
            char *MorseValues= createKeyWord();
                for(int i=0;i<26;i++){
                if(charInput == *(MorseValues+i)){
                    int z=0;
                    count=0;

                    while(z != 3){
                        char ch= *(*(fractionated_table+i)+z);
                        if(ch == 'x')
                        {
                            if(count == 0){
                                *(createBuffer+BufferCounter)='\0';
                                int p = checkExistence(createBuffer);
                                char c = '!'+p;
                                printf("%c",c);     // Print Statement for the char
                                BufferCounter=0;
                                 count ++;
                            }
                            else{
                                printf(" ");
                            }
                            z++;
                        }
                        else{
                            z++;
                            count=0;
                            *(createBuffer+BufferCounter) = ch;
                            BufferCounter++;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

void printdecryption(char *here){
    int i=0;
    while(*(here+i)!='\0'){
        printf("%c",*(here+i));
        i++;
    }
}

int checkValidEncode(char ch){
    if(ch < '!' || ch > 'z'){
        return 0;
    }
    else
        return 1;
}

int runMorseEncryption(){
    int charInput=0;
    int morse_index=0;
    int n=0;
    long spaceMorse=0;
    char *createBuffer= (char*)&spaceMorse;
    int ok=0;
    int newlineflag = 0;

    while ((charInput = getchar()) != EOF){

        if(charInput =='\n'){
            newlineflag = 1;
        }
        else
        {
            if(charInput == ' ')
            {

                *(createBuffer+n)= 'x';
                n++;
            }
            else if (checkValidEncode(charInput) == 0)
            {
                return 1;
            }
            else
            {
                morse_index = charInput - 33;
                const char *here = *(morse_table+morse_index);

                if(*here){
// good
                }else{
                    return 1;
                }

                int i=0;
                while(*(here+i) != '\0'){
                    *(createBuffer+n)= *(here+i);
                    n++;
                    if(n==3){
                        n = 0;
                        ok = compareWithFraction(createBuffer);
                        printMorseEncryption(ok);
                    }
                    if(newlineflag == 1){
                        printf("\n");
                        newlineflag = 0;
                    }
                    i++;
                }

                *(createBuffer+n)= 'x';
                n++;
            }
            if(n==3)
            {
                n = 0;
                ok= compareWithFraction(createBuffer);
                printMorseEncryption(ok);
            }
        }
    }

    printf("\n");
    return 0;
}

void printMorseEncryption(int n){
    char *MorseValues= createKeyWord();
    printf("%c",*(MorseValues+n));
}

int compareWithFraction(char *set){
    char *setNew= set;
    int i=0;
    int n=0;
    while (i < 26)
    {
        const char *compFrac = *(fractionated_table+i);
        n = 0;
        while(*(compFrac+n) != '\0'){
            if(*(compFrac+n) == *(setNew+n)){
                n++;
                    if(n == 3){
                        return i;
                    }
            }else{
                break;
            }
        }
        i++;
    }
   return -1;
}

// Making the correction in the FMKEY REturn value neccessary
char* createKeyWord(){
    const char *gave=key;
    char *fmKey=fm_key;
    const char *alphabet=fm_alphabet;

    int count=0;
    while(*(gave+count) != '\0'){
        *(fmKey+count) = *(gave+count);
        count++;
    }
    //char charA='A';
    int n=0;
    int sum=count+n;

   while(*(alphabet+n) != '\0'){
        if(CheckingInKey(*(alphabet+n)) == -1){
            *(fmKey+sum++)=*(alphabet+n);
        }
        n++;
    }
    //printf("%s",fmKey);
    return fmKey;
}