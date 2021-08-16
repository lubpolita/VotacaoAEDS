#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //delay
#include "arvoreBinaria.h"
#include "votacao.h"
#include "cores.h"

//a funcao retorna o titulo se ele existir e se nao existir retorna 0
int existeTitulo(No* pRaiz, int titulo) {
    int valorEncontrado = 0;
    if (pRaiz == NULL) return 0;
    if (titulo < pRaiz->info->titulo_eleitor)
        return existeTitulo(pRaiz->esq, titulo);
    if (titulo > pRaiz->info->titulo_eleitor)
        return existeTitulo(pRaiz->dir, titulo);
    valorEncontrado = pRaiz->info->titulo_eleitor;
    return valorEncontrado;
}

//esta funcao retorna a info do titulo se ela existir
Info *retornaInfoTitulo(No* pRaiz, int titulo) {
    Info *valorEncontrado;
    if (pRaiz == NULL) return NULL;
    if (titulo < pRaiz->info->titulo_eleitor)
        return retornaInfoTitulo(pRaiz->esq, titulo);
    if (titulo > pRaiz->info->titulo_eleitor)
        return retornaInfoTitulo(pRaiz->dir, titulo);
    valorEncontrado = pRaiz->info;
    return valorEncontrado;
}

//esta funcao retorna a info do titulo se ela existir
Info *retornaInfoVoto(No* pRaiz, int titulo) {
    Info *valorEncontrado;
    if (pRaiz == NULL) return NULL;
    if (titulo < pRaiz->info->voto)
        return retornaInfoVoto(pRaiz->esq, titulo);
    if (titulo > pRaiz->info->voto)
        return retornaInfoVoto(pRaiz->dir, titulo);
    valorEncontrado = pRaiz->info;
    return valorEncontrado;
}

void inOrderTitulos(No *raiz)
{
    if (raiz)
    {
        inOrderTitulos(raiz->esq);
        printf("\n\n╔═══════════════════════════════════════════════════════════════╗");
        printf("\n║----------------------------ELEITOR----------------------------║\n");
        printf("║Nome: %s\n║Titulo: %d\n", raiz->info->Nome, raiz->info->titulo_eleitor);
        printf("\n║Vezes votado: %.0lf\n", raiz->info->vezesVotado);
        printf("\n╚═══════════════════════════════════════════════════════════════╝\n");
        inOrderTitulos(raiz->dir);
    }
}

//retorna o no do titulo encontrado
No *retornaNoTitulo(No* pRaiz, int titulo) {
    No *valorEncontrado;
    if (pRaiz == NULL) return NULL;
    if (titulo < pRaiz->info->titulo_eleitor)
        return retornaNoTitulo(pRaiz->esq, titulo);
    if (titulo > pRaiz->info->titulo_eleitor)
        return retornaNoTitulo(pRaiz->dir, titulo);
    valorEncontrado = pRaiz;
    return valorEncontrado;
}

//essa funcao imprimi APENAS os titulos que ja votaram
void inOrderVotou(No *raiz, No *arvoreVotos){
    if(raiz){
        inOrderVotou(raiz->esq, arvoreVotos);
        if(retornaInfoTitulo(arvoreVotos, raiz->info->titulo_eleitor)){
            corCiano();
            printf("\n\n╔═══════════════════════════════════════════════════════════════╗");
            printf("\n║----------------------------ELEITOR----------------------------║\n");
            corPadrao();
            printf("║Nome: %s║Titulo: %d", raiz->info->Nome, raiz->info->titulo_eleitor);
            corCiano();
            printf("\n╚═══════════════════════════════════════════════════════════════╝\n");
            corPadrao();

        }
        inOrderVotou(raiz->dir, arvoreVotos);
    }
}

