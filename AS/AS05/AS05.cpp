// Aluno: Rafael Amauri Diniz Augusto -- 651047
// Tarefa: AS05 - Componentes Conexos
// Professor: Wladmir Cardoso
// Matéria: LPA
// Complexidade: O(V^2), onde V é o número de vértices


#include <iostream>
#include <map>
#include <vector>
#include <algorithm>


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
}

// Clears the list of visited vertexes
void Graph::clear_visited_vertexes()
{
    this->visited_vertexes.clear();
}

// Calls _dfs_tag_vertexes()
void dfs_tag_vertexes(Graph *g, int current_vertex, int parent_vertex);

// Tags all vertexes connected to current_vertex
void _dfs_tag_vertexes(Graph *g, int current_vertex, int parent_vertex, std::vector<int> *arr);


int main()
{
    int N, V, E, e1, e2;
    // Variavel para converter de letra para um int equivalentes
    char aux;
    
    std::cin >> N;

    for(int i = 0; i < N; i++)
    {
        // Um array cheio de 0. Ele vai ser usado para identificar vertices que não têm arestas e adicionálos
        short *array_aux = (short*)calloc(N, sizeof(short));

        // Estrutura de grafo
        Graph *g = new Graph();

        // Conta o numero de componentes de cada grafo
        int componentes = 1;

        std::cout << "Case #" << i+1 << ":\n";
        std::cin >> V >> E;

        // Para cada aresta, pegar os valores de onde ela é declarada
        for(int j = 0; j < E; j++)
        {
            std::cin >> aux;
            e1 = aux - 'a';
            array_aux[e1] = 1;

            std::cin >> aux;
            e2 = aux - 'a';
            array_aux[e2] = 1;

            g->add_edge(e1, e2, 0);
        }
        
        // Caso o vertice exista e não foi declarado, colocar ele no grafo conectado a si mesmo.
        for(int i = 0; i < V; i++)
            if(array_aux[i] == 0)
                g->add_edge(i, i, 0);
        

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
                std::cout << "\n";
            }     
        }
        
        std::cout << componentes << " connected components\n\n";

        // É mais rápido desalocar da memória e realocar do que fazer função de clean-up pro grafo e pro array
        free(g);
        free(array_aux);
    }

    return 0;
}

void dfs_tag_vertexes(Graph *g, int current_vertex, int parent_vertex)
{
    // Vetor com os vertices
    std::vector<int> array_aux;

    _dfs_tag_vertexes(g, current_vertex, parent_vertex, &array_aux);

    // Colocando a saida em ordem alfabetica
    std::sort(array_aux.begin(), array_aux.end());

    // Printando elementos do array
    for(auto i : array_aux)
        std::cout << (char)(i + 'a') << ",";

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