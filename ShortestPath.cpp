#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class edge
{
public:
    int targetNode = 0;
    int weight = 0;
};

class node
{
public:
    int ID;
    int distance = 1e9;
};

bool operator>(const node &a, const node &b)
{
    return a.distance > b.distance;
}

bool operator<(const node &a, const node &b)
{
    if (a.distance == b.distance)
    {
        return a.ID > b.ID;
    }
    return a.distance < b.distance;
}
bool operator==(const node &a, const node &b)
{
    return a.distance == b.distance;
}

bool operator>=(const node &a, const node &b)
{
    return a.distance >= b.distance;
}
bool operator<=(const node &a, const node &b)
{
    return a.distance <= b.distance;
}

template <class C>
int partition(C &arr, int left, int right, int loc)
{
    bool flag = 0;
    while (flag == 0)
    {
        while (arr[loc] <= arr[right] && loc != right)
        {
            right--;
        }
        if (loc == right)
        {
            flag = 1;
        }
        else if (arr[loc] > arr[right])
        {
            swap(arr[loc], arr[right]);
            loc = right;
        }

        if (flag == 0)
        {
            while (arr[loc] >= arr[left] && loc != left)
            {
                left++;
            }
            if (loc == left)
            {
                flag = 1;
            }
            else if (arr[loc] < arr[left])
            {
                swap(arr[loc], arr[left]);
                loc = left;
            }
        }
    }
    return loc;
}

template <class T>
void quickSort(T &arr, int begin, int end)
{
    if (begin < end)
    {
        int loc = partition(arr, begin, end, begin);
        quickSort(arr, begin, loc - 1);
        quickSort(arr, loc + 1, end);
    }
}

class shortestPath
{
public:
    shortestPath(int, int);
    void inputEdges();
    void walkPath(int);
    void printNodes();

    int nodeNumber;
    int edgeNumber;
    int beginNode;

    vector<node> nodes;
    map<int, vector<edge>> edges;
};

void shortestPath::printNodes()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i].distance != 1e9)
        {
            cout << nodes[i].ID << " " << nodes[i].distance<<endl;
        }
        else
        {
            return;
        }
    }
}

void shortestPath::walkPath(int startPoint)
{
    //from start node to find every next node and add distance to nodes
    for (auto &edge : edges[startPoint])
    {
        int d = nodes[startPoint].distance + edge.weight;
        if (d < nodes[edge.targetNode].distance)
        {
            nodes[edge.targetNode].distance = d;
            walkPath(edge.targetNode);
        }
        // else
        // {
        //     return;
        // }
    }
}

void shortestPath::inputEdges()
{
    for (int i = 0; i < edgeNumber; i++)
    {
        edge temp;
        int firstN;
        cin >> firstN >> temp.targetNode >> temp.weight;
        edges[firstN].push_back(temp);
    }
}

shortestPath::shortestPath(int node, int edge)
{
    nodeNumber = node;
    edgeNumber = edge;
    this->nodes.resize(node + 1);
    for (int i = 0; i <= node; i++)
    {
        nodes[i].ID = i;
    }
};

int main()
{
    int edge, node;
    while (cin >> node >> edge)
    {
        // cin >> node >> edge;
        shortestPath s(node, edge);
        s.inputEdges();
        cin >> s.beginNode;
        s.nodes[s.beginNode].distance = 0;
        s.walkPath(s.beginNode);
        //sort(s.nodes.begin(), s.nodes.end());
        quickSort(s.nodes, 0, s.nodes.size() - 1);
        s.printNodes();
    }
}