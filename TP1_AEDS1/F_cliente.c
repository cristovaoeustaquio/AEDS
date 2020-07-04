#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CRUD.h"
void exibeCard() //funcao para exibir o cardapio
{
    char linha[200]; //string que recebe a linha lida do arquivo
    FILE *pcard = fopen("cardapio.txt","r");
    if(pcard != NULL)
    {
        while (!feof(pcard)) //le ate o fim do arquivo
        {
            fflush(stdin);
            fgets(linha,200,pcard);     //guarda na string a linha do arquivo
            printf("%s",linha);     //imprime a string
        }
        fclose(pcard);  //fechando o arquivo
    }
}
void pedidos() //funcao que escreve em um arquivo os pedidos que estao pendentes
{
    FILE *pped = fopen("pedido_pendente.txt","w");  //abrindo o arquivo que sera escrito
    FILE *pcard = fopen("cardapio.txt", "r"); //abrindo o arquivo que sera lido
    int i=1, n, alt=0, l=0;
    char linha[30];
    int *pedido = (int*)calloc(1,sizeof(int)); //vetor alocado dinamicamente para receber o numero do pedido
    if(pedido != NULL && pped != NULL && pcard != NULL) // verificando se os arquivos foram abertos
    {
        while(fgets(linha,30,pcard)!=NULL)
        {
            l++; //variavel que conta as linhas do arquivo cardapio
        }
        printf("\n\nDigite os numeros correspondentes ao seu pedido e ao terminar digite (f):\n");
        while(scanf("%d",&n) != 0) //lendoo uma sequencia de tamanho indeterminado
        {
            if(n<1 || n>l) //se o numero nao estiver dentro do cardapio sera exibida a mensagem
            {
                printf("\nPedido invalido %d nao existe no cardapio\n",n);
                printf("\nDigite o numero do pedido correspondente ao cardapio: \n");
                continue;
            }
            else
            {
                pedido = (int*)realloc(pedido,sizeof(int)*i); //realocando o tamanho do vetor
                pedido[i-1]= n; //atribuindo o numero digitado ao elemento do vetor
                fprintf(pped,"%d ",pedido[i-1]); //escrevendo o elemento no arquivo pedido_pendente
                i++; //indice de elementos
            }
        }
        printf("\nDeseja alterar seu pedido? Sim (1), Nao (0): \n");
        fflush(stdin);
        scanf("%d",&alt); //opcao para alterar o pedido
        while (alt<0 || alt>1)      //verificando se foi digitado corretamente
        {
            printf("\nDigito invalido\n");
            printf("\nDigite (1) para alterar o pedido e (0) para registrar: \n");
            scanf("%d",&alt);
        }
        if(alt == 1)
        {
            system("cls");
            printf("\n*******CARDAPIO*******\n");
            exibeCard();
            pedidos();      //chamando a funcao de forma recurssiva
        }
        else
        {
            system("cls");
            printf("Pedido encaminhado!\n\n");
            fclose(pped);
            fclose(pcard);
        }
    }
    free(pedido); //liberando o ponteiro
}
void cliente() //menu para o cliente
{
    int a;
    printf("Digite 1 para fazer o pedido:\n");
    scanf("%d",&a);
    switch(a)
    {
    case 1:
        printf("\n*******CARDAPIO*******\n");
        exibeCard();
        pedidos();
        break;
    default:
        printf("\n Digito invalido\n");
    }
}
