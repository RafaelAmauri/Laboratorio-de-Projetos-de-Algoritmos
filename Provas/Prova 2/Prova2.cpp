// Rafael Amauri Diniz Augusto - 651047
// Prova 2
// Professor: Wladimir Cardoso Brandão
// Complexidade: O(N^2), onde N é o número de vértices


#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <limits>


class Graph
{
    public:
        // This data structure uses a short to say whether a given vertex is not visited, partially visited or completely visited
        // vertex // visited -------- 0 = not visited ... 1 = partially visited ... 2 = visited
        std::map<int, short> visited_vertexes;
        
        // This data structure is used to store all edges and their values connected to a given vertex 
        // vertex 1 // connected_vertex // weight
        std::map<int, std::vector<std::map<int, int>>> adjacent_vertexes;
        
        int total_weight = 0;
        int num_vertexes = 0;

        void add_edge(int vertex1, int vertex2, int weight);
        void clear_visited_vertexes();
};


// Adds an edge to the graph
void Graph::add_edge(int vertex1, int vertex2, int weight)
{
    // temporary map to be inserted onto the list
    std::map<int, int> temp;
    
    temp = {{vertex2, weight}}; 
    this->adjacent_vertexes[vertex1].push_back(temp);

    temp = {{vertex1, weight}};
    this->adjacent_vertexes[vertex2].push_back(temp);

    total_weight += weight;
    num_vertexes += 1;
}

// Clears the list of visited vertexes
void Graph::clear_visited_vertexes()
{
    this->visited_vertexes.clear();
}


class Prim
{
    private:
        // Priority Queue (PQ) to be used in Prim's algorithm
        // vertex 1 // connected_vertex // weight
        std::map<int, std::vector<std::map<int, int>>> priority_queue;
        
        void add_edge_priority_queue(int vertex1, int vertex2, int weight);
        int mst_add_lowest_edge(Graph *g, Graph *mst);

    public:
        void prim_generate_mst(Graph *g, Graph *mst, int current_vertex);
};

// Adds the edge with the lowest value in <priority_queue> to <mst> and then excludes it from the PQ
int Prim::mst_add_lowest_edge(Graph *g, Graph *mst)
{
    int lowest_edge_v1;
    int lowest_edge_v2;
    int lowest_edge_value = std::numeric_limits<int>::max();

    for(auto i : this->priority_queue)
        for(auto j : i.second)
            for(auto k : j)
            {
                // Skipping already visited vertexes
                if(g->visited_vertexes[k.first] == 2)
                    continue;

                // Finding lowest value of all edges in the PQ
                if(k.second < lowest_edge_value)
                {
                    lowest_edge_v1     =  i.first;
                    lowest_edge_v2     =  k.first;
                    lowest_edge_value  =  k.second;
                }
            }

    // Adds the selected edge to the MST
    mst->add_edge(lowest_edge_v1, lowest_edge_v2, lowest_edge_value);

    for(int i = 0; i < this->priority_queue.find(lowest_edge_v1)->second.size(); i++)
        if(this->priority_queue.find(lowest_edge_v1)->second.at(i).find(lowest_edge_v2)->first == lowest_edge_v2)
            this->priority_queue.find(lowest_edge_v1)->second.at(i).erase(lowest_edge_v2);

    return lowest_edge_v2;
}


// Adds an edge to the priority queue
void Prim::add_edge_priority_queue(int vertex1, int vertex2, int weight)
{
    std::map<int, int> temp;
    
    temp = {{vertex2, weight}}; 
    this->priority_queue[vertex1].push_back(temp);
}


