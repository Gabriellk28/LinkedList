/*
Listas encadeadas são estruturas de dados que permitem armazenar uma coleção
 de elementos de um mesmo tipo.

Neste arquivo, temos a implementação de uma lista encadeada simples de inteiros.
*/

#include "lista.h"

struct lista
{
	int info;
	struct lista *prox;
};

Lista *lst_cria(void) 
{
	return NULL; 
}

Lista *lst_insere(Lista *l, int v) //Retorna um ponteiro para uma strutura do tipo Lista, e recebe como parâmetro uma lista e um valor do tipo inteiro
{
	Lista *novo = (Lista *)malloc(sizeof(Lista)); //Aloca memória para um novo elemento da lista
	if (novo == NULL) //Verifica se a alocação de memória para um novo elemento da lista foi bem sucedida
	{
		printf("[ERRO] memoria insuficiente!"); //Imprime um menssagem de erro caso tenho dado erro na alocação de memória
		exit(1); //Aborta a execução
	}
	novo->info = v; //O novo elemento da lista recebe o valor 
	novo->prox = l; //O novo elemento da lista aponta para o ultimo elemento inserido na lista
	return novo; //Retorna o endereço do ultimo elemento inserido na lista

	/* Ou para alterar diretamente

	void lst_insere(Lista** t, int v){
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	novo->info = v;
	novo->prox = *t;
	*t = novo; */
}

int lst_vazia(Lista *l) //Retorna um valor do tipo inteiro, e recebe como parâmetro o endereço de uma lista
{
	return (l == NULL); //Retorna 0 caso exista algum elemento na lista e 1 caso não exista nenhum elemento na lista
}

void lst_imprime(Lista *l) //Não retorna nenhum valor e recebe como parâmetro uma lista
{
	Lista *p; //Declara um elemento do tipo Lista
	for (p = l; p != NULL; p = p->prox) //Faz com que p receba o primeiro elemento da lista 'l', verifica se p tem algum elemento e faz com que p receba o endereço do próximo elemento da lista
	{
		printf("\tInfo = %d \n", p->info); //Imprime o valor do campo info do elemento 'p'
	}
}

Lista *lst_busca(int elemento, Lista *l) //Retorna um poneteiro do tipo Lista e recebe como parâmetro um valor do tipo ineteiro e uma lista
{
	Lista *p; //Declara um elemento do tipo Lista
	for (p = l; p != NULL; p = p->prox) //'p' recebe a lista 'l', verifica se 'p' está vazio e faz com que 'p' receba o endereço do próximo elemento da lista
	{
		if (p->info == elemento) //Verifica se o valor do campo info do elemento 'p' é igual ao valor que está sendo buscado
			return p; //Caso a condição seja verdadeira é retornado o elemento 'p'
	}

	return NULL; //Se o elemento for achado na lista é retornado NULL, para indicar que o elemento não existe na lista
}

Lista *lst_retira(Lista *l, int v) //Retorna um ponteiro do Lista e recebe como parâmetro uma lista e um valor do tipo inteiro
{
	Lista *ant = NULL; /* ponteiro para elemento anterior */
	//O ponetrio 'ant' recebe NULL porque não existe um elemento anterior ou primeiro elemento da lista

	Lista *p = l;	   /* ponteiro para percorrer a lista*/
	//O poneteiro 'p' recebe o primeiro elemento para poder ir percorrendo os elementos da lista
	/* procura elemento na lista, guardando anterior */
	while (p->info != v) //Verifica valor do campo do primeiro elemento da lista é diferente do valor a ser retirado da lista
	{
		if (p == NULL) //Verifica se 'p' é o ultimo elemento da lista
			return l; /* não achou: retorna lista original */
		ant = p; //O poneteiro 'ant' recebe o elemento do inicio da lista
		p = p->prox; //O ponteiro 'p' recebe o elemento seguinte a 'p'
		/* verifica se achou elemento */
	}
	/* retira elemento */
	if (ant == NULL) //Verifica se o poneteiro 'ant' está vazio
		/* retira elemento do inicio */
		l = p->prox; //
	else
		/* retira elemento do meio da lista */
		ant->prox = p->prox;
	free(p);
	return l;
}

void lst_libera(Lista *l) //Não retorna nenhum valor e recebe como parâmetro
{
	Lista *p = l; //Declara o ponteiro 'p' do tipo Lista e faz ele apontar para o inicio da lista
	Lista *t;
	while (p != NULL)
	{
		t = p->prox;
		free(p);
		p = t;
	}
}

Lista *lst_insere_ordenada(Lista *l, int v)
{
	Lista *novo;
	Lista *ant = NULL;
	Lista *p = l;
	while (p != NULL && p->info < v)
	{
		ant = p;
		p = p->prox;
	}
	novo = (Lista *)malloc(sizeof(Lista));
	novo->info = v;
	if (ant == NULL)
	{
		novo->prox = l;
		l = novo;
	}
	else
	{
		novo->prox = ant->prox;
		ant->prox = novo;
	}
	return l;
}

Lista *lst_ler_arquivo(char *nome_arquivo)
{
	FILE *arquivo;
	int valor;
	Lista *l = lst_cria();
	arquivo = fopen(nome_arquivo, "r");
	if (arquivo == NULL)
	{
		printf("Erro ao abrir o arquivo!\n");
		exit(1);
	}
	while (fscanf(arquivo, "%d", &valor) != EOF)
	{
		l = lst_insere(l, valor);
	}
	fclose(arquivo);
	return l;
}
