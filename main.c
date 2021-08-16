#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreBinaria.h"
#include "votacao.h"
#include "cores.h"

//para que seja possivel diferenciar os SO
#ifdef __unix__
#include <unistd.h>
#include <stdio_ext.h>

#elif defined(_WIN32) || defined(WIN32)
#define OS_Windows
#include <windows.h>
#endif

int main(){

    //declaracao para variaveis auxiliares
    No *arvoreTitulos;
    No *arvoreVotos;
    No *aux, *arvoreOrdenada;
    Info *info, *info2;

    int titulo = -1, voto = -1;
    int ocorreuVotacao = 0;
    int opcao, alerta;
    double totalVotos = 0;

    //alocando arvores na memoria
    arvoreTitulos = (No*)malloc(sizeof(No));
    arvoreVotos = (No*)malloc(sizeof(No));
    arvoreOrdenada = (No*)malloc(sizeof(No));

    criaArvore(&arvoreTitulos); //criando arvore de titulos
    criaArvore(&arvoreOrdenada);
    
    //laco do menu principal
    while(opcao != 8){

        //limpar a tela
        #ifdef OS_Windows
            system("cls");
	    menuWin();
        #else
            system("clear");
	    menu(); //menu principal
        #endif


        #ifdef OS_Windows
            fflush(stdin);
        #else
            __fpurge(stdin); //limpa o buffer
        #endif
        scanf("%d", &opcao); //recebe a opcao escolhida pelo usuario

        switch (opcao)
            {
            case 1:
                info = (Info *) malloc(sizeof(Info));
                titulo = -1;
                #ifdef OS_Windows
                printf("\n%c Digite o nome do eleitor: ", 175);
                fflush(stdin);
                #else
                printf("\n➢ Digite o nome do eleitor: ");
                __fpurge(stdin); //limpa o buffer
                #endif
                fgets(info->Nome, 50, stdin);
                while(titulo <= 0){
                    #ifdef OS_Windows
                    printf("\n%c Digite o titulo do eleitor: ", 175);
                    fflush(stdin);
                    #else
                    printf("\n➢ Digite o titulo do eleitor: ");
                    __fpurge(stdin); //limpa o buffer
                    #endif
                    scanf("%d", &titulo);
                    if(titulo < 0){
                        corVermelho();
                        printf("\nPor favor, digite um numero maior que 0. \n");
                        corPadrao();
                        delay(2);
                    }
                    else{
                        int search = existeTitulo(arvoreTitulos, titulo);
                        if(search == titulo){
                            corVermelho();
                            printf("\nEste titulo ja existe! Espere uns segundos para tentar novamente...\n");
                            corPadrao();
                            titulo = -1;
                            delay(2);
                        }
                    }
                }
                info->titulo_eleitor = titulo;
                info->vezesVotado = 0;
                insere(&arvoreTitulos, info);
                corVerde();
                printf("\nEleitor criado! \n");
                corPadrao();
                delay(2);
                break;
            
            case 2:
                #ifdef OS_Windows
                    printf("\n%c Digite o titulo que voce deseja excluir: ", 175);
                    fflush(stdin);
                #else
                    printf("\n➢ Digite o titulo que voce deseja excluir: ");
                    __fpurge(stdin); //limpa o buffer
                #endif
                scanf("%d", &titulo);
                info = retornaInfoTitulo(arvoreTitulos, titulo);
                if(info){
                    retira(*info, &arvoreTitulos);
                    corVerde();
                    printf("\nTitulo excluido com sucesso!\n");
                    corPadrao();
                    delay(3);

                }
                else{
                    corVermelho();
                    printf("\nEste titulo nao existe na lista!\n");
                    corPadrao();
                    delay(2);
                }
                break;
            
            case 3:
                if(ocorreuVotacao == 0) {
                    criaArvore(&arvoreVotos);
                    ocorreuVotacao = 1;
                    corVerde();
                    printf("\nVotacao iniciada com sucesso!\n");
                    corPadrao();
                    delay(2);
                }
                else{ 
                    corVermelho();
                    printf("\n☢ Cuidado! Iniciar uma nova votacao ira excluir a votacao anterior, deseja continuar? ");
                    corPadrao();
                    printf("\n1) Continuar.");
                    printf("\n2) Cancelar.");
                    printf("\nDigite sua opcao: ");
                    #ifdef OS_Windows
                        fflush(stdin);
                    #else
                        __fpurge(stdin); //limpa o buffer
                    #endif
                    scanf("%d", &alerta);
                    if(alerta == 1){
                        arvoreVotos = liberar(&arvoreVotos);
                        arvoreVotos = (No*)malloc(sizeof(No));
                        criaArvore(&arvoreVotos);
                        corVerde();
                        printf("\nVotacao iniciada com sucesso!\n");
                        corPadrao();
                        delay(2);
                    }
                    else{
                        printf("\nOperacao cancelada. Voltando para o menu principal... ");
                        delay(2);
                    }
                }
                break;

            case 4:
                if(ocorreuVotacao == 0){
                    corVermelho();
                    printf("\nPor favor, inicie uma votacao antes de continuar... ");
                    corPadrao();
                    delay(2);
                }
                else{
                    #ifdef OS_Windows
                        printf("\n%c Digite o numero do seu titulo para continuar: ", 175);
                        fflush(stdin);
                    #else
                    printf("\n➢ Digite o numero do seu titulo para continuar: ");
                        __fpurge(stdin); //limpa o buffer
                    #endif
                    scanf("%d", &titulo);

                    if(retornaInfoTitulo(arvoreTitulos, titulo) && !retornaInfoTitulo(arvoreVotos, titulo)){

                        //aloca nova info
                        info = (Info *) malloc(sizeof(Info));
                        info->titulo_eleitor = titulo;

                        #ifdef OS_Windows
                        menuVotacaoWin();
                        fflush(stdin);
                        #else
                        menuVotacao(); //inicia menu
                        __fpurge(stdin); //limpa o buffer
                        #endif

                        scanf("%d", &voto); //le o voto
                        info->voto = voto; //armazenando voto em info

                        aux = retornaNoTitulo(arvoreTitulos, voto); //variavel auxiliar para mudar o valor da quantidade de votos
                        if(aux){
                            aux->info->vezesVotado++;
                            totalVotos++;
                            insere(&arvoreVotos, info); //adicionando info na arvore de votos
                            corVerde();
                            printf("\nSeu voto foi armazenado com sucesso!\n");
                            corPadrao();
                            delay(2);
                        }
                        else{
                            corVermelho();
                            printf("\nO titulo que voce quer votar nao existe!\n");
                            corPadrao();
                            delay(2);
                        }
                    }
                    else{
                        corVermelho();
                        printf("\nO titulo digitado nao existe ou ja votou! \n");
                        corPadrao();
                        delay(2);
                    }
                }
                break;
            case 5:
                if(!vazia(arvoreVotos) && ocorreuVotacao != 0){
                    #ifdef OS_Windows
                        printf("\n%c Digite o numero do seu titulo para continuar: ", 175);
                        fflush(stdin);
                    #else
                        printf("\n➢ Digite o numero do seu titulo para continuar: ");
                        __fpurge(stdin); //limpa o buffer
                    #endif
                    scanf("%d", &titulo);
                    info = retornaInfoTitulo(arvoreVotos, titulo); 
                    if(info){
                        totalVotos--;
                        aux = retornaNoTitulo(arvoreTitulos, info->voto);
                        aux->info->vezesVotado--;
                        retira(*info, &arvoreVotos);
                        corVerde();
                        printf("\nVoto excluido com sucesso!\n");
                        corPadrao();
                        delay(2);
                    }
                    else{
                        corVermelho();
                        printf("\nO titulo digitado nao existe!\n");
                        corPadrao();
                        delay(2);
                    }
                } 
                else{
                    corVermelho();
                    printf("\nERRO! Ainda nao foram registrados votos.\n");
                    delay(2);
                    corPadrao;
                }
                break;

            case 6:
                //resultado parcial
                ordernaVotacao(arvoreTitulos, &arvoreOrdenada);
                #ifdef OS_Windows
                    imprimeDecrescenteWin(arvoreOrdenada);
                    fflush(stdin);
                    system("PAUSE");
                #else
                    imprimeDecrescente(arvoreOrdenada);
                    printf("\nPara continuar pressione ENTER...");
                    __fpurge(stdin); //limpa o buffer
                    getchar();
                #endif
                break;
            case 7: 
                if(ocorreuVotacao == 0 || vazia(arvoreVotos)){
                    corVermelho();
                    printf("\nAinda nao foram registrados votos. \n");
                    corPadrao();
                    delay(2);
                }
                else{
                    #ifdef OS_Windows
                        inOrderVotouWin(arvoreTitulos, arvoreVotos);
                        fflush(stdin);
                        system("PAUSE");
                    #else
                        inOrderVotou(arvoreTitulos, arvoreVotos);
                        printf("\nPara continuar pressione ENTER...");
                        __fpurge(stdin); //limpa o buffer
                        getchar();
                    #endif
                }
                break;
            case 20: 
                if(!vazia(arvoreTitulos)){
                    printf("\n******************TITULOS********************\n");
                    inOrderTitulos(arvoreTitulos);
                }
                else{
                    printf("\nA lista de titulos esta vazia!");
                }
                if(ocorreuVotacao != 0){
                    printf("\n******************VOTOS*********************\n");
                    inOrderVotos(arvoreVotos);
                }
                else{
                    printf("\nA lista de votos esta vazia!");
                }

                printf("\nPara continuar pressione ENTER...");
                #ifdef OS_Windows
                    fflush(stdin);
                    system("PAUSE");
                #else
                    __fpurge(stdin); //limpa o buffer
                    getchar();
                #endif
                break;
            case 8:
                arvoreTitulos = liberar(&arvoreTitulos);
                if(ocorreuVotacao != 0) arvoreVotos = liberar(&arvoreVotos);
                arvoreOrdenada = liberar(&arvoreOrdenada);
                corCiano();
                printf("\nSaindo...\n");
                corPadrao();
                exit(0);
                break; 
            default:
                break;
            }
    }  
    return 0; 
}