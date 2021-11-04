// Autor: Rafael Amauri
// Tarefa: LED
// ID da Tarefa: 1168
// URL: https://www.beecrowd.com.br/judge/pt/problems/view/1168
// Complexidade: O(N), onde N é o número de dígitos totais

#include <iostream>
#include <string>

// Returns the number of LEDs required for a given num
short leds_required(short num)
{                       
    //                  0  1  2  3  4  5  6  7  8  9
    short num_leds[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
    
    return num_leds[num];
}

int main()
{
    short N, number_of_leds;
    std::string num;
    
    // reading the number of numbers that are going to be read from stdin
    std::cin >> N;
    
    for(short i = 0; i < N; i++)
    {
        std::cin >> num;
        number_of_leds = 0;

        // Para cada char na string, somar o numero de LEDs que o dígito precisa na
        // variavel <number_of_leds>
        for(char j: num)
            number_of_leds += leds_required(j-'0');
        
        std::cout << number_of_leds << " leds\n";
    }

    return 0;
}