void inOrderVotouWin(No *raiz, No *arvoreVotos){
    int i;
    if(raiz){
        inOrderVotouWin(raiz->esq, arvoreVotos);
        if(retornaInfoTitulo(arvoreVotos, raiz->info->titulo_eleitor)){
            corCiano();
            printf("\n%c", 201);
            for(i = 0; i < 64; i++) printf("%c", 205);	
	        printf("%c", 187);

            printf("\n%c----------------------------ELEITOR----------------------------%c\n",186,186);
            corPadrao();
            printf("%cNome: %s%cTitulo: %d", 186, raiz->info->Nome, 186, raiz->info->titulo_eleitor);
            corCiano();
              printf("\n");
	        printf("%c", 200);
    	    for(i = 0; i < 64; i++) printf("%c", 205);	
	        printf("%c", 188);
            corPadrao();

        }
        inOrderVotouWin(raiz->dir, arvoreVotos);
    }    

}


//essa funcao imprimi os votos pelo metodo in order
void inOrderVotos(No *raiz)
{
    if (raiz)
    {
        inOrderVotos(raiz->esq);
        printf("\n\n_____________________________________\n");
        printf("\n║Titulo║ %d                            ║\n║Voto║ %d                             ║", raiz->info->titulo_eleitor, raiz->info->voto);
        inOrderVotos(raiz->dir);
    }
}

//essa funcao imprime a arvore em forma decrescente
void imprimeDecrescente(No *no){
    if(no){
        imprimeDecrescente(no->dir);
        corCiano();
        printf("\n\n╔═══════════════════════════════════════════════════════════════╗");
        printf("\n║----------------------------ELEITOR----------------------------║\n");
        corPadrao();
        printf("\n║Nome: %s",no->info->Nome);
        printf("\n║Titulo: %d \n", no->info->titulo_eleitor);
        printf("\n║Votos: %.0lf \n", no->info->vezesVotado);
        corCiano();
        printf("\n╚═══════════════════════════════════════════════════════════════╝\n");
        corPadrao();
        imprimeDecrescente(no->esq);
    }
}


void imprimeDecrescenteWin(No *no){
       if(no){
        imprimeDecrescenteWin(no->dir);
        int i;
        corCiano();
        printf("\n");
        printf("%c", 201);
        for(i = 0; i < 64; i++) printf("%c", 205);	
	    printf("%c", 187);

        printf("\n%c----------------------------ELEITOR----------------------------%c\n", 186,186);
        printf("%cNome: %s\n%cTitulo: %d\n", 186, no->info->Nome, 186, no->info->titulo_eleitor);
        printf("\n%cVotos: %.0lf\n", 186, no->info->vezesVotado);

        printf("\n");
	    printf("%c", 200);
    	for(i = 0; i < 64; i++) printf("%c", 205);	
	    printf("%c", 188);
        imprimeDecrescenteWin(no->esq);
    }


}
//essa funcao ordena a arvoreTitulos de acordo com a contagem de votos 
//e retorna a arvore ordenada para arvoreDecrescente
void ordernaVotacao(No *arvoreTitulos, No **arvoreDecrescente){
    Info *info; 
    info = (Info *) malloc(sizeof(Info));

    if(arvoreTitulos){
        ordernaVotacao(arvoreTitulos->dir, arvoreDecrescente);
        info = arvoreTitulos->info;
        inserePorVoto(arvoreDecrescente, info);
        ordernaVotacao(arvoreTitulos->esq, arvoreDecrescente);
    }
}   

