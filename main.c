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
    No *arvoreTitulos; //arv titulos
    No *arvoreVotos; //arv de votos
    No *aux, *arvoreOrdenada; //arvore auxiliar e arvore ordenada
    Info *info, *info2; //infos auxiliares para inserir nas arvores

    int titulo = -1, voto = -1; //inicializando titulo e voto de entrada.
    int ocorreuVotacao = 0; //caso ja tenha ocorrido uma votacao ela recebe 1, c.c recebe 0
    int opcao, alerta; //recebem entradas de opcoes
    double totalVotos = 0;

    //alocando arvores na memoria
    arvoreTitulos = (No*)malloc(sizeof(No));
    arvoreVotos = (No*)malloc(sizeof(No));
    arvoreOrdenada = (No*)malloc(sizeof(No));

    criaArvore(&arvoreTitulos); //criando arvore de titulos
    criaArvore(&arvoreOrdenada); //criando arvore auxiliar para guardar a arvore ja ordenada
    
    //laco do menu principal
    while(opcao != 8){

        #ifdef OS_Windows
            system("cls");
	        menuWin();
            fflush(stdin);
        #else
            system("clear"); //limpar tela
	        menu(); //menu principal
            __fpurge(stdin); //limpa o buffer
        #endif

        scanf("%d", &opcao); //recebe a opcao escolhida pelo usuario

        //funcionalidades
        switch (opcao) 
            {
            case 1:         //adicionar titulo
                info = (Info *) malloc(sizeof(Info)); //alocando uma nova info para colocar na arvore
                titulo = -1;

                #ifdef OS_Windows
                printf("\n%c Digite o nome do eleitor: ", 175);
                fflush(stdin);
                #else
                printf("\n➢ Digite o nome do eleitor: ");
                __fpurge(stdin); //limpa o buffer
                #endif

                fgets(info->Nome, 50, stdin); //recebe o nome

                while(titulo <= 0){ //enquanto o titulo estiver incorreto o laco se repete
                    #ifdef OS_Windows
                    printf("\n%c Digite o titulo do eleitor: ", 175);
                    fflush(stdin);
                    #else
                    printf("\n➢ Digite o titulo do eleitor: ");
                    __fpurge(stdin); //limpa o buffer
                    #endif
                    scanf("%d", &titulo);

                    if(titulo < 0){ //caso nao seja inteiro positivo
                        corVermelho();
                        printf("\nPor favor, digite um numero maior que 0. \n");
                        corPadrao();
                        delay(2);
                    }
                    else{
                        int search = existeTitulo(arvoreTitulos, titulo); //caso o titulo ja exista
                        if(search == titulo){
                            corVermelho();
                            printf("\nEste titulo ja existe! Espere uns segundos para tentar novamente...\n");
                            corPadrao();
                            titulo = -1; //titulo recebe -1 para continuar no laco
                            delay(2);
                        }
                    }
                }
                info->titulo_eleitor = titulo; //adiciona titulo na info
                info->vezesVotado = 0;          //inicializa as vezes que foi votado
                insere(&arvoreTitulos, info);   //insere a info na arvore de titulos
                corVerde();                     //muda cor do terminal para exibir mensagem em verde
                printf("\nEleitor criado! \n");
                corPadrao();                    //volta para cor padrao do sistema do terminal
                delay(2);                       //atraso para que seja possivel ler a mensagem na tela
                break;
            
            case 2:         //excluir titulo
                #ifdef OS_Windows
                    printf("\n%c Digite o titulo que voce deseja excluir: ", 175);
                    fflush(stdin);
                #else
                    printf("\n➢ Digite o titulo que voce deseja excluir: ");
                    __fpurge(stdin); //limpa o buffer
                #endif
                scanf("%d", &titulo);

                info = retornaInfoTitulo(arvoreTitulos, titulo); //retorna a info do titulo digitado
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
            
            case 3:     //inicia votacao
                if(ocorreuVotacao == 0) { //se for a primeira votacao
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

                    if(alerta == 1){    //se ja ocorreu votacao eh necessario liberar a arvore da ultima votacao
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

            case 4:     //votar
                if(ocorreuVotacao == 0){          //se ainda nao foi iniciada votacao
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
                    scanf("%d", &titulo);           //titulo da pessoa que ira votar
                    
                    //se o titulo existir na arvore de titulos e ainda nao votou (nao existe na arvore de votos)
                    //eh realizada a votacao
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
            case 5:             //retirar voto
                if(!vazia(arvoreVotos) && ocorreuVotacao != 0){     //confere se ja foi iniciada a votacao
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
                        aux = retornaNoTitulo(arvoreTitulos, info->voto);   //pega info por referencia do titulo da pessoa que foi votada 
                        aux->info->vezesVotado--;       //diminui o numero de voto do candidado que tinha o voto
                        retira(*info, &arvoreVotos); //retira voto da arvore
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
                ordernaVotacao(arvoreTitulos, &arvoreOrdenada); //ordena votacao e passa a arvore ordenada para "arvoreOrdenada"
                #ifdef OS_Windows
                    imprimeDecrescenteWin(arvoreOrdenada);
                    fflush(stdin);
                    system("PAUSE");
                #else
                    imprimeDecrescente(arvoreOrdenada);     //imprime a arvore em ordem decrescente ordenada pelos votos
                    printf("\nPara continuar pressione ENTER...");
                    __fpurge(stdin); //limpa o buffer
                    getchar();
                #endif
                break;
            case 7:     //lista todos que votaram
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
                        inOrderVotou(arvoreTitulos, arvoreVotos);   //imprime pessoas que votaram
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
            case 8:     //libera da memoria as arvores e sai do programa
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