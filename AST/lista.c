#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lista.h"

struct _node{
	void* thing;
	struct _node* next;
	struct _node* prev;
};
struct _lista{
	struct _node* first;
	struct _node* last;
	int lenght;
};
typedef struct _node node;
typedef struct _lista lista;
/*CRIA UMA INSTÂNCIA DE LISTA*/
Lista createLista(){
	lista* anyLista=NULL;

	anyLista=(lista*)malloc(sizeof(lista));
	anyLista->lenght=0;
	anyLista->first=NULL;
	anyLista->last=NULL;

	return (Lista)anyLista;
}
/*RETORNA O TAMANHO DA LISTA*/
int lenghtLista(Lista anyLista){
	lista* anotherLista=NULL;

	anotherLista=(lista*)anyLista;

	return anotherLista->lenght;
}
/*INSTANCIA UM NODE, ADICIONA O CONTEÚDO (THING) E ADICIONA NO FINAL DA LISTA*/
Posic addNode(Lista anyLista, void* thing){
	node* anyNode=NULL;
	node* anotherNode=NULL;
	lista* anotherLista=NULL;
	
	anotherLista=(lista*)anyLista;
	if(anotherLista->lenght!=0){
		anyNode=(node*)anotherLista->last;
		anotherNode=(node*)malloc(sizeof(node));
		anotherNode->prev=anyNode;
		anotherNode->next=NULL;
		anotherNode->thing=thing;
		anyNode->next=anotherNode;
		anotherLista->last=anotherNode;
		anotherLista->lenght++;
	}
	else{
		anotherNode=(node*)malloc(sizeof(node));
		anotherNode->prev=NULL;
		anotherNode->next=NULL;
		anotherNode->thing=thing;
		anotherLista->first=anotherNode;
		anotherLista->last=anotherNode;
		anotherLista->lenght++;
	}

	return anotherNode;
}
/*REMOVE O NODE DA LISTA*/
/* mode = 0 mantém o conteúdo na memória
	mode = 1 libera o espaço do conteúdo na memória*/
void removeNode(Lista anyLista, Posic position, int mode){
	node* anyNode=NULL;
	node* anotherNode=NULL;
	lista* anotherLista=NULL;

	anyNode=(node*)position;
	anotherLista=(lista*)anyLista;
	if(anotherLista->lenght==1){
		anotherLista->first=NULL;
		anotherLista->last=NULL;
	}
	else{
		if(anotherLista->first==anyNode){
			anotherLista->first=(node*)anyNode->next;
			anotherNode=(node*)anyNode->next;
			anotherNode->prev=NULL;
		}
		else if(anotherLista->last==anyNode){
			anotherNode=(node*)anyNode->prev;
			anotherNode->next=NULL;
			anotherLista->last=anotherNode;
		}
		else{
			anotherNode=(node*)anyNode->prev;
			anotherNode->next=(node*)anyNode->next;
			anotherNode=anotherNode->next;
			anotherNode->prev=anyNode->prev;
		}
	}
	if(anyNode->thing!=NULL && mode==1)
			free(anyNode->thing);
	free(anyNode);
	anotherLista->lenght--;
}
/*RETORNA O CONTEÚDO DO NODE*/
void* getThing(Posic position){
	node* anyNode=NULL;

	anyNode=(node*)position;

	return anyNode->thing;
}
/*ALTERA O CONTEÚDO DE UM NÓ PARA UM NOVO CONTEÚDO*/
void* setThing(Posic position, void* thing){
	node* anyNode=NULL;

	anyNode=(node*)position;
	anyNode->thing=thing;

	return anyNode;
}
/*INSERE UM NODE COM O CONTEUDO ANTES DE UM OUTRO NODE*/
Posic insertBefore(Lista anyLista, Posic position, void* thing){
	node* anyNode=NULL;
	node* anotherNode=NULL;
	lista* anotherLista=NULL;

	anotherLista=(lista*)anyLista;
	anyNode=(node*)position;
	anotherNode=(node*)malloc(sizeof(node));
	anotherNode->prev=anyNode->prev;
	anotherNode->next=anyNode;
	anotherNode->thing=thing;
	anyNode->prev=anotherNode;
	if(anotherLista->first==anyNode){
		anotherLista->first=anotherNode;
	}
	else{
		anyNode=anotherNode->prev;
		anyNode->next=anotherNode;
	}
	anotherLista->lenght++;	

	return anotherNode;
}
/*INSERE UM NODE COM O CONTEUDO DEPOIS DE UM OUTRO NODE*/
Posic insertAfter(Lista anyLista, Posic position, void* thing){
	node* anyNode=NULL;
	node* anotherNode=NULL;
	lista* anotherLista=NULL;

	anotherLista=(lista*)anyLista;
	anyNode=(node*)position;
	anotherNode=(node*)malloc(sizeof(node));
	anotherNode->prev=anyNode;
	anotherNode->next=anyNode->next;
	anotherNode->thing=thing;
	anyNode->next=anotherNode;
	if(anotherLista->last==anyNode){
		anotherLista->last=anotherNode;
	}
	else{
		anyNode=anotherNode->next;
		anyNode->prev=anotherNode;
	}
	anotherLista->lenght++;
	
	return anotherNode;
}
/*RETORNA O PRIMEIRO NODE DE UMA LISTA*/
Posic getFirstNode(Lista anyLista){
	node* anyNode=NULL;
	lista* anotherLista=NULL;

	anotherLista=(lista*)anyLista;
	anyNode=anotherLista->first;

	return anyNode;
}
/*RETORNA O PRÓXIMO NODE DE UM NODE*/
Posic getNext(Posic anyNode){
	node* anotherNode=NULL;

	anotherNode=(node*)anyNode;

	return anotherNode->next;
}
/*RETORNA O ÚLTIMO NODE DE UMA LISTA*/
Posic getLastNode(Lista anyLista){
	node* anyNode=NULL;
	lista* anotherLista=NULL;

	anotherLista=(lista*)anyLista;
	anyNode=anotherLista->last;

	return anyNode;
}
/*RETORNA O NODE ANTERIOR DE UM NODE*/
Posic getPrevious(Posic anyNode){
	node* anotherNode=NULL;

	anotherNode=(node*)anyNode;

	return anotherNode->prev;
}
/*RETORNA O NODE DE NÚMERO 'INDEX' DE UMA LISTA*/
Posic getNodeByIndex(Lista anyLista, int index){
	lista* anotherLista=NULL;
	node* anyNode=NULL;
	int i=1;

	anotherLista=(lista*)anyLista;
	anyNode=(node*)anotherLista->first;
	while(1){
		if(i==index)
			break;
		anyNode=anyNode->next;
		i++;
	}

	return anyNode;
}
/*DESALOCA OS NODES DE UMA LISTA*/
/*OBS: MODE THING 1 DESTROI CONTEUDO
		MODE THING 0 MANTEM CONTEUDO*/