void menuWin(){
	int i; 

    corCiano();
	printf("\n\t\t\t");
	printf("%c", 201);
    for(i = 0; i < 64; i++) printf("%c", 205);	
	printf("%c", 187);

	printf("\n\t\t\t");
	printf("%c", 186);
	for(i = 0; i < 30; i++) printf(" ");
	printf("MENU");
	for(i = 0; i < 30; i++) printf(" ");
	printf("%c", 186);
	
	printf("\n\t\t\t");
	printf("%c", 204);
    	for(i = 0; i < 64; i++) printf("%c", 205);	
	printf("%c", 185);


	printf("\n\t\t\t%c ", 186); corPadrao(); printf("1) Cadastrar titulo");
    corCiano(); printf("                                            %c",186);
    printf("\n\t\t\t%c ",186); corPadrao(); printf("2) Descadastrar titulo");
    corCiano(); printf("                                         %c ",186);
    printf("\n\t\t\t%c ",186); corPadrao(); printf("3) Iniciar nova votacao");
    corCiano(); printf("                                        %c ",186);
    printf("\n\t\t\t%c ",186); corPadrao(); printf("4) Votar"); 
    corCiano(); printf("                                                       %c ",186);
    printf("\n\t\t\t%c ",186); corPadrao(); printf("5) Retirar voto"); 
    corCiano(); printf("                                                %c ",186);
    printf("\n\t\t\t%c ",186); corPadrao(); printf("6) Resultado parcial"); 
    corCiano(); printf("                                           %c ",186);
    printf("\n\t\t\t%c ",186); corPadrao(); printf("7) Listar todos nomes/titulos de pessoas que ja votaram");
    corCiano(); printf("        %c ",186);
    printf("\n\t\t\t%c ",186); corPadrao(); printf("8) Sair");
    corCiano(); printf("                                                        %c ",186);

    printf("\n\t\t\t");
	printf("%c", 200);
    	for(i = 0; i < 64; i++) printf("%c", 205);	
	printf("%c", 188);

    corPadrao();
    printf("\n\t\t\t%c Digite a opcao desejada: ", 175);
}

//funcao para imprimir o menu para o usuario
void menu(){
	int i;
    corCiano();	
    printf("\n\t\t\t╔═══════════════════════════════════════════════════════════════╗");
    printf("\n\t\t\t║                              MENU                             ║");
    printf("\n\t\t\t╠═══════════════════════════════════════════════════════════════╣");
    printf("\n\t\t\t║ "); corPadrao(); printf("1) Cadastrar titulo");
    corCiano(); printf("                                           ║");
    printf("\n\t\t\t║ "); corPadrao(); printf("2) Descadastrar titulo");
    corCiano(); printf("                                        ║");
    printf("\n\t\t\t║ "); corPadrao(); printf("3) Iniciar nova votacao");
    corCiano(); printf("                                       ║");
    printf("\n\t\t\t║ "); corPadrao(); printf("4) Votar"); 
    corCiano(); printf("                                                      ║");
    printf("\n\t\t\t║ "); corPadrao(); printf("5) Retirar voto"); 
    corCiano(); printf("                                               ║");
    printf("\n\t\t\t║ "); corPadrao(); printf("6) Resultado parcial"); 
    corCiano(); printf("                                          ║");
    printf("\n\t\t\t║ "); corPadrao(); printf("7) Listar todos nomes/titulos de pessoas que ja votaram");
    corCiano(); printf("       ║");
    printf("\n\t\t\t║ "); corPadrao(); printf("8) Sair");
    corCiano(); printf("                                                       ║");
    printf("\n\t\t\t╚═══════════════════════════════════════════════════════════════╝\n");
    corPadrao();
    printf("\n\t\t\t➢ Digite a opcao desejada: ");
}

void menuVotacao(){
    corCiano(); 
    printf("\n║--------------------------VOTE--------------------------------║");
    printf("\n║");
    corPadrao();
    printf("➢ Digite o titulo da pessoa que deseja votar: ");
}

void menuVotacaoWin(){
    corCiano(); 
    printf("\n%c--------------------------VOTE--------------------------------%c",186, 186);
    printf("\n%c", 186);
    corPadrao();
    printf("%c Digite o titulo da pessoa que deseja votar: ", 175);
}

//funcao para adicionar um delay na tela do usuario, para que as mensagens possam ser lidas
void delay(int seg){
     sleep(seg);
}