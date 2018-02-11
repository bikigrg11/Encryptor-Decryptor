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

int str_cmp(char *str1, char* str2);
void okPrintNow(short number);
int getNumber(char *charNum);
int validAlphabet(char *str);
int validMorse(char *str);
int countLengthString(char *strCount);


/**
 * @brief Validates command line arguments passed to the program.
 * @details This function will validate all the arguments passed to the program
 * and will return a unsigned short (2 bytes) that will contain the
 * information necessary for the proper execution of the program.
 *
 * IF -p is given but no (-r) ROWS or (-c) COLUMNS are specified this function
 * MUST set the lower bits to the default value of 10. If one or the other
 * (rows/columns) is specified then you MUST keep that value rather than assigning the default.
 *
 * @param argc The number of arguments passed to the program from the CLI.
 * @param argv The argument strings passed to the program from the CLI.
 * @return Refer to homework document for the return value of this function.
 */

unsigned short validargs(int argc, char **argv) {

    unsigned short shiftBit=0;
    int shiftRow, shiftColumn;
    int numberOfRow, numberOfColumn;
    int flagP=0;
    int flagF=0;

    // **** Display the usage if nothing is eneterd not working ??
    if(argc ==1 ){
        return 0;
    }
    // Checking if the first arg is -h
    if(str_cmp("-h", *(argv+1)) == 1)
    {
        int shifter = 1<<15;
        shiftBit= shifter| shiftBit;
        return shiftBit;
    }else{
        if(argc == 2){
            //printf("EXIT FAILURE\n");
            return 0;
        }
    }
    int k=1,c=1,r=1;
    for(int i=1; i < argc; i++){
        if(i == 1){
            // becuase -h is already check so -p and -f byitself is error
             if(str_cmp("-p", *(argv+i)) == 1)
            {
                int shifter = 0 << 14;
                shiftBit= shiftBit | shifter;

            }
            else if(str_cmp("-f", *(argv+i)) == 1)
            {
                flagF=1;
                flagP=2;
                int shifter = 1 << 14;
                shiftBit = shifter | shiftBit;
            }
            else
            {
                //printf("EXIT FAILURE\n");
                return 0;
            }
        }

        else if(i == 2)
        {
            if(str_cmp("-d", *(argv+i)) == 1){

                int shifter = 1 << 13;
                shiftBit = shifter | shiftBit;

            }
            else if(str_cmp("-e", *(argv+i)) == 1){

                int shifter = 0 << 13;
                shiftBit = shifter | shiftBit;
            }
             else
            {
                //printf("EXIT FAILURE\n");
                return 0;
            }
        }
        else if( i == 3 || 5 || 7)
        {
            int numValue=0;

            if((str_cmp("-k", *(argv+i)) == 1) && k != 0) {
                k = 0;
                i++;
                int n=0;

                if(*(argv+i)== NULL ){
                    return 0;
                }

                if(flagF == 1){
                     n= validMorse(*(argv+i));
                }else{
                     n= validAlphabet(*(argv+i));
                }


                if(n == 0){
                    //printf("EXIT FAILURE\n");
                    return 0;
                }else{
                    key= *(argv+i);
                }

            }
            else if((str_cmp("-r", *(argv+i)) == 1) && r != 0)
            {


                r = 0;
                if(flagF == 1){
                    //printf("EXIT FAILURE \n");
                    return 0;
                }
                if(*(argv+i+1)== NULL ){
                    return 0;
                }

                flagP=1;
                i++;
                numValue= getNumber(*(argv+i));
                // validate rows and columns
                if((numValue > 8) && (numValue < 16)){
                    numberOfRow = numValue;
                    shiftRow = numValue << 4;
                    shiftBit = shiftRow | shiftBit;
                }else{
                    return 0;
                }
            }
            else if((str_cmp("-c",*(argv+i))==1) && c!=0)
            {


                c = 0;
                if(flagF == 1){
                    //printf("EXIT FAILURE\n");
                    return 0;
                }

                if(*(argv+i+1)== NULL ){
                    return 0;
                }

                flagP=1;
                i++;
                numValue= getNumber(*(argv+i));
                if((numValue > 8) && (numValue < 16)){
                    numberOfColumn = numValue;
                    shiftColumn = numValue << 0;
                    shiftBit = shiftColumn | shiftBit;
                }else{
                    return 0;
                }
            }
            else{
                //printf("EXIT FAILURE\n");
                return 0;
            }
        }
        else{
            return 0;
        }
    }

    if(flagP == 1){     // If p is set but row and column might be default


        if(r !=0){
            numberOfRow = 10;   // setting Row if Row is not given
            shiftRow = 10<<4;
            shiftBit = shiftBit | shiftRow;
        }
        else if (c!= 0)
        {
            shiftColumn = 10<<0;
            numberOfColumn = 10;    // setting Col if col is not given
            shiftBit = shiftBit | shiftColumn;
        }else{
            // do nothing and relax
        }
    }
    else if(flagP == 2){
        // do nothing
    }
    else{
        numberOfRow = 10;
        numberOfColumn = 10;
        shiftRow = 10<<4;
        shiftBit = shiftBit | shiftRow;
        shiftColumn = 10<<0;
        shiftBit = shiftBit | shiftColumn;
    }

    /*
         Ask later if polybus below the character checking is necessary ??
    */
    //Checking if the length of Polybus is less than Row * Column
    if(!flagF){
        char *lenPoly = polybius_alphabet;
        int z = countLengthString(lenPoly);
        if((numberOfRow * numberOfColumn) < z){
            //
            return 0;
        }else{
            // do nothing
        }
    }


    //okPrintNow(shiftBit);
    //printf("\n");
    return shiftBit;
}
///// ********** Extra Function Added  ******

