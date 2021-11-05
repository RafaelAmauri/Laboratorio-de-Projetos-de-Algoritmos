// Aluno: Rafael Amauri Diniz Augusto -- 651047
// Tarefa: AS11 - Backtracking
// Professor: Wladmir Cardoso
// Matéria: LPA
// Complexidade: O(M*N), onde M e N são as dimensões do tabuleiro


#include <bits/stdc++.h>
#include <vector>

#define MAX_SIZE 1024

int n, m, k, orig, dj[] = {-2,-1,1,2,2,1,-1,-2};
int di[] = {-1,-2,-2,-1,1,2,2,-1}, memo[16][1<<16], adj[1<<4][1<<4], t[MAX_SIZE][MAX_SIZE], id;

char tabuleiro[MAX_SIZE][MAX_SIZE];

std::vector<int> peca, dist;

// Realiza uma busca por BFS
void bfs(int s);

int tsp(int u, int vis);

int main()
{
    std::cin >> n >> m >> k;

    while( (n + m + k) != 0 ){
        
        id = 1;
        k++;
        
        for(int i = 0; i < k; i++)
            for(int j = 0; j < k; j++)
                adj[i][j] = (i != j) * INT_MAX;


        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                std::cin >> tabuleiro[i][j];

                switch (tabuleiro[i][j])
                {
                    case 'P':
                        t[i][j] = id++;
                        peca.push_back(i * (m+2) + j);
                        break;
                    
                    case 'C':
                        t[i][j] = 0;
                        peca.insert(peca.begin(), (i)*(m+2)+(j));
                        break;

                    case '.':
                        t[i][j] = -1;
                        break;

                    default:
                        t[i][j] = -2;
                        break;
                }
            }
        }


        for(int i = 0; i < k; i++)
            bfs(peca[i]);


        for(int i = k; i--;) 
            for(int j = (1<<k); j > 0; j--) 
                memo[i][j] = -1;


        std::cout<<tsp(0,1)<<std::endl;
        peca.clear();

        std::cin >> n >> m >> k;
    }

    return 0;
}

void bfs(int s)
{
    std::queue<int> fila;
    fila.push(s);

    std::vector<int> dist = std::vector<int> ( (n + 2) * (m + 2) + 10, INT_MAX); 
    dist[s] = 0;
    s = t[s / (m+2)][s % (m+2)];
    
    while (!fila.empty())
    {
        int u = fila.front(); 
        fila.pop();
        
        int i = u / (m+2);
        int j = u % (m+2);

        if (t[i][j] > -1)
        {
            int x = std::min(std::min(adj[s][t[i][j]], adj[t[i][j]][s]), dist[u]);
            adj[s][t[i][j]] = adj[t[i][j]][s] = x;
        }

        int k = 8;

        while(k > 0)
        {
            int a = i + di[k];
            int b = j + dj[k];

            int v = (a * (m+2) + b);
            
            if ((1<=(a) && (a)<=n && 1<=(b) && (b)<=m) && tabuleiro[a][b]!='#' && dist[v]==INT_MAX)
            {
                dist[v] = dist[u]+1;
                fila.push(v);
            }

            k--;
        }
    }
}


int tsp(int u, int vis)
{
    if (vis == (1<<k)-1) 
        return adj[u][0];
    
    if (memo[u][vis]!=-1)
        return memo[u][vis];
    
    int ans = INT_MAX;
    
    for (int i = 0; i < k; i++)
    {
        if (!(vis & (1 << i)))ans = std::min(ans, adj[u][i] + tsp(i, vis | (1 << i)));
    }
    return memo[u][vis]=ans;
}
