// Aluno: Rafael Amauri Diniz Augusto -- 651047
// Tarefa: AS11 - Backtracking
// Professor: Wladmir Cardoso
// Matéria: LPA
// Complexidade: O(M*N), onde M e N são as dimensões do tabuleiro


#include <bits/stdc++.h>
#include <vector>

#define MAX_SIZE 1024

int orig, dj[] = {-2,-1,1,2,2,1,-1,-2};
int di[] = {-1,-2,-2,-1,1,2,2,-1};

int aux1[16][1<<16];
int aux2[1<<4][1<<4];

int id;

std::vector<int> peca, dist;

// Realiza uma busca por BFS utilizando os dois tabuleiros
void bfs(int s, int tabuleiro_int[MAX_SIZE][MAX_SIZE], char tabuleiro_char[MAX_SIZE][MAX_SIZE], int N, int M);

int tsp(int u, int vis, int K);


int main()
{
    int N, M, K;

    std::cin >> N >> M >> K;

    int tabuleiro_int[MAX_SIZE][MAX_SIZE];
    char tabuleiro_char[MAX_SIZE][MAX_SIZE];

    // Enquanto as variaveis não forem vazias
    while( (N + M + K) != 0 )
    {
        int i, j;

        id = 1;
        K++;

        for(i = 0; i < K; i++)
            for(j = 0; j < K; j++)
                aux2[i][j] = (i != j) * INT_MAX;


        i = j = 1;


        // Percorre o tabuleiro_char
        while(i <= N)
        {
            while(j <= M)
            {
                // Verifica as posicoes do tabuleiro_char procurando o peao, o cavalo e as posicoes vazias
                std::cin >> tabuleiro_char[i][j];

                switch (tabuleiro_char[i][j])
                {
                    case 'P':
                        tabuleiro_int[i][j] = id++;
                        peca.push_back(i * (M + 2) + j);
                        break;
                    
                    case 'C':
                        tabuleiro_int[i][j] = 0;
                        peca.insert(peca.begin(), (i)*(M + 2) + (j));
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


        for(i = 0; i < K; i++)
            bfs(peca[i], tabuleiro_int, tabuleiro_char, N, M);


        for(i = K; i--;)
            for(j = (1 << K); j > 0; j--) 
                aux1[i][j] = -1;


        std::cout << tsp(0, 1, K) << std::endl;
        peca.clear();

        std::cin >> N >> M >> K;
    }

    return 0;
}

void bfs(int s, int tabuleiro_int[MAX_SIZE][MAX_SIZE], char tabuleiro_char[MAX_SIZE][MAX_SIZE], int N, int M)
{
    std::queue<int> fila;
    fila.push(s);

    std::vector<int> dist = std::vector<int> ( (N + 2) * (M + 2) + 10, INT_MAX); 
    dist[s] = 0;
    s = tabuleiro_int[s / (M+2)][s % (M+2)];
    
    while (!fila.empty())
    {
        int primeiro = fila.front(); 
        fila.pop();
        
        int i = primeiro / (M + 2);
        int j = primeiro % (M + 2);

        if (tabuleiro_int[i][j] > -1)
        {
            int x = std::min(std::min(aux2[s][tabuleiro_int[i][j]], aux2[tabuleiro_int[i][j]][s]), dist[primeiro]);
            aux2[s][tabuleiro_int[i][j]] = aux2[tabuleiro_int[i][j]][s] = x;
        }

        int k = 8;

        while(k > 0)
        {
            int a = i + di[k];
            int b = j + dj[k];

            int v = (a * (M + 2) + b);
            
            if ((1<=(a) && (a) <= N && 1 <= (b) && (b) <= M) && tabuleiro_char[a][b]!='#' && dist[v]==INT_MAX)
            {
                dist[v] = dist[primeiro]+1;
                fila.push(v);
            }

            k--;
        }
    }
}


int tsp(int u, int vis, int K)
{
    if (vis == (1 << K)-1) 
        return aux2[u][0];
    
    if (aux1[u][vis]!=-1)
        return aux1[u][vis];
    
    int ans = INT_MAX;
    
    for (int i = 0; i < K; i++)
    {
        if (!(vis & (1 << i)))ans = std::min(ans, aux2[u][i] + tsp(i, vis | (1 << i), K));
    }
    return aux1[u][vis]=ans;
}
