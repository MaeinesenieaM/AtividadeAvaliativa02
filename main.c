#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "read.c" //Insere funções customizadas para ler valores.

typedef struct Lista
	{
		int codigo, quantidade;
		float valor;
		char descricao [256];

		Lista *proximo;
	} Catalogo;

//aloca memoria suficiente para guardar a lista atual.
Catalogo *aloca ()
{
	Catalogo *novocatalogo = (Catalogo*) malloc(1 * sizeof(Catalogo));

	if (novocatalogo == NULL)
	{
		printf ("!!ERROR!!\n!!NÃO FOI POSSÍVEL ALOCAR MEMORIA!!\n");
		exit(1);
	}

	return novocatalogo;
}

//Imprime os valores de um registro específico.
void imprimir (Catalogo *memoria)
{
	if (memoria == NULL) return;
	printf ("==#==\n");
	printf ("Codigo: %d\nValor: %.2f\nQuantidade: %d\nDescrição: %s\n", memoria->codigo, memoria->valor, memoria->quantidade, memoria->descricao);
}

//Mostra a lista inteira do registro.
void mostra (Catalogo *memoria)
{
	Catalogo *olho = memoria;
	if (olho == NULL) printf ("\n!A lista esta vazia!\n\n");
	while (olho != NULL)
	{
		imprimir (olho);
		olho = olho->proximo;
	}
}

//Procura o registro pelo o codigo do mesmo.
Catalogo *procura (Catalogo *memoria, int codigo, int toggle) //Se 'toggle' for 0, ira retornar registro específico e se for 1 retornara o registro anterior.
{
	Catalogo *olho = memoria;
	Catalogo *anterior;

	while (olho->codigo != codigo && olho->proximo != NULL) 
	{
		anterior = olho;
		olho = olho->proximo;
	}

	if (olho->codigo != codigo)
	{
		printf ("\n!!REGISTRO NÃO ENCONTRADO!!CODIGO INVALIDO OU INEXISTENTE!!\n\n");
		return NULL;
	}

	switch (toggle)
	{
		case 0:
			return olho;
		case 1:
			return anterior;
		default:
			printf("!!ERROR!!\n!!VALOR DE TOGGLE INVALIDO!!\n");
			exit(2);
	}
}
//Libera memoria de um registro específico.
void liberaMemoria (Catalogo *memoria)
{
	memoria->codigo = NULL;
	memoria->valor = NULL;
	memoria->quantidade = NULL;
	char *desc = memoria->descricao;
	*desc = '\0'; //Faz com que a string se torne fazia.

	free (memoria);
}
//Diferente de liberaMemoria, limpa a memoria inteira do registro em vez de um.
void limpaMemoria (Catalogo *memoria)
{
	Catalogo *atual = memoria;
	while (atual->proximo != NULL) 
	{
		Catalogo *seguinte = atual->proximo;
		liberaMemoria (atual);
		atual = seguinte;
	}
	liberaMemoria (atual);
}

void exclui (Catalogo *memoria, int codigo)
{
	Catalogo *atual = procura (memoria, codigo, 0);
	if (atual == NULL) return;
	Catalogo *anterior = procura (memoria, codigo, 1);
	if (atual->proximo == NULL)
	{
		anterior->proximo = NULL;
		liberaMemoria (atual);
		return;
	}
	else
	{
		anterior->proximo = atual->proximo; //Faz com que o anterior aponte para o registro depois do atual.
		liberaMemoria (atual);
	}
}

void guarda (Catalogo *memoria) //Registra os valores para um produto.
{
	readInt ("Insire O Codigo", &memoria->codigo);
	readFloat ("Insire O Valor", &memoria->valor);
	readInt ("Insire A Quantidade", &memoria->quantidade);
	readString ("Escreva A Descriçao do produto.\n#", memoria->descricao);
	memoria->proximo = NULL;

	printf ("\nRegistrado com sucesso!\n\n");
}

Catalogo *registrar (Catalogo *memoria) //Registra, aloca e guarda o produto.
{
	Catalogo *novo;

	if (memoria == NULL)
	{
		novo = aloca ();
		guarda (novo);
	}
	else
	{
		novo = memoria;

		while (novo->proximo != NULL) novo = novo->proximo;

		novo->proximo = aloca ();
		guarda(novo->proximo);
	}
	return novo;
}

int vazio (Catalogo *lista)
{
	if (lista == NULL)
	{ 
		printf ("\n!A LISTA ESTA VAZIA!\n\n");
		return 1;
	}
	return 0;
}

int main ()
{
	setlocale (LC_ALL, "Portuguese"); 
	//como consequencia de usar a lingua portuguesa. Todos valores tipo float são lidos com ',' em vez de '.'

	printf ("\n==+Registro de Estoque+==\n");

	Catalogo *lista = NULL;

	int escolha, codigo;

	printf ("Escolha o que deseja fazer.\n\n");

	while (1 == 1)
	{
		printf ("\nRegistrar produto (1)\nRemover produto (2)\nProcurar com codigo (3)\nMostrar o registro inteiro (4)\nSair (0)\n");
	
		switch (readInt ("#", &escolha))
		{
			case 1:
				if (lista == NULL) lista = registrar (lista);
				else registrar (lista);
				break;
			case 2:
				if (vazio (lista) == 1) break;
				else if (lista->codigo == readInt ("Insira o codigo do produto", &codigo))
				{
					if (lista->proximo != NULL)
					{ 
						Catalogo *seguinte = lista->proximo;
						liberaMemoria (lista);
						lista = seguinte;
						break;
					}
					liberaMemoria (lista);
					lista = NULL;
					break;
				}
				else exclui (lista, codigo);
				break;
			case 3:
				if (vazio (lista) == 1) break;
				imprimir (procura (lista, readInt ("Insira o codigo do produto", &codigo), 0));
				break;
			case 4:
				if (vazio (lista) == 1) break;
				mostra (lista);
				break;
			case 0:
				if (lista != NULL) limpaMemoria (lista);
				printf ("\n    __o  bici! \n  _/><_ \n (_)/(_) \n  ");
				exit (0);
				break;
			default:
				printf ("\n!Seleção invalida!\n\n");
		}
	}

	return 0;
}


