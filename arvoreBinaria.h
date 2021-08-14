#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H
#include <stdio.h>
#include <stdlib.h>

/*Estrutura da arvore*/

typedef struct candidatos{
    char Nome[50];
    int num;
    double totalVotos;
}Candidato;

typedef struct Info_Est{
    int titulo_eleitor;
    char Nome[50];
    int voto;
    double vezesVotado;
}Info;

typedef struct No_Est{
    Info *info;
    struct No_Est *esq, *dir;
}No;

//operacoes auxiliares basicas da arvore
void criaArvore(No **no);
int vazia(No *no);
No *liberar(No **no);
No* criarNo (Info *info);
void insere(No **no, Info *info);
void sucessor (No* q, No** r);
int retira (Info info, No** no);
void inserePorVoto(No **no, Info *info);


#endif