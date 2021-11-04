// Autor: Rafael Amauri
// Tarefa: Subsequências
// ID da Tarefa: 1507
// URL: https://www.beecrowd.com.br/judge/pt/problems/view/1507
// Complexidade: O(N*M), onde N é o número de letras na string maior e M é o número de letras na sub-sequência


#include <iostream>
#include <string>

// Verifica se uma substring existe dentro de uma string
bool isSubstring(std::string string, std::string substring)
{
    // Marca a posicao na string onde cada letra da substring foi encontrada
    unsigned int last_position = 0;

    // Esse for percorre cada letra da substring
    for(unsigned int i = 0; i < substring.length(); i++)
    {
        bool letter_found = false;

        // Percorre a string toda procurando por substring[i]. Quando ela é achada, sua posicao é
        // marcada na variável last_position avancando 1 casa (para nao repetir várias vezes a mesma letra)
        for(unsigned int j = last_position; j < string.length() && !letter_found; j++)
        {
            if(substring[i] == string[j])
            {   
                last_position = j+1;
                letter_found = true;
            }
        }

        // Caso a letra em substring[i] nao seja achada em nenhuma posicao da string
        if(!letter_found)
            return false;
    }

    return true;
}

int main()
{
    unsigned int N, Q;
    std::string S, R;

    std::cin >> N;
    for(unsigned int i = 0; i < N; i++)
    {
        std::cin >> S;
        std::cin >> Q;

        for(unsigned int j = 0; j < Q; j++)
        {
            std::cin >> R;

            if(isSubstring(S, R))
                std::cout << "Yes\n";
            else
                std::cout << "No\n";
        }
    }

    return 0;
}