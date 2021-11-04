// Autor: Rafael Amauri
// Tarefa: Bolhas e Baldes
// ID da Tarefa: 1088
// URL: https://www.beecrowd.com.br/judge/pt/problems/view/1088
// Complexidade: O(N logN), onde N é o número de elementos no array

#include <iostream>


// Mergesort modificado. A cada shift de elementos para a direita, ele soma em <num_movimentações> o numero de casas nesse shift.
// No final, <num_movimentacoes> vai nos dar o número de shifts seguindo as regras do jogo
void mergesort(int i, int j, int a[], int aux[], int *num_movimentacoes)
{
	if (j <= i)
	{
		return;
	}

	int mid = (i + j) / 2;

	mergesort(i, mid, a, aux, num_movimentacoes);
	mergesort(mid + 1, j, a, aux, num_movimentacoes);

	int pointer_left = i;
	int pointer_right = mid + 1;
	int k;

	for (k = i; k <= j; k++)
	{
		if (pointer_left == mid + 1)
		{
			aux[k] = a[pointer_right];
			pointer_right++;
			*num_movimentacoes += mid-k;
		}

		else if (pointer_right == j + 1)
		{
			aux[k] = a[pointer_left];
			pointer_left++;
		}
		else if (a[pointer_left] < a[pointer_right])
		{
			aux[k] = a[pointer_left];
			pointer_left++;
		}
		else
		{
			aux[k] = a[pointer_right];
			pointer_right++;
			*num_movimentacoes += mid-k;
		}
	}

	for(k = i; k <= j; k++)
	{
		a[k] = aux[k];
	}
}


int main()
{
	unsigned int quant, num_movimentacoes;
	std::cin >> quant;

	while (quant != 0)
	{
		int *array = new int[quant], *aux = new int[quant], num_movimentacoes = 0;

		// Armazena numeros no array
		for (int i = 0; i < quant; i++)
		{
			std::cin >> array[i];
		}

		// O objetivo do mergesort é contar as movimentacoes e armazenar em <num_movimentacoes>
		mergesort(0, quant-1, array, aux, &num_movimentacoes);

		// Caso o numero de shifts seja par, Carlos ganha
		if(num_movimentacoes % 2 == 0)
		{
			std::cout << "Carlos\n";
		}
		// Caso contrario, Marcelo ganha
		else
		{
			std::cout << "Marcelo\n";
		}

		// Resetando variáveis
		std::cin >> quant;
		num_movimentacoes = 0;
		
		delete array;
		delete aux;
	}

	return 0;
}