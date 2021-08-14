#ifndef VOTACAO_H
#define VOTACAO_H
#include <stdio.h>
#include <stdlib.h>
#include "arvoreBinaria.h"

//funcoes para funcionamento da votacao
No *retornaNoTitulo(No* pRaiz, int titulo);
Info *retornaInfoVoto(No* pRaiz, int titulo);
Info *retornaInfoTitulo(No* pRaiz, int titulo);
void inOrderTitulos(No *raiz);
void inOrderVotos(No *raiz);
void resultadoParcial(No *no);
void ordernaVotacao(No *arvoreTitulos, No **arvoreDecrescente);
void imprimeDecrescente(No *no);
void inOrderVotou(No *raiz, No *arvoreVotos);
int existeTitulo(No* pRaiz, int titulo);

//funcoes para funcionamento da interface
void menu();
void menuVotacao();
void delay(int seg);

#endif