// Finds the minimum spanning tree and loads it into <mst>
void Prim::prim_generate_mst(Graph *g, Graph *mst, int current_vertex)
{
    g->visited_vertexes[current_vertex] = 1;

    // Add vertexes adjacent to <current vertex> to the PQ
    for(auto i : g->adjacent_vertexes[current_vertex])
        for(auto j : i)
        {
            // Skipping visited vertexes so they don't get added to the PQ
            if(g->visited_vertexes[j.first] != 2)
            {
                g->visited_vertexes[j.first] = 1;
                this->add_edge_priority_queue(current_vertex, j.first, j.second);
            }
        }
    
    // If sizes are different, it means <mst> still hasn't found a way to all the vertexes in <g>
    if(mst->adjacent_vertexes.size() != g->adjacent_vertexes.size())
    {
        g->visited_vertexes[current_vertex] = 2;
        int selected_destination_vertex = this->mst_add_lowest_edge(g, mst);
        
        this->prim_generate_mst(g, mst, selected_destination_vertex);
    }

    return;
}

// Marca os vertices
void _dfs_tag_vertexes(Graph *g, int current_vertex, int parent_vertex)
{
    // Se ja for completamente visitado, fazer um return
    if(g->visited_vertexes[current_vertex] == 2)
        return;

    // Marcando current_vertex como parcialmente visitado
    g->visited_vertexes[current_vertex] = 1;

    for(auto i : g->adjacent_vertexes[current_vertex])
        for(auto j : i)
            if(j.first != parent_vertex && g->visited_vertexes[j.first] != 1)
            {
               _dfs_tag_vertexes(g, j.first, current_vertex);
            }

    // Marcar como completamente visitado
    g->visited_vertexes[current_vertex] = 2;

    return;
}


void dfs_tag_vertexes(Graph *g, int current_vertex, int parent_vertex)
{
    _dfs_tag_vertexes(g, current_vertex, parent_vertex);
}


int main()
{
    int s, t, weight, aux1, aux2, starting_station_id;
    std::string estacao1, estacao2, starting_station;
    std::map<std::string, int> array_nomes_estacoes;

    int componentes = 1;

    // Lendo numero de estacoes e de componentes
    std::cin >> s >> t;

    while(s != 0 && t != 0)
    {
        // Grafo normal
        Graph *g   = new Graph();
        // MST com os menores pesos
        Graph *mst = new Graph();
        // Classe prim para gerar a MST
        Prim  *p = new Prim();
        

        // Um array cheio de 0. Ele vai ser usado para identificar vertices que não têm arestas e adicioná-los
        short *array_aux = (short*)calloc(s, sizeof(short));


        // Adiciona estacoes
        for(int i = 0; i < s; i++)
        {
            std::cin >> estacao1;
            array_nomes_estacoes[estacao1] = i;
        }

        // Lendo as componentes e adicionando no grafo G
        for(int i = 0; i < t; i++)
        {    
            std::cin >> estacao1 >> estacao2;
            std::cin >> weight;

            aux1 = array_nomes_estacoes[estacao1];
            aux2 = array_nomes_estacoes[estacao2];

            g->add_edge(aux1, aux2, weight);
        }

        // Lendo a estacao de inicio
        std::cin >> starting_station;
        starting_station_id = array_nomes_estacoes[starting_station];


        // Caso o vertice exista e não foi declarado, colocar ele no grafo conectado a si mesmo.
        // Isso nos ajuda a descobrir quantos componentes tem
        for(int i = 0; i < s; i++)
            if(array_aux[i] == 0)
                g->add_edge(i, i, 0);


        // Marca os vertices conectados a <starting station>
        dfs_tag_vertexes(g, starting_station_id, -1);
        
        for(auto k : g->adjacent_vertexes)
        {
            if(g->visited_vertexes[k.first] == 0)
            {
                componentes++;
            }
        }

        // Caso haja mais de um componente no grafo, é impossível visitar todas estacoes. Logo, printar "Impossible"
        if(componentes > 1)
        {
            std::cout << "Impossible\n";
        }
        // Caso contrario, vamos gerar uma MST do grafo e basta printar o peso total de todas arestas conectadas
        else
        {
            g->clear_visited_vertexes();
            p->prim_generate_mst(g, mst, 0);
            std::cout << mst->total_weight << "\n";
        }

        std::cin >> s >> t;

        // Resetando o numero de componentes
        componentes = 1;

        
        // Limpando a memoria e variaveis
        array_nomes_estacoes.clear();

        delete p;
        delete g;
        delete mst;
        delete array_aux;
    }

    return 0;
}