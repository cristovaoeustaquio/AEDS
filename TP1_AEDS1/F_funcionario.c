#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CRUD.h"
typedef struct usuario_ //struc de usuario
{
    char login[11]; //login lido do arquivo
    char logind[11]; //login digitado pelo usuario
    char senha[9]; //senha lida do arquivo
    char senhad[9]; //senha digitada pelo usuario
} usuario;
void registraPedido() //funcao que escreve em um arquivo o pedido do cliente
{
    char ped[20]; //string que armazena os pedidos
    FILE *pped = fopen("pedido_pendente.txt","r"); //abrindo arquivo em modo de leitura
    FILE *ppedr=fopen("pedidos_registrados.txt","w"); //abrindo o arquivo em modo escrita
    if(ppedr!=NULL&&pped!=NULL) //verificando se nao houve erro ao abrir arquivos
    {
        while(fgets(ped,20,pped)!=NULL) //lendo o arquivo ate o final
        {
            fprintf(ppedr,"%s",ped); //escrevendo a string no arquivo
            printf("\nPedido registrado!\n");
        }
    }
    fclose(pped);
    fclose(ppedr);  //fechando arquivos
}
void exibePedidos() //funcao que exibe os pedidos pendentes
{
    char linha[200]; //string que armazena a linha lida do arquivo
    FILE *pped = fopen("pedido_pendente.txt","r"); //abrindo o arquivo em modo de leitura
    if(pped != NULL)
    {
        while (fgets(linha,200,pped)) //lendo o arquivo ate o final e salvando a linha na string
        {
            fflush(stdin);
            printf("%s",linha); //printando na tela
        }
        fclose(pped);//fechando arquivo
    }
}
void funcionario() //funcao que exibe o menu para o funcionario
{
    int n, i=0;
    char fi[40];
    usuario u;
    FILE *pf = fopen("usuarios.txt","r");
    if(pf!=NULL)
    {
        printf("Digite seu login de 4 caracteres:\n");
        scanf("%s",u.logind);
        while(fgets(fi,40,pf)!=NULL) //lendo ate o final do arquivo e salvando a linha na string
        {
            char *token = strtok(fi," "); //guardando no token o login lido do arquivo
            strcpy(u.login,token);  //copiando o conteudo do token na string referente ao login
            if(strcmp(u.logind,u.login)==0) //verificando se o login digitado corresponde a algum login no arquivo
            {
                printf("Digite sua senha de 4 digitos:\n");
                scanf("%s",u.senhad); // le senha
                token = strtok(NULL, " \n"); //token agora recebe a senha lida do arquivo
                strcpy(u.senha,token); //copia o conteudo de token
            }

            if(strcmp(u.senhad,u.senha) != 0) //caso digite a senha errada, tera um numero limitado de tentativas
            {
                while(i!=2)
                {
                    printf("\nSenha incorreta, digite novamente:\n");
                    scanf("%s",u.senhad);
                    i++;
                    if(strcmp(u.senha,u.senhad)==0)
                        break;
                }
            }
            if(strcmp(u.senha,u.senhad)==0 && strcmp(u.login,u.logind)==0) //se o login e senha estiverem corretos, libera o acesso ao menu
            {
                while(1)
                {
                    printf("\nDigite 1 para exibir o pedido, 2  para registrar o pedido, 3 para sair:\n");
                    scanf("%d",&n);
                    switch(n)
                    {
                    case 1:
                        printf("\nPedido:\n");
                        exibePedidos();
                        break;
                    case 2:
                        registraPedido();
                        break;
                    case 3:
                        system("cls");
                        printf("\nSaiu\n");
                        break;
                    default:
                        printf("\nDigito invalido\n");
                    }
                    if(n == 3)
                        break;
                }
            }
        }
    }
    fclose(pf);
}