int countLengthString(char *strCount){
    int z=0;
    while(*(strCount+z) != '\0'){
        z++;
    }
    //printf("%d \n",z);
    return z;
}

// Validate for the Morse Alphabets
int validMorse(char *str){
    const char *cipherAlphabets = fm_alphabet;
    char *strComp= str;
    int a =0;
    int b =0;
    int curr=0;



    // checking if all the characters are valid or not ::
    while(*(strComp+a)!= '\0'){
        if(*(cipherAlphabets+b) == '\0'){
            return 0;
        }
        if(*(strComp+a) == *(cipherAlphabets+b)){
            a++;
            b=0;
            curr = 1;
        }
        else{
            b++;
        }
    }
    a=0;
    b=0;
    curr=0;


    // compare with oneself first and see if some character is repeated
    while (*(strComp+a)!='\0'){
        if(*(strComp+b) == '\0'){
            a++;
            b=0;
            curr = 0;
        }else{
            if(*(strComp+b)== *(strComp+a)){
                curr++;
            }
            b++;
            if(curr> 1){
                return 0;
            }
        }
    }
    return 1;
}

// Validate for the Polyibus Albhabets
int validAlphabet(char *str){
    char *cipherAlphabets = polybius_alphabet;
    char *strComp= str;
    int a =0;
    int b =0;
    int curr=0;
    while(*(strComp+a)!= '\0'){
        if(*(cipherAlphabets+b) == '\0'){
            return 0;
        }
        if(*(strComp+a) == *(cipherAlphabets+b)){
            a++;
            b=0;
            curr = 1;
        }
        else{
            b++;
        }
    }
    a=0;
    b=0;
    curr=0;

    // compare with oneself first and see if some character is repeated
    while (*(strComp+a)!='\0'){
        if(*(strComp+b) == '\0'){
            a++;
            b=0;
            curr = 0;
        }else{
            if(*(strComp+b)== *(strComp+a)){
                curr++;
            }
            b++;
            if(curr> 1){
                return 0;
            }
        }
    }
    return 1;
}
// changing the character array of int to Number with validation
int getNumber(char *character1)
{   int i=0;
    int sumNumber=0;
    while (*(character1+i)!= '\0') //iterate until the array end
    {
        if( *(character1+i) <= '9' && *(character1+i)>= '0')
        {
            sumNumber = (*(character1+i)-'0') + sumNumber*10 ;
        }
        else
        {
            return -10;
        }
        i++;
    }
    return sumNumber;
}

// Compare two string and return 1 if same and 0 if different
int str_cmp(char *str1, char *str2)
{
    int same=1, diff=0;
    int counter=0;
    while(*(str1+counter)!='\0')
    {
         if(*(str1+counter) != *(str2 + counter)){
            return diff;
         }
         counter++;
    }
    return same;
}

// void okPrintNow(short num)
// {
//     if(num){
//         okPrintNow(num >>1);
//         putc((num & 1)? '1' : '0', stdout);
//     }
// }