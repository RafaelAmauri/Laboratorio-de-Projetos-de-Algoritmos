// Aluno: Rafael Amauri Diniz Augusto -- 651047
// Tarefa: AS11 - Backtracking
// Professor: Wladmir Cardoso
// Matéria: LPA
// Complexidade: O(largura*comprimento), onde largura e comprimento são as dimensões do tabuleiro


#include <bits/stdc++.h>
#include <vector>

#define MAX_SIZE 1024

int orig, id;

int aux1[16][1<<16];
int aux2[1<<4][1<<4];


std::vector<int> peca, dist;

// Realiza uma busca por BFS utilizando os dois tabuleiros
void bfs(int s, int tabuleiro_int[MAX_SIZE][MAX_SIZE], char tabuleiro_char[MAX_SIZE][MAX_SIZE], int comprimento, int largura);

// Recebe 
int tsp(int aux, int vis, int quant_peoes);


int main()
{
    int comprimento, largura, quant_peoes;

    std::cin >> comprimento >> largura >> quant_peoes;

    int tabuleiro_int[MAX_SIZE][MAX_SIZE];
    char tabuleiro_char[MAX_SIZE][MAX_SIZE];

    // Enquanto as variaveis não forem vazias
    while( (comprimento + largura + quant_peoes) != 0 )
    {
        int i, j;

        id = 1;
        quant_peoes++;

        for(i = 0; i < quant_peoes; i++)
            for(j = 0; j < quant_peoes; j++)
                aux2[i][j] = (i != j) * INT_MAX;


        i = j = 1;


        // Percorre o tabuleiro_char
        while(i <= comprimento)
        {
            while(j <= largura)
            {
                // Verifica as posicoes do tabuleiro_char procurando o peao, o cavalo e as posicoes vazias
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


        for(i = 0; i < quant_peoes; i++)
            bfs(peca[i], tabuleiro_int, tabuleiro_char, comprimento, largura);


        for(i = quant_peoes; i--;)
            for(j = (1 << quant_peoes); j > 0; j--) 
                aux1[i][j] = -1;


        std::cout << tsp(0, 1, quant_peoes) << std::endl;
        peca.clear();

        std::cin >> comprimento >> largura >> quant_peoes;
    }

    return 0;
}


void bfs(int s, int tabuleiro_int[MAX_SIZE][MAX_SIZE], char tabuleiro_char[MAX_SIZE][MAX_SIZE], int comprimento, int largura)
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
            int x = std::min(std::min(aux2[s][tabuleiro_int[i][j]], aux2[tabuleiro_int[i][j]][s]), dist[primeiro]);
            aux2[s][tabuleiro_int[i][j]] = aux2[tabuleiro_int[i][j]][s] = x;
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


int tsp(int u, int vis, int quant_peoes)
{
    if (vis == (1 << quant_peoes)-1) 
        return aux2[u][0];
    
    if (aux1[u][vis]!=-1)
        return aux1[u][vis];
    
    int ans = INT_MAX;
    
    for (int i = 0; i < quant_peoes; i++)
    {
        if (!(vis & (1 << i)))ans = std::min(ans, aux2[u][i] + tsp(i, vis | (1 << i), quant_peoes));
    }
    return aux1[u][vis]=ans;
}
