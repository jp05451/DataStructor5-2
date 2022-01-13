#include <iostream>
#include <map>
#include <vector>

using namespace std;

class edge
{
public:
    int firstNode;
    int secondNode;
    int weight;
};

class shortestPath
{
public:
    shortestPath(int, int);
    int nodeValue;
    int edgeValue;
    vector<int> nodes;
};

shortestPath::shortestPath(int node, int edge)
{
    nodeValue = node;
    edgeValue = edge;
};

int main()
{
}