// Aluno: Rafael Amauri Diniz Augusto -- 651047
// Tarefa: AS10 - Notas e Moedas
// Professor: Wladmir Cardoso
// Matéria: LPA
// Complexidade: O(N), onde N é o número de moedas e notas totais


#include <iostream>
#include <iomanip>


int main()
{
    const double valores[]  = { 100, 50, 20, 10, 5, 2, 1, 0.50, 0.25, 0.10, 0.05, 0.01 };
    short quantidade_valores[]  = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    //  N é o valor em dinheiro
    double N;

    const short size_valores  =  12;
    const short size_notas    =  6;
    const short size_moedas   =  6;

    // Pegando o numero
    std::cin >> N;
    

    // Verificando o troco possivel de retornar com as notas e moedas
    for(int i = 0; i < size_valores; i++)
    {
        if(valores[i] <= N)
        {
            // Subtrai valores[i] do valor total que precisa de troco
            N -= valores[i];
            
            // Adiciona 1 na quantidade de valores da posicao 1 usados
            quantidade_valores[i] += 1;

            // Voltar 1 posicao no array de notas para caso a mesma nota ainda possa ser usada
            // para subtrair ainda mais o valor
            i = i - 1;
        }
    }
    

    std::cout << "NOTAS:\n";
    for(int i = 0; i < size_notas; i++)
    {
        std::cout << quantidade_valores[i] << " nota(s) de R$ " << valores[i] << ".00\n";
    }
    

    std::cout << "MOEDAS:\n";
    for(int i = size_notas; i < size_notas + size_moedas; i++)
    {
        if(valores[i] == 1)
        {
            std::cout << quantidade_valores[i] << " moeda(s) de R$ " << valores[i] << std::fixed << std::setprecision(2) << ".00\n";
            continue;
        }
        std::cout << quantidade_valores[i] << " moeda(s) de R$ " << valores[i] << std::fixed << std::setprecision(2) << "\n";
    }
}