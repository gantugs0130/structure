#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class node {
   public:
    int with;
    int wight;
    node(int with, int wight) {
        this->with = with;
        this->wight = wight;
    }
};
class table {
    class row {
       public:
        // known shortest path
        int nsp;
        int previous;

        row() {
            nsp = 2147483647;
            previous = -1;
        }
    };

   public:
    vector<row> info;

    table(int size) {
        this->info.reserve(size);
        for (int i = 0; i < size; ++i) {
            row temp;
            this->info.push_back(temp);
        }
    }

    void print_table() {
        if (this->info.size() <= 0)
            return;

        printf("%4s | %10s | %10s\n", "Node", "KSP", "Previous");
        for (int i = 0; i < this->info.size(); ++i) {
            printf("%4d | %10d | %10d\n", i, this->info[i].nsp, this->info[i].previous);
        }
        printf("\n");
    }
};

vector<vector<node>> graph;

int add_node() {
    vector<node> temp;
    graph.push_back(temp);
    return graph.size();
}

int add_edge(int index_one, int index_two, int wight = 1) {
    if (index_one >= graph.size() || index_one < 0 || index_two >= graph.size() || index_two < 0)
        return -1;

    if (index_one == index_two)
        return -1;

    if (wight < 1)
        return -1;

    for (const node &element : graph[index_one]) {
        if (element.with == index_two)
            return -1;
    }

    graph[index_one].push_back(node(index_two, wight));
    graph[index_two].push_back(node(index_one, wight));
    return 0;
}

int main() {
    add_node();
    add_node();
    add_node();
    add_node();
    add_node();

    add_edge(0, 1, 7);
    add_edge(0, 2, 3);
    add_edge(1, 2, 1);
    add_edge(1, 3, 2);
    add_edge(1, 4, 6);
    add_edge(2, 3, 2);
    add_edge(3, 4, 4);

    return 0;
}