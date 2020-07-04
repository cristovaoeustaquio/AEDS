#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CRUD.h"
int main()
{
    int b;
    while(1)
    {
        printf("*******MENU*******\n");
        printf("Digite (1) se for cliente;\nDigite (2) se for funcionario;\nDigite (3) se for gerente;\nDigite (4) para sair.\nEntrada:");
        scanf("%d",&b);
        system("cls");
        switch(b)
        {
        case 1:
            cliente();
            break;
        case 2:
            funcionario();
            break;
        case 3:
            gerente();
            break;
        case 4:
            printf("\nSaiu do sistema\n");
            break;
        default:
            printf("\nDigito invalido\n");
        }
        if(b == 4)
            break;
    }
    return 0;
}
