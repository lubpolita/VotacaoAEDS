#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreBinaria.h"
#include "votacao.h"

//para que seja possivel diferenciar os SO
#ifdef __unix__
#include <unistd.h>
#include <stdlib.h>
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
    
    //laco do menu principal
    while(opcao != 9){

        //limpar a tela
        #ifdef OS_Windows
            system("cls");
        #else
            system("clear");
        #endif

        menu(); //menu principal

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
                printf("\nDigite o nome do eleitor: ");
                #ifdef OS_Windows
                fflush(stdin);
                #else
                __fpurge(stdin); //limpa o buffer
                #endif
                fgets(info->Nome, 50, stdin);
                while(titulo <= 0){
                    printf("\nDigite o titulo do eleitor: ");
                    #ifdef OS_Windows
                    fflush(stdin);
                    #else
                    __fpurge(stdin); //limpa o buffer
                    #endif
                    scanf("%d", &titulo);
                    int search = existeTitulo(arvoreTitulos, titulo);
                    if(search == titulo){
                        printf("\nEste titulo ja existe! Espere uns segundos para tentar novamente...\n");
                        titulo = -1;
                        delay(2);
                    }
                }
                info->titulo_eleitor = titulo;
                info->vezesVotado = 0;
                insere(&arvoreTitulos, info);
                printf("\nEleitor criado! \n");
                delay(2);
                break;
            
            case 2:
                printf("\nDigite o titulo que voce deseja excluir: ");
                #ifdef OS_Windows
                    fflush(stdin);
                #else
                    __fpurge(stdin); //limpa o buffer
                #endif
                scanf("%d", &titulo);
                info = retornaInfoTitulo(arvoreTitulos, titulo);
                if(info){
                    retira(*info, &arvoreTitulos);
                    printf("\nTitulo excluido com sucesso! Digite 7 para ver a nova lista de titulos.\n");
                    delay(3);

                }
                else{
                    printf("\nEste titulo nao existe na lista!\n");
                    delay(2);
                }
                break;
            
            case 3:
                if(ocorreuVotacao == 0) {
                    criaArvore(&arvoreVotos);
                    ocorreuVotacao = 1;
                    printf("\nVotacao iniciada com sucesso!\n");
                    delay(2);
                }
                else{ 
                    printf("\nCuidado! Iniciar uma nova votacao ira excluir a votacao anterior, deseja continuar? ");
                    printf("\n1) Continuar.");
                    printf("\n2) Cancelar.");
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
                        printf("\nVotacao iniciada com sucesso!\n");
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
                    printf("\nPor favor, inicie uma votacao antes de continuar... ");
                    delay(2);
                }
                else{
                    printf("\nDigite o numero do seu titulo para continuar: ");
                    #ifdef OS_Windows
                        fflush(stdin);
                    #else
                        __fpurge(stdin); //limpa o buffer
                    #endif
                    scanf("%d", &titulo);

                    if(retornaInfoTitulo(arvoreTitulos, titulo) && !retornaInfoTitulo(arvoreVotos, titulo)){

                        //aloca nova info
                        info = (Info *) malloc(sizeof(Info));
                        info->titulo_eleitor = titulo;

                        menuVotacao(); //inicia menu
                        #ifdef OS_Windows
                        fflush(stdin);
                        #else
                        __fpurge(stdin); //limpa o buffer
                        #endif

                        scanf("%d", &voto); //le o voto
                        info->voto = voto; //armazenando voto em info

                        aux = retornaNoTitulo(arvoreTitulos, voto); //variavel auxiliar para mudar o valor da quantidade de votos
                        if(aux){
                            aux->info->vezesVotado++;
                            totalVotos++;
                            insere(&arvoreVotos, info); //adicionando info na arvore de votos
                            printf("\nSeu voto foi armazenado com sucesso! \n");
                            delay(2);
                        }
                        else{
                            printf("\nO titulo que voce quer votar nao existe! ");
                            delay(2);
                        }
                    }
                    else{
                        printf("\nO titulo digitado nao existe ou ja votou! \n");
                        delay(2);
                    }
                }
                break;
            case 5:
                printf("\nDigite o numero do seu titulo para continuar: ");
                #ifdef OS_Windows
                    fflush(stdin);
                #else
                    __fpurge(stdin); //limpa o buffer
                #endif
                scanf("%d", &titulo);
                info = retornaInfoTitulo(arvoreVotos, titulo); 
                if(info){
                    totalVotos--;
                    aux = retornaNoTitulo(arvoreTitulos, info->voto);
                    aux->info->vezesVotado--;
                    retira(*info, &arvoreVotos);
                    printf("\nVoto excluido com sucesso! ");
                    delay(2);
                }
                else{
                    printf("\nO titulo digitado nao existe! ");
                }
                break;

            case 6:
                //resultado parcial
                criaArvore(&arvoreOrdenada);
                ordernaVotacao(arvoreTitulos, &arvoreOrdenada);
                imprimeDecrescente(arvoreOrdenada);

                printf("\nPara continuar pressione ENTER...");
                #ifdef OS_Windows
                    fflush(stdin);
                    system("PAUSE");
                #else
                    __fpurge(stdin); //limpa o buffer
                    getchar();
                #endif
                break;
            case 7: 
                inOrderVotou(arvoreTitulos, arvoreVotos);
                printf("\nPara continuar pressione ENTER...");
                #ifdef OS_Windows
                    fflush(stdin);
                    system("PAUSE");
                #else
                    __fpurge(stdin); //limpa o buffer
                    getchar();
                #endif
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
                arvoreVotos = liberar(&arvoreVotos);
                arvoreOrdenada = liberar(&arvoreOrdenada);
                printf("\nSaindo...\n");
                exit(0);
                break; 
            default:
                break;
            }
    }  
    return 0; 
}