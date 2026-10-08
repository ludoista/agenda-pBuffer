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

#define INT_AT(o) (*(int *)((char *)pBuffer + (o)))

void *Adicionar(void *pBuffer) {
    printf("Adicionar\n");
    printf("Nome: ");
    scanf(" %51[^\n]", (char *)pBuffer + IN_NAME);
    printf("Idade: ");
    scanf(" %d", &INT_AT(IN_AGE));
    printf("Email: ");
    scanf(" %79[^\n]", (char *)pBuffer + IN_MAIL);

    INT_AT(TOTAL)++;
    pBuffer = realloc(pBuffer, HEADER_SIZE + (INT_AT(TOTAL) * PERSON_SIZE));
    if(pBuffer == NULL) {
        exit(1);
    }
    memcpy((char *)pBuffer + HEADER_SIZE + ((INT_AT(TOTAL)-1) * PERSON_SIZE), (char *)pBuffer + IN_NAME, PERSON_SIZE);

    return pBuffer;
}

void *Remover(void *pBuffer) {
    printf("Digite o nome de quem você quer remover\n");
    printf("Nome: ");
    scanf(" %51[^\n]", (char *)pBuffer + IN_NAME);

    for(INT_AT(RI) = 0; INT_AT(RI) < INT_AT(TOTAL); INT_AT(RI)++) {
        if(strcmp((char *)pBuffer + HEADER_SIZE + (INT_AT(RI) * PERSON_SIZE), (char *)pBuffer + IN_NAME) == 0) {
            break;
        }
    }
    if( INT_AT(RI) == INT_AT(TOTAL) ) {
        printf("Pessoa não encontrada.\n");
        return pBuffer;
    } else {
        memmove((char *)pBuffer + INT_AT(RI)*PERSON_SIZE+HEADER_SIZE, (char *)pBuffer + (INT_AT(RI)+1)*PERSON_SIZE+HEADER_SIZE, (INT_AT(TOTAL) - INT_AT(RI) - 1) * PERSON_SIZE);
    }
    INT_AT(TOTAL)--;
    pBuffer = realloc(pBuffer, HEADER_SIZE + (INT_AT(TOTAL) * PERSON_SIZE));
    if(pBuffer == NULL) {
        exit(1);
    }
    return pBuffer;
}

void *Buscar(void *pBuffer) {
    printf("Digite o nome da pessoa que você quer buscar\n");
    printf("Nome: ");
    scanf(" %51[^\n]", (char *)pBuffer + IN_NAME);

    for(INT_AT(RI) = 0; INT_AT(RI) < INT_AT(TOTAL); INT_AT(RI)++) {
        if(strcmp((char *)pBuffer + HEADER_SIZE + (INT_AT(RI) * PERSON_SIZE), (char *)pBuffer + IN_NAME) == 0) {
            break;
        }
    }
    if( INT_AT(RI) == INT_AT(TOTAL) ) {
        printf("Pessoa não encontrada.\n");
        return pBuffer;
    }

    printf("Nome: %s\n", (char *)pBuffer + HEADER_SIZE + (INT_AT(RI) * PERSON_SIZE) + R_NAME);
    printf("Idade: %d\n", INT_AT(INT_AT(RI) * PERSON_SIZE + HEADER_SIZE + R_AGE));
    printf("Email: %s\n", (char *)pBuffer + HEADER_SIZE + (INT_AT(RI) * PERSON_SIZE) + R_MAIL);
    return pBuffer;
}

void *Listar(void *pBuffer) {
    for(INT_AT(RI) = 0; INT_AT(RI) < INT_AT(TOTAL); INT_AT(RI)++) {
        printf("Nome: %s\n", (char *)pBuffer + HEADER_SIZE + (INT_AT(RI) * PERSON_SIZE) + R_NAME);
        printf("Idade: %d\n", INT_AT(INT_AT(RI) * PERSON_SIZE + HEADER_SIZE + R_AGE));
        printf("Email: %s\n", (char *)pBuffer + HEADER_SIZE + (INT_AT(RI) * PERSON_SIZE) + R_MAIL);
    }
    printf("Total de pessoas: %d\n", INT_AT(TOTAL));
    return pBuffer;
}

int main ( void ) {
    void *pBuffer = malloc(HEADER_SIZE);
    if (pBuffer == NULL) {
        printf("Error: Unable to allocate memory.\n");
        return 1;
    }
    memset(pBuffer, 0, HEADER_SIZE);

    while (1) {
        printf("Menu:\n");
        printf("1. Adicionar\n");
        printf("2. Remover\n");
        printf("3. Buscar\n");
        printf("4. Listar\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");

        scanf("%d", &INT_AT(MENU));

        switch (INT_AT(MENU)) {
            case 1:
                pBuffer = Adicionar(pBuffer);
                break;
            case 2:
                pBuffer = Remover(pBuffer);
                break;
            case 3:
                Buscar(pBuffer);
                break;
            case 4:
                Listar(pBuffer);
                break;
            case 5:
                printf("Sair\n");
                free(pBuffer);
                return 0;
            default:
                printf("Opção inválida.\n");
        }
    }

    free(pBuffer);
    return 0;
}
