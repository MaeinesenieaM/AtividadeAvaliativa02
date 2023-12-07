#include <stdio.h>
#include <string.h>

//Este arquivo contem funções para ler valores de forma que seja possível modificar o texto inicial.

void stringVerify (const char * T)
{
	fflush (stdin);
	if (T == NULL)
	{
		printf ("#: ");
	}
	else
	{
		printf ("%s: ", T);
	}
}

int readInt (const char *texto, int *entrada)
{	
	stringVerify (texto);
	while (scanf ("%d", &*entrada) == 0)
	{
		printf ("\n!!VALOR INVALIDO!!\n\n");
		stringVerify (texto);
	} 
	return *entrada;
}

float readFloat (const char *texto, float *entrada)
{
	stringVerify (texto);
	while (scanf ("%f", &*entrada) == 0)
	{
		printf ("\n!!VALOR INVALIDO!!\n\n");
		stringVerify (texto);
	} 
	return *entrada;
}

double readDouble (const char *texto, double *entrada)
{
	stringVerify (texto);
	while (scanf ("%lf", &*entrada) == 0)
	{
		printf ("\n!!VALOR INVALIDO!!\n\n");
		stringVerify (texto);
	} 
	return *entrada;
}

char readChar (const char *texto, char *entrada)
{
	stringVerify (texto);
	while (scanf ("%c", &*entrada) == 0)
	{
		printf ("\n!!LETRA INVALIDA!!\n\n");
		stringVerify (texto);
	} 
	return *entrada;
}

char readString (const char *texto, char entrada[]) //Vetores de chars nao precisam de '&' para ser apontado, pois ja sao ponteiros.
{
	stringVerify (texto); 

	while (scanf ("%[^\n]s", &*entrada) == 0)
	{
		printf ("\n!!LETRA INVALIDA!!\n\n");
		stringVerify (texto);
	}

	return *entrada;
}

/*    __o  bici! 
    _/><_ 
   (_)/(_) 
*/