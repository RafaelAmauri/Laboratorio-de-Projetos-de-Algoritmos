// Aluno: Rafael Amauri Diniz Augusto -- 651047
// Tarefa: Cavalo
// ID da Tarefa: 1513
// URL da Tarefa: https://www.beecrowd.com.br/judge/pt/problems/view/1513
// Complexidade: O(N*M), onde largura e comprimento são as dimensões do tabuleiro


#include <iostream>
#include <queue>
#include <climits>
#include <vector>

#define MAX_SIZE 1024

int array_aux1[16][1<<16];
int array_aux2[1<<4][1<<4];


// Realiza uma busca pelos dois tabuleiros utilizando o algoritmo BFS
void search(int s, int tabuleiro_int[MAX_SIZE][MAX_SIZE], 
        char tabuleiro_char[MAX_SIZE][MAX_SIZE], int comprimento, 
        int largura);


// Faz uma verificacao para contar quantos movimentos o cavalo faz para
// capturar os peoes
int capturar_peoes(int aux, int vis, int quant_peoes);


int main()
{
    // Tabuleiro com numeros para facilitar comparacoes
    int tabuleiro_int[MAX_SIZE][MAX_SIZE];
    // Tabuleiro com as pecas em char
    char tabuleiro_char[MAX_SIZE][MAX_SIZE];
    
    // array com as pecas e suas distancias
    std::vector<int> peca, dist;
    
    // N, M e K. ID é o identificador da peça sendo analisada
    int comprimento, largura, quant_peoes, id;

    std::cin >> comprimento >> largura >> quant_peoes;


    // Enquanto as variaveis não forem vazias
    while( (comprimento + largura + quant_peoes) != 0 )
    {
        // Para a iteracao dos for
        int i, j;

        id = 1;
        quant_peoes++;

        for(i = 0; i < quant_peoes; i++)
            for(j = 0; j < quant_peoes; j++)
                array_aux2[i][j] = (i != j) * INT_MAX;


        i = j = 1;


        // Percorre o tabuleiro
        while(i <= comprimento)
        {
            while(j <= largura)
            {
                // Preenche o tabuleiro com os caracteres
                std::cin >> tabuleiro_char[i][j];

                switch (tabuleiro_char[i][j])
                {
                    case 'P':
                        tabuleiro_int[i][j] = id++;
                        peca.push_back(i * (largura + 2) + j);
                        break;
                    
                    case 'C':
                        tabuleiro_int[i][j] = 0;
                        peca.insert(peca.begin(), (i)*(largura + 2) + (j));
                        break;

                    case '.':
                        tabuleiro_int[i][j] = -1;
                        break;

                    default:
                        tabuleiro_int[i][j] = -2;
                        break;
                }
                j++;
            }
            j = 1;
            i++;
        }


        // Para cada um dos peoes, buscar a peca
        for(i = 0; i < quant_peoes; i++)
            search(peca[i], tabuleiro_int, tabuleiro_char, comprimento, largura);


        // Marca as posicoes vazias com -1
        for(i = quant_peoes; i--;)
            for(j = (1 << quant_peoes); j > 0; j--) 
                array_aux1[i][j] = -1;


        std::cout << capturar_peoes(0, 1, quant_peoes) << std::endl;
        peca.clear();

        std::cin >> comprimento >> largura >> quant_peoes;
    }

    return 0;
}


void search(int s, int tabuleiro_int[MAX_SIZE][MAX_SIZE], 
        char tabuleiro_char[MAX_SIZE][MAX_SIZE], int comprimento, 
        int largura)
{
    std::queue<int> fila;
    fila.push(s);

    int distancias_1[] = {-1,-2,-2,-1,1,2,2,-1};
    int distancias_2[] = {-2,-1,1,2,2,1,-1,-2};

    std::vector<int> dist = std::vector<int> ( (comprimento + 2) * (largura + 2) + 10, INT_MAX);
    dist[s] = 0;
    s = tabuleiro_int[s / (largura+2)][s % (largura+2)];
    
    while (!fila.empty())
    {
        int primeiro = fila.front();
        fila.pop();
        
        int i = primeiro / (largura + 2);
        int j = primeiro % (largura + 2);

        if (tabuleiro_int[i][j] > -1)
        {
            int x = std::min(std::min(array_aux2[s][tabuleiro_int[i][j]], array_aux2[tabuleiro_int[i][j]][s]), dist[primeiro]);
            array_aux2[s][tabuleiro_int[i][j]] = array_aux2[tabuleiro_int[i][j]][s] = x;
        }

        int quant_peoes = 8;

        while(quant_peoes > 0)
        {
            int a = i + distancias_1[quant_peoes];
            int b = j + distancias_2[quant_peoes];

            int v = (a * (largura + 2) + b);
            
            if ((1<=(a) && (a) <= comprimento && 1 <= (b) && (b) <= largura) && tabuleiro_char[a][b]!='#' && dist[v]==INT_MAX)
            {
                dist[v] = dist[primeiro]+1;
                fila.push(v);
            }

            quant_peoes--;
        }
    }
}


int capturar_peoes(int aux1, int vis, int quant_peoes)
{
    if (vis == (1 << quant_peoes)-1) 
        return array_aux2[aux1][0];
    
    if (array_aux1[aux1][vis]!=-1)
        return array_aux1[aux1][vis];
    
    int ans = INT_MAX;
    
    for (int i = 0; i < quant_peoes; i++)
    {
        if (!(vis & (1 << i)))ans = std::min(ans, array_aux2[aux1][i] + capturar_peoes(i, vis | (1 << i), quant_peoes));
    }
    return array_aux1[aux1][vis]=ans;
}