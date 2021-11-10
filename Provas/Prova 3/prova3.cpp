// Autor: Rafael Amauri
// Tarefa: Países em Guerra
// ID da Tarefa: 1148
// URL da Tarefa: https://www.beecrowd.com.br/judge/pt/problems/view/1148
// Complexidade: O(N^2), onde N é o número de cidades


#include <iostream>

#define MAX_SIZE_GRAFO 1024
#define FLAG_EMPTY 99999

// Acha no grafo as menores distancias. O peso de cada aresta é o numero de horas
void find(int grafo[MAX_SIZE_GRAFO][MAX_SIZE_GRAFO], int N);


int main()
{
    // N eh o numero de cidades e E eh o numero de ligações
    int N, E;
    
    // X eh a cidade 1, Y eh a cidade 2 e H eh o numero de horas para transportar uma carta de X a Y
    int X, Y, H;

    // K é a quantidade de consultas, O eh a origem e D eh o destino
    int K, O, D;

    std::cin >> N >> E;

    // Enquanto nenhum dos dois for zero
    while(N && E)
    {
        int grafo[MAX_SIZE_GRAFO][MAX_SIZE_GRAFO];

        for(int i = 1; i <= N; i++)
        {
            for(int j = 1; j <= N; j++)
            {
                if(i == j)
                    grafo[i][j] = 0;
                else
                    grafo[i][j] = FLAG_EMPTY;
            }
        }

        // Para cada aresta, verificar se ja existe um peso para aquela aresta
        while(E)
        {
            std::cin >> X >> Y >> H;

            if(grafo[Y][X] == FLAG_EMPTY)
                grafo[X][Y] = H;
            else
            {
                grafo[X][Y] = 0;
                grafo[Y][X] = 0;
            }

            E--;
        }

        // Usa o algoritmo de Floyd-Warshall para achar o caminho mais curto entre as N cidades
        find(grafo, N);

        // Lendo o numero de consultas
        std::cin >> K;

        // Para cada uma das consultas, verificar se eh menor que a flag de vazio (nao tem conexoes)
        for(int it = 0; it < K; it++)
        {
            // Lendo a origem e destino
            std::cin >> O >> D;

            if(grafo[O][D] < FLAG_EMPTY)
                std::cout << grafo[O][D] << std::endl;
            else
                std::cout << "Nao e possivel entregar a carta\n";
        }

        // Se for vazio, pular uma linha
        if(K != 0)
            std::cout << "\n";

        std::cin >> N >> E;
    }

    return 0;
}


void find(int grafo[MAX_SIZE_GRAFO][MAX_SIZE_GRAFO], int N)
{
    for(int k = 1; k <= N; k++)
        for(int i = 1; i <= N ; i++)
            if(k != i)
                for(int j = 1; j <= N; j++)
                    if(grafo[i][j] > grafo[i][k] + grafo[k][j])
                        grafo[i][j] = grafo[i][k] + grafo[k][j];
}
