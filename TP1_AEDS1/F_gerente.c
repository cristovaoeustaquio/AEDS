#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CRUD.h"
typedef struct ingredientes_ //struct que contem codigo do ingrediente e a respectiva quantidade
{
    char coding[10];
    char qtd[5];
} ingredientes;
typedef struct prato_ //struct que contem o nome do prato e os ingredientes
{
    char nprt[11];
    ingredientes in;
} prato;
typedef struct usuario_ //struct de usuario
{
    char login[11]; //login lido do arquivo
    char logind[11]; //login digitado pelo usuario
    char senha[9]; //senha lida do arquivo
    char senhad[9]; //senha digitada pelo usuario
} usuario;
typedef struct gestor_
{
    char senhacomp[100]; //senha lida do arquivo
    char senhadig[100]; //senha digitada pelo usuario
    char newsenha[100]; //senha que substituira a senha antiga
} gestor;
void createUsr() //funcao para criar usuario
{
    FILE *pc = fopen("usuarios.txt","a"); //abrindo o arquivo no modo anexo
    usuario usr;
    if(pc!=NULL)
    {
        printf("\nDigite o novo login:\n");
        fflush(stdin);
        gets(usr.login); //lendo do usuario o login
        printf("\nDigite a senha para %s:\n",usr.login);
        scanf("%s",usr.senha); //lendo a senha do usuario
        strcat(usr.senha,"\n"); //adicionando um \n a string
        fprintf(pc,"%s %s\n",usr.login,usr.senha); //escrevendo a string no arquivo
        system("cls");
        printf("\nUsuario registrado!\n");
        fclose(pc); //fechando arquivo
    }
}
void exibeUsr() //funcao para exibir usuario
{
    char u[100]; //string que guada a linha lida do arquivo do arquivo
    FILE *pc = fopen("usuarios.txt","r"); //abrindo o arquivo em modo leitura
    if(pc != NULL)
    {
        while (fgets(u,100,pc) != NULL) //lendo arquivo ate o final e salvando a linha na string
        {
            fflush(stdin);
            if(strcmp(u,"DELETADO!\n")!= 0) //Verificando se a linha não e uma flag
                printf("%s",u);
        }
        fclose(pc); //fechando arquivo
    }
}
void altSGer() //funcao para alterar a senha do gerente
{
    int i=0; //variavel que conta quantas vezes a senha foi digitada
    gestor g;
    FILE *psg=fopen("senha_gerente.txt","r+"); //abrindo o arquivo em modo leitura e escrita
    if(psg!=NULL)
    {
        fscanf(psg,"%s", g.senhacomp); //lendo a senha que esta no arquivo e salvando na struct
        printf("Digite sua senha:\n");
        scanf("%s",g.senhadig); //lendo a senha digitada pelo usuario
        fclose(psg); //fechando o arquivo
        while(strcmp(g.senhadig,g.senhacomp)!= 0) //enquanto a senha digitada for diferente a senha lida do arquivo
        {
            printf("\nSenha incorreta, digite novamente:\n");
            scanf("%s",g.senhadig);
            i++;
            if(i>2) //se o numero de tentativas for 3 voltara ao menu
                break;
        }
        if(strcmp(g.senhadig,g.senhacomp)==0) //se as senha digitada for igual a senha lida do arquivo
        {
            psg = fopen("senha_gerente.txt","w"); //abrindo o arquivo em modo escrita
            printf("\nDigite sua nova senha:\n");
            scanf("%s",g.newsenha); //lendo a nova senha
            fseek(psg, 0, SEEK_SET); //setando o cursor para o inicio do arquivo
            fprintf(psg,"%s",g.newsenha);
            fprintf(psg,"%s"," ");   //sobreescrevendo a senha
            printf("\nSenha Alterada!\n");
            fclose(psg); //fechando o arquivo
        }
    }
}
void altUsr() //funcao para alterar usuario
{
    FILE *pc = fopen("usuarios.txt","r+"); //abrindo o arquivo em modo leitura e escrita
    usuario u;
    char linha[40]; //string que vai receber as linhas do arquivo
    if(pc != NULL)
    {
        printf("\nDigite o login do usuario que deseja mudar: \n");
        fflush(stdin);
        gets(u.logind); //lendo login que sera alterado
        while(fgets(linha,40,pc)!=NULL) //lendo ate o final do arquivo e salvando a linha na string
        {
            char *token = strtok(linha," "); //guardando no token o login lido do arquivo
            if(strcmp(u.logind,token)== 0) //comparando o login digitado com o do arquivo
            {
                printf("\nDigite o novo login (obrigatoriamente 4 digitos!):\n");
                fflush(stdin);
                gets(u.login); //lendo novo login
                printf("\nDigite a nova senha (obrigatoriamente 4 digitos!):\n");
                fflush(stdin);
                gets(u.senhad); //lendo nova senha
                fseek(pc,-11,SEEK_CUR); //setando o cursor para o inicio da linha atual
                fprintf(pc,"%s %s\n",u.login,u.senhad); //sobreescrevendo a linha
                system("cls");
                printf("Usuario alterado com sucesso!\n");
                fclose(pc); //fechando arquivo
                break;
            }
        }
    }
}
void delUsr() //funcao para deletar usuario
{
    usuario del;
    char line[40]; //string que vai armazenar a linha do arquivo
    printf("\nDigite o usuario que deseja deletar:\n");
    fflush(stdin);
    gets(del.logind); //lendo login que sera deletado
    FILE *pc = fopen("usuarios.txt","r+");
    while(fgets(line,40,pc)!=NULL) //lendo linhas ate o final do arquivo e salvando a linha na string
    {
        char *token = strtok(line," "); //token que recebera o login do arquivo
        if(strcmp(del.logind,token)== 0) //comparando o login digitado com o login do arquivo
        {
            fseek(pc,-11,SEEK_CUR); //setando o cursor para o inicio da posicao atual
            fprintf(pc,"DELETADO!\n"); //subtituindo a linha pela FLAG
            system("cls");
            printf("\nUsuario deletado!\n");
            fclose(pc); //fechando o arquivo
            break;
        }
    }
}
void creatIng() //funcao para adicionar um ingrediente
{
    char lin[30]; //string que armazena a nova linha
    prato h;
    char z3[] = "000"; //->
    char z2[] = "00"; //->      strings usadas para deixar o numero de caracteres da quantidade padronizado
    char z1[] = "0";  //->
    FILE *ping = fopen("estoque.txt","a"); //abrindo arquivo
    if(ping != NULL)
    {
        printf("\nDigite o codigo do novo ingrediente (3 digitos): \n");
        fflush(stdin);
        gets(h.in.coding); //lendo o codigo que desejamos encontrar
        strcat(h.in.coding," ");
        strcpy(lin,h.in.coding); //copiando para nova linha o conteudo da string que contem o codigo do ingrediente
        printf("\nDigite a quantidade do ingrediente (max 4 digitos):\n");
        fflush(stdin);
        gets(h.in.qtd); //lendo a quantidade do novo ingrediente
        if(strlen(h.in.qtd)==1) //se tiver um caractere em quantidade
        {
            strcat(z3,h.in.qtd);
            strcat(lin,z3);
            fprintf(ping,"\n%s",lin); //completa com tres zeros e escreve no arquivo
        }
        else if(strlen(h.in.qtd)==2) //se tiver dois caracteres em quantidade
        {
            strcat(z2,h.in.qtd);
            strcat(lin,z2);
            fprintf(ping,"\n%s",lin); //completa com dois zeros e escreve no arquivo
        }
        else if(strlen(h.in.qtd)==3) //se tiver tres caracteres em quantidade
        {
            strcat(z1,h.in.qtd);
            strcat(lin,z1);
            fprintf(ping,"\n%s",lin); //completa com um zero e escreve no arquivo
        }
        else
        {
            strcat(lin,h.in.qtd);       //se a quandidade tiver quatro caracteres
            fprintf(ping,"\n%s",lin);   //escreve no arquivo
        }
        system("cls");
        printf("Ingrediente cadastrado com sucesso!\n");
        fclose(ping);
    }
}
void exibeEst() //funcao que exibe o estoque
{
    char linha[200]; //string que armazena linha lida do arquivo
    FILE *ping=fopen("estoque.txt","r");
    while(fgets(linha,200,ping)!=NULL) //lê ate o fim do arquivo e salva a linha na string
    {
        printf("%s",linha); //printa na tela
    }
    fclose(ping);
}
void altQtdIng() //funcao que altera a quantidade de um determinado ingrediente
{
    char ing[4]; //string que armazena o codigo do ingrediente que sera editado
    char z3[] = "000";
    char z2[] = "00";   //strings que completam o numero de caracteres da quantidade
    char z1[] = "0";
    prato p;
    printf("\nEstoque\n");
    printf("Cod Qtd\n");
    exibeEst(); //chamando a funcao apara exibir o estoque
    printf("\nDigite o codigo do ingrediente que deseja alterar a quantidade:\n");
    scanf("%s",ing); //lendo a string do codigo
    char li[50]; //string que recebera a linha lida do arquivo
    FILE *ping=fopen("estoque.txt","r+"); //abrindo arquivo
    if(ping!=NULL)
    {
        while(fgets(li,50,ping)!=NULL) //fazendo leitura ate o fim do arquivo
        {
            char *token=strtok(li," "); //token que guarda o conteudo da linha ate o caractere delimitador
            strcpy(p.in.coding,token); //copiando o token para a struct
            if(strcmp(p.in.coding,ing)==0) // compara duas strings
            {
                printf("Digite a nova quantidade:\n");
                fflush(stdin);
                gets(p.in.qtd); //le a nova quantidade
                fseek(ping,-6,SEEK_CUR); //seta o cursor para o inicio da linha autal
                if(strlen(p.in.qtd)==1) //verifica o tamanho em bytes da string
                {
                    strcat(z3,p.in.qtd);        //completa com tres zeros
                    fprintf(ping,"%s\n",z3);    //escreve no arquivo
                }
                else if(strlen(p.in.qtd)==2)
                {
                    strcat(z2,p.in.qtd);        //completa com dois zeros
                    fprintf(ping,"%s\n",z2);    //escreve no arquivo
                }
                else if(strlen(p.in.qtd)==3)
                {
                    strcat(z1,p.in.qtd);         //completa com um zero
                    fprintf(ping,"%s\n",z1);    //escreve no arquivo
                }
                else
                {
                    fprintf(ping,"%s\n",p.in.qtd); //se tiver 4 caracteres escreve na string
                }
                system("cls");
                printf("Quantidade atualizada!\n");
                fclose(ping);
                break;
            }
        }
    }
}
void createCard() //funcaio que adiociona um prato ao cardapio
{
    prato p;
    FILE *pcard=fopen("cardapio.txt","a"); //abre o arquivo em modo anexo
    if(pcard!=NULL)
    {
        printf("\nCardapio\n");
        exibeCard(); //chamando a funcao para exibir o cardapio
        printf("\nDigite o novo prato desejado de acordo com os modelos acima:\n");
        fflush(stdin);
        gets(p.nprt); //lendo o nome do novo prato
        fprintf(pcard,"\n%s",p.nprt); //escrevendo no arquivo
        system("cls");
        printf("Prato cadastrado com sucesso!\n");
        fclose(pcard);
    }
}
void gerente () //menu que chama as funcoes acima
{
    int n,i=0,o=0;
    gestor h;
    FILE *psg=fopen("senha_gerente.txt","r");
    if(psg!=NULL)
    {
        fscanf(psg,"%s", h.senhacomp);
        printf("Digite sua senha:\n");
        scanf("%s",h.senhadig); //lendo a senha digitada
        while(strcmp(h.senhadig,h.senhacomp) != 0) //caso a senha esteja incorreta sera solicitada novamente
        {
            printf("\nSenha incorreta, digite novamente:\n");
            scanf("%s",h.senhadig);
            i++; //conta o numero de tentativas
            if(i>2) //se foram feitas mais de 3 tentativas volta ao menu anterior
                break;
        }
        while(strcmp(h.senhadig,h.senhacomp) == 0) //compara a senha digitada e lida do arquivo e se foram iguais exibe o menu
        {
            printf("\nDigite (1) para criar usuario;\nDigite (2) para alterar usuario;\nDigite (3) para adicionar ingrediente no estoque;\n");
            printf("Digite (4) para alterar senha gerente;\nDigite (5) para deletar usuario;\nDigite (6) para exibir pedido;\n");
            printf("Digite (7) para alterar quantidade do estoque;\nDigite (8) para criar prato;\nDigite (9) para sair.\nEntrada: ");
            scanf("%d",&n);
            system("cls");
            switch(n)
            {
            case 1:
                createUsr();
                break;
            case 2:
                printf("\nUsuarios:\n");
                exibeUsr();
                printf("\n");
                altUsr();
                break;
            case 3:
                printf("\nESTOQUE:\n");
                printf("Cod Qtd\n");
                exibeEst();
                printf("\n");
                creatIng();
                break;
            case 4:
                altSGer();
                break;
            case 5:
                printf("\nUSUARIOS:\n");
                exibeUsr();
                printf("\n");
                delUsr();
                break;
            case 6:
                printf("Pedidos:\n");
                exibePedidos();
                printf("\nPara registrar digite 1 e para voltar digite 0:\n");
                scanf("%d",&o);
                if(o == 1)
                {
                    registraPedido();
                    system("cls");
                    printf("Pedido registrado!\n");
                }
                break;
            case 7:
                altQtdIng();
                break;
            case 8:
                createCard();
                break;
            case 9:
                printf("\nGerente saiu\n");
                break;
            default:
                printf("\nDigito invalido\n");
            }
            if(n == 9)
                break;
        }
        fclose(psg);
    }
}
