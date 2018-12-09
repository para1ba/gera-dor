#ifndef LISTA_H
#define LISTA_H

	/*---Sobre o Módulo---*/
    /*Este módulo implementa uma lista duplamente encadeada, dá acesso aos seus nós para manipulação, para modificação e pode destruí-los.*/
    /*Autor: Vitor Hugo da Silva Custódio  ---  Ano: 2017*/

    /* Tipo Exportado */
    /*tipo abstrato Node 
		Definição: Pode ser entendido como uma estrutura-nó dentro de uma lista. 
					Possui referência para o próximo, o anterior e referenciam algum 
					conteúdo que esse determinado nó “guarda”.*/
	typedef void* Node;

	/*tipo abstrato Posic 
		Definição: Indica a posição de um item dentro da lista. Este tipo possui um valor
					inválido para qualquer lista. Tal valor inválido é denotado por NULL.*/
	typedef void* Posic;
	
	/*tipo abstrato Lista
		Definição: Esse tipo possui uma forma parecida aos tipos Posic ou Node. 
					Possui uma referência para o primeiro Node/Posic, uma referência para 
					o último Node/Posic e um valor inteiro que indica o tamanho atual da lista.*/	
	typedef void* Lista;
	
	/*CRIA UMA INSTÂNCIA DE LISTA*/
	/*função createLista(): Lista
			pós-condição: Retorna uma instância do tipo Lista.*/
	Lista createLista();

	/*RETORNA O TAMANHO DA LISTA*/
	/*função lenghtLista(anyLista: Lista): ‘lenght’ (inteiro)
			pré-condição: Existir a instância de Lista.
			pós-condição: Retorna o tamanho da Lista.*/
	int lenghtLista(Lista anyLista);

	/*INSTANCIA UM NODE, ADICIONA O CONTEÚDO (THING) E ADICIONA NO FINAL DA LISTA*/
	/*função addNode(anyLista: Lista, void* thing): Posic
			pré-condição: Existir a instãncia de Lista.
			pós-condição: Adiciona ‘thing’ a uma instância de Node e insere no final da Lista.*/
	Posic addNode(Lista anyLista, void* thing);

	/*REMOVE O NODE DA LISTA*/
	/*procedimento removeNode(anyLista: Lista, position: Posic)
			pré-condição: Existir a instância de Lista, e um Posic não-nulo.
			pós-condição: Exclusão de dado nó de uma Lista.*/
	void removeNode(Lista anyLista, Posic position, int mode);

	/*RETORNA O CONTEÚDO DO NODE*/
	/*função getThing(position: Posic): ‘Item’ (conteúdo)
			pré-condição: Existir um Posic não-nulo e que esteja preenchido.
			pós-condição: Retorna o conteúdo que um dado nó “guarda”.*/
	void* getThing(Posic position);

	/*ALTERA O CONTEÚDO DE UM NÓ PARA UM NOVO CONTEÚDO*/
	/*função setThing(position: Posic, thing: void*): position
			pós-condição: Altera e retorna o nó com o novo conteúdo*/
	void* setThing(Posic position, void* thing);

	/*INSERE UM NODE COM O CONTEUDO ANTES DE UM OUTRO NODE*/
	/*função insertBefore(anyLista: Lista, void* thing): Posic
			pré-condição: Existir a instância de Lista, e um Posic não-nulo.
			pós-condição: Adiciona ‘thing’ a uma instância de Node e insere antes de Posic.*/
	Posic insertBefore(Lista anyLista, Posic position, void* thing);

	/*INSERE UM NODE COM O CONTEUDO DEPOIS DE UM OUTRO NODE*/
	/*função insertAfter(anyLista: Lista, void* thing): Posic
			pré-condição: Existir a instância de Lista, e um Posic não-nulo.
			pós-condição: Adiciona ‘thing’ a uma instância de Node e insere depois de Posic.*/
	Posic insertAfter(Lista anyLista, Posic position, void* thing);

	/*RETORNA O PRIMEIRO NODE DE UMA LISTA*/
	/*função getFirstNode(anyLista: Lista): Posic
			pré-condição: Existir a instância de Lista.
			pós-condição: Retorna uma referência para o primeiro nó da Lista.*/
	Posic getFirstNode(Lista anyLista);

	/*RETORNA O PRÓXIMO NODE DE UM NODE*/
	/*função getNext(anyNode: Posic): Posic
			pré-condição: Existir a instância de Node (a qual Posic referencia).
			pós-condição: Retorna uma referência para o próximo nó que Posic indica.*/
	Posic getNext(Posic anyNode);

	/*RETORNA O ÚLTIMO NODE DE UMA LISTA*/
	/*função getLastNode(anyLista: Lista): Posic
			pré-condição: Existir a instância de Lista.
			pós-condição: Retorna uma referência para o último nó da Lista.*/
	Posic getLastNode(Lista anyLista);

	/*RETORNA O NODE ANTERIOR DE UM NODE*/
	/*função getPrevious(anyNode: Posic): Posic
			pré-condição: Existir a instância de Node (a qual Posic referencia).
			pós-condição: Retorna uma referência para o nó anterior que Posic indica.*/
	Posic getPrevious(Posic anyNode);

	/*RETORNA O NODE DE NÚMERO 'INDEX' DE UMA LISTA*/
	/*função getNodeByIndex(anyLista: Lista, int index): Posic
			pré-condição: Existir a instância de Lista e index um valor inteiro positivo.
			pós-condição: Retorna uma referência para o nó de número ‘index’ na Lista.*/
	Posic getNodeByIndex(Lista anyLista, int index);

	/*DESALOCA OS NODES DE UMA LISTA*/
	/*procedimento destroiNodes(anyLista: Lista)
			pré-condição: Existir a instância de Lista com o tamanho maior que zero.
			pós-condição: Desaloca todos os nós da Lista.*/
	void destroiNodes(Lista anyLista, int mode);
	
	/*DESALOCA A LISTA*/
	/*procedimento destroiLista(anyLista: Lista)
			pré-condição: Existir a instância de Lista.
			pós-condição: Desaloca a instância de Lista.*/
	void destroiLista(Lista anyLista);

	/*CONCATENA DUAS LISTAS*/
	/*procedimento concatenateListas(lista1: Lista, lista2: Lista)
		pós-condição: A lista 1 concatenada com a lista2*/
	void concatenateListas(Lista lista1, Lista lista2);

	/*COPIA UMA LISTA PARA OUTRA*/
	/*procedimento copyList(lista1: Lista, lista2: Lista)
		pós-condição: Copia lista2 para lista 1*/
	void copyList(Lista lista1, Lista lista2);

	/*PEGA O CONTEÚDO E DESALOCA O NÓ NO ESQUEMA LIFO (PILHA)*/
	/*função getThingWhyStack(anyStack: Lista): 'conteúdo'
		pré-condição: Uma lista válida
		pós-condição: Pega o conteúdo da lista no esquema pilha*/
	void* getThingWhyStack(Lista anyStack);

	/*PEGA O CONTEÚDO E DESALOCA O NÓ NO ESQUEMA LILO (FILA)*/
	/*função getThingWhyQueue(anyQueue: Lista): 'conteúdo'
		pré-condição: Uma lista válida
		pós-condição: Pega o conteúdo da lista no esquema fila*/
	void* getThingWhyQueue(Lista anyQueue);

	Lista createVetorDeListas(int size);

	void destroiVetorDeListas(Lista vetor[], int size, int mode);

#endif