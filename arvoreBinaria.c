#include <stdio.h>
#include <stdlib.h>
#include "arvoreBinaria.h"

//inicia uma nova arvore
void criaArvore(No **no){
    *no = NULL;
}

//confere se a arvore esta vazia
int vazia(No *no){
    return no == NULL;
}

//libera da memoria todos os nos da arvores e suas respectivas infos
No *liberar(No **no){
    if(!vazia(*no)){
    liberar(&(*no)->esq);
    liberar(&(*no)->dir);
    free(*no);
    free((*no)->info);
    }
    return NULL;
}

//cria um novo 
No* criarNo (Info *info){
    No* novo_no;
    novo_no = (No*) malloc (sizeof(No));
    novo_no->info = info;
    novo_no->esq = NULL;
    novo_no->dir = NULL;
    return (novo_no);
}

//insere um no na arvore binaria
void insere(No **no, Info *info){
    if (*no == NULL) {
        *no = (No *) malloc(sizeof(No));
        (*no)->esq = NULL;
        (*no)->dir = NULL;
        (*no)->info = info;
    } else {
        if (info->titulo_eleitor < (*no)->info->titulo_eleitor) insere(&((*no)->esq), info);
        else insere(&((*no)->dir), info);
    }
}

//insere ordenando por voto
void inserePorVoto(No **no, Info *info){
    if (*no == NULL) {
        *no = (No *) malloc(sizeof(No));
        (*no)->esq = NULL;
        (*no)->dir = NULL;
        (*no)->info = info;
    } else {
        if (info->vezesVotado < (*no)->info->vezesVotado) inserePorVoto(&((*no)->esq), info);
        else inserePorVoto(&((*no)->dir), info);
    }
}

void sucessor (No* q, No** r){
    No* pAux;
    if ((*r)->esq != NULL) {
        sucessor (q, &(*r)->esq);
        return; 
    }
    q->info = (*r)->info;
    pAux = *r;
    *r = (*r)->dir;
    free (pAux);
}

//retira o no
int retira (Info info, No** no){
    No* pAux;
    if (*no == NULL)
        return 0;
    if (info.titulo_eleitor < (*no)->info->titulo_eleitor)
        return retira (info, &(*no)->esq);
    if (info.titulo_eleitor > (*no)->info->titulo_eleitor)
        return retira (info, &(*no)->dir);
    if ((*no)->dir == NULL) {
        pAux = *no;
        *no = (*no)->esq;
        free (pAux);
        return 1; 
        }
    if ((*no)->esq == NULL) {
        pAux = *no;
        *no = (*no)->dir;
        free (pAux);
        return 1;
        }
    sucessor (*no, &(*no)->dir);
    return 1;
}

