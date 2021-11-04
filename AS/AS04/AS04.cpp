// Autor: Rafael Amauri
// Tarefa: Roteadores
// ID da Tarefa: 1774
// URL: https://www.beecrowd.com.br/judge/pt/problems/view/1774
// Complexidade: O(V^2), onde V é o número de vértices

#include <iostream>
#include <vector>
#include <limits>
#include <map>


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

int main(void)
{
    // Complete Graph
    Graph *g = new Graph();
    // Minimum Spanning Tree
    Graph *mst = new Graph();

    int R, C, V, W, P;
    std::cin >> R >> C;

    for(int i = 0; i < C; i++)
    {
        std::cin >> V >> W >> P;

        // Adds edge and weight to the Graph
        g->add_edge(V, W, P);
    }

    // Generates a MST and stores it in <mst>
    Prim *p = new Prim();
    p->prim_generate_mst(g, mst, V);

    // Print the total weight in the MST
    std::cout << mst->total_weight;
}