// Aluno: Rafael Amauri Diniz Augusto -- 651047
// Tarefa: AS06 - Penalização
// Professor: Wladmir Cardoso
// Matéria: LPA
// Complexidade: O(V^2), onde V é o número de vértices


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

        // Adds an edge to the graph
        void add_edge(int vertex1, int vertex2, int weight);


        // Clears the list of visited vertexes
        void clear_visited_vertexes();
};


class Prim
{
    private:
        // Priority Queue (PQ) to be used in Prim's algorithm
        // vertex 1 // connected_vertex // weight
        std::map<int, std::vector<std::map<int, int>>> priority_queue;

        // Adds an edge to the priority queue
        void add_edge_priority_queue(int vertex1, int vertex2, int weight);

        // Adds the edge with the lowest value in <priority_queue> to <mst> and then excludes it from the PQ
        int mst_add_lowest_edge(Graph *g, Graph *mst);

    public:
        // Finds the minimum spanning tree and loads it into <mst>
        void prim_generate_mst(Graph *g, Graph *mst, int current_vertex);
};


// Returns the number of components in the graph
int num_componentes(Graph *g, int M, int N);

void dfs_tag_vertexes(Graph *g, int current_vertex, int parent_vertex);

void _dfs_tag_vertexes(Graph *g, int current_vertex, int parent_vertex, std::vector<int> *arr);


int main()
{
    int n_tests, M, N, K, e1, e2;
    // Variavel para converter de letra para um int equivalentes
    char aux;
    
    std::cin >> n_tests;


    for(int i = 0; i < 1; i++)
    {
        // Estrutura de grafo
        Graph *g = new Graph();
        Graph *mst = new Graph();
        Prim *p  = new Prim();
        
        std::cin >> M >> N >> K;
        std::cin.ignore();

        std::cout << num_componentes(g, M, N) << " componentes\n\n";

        g->clear_visited_vertexes();

        p->prim_generate_mst(g, mst, 1);

        //g->clear_visited_vertexes();
        //mst->clear_visited_vertexes();

        //std::cout << num_componentes(mst, M, N) << " componentes\n";
        
        for(auto i : mst->adjacent_vertexes)
        {
            std::cout << i.first+1 << "\n";
        }
        

        free(g);
        free(p);
    }

    return 0;
}


int num_componentes(Graph *g, int M, int N)
{
    // Um array cheio de 0. Ele vai ser usado para identificar vertices que não têm arestas e adicionálos
    short *array_aux = (short*)calloc(M, sizeof(short));

    // Conta o numero de componentes de cada grafo
    int componentes = 1, e1, e2, w;

    // Para cada aresta, pegar os valores de onde ela é declarada
    for(int j = 0; j < N; j++)
    {
        std::cin >> e1;
        array_aux[e1-1] = 1;

        std::cin >> e2;
        array_aux[e2-1] = 1;

        std::cin >> w;

        g->add_edge(e1-1, e2-1, w);
    }
    
    // Caso o vertice exista e não foi declarado, colocar ele no grafo conectado a si mesmo.
    for(int i = 0; i < M; i++)
        if(array_aux[i] == 0)
        {
            std::cout << array_aux[i] << " detectado como nao visitado\n\n"; 
            g->add_edge(i, i, 0);
        }

    // Marcar todos vertices ligados ao primeiro vertice
    dfs_tag_vertexes(g, g->adjacent_vertexes.begin()->first, -1);
    std::cout << "\n";

    // Para cada vertice existente, vamos marcá-los também. 
    // Caso ele não tenha sido marcado ainda, é porque é um componente desconexo
    for(auto k : g->adjacent_vertexes)
    {
        if(g->visited_vertexes[k.first] == 0)
        {
            componentes++;
            dfs_tag_vertexes(g, k.first, -1);
        }
    }

    // É mais rápido desalocar da memória e realocar do que fazer função de clean-up pro array
    free(array_aux);

    return componentes;
}


void dfs_tag_vertexes(Graph *g, int current_vertex, int parent_vertex)
{
    // Vetor com os vertices
    std::vector<int> array_aux;

    _dfs_tag_vertexes(g, current_vertex, parent_vertex, &array_aux);

    // Colocando a saida em ordem alfabetica
    std::sort(array_aux.begin(), array_aux.end());

    // Printando elementos do array
    //for(auto i : array_aux)
    //    std::cout << (char)(i + 'a') << ",";

}


void _dfs_tag_vertexes(Graph *g, int current_vertex, int parent_vertex, std::vector<int> *arr)
{
    // Se ja for completamente visitado, fazer um return
    if(g->visited_vertexes[current_vertex] == 2)
        return;

    // Marcando current_vertex como parcialmente visitado
    g->visited_vertexes[current_vertex] = 1;
    
    // Inserindo na lista de elementos
    arr->push_back(current_vertex);


    for(auto i : g->adjacent_vertexes[current_vertex])
        for(auto j : i)
            if(j.first != parent_vertex && g->visited_vertexes[j.first] != 1)
               _dfs_tag_vertexes(g, j.first, current_vertex, arr);


    // Marcar como completamente visitado
    g->visited_vertexes[current_vertex] = 2;

    return;
}


void Graph::add_edge(int vertex1, int vertex2, int weight)
{
    // temporary map to be inserted onto the list
    std::map<int, int> temp;
    
    temp = {{vertex2, weight}}; 
    this->adjacent_vertexes[vertex1].push_back(temp);

    temp = {{vertex1, weight}};
    this->adjacent_vertexes[vertex2].push_back(temp);

    total_weight += weight;
}


void Graph::clear_visited_vertexes()
{
    this->visited_vertexes.clear();
}


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


void Prim::add_edge_priority_queue(int vertex1, int vertex2, int weight)
{
    std::map<int, int> temp;
    
    temp = {{vertex2, weight}}; 
    this->priority_queue[vertex1].push_back(temp);
}


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