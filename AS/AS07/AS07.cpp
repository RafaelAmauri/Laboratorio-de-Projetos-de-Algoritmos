// Autor: Rafael Amauri
// Tarefa: Problema dos Pares Mais Próximos
// ID da Tarefa: 1295
// URL: https://www.beecrowd.com.br/judge/pt/problems/view/1295
// Complexidade: O(N^2), onde N é o número de pares de coordenadas


#include <iostream>
#include <cmath>


// Calcula a distancia entre 2 pontos
float calcular_distancia(float x1, float y1, float x2, float y2);


int main()
{
    int N;
    float x, y, *array_pontos;
    float dist, menor_dist = 10000.0;

    std::cin >> N;

    do
    {
        // Alocando um array com os valores
        array_pontos = (float*) malloc(N * 2 * sizeof(float));

        for (int i = 0; i < N; i++)
        {

            // Pegando os numeros
            std::cin >> x >> y;

            array_pontos[i*2] = x;
            array_pontos[i*2+1] = y;
        }

        // Comparando todos os pares possiveis de numeros.
        for (int i = 0; i < N; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                dist = calcular_distancia(array_pontos[i*2], array_pontos[i*2+1], array_pontos[j*2], array_pontos[j*2+1]);
                
                // Se o valor retornado pela funcao for menor que menor_dist, substituir menor_dist.
                if(dist < menor_dist)
                {
                    menor_dist = dist;
                }
            }
        }

        // Se a menor distancia possivel for maior ou igual a 10000, print "INFINITY"
        if(menor_dist >= 10000)
            printf("INFINITY\n");

        // Caso contrario, print a distancia com 4 casas decimais
        else
            printf("%.4f\n", menor_dist);


        // Desalocando o array
        free(array_pontos);
        array_pontos = NULL;

        // Reset da menor distancia
        menor_dist = 10000.0;

        std::cin >> N;

    } while(N > 0);

    return 0;
}

float calcular_distancia(float x1, float y1, float x2, float y2)
{
    // Distancia entre 2 pontos = ((x1 - x2)^2) + ((y1 - y2)^2))^1/2
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}