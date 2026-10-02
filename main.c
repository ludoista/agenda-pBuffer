#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MENU 0
#define TOTAL 4
#define RI 8
#define RK 12
#define SRC 16
#define DST 24

#define IN_NAME 32
#define IN_AGE 84
#define IN_MAIL 88

#define R_NAME 0
#define R_AGE 52
#define R_MAIL 56

#define HEADER_SIZE 168
#define PERSON_SIZE 136

int main ( void ) {
    void *pBuffer = malloc(HEADER_SIZE);
    memset(pBuffer, 0, HEADER_SIZE);
    if (pBuffer == NULL) {
        printf("Error: Unable to allocate memory.\n");
        return 1;
    }

    free(pBuffer);
    return 0;
}