void destroiNodes(Lista anyLista, int thing){
	node* anyNode=NULL;
	node* anotherNode=NULL;
	lista* anotherLista=NULL;

	anotherLista=(lista*)anyLista;
	if(anotherLista!=NULL && anotherLista->first!=NULL){
		anyNode=(node*)anotherLista->first;
		while(1){
			if(anyNode==NULL)
				break;
			if(anyNode==anotherLista->last){
				if(thing==1)
					free(anyNode->thing);
				free(anyNode);
				break;
			}
			anotherNode=(node*)anyNode->next;
			if(thing==1 && anyNode->thing!=NULL)
				free(anyNode->thing);
			else
				anyNode->thing=NULL;
			free(anyNode);
			anyNode=(node*)anotherNode;
		}
		anotherLista->lenght=0;
	}
}
/*DESALOCA A LISTA*/
void destroiLista(Lista anyLista){
	lista* anotherLista=NULL;

	anotherLista=(lista*)anyLista;
	free(anotherLista);
}
/*CONCATENA DUAS LISTAS*/
void concatenateListas(Lista lista1, Lista lista2){
	int tam;
	lista* anyLista=NULL;
	lista* anotherLista=NULL;
	node* anyNode=NULL;

	if(lenghtLista(lista1)>0 && lenghtLista(lista2)>0){
		anyLista=(lista*)lista1;
		anotherLista=(lista*)lista2;
		anyNode=(node*)getLastNode(anyLista);
		anyNode->next=(node*)getFirstNode(anotherLista);
		anyNode=(node*)anyNode->next;
		anyNode->prev=(node*)getLastNode(anyLista);
		anyLista->last=anotherLista->last;
		tam=anotherLista->lenght;
		tam+=anyLista->lenght;
		anyLista->lenght=tam;
	}	
	else if(lenghtLista(lista1)==0){
		anyLista=(lista*)lista1;
		anyLista->lenght=lenghtLista(lista2);
		anyLista->first=getFirstNode(lista2);
		anyLista->last=getLastNode(lista2);
	}
}
/*COPIA UMA LISTA PARA OUTRA*/
void copyList(Lista lista1, Lista lista2){
	lista* anyLista=NULL;
	lista* anotherLista=NULL;

	anyLista=(lista*)lista1;
	anotherLista=(lista*)lista2;
	anyLista->first=anotherLista->first;
	anyLista->last=anotherLista->last;
	anyLista->lenght=anotherLista->lenght;
}
/*PEGA O CONTEÚDO E DESALOCA O NÓ NO ESQUEMA LIFO (PILHA)*/
void* getThingWhyStack(Lista anyStack){
	lista* anyLista=NULL;
	node* anyNode=NULL;
	void* thing=NULL;

	anyLista=(lista*)anyStack;
	anyNode=(node*)getLastNode(anyLista);
	thing=anyNode->thing;
	anyNode->thing=NULL;
	removeNode(anyLista, anyNode, 1);

	return thing;
}
/*PEGA O CONTEÚDO E DESALOCA O NÓ NO ESQUEMA LILO (FILA)*/
void* getThingWhyQueue(Lista anyQueue){
	lista* anyLista=NULL;
	node* anyNode=NULL;
	void* thing=NULL;

	anyLista=(lista*)anyQueue;
	anyNode=(node*)getFirstNode(anyLista);
	thing=anyNode->thing;
	anyNode->thing=NULL;
	removeNode(anyLista, anyNode, 1);

	return thing;
}
/*RETORNA UM VETOR DE LISTAS*/
Lista createVetorDeListas(int size){
	int i;
	lista* anyVector=NULL;
	lista* anyLista=NULL;

	anyVector=(lista*)malloc(size*sizeof(lista));
	for(i=0;i<size;i++){
		anyLista=&anyVector[i];
		anyLista->lenght=0;
		anyLista->first=NULL;
		anyLista->last=NULL;
	}


	return (Lista)anyVector;
}
void destroiVetorDeListas(Lista vetor[], int size, int mode){
	int i;
	lista* anyVector=NULL;
	lista* anyLista=NULL;

	anyVector=(lista*)vetor;
	for(i=0;i<size;i++){
		anyLista=&anyVector[i];
		destroiNodes(anyLista, mode);
	}
	free(anyVector);
}