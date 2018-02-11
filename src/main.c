#include <stdlib.h>

#include "hw1.h"
#include "debug.h"

#ifdef _STRING_H
#error "Do not #include <string.h>. You will get a ZERO."
#endif

#ifdef _STRINGS_H
#error "Do not #include <strings.h>. You will get a ZERO."
#endif

#ifdef _CTYPE_H
#error "Do not #include <ctype.h>. You will get a ZERO."
#endif

int main(int argc, char **argv)
{
    unsigned short mode;
    mode = validargs(argc, argv);
    debug("Mode: 0x%X", mode);
    //printf("0x%X\n",mode);
    //int c = mode & 0x8;
    //c = c >> ;
    //printf("%X",c);

    if(mode == 0){
        USAGE(*argv, EXIT_FAILURE);
    }
    else if(mode & 0x8000) {
        USAGE(*argv, EXIT_SUCCESS);
    }
    else{
         int c = makePolybiusCipher(mode);
         if(c == 1){
            USAGE(*argv, EXIT_FAILURE);
         }
    }
    return EXIT_SUCCESS;
}

/*
 * Just a reminder: All non-main functions should
 * be in another file not named main.c
 */