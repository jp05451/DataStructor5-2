#include <iostream>
#include <vector>

using namespace std;

class graph;

class node
{
public:
	int index, label = 2147364847, past = NULL;
	graph *origin;

	void find_next();
};

class edge
{
public:
	int start, end, weight;
};

class graph
{
public:
	vector<edge> edges;
	vector<node> nodes;
	vector<node> n;

	void insert(int node_index)
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i].index == node_index)
				return;
		}
		node node_new;
		node_new.index = node_index;
		node_new.origin = this;
		nodes.push_back(node_new);
	}

	void insert(int start, int end, int weight)
	{
		edge edge_in;
		edge_in.start = start;
		edge_in.end = end;
		edge_in.weight = weight;
		edges.push_back(edge_in);
		insert(start);
		insert(end);
	}

	void find_n()
	{
		node pop_node;
		for (int i = 0; i < nodes.size(); i++)
		{
			if (pop_node.label > nodes[i].label)
				pop_node = nodes[i];
		}
		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i].index == pop_node.index)
			{
				nodes.erase(nodes.begin() + i);
				break;
			}
		}
		if (pop_node.label != 2147364847)
			n.push_back(pop_node);
	}

	void find_path(int start, int end)
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i].index == start)
			{
				nodes[i].label = 0;
				n.push_back(nodes[i]);
				nodes.erase(nodes.begin() + i);
				break;
			}
		}
		int point = 0;
		do
		{
			n.back().find_next();
			find_n();
			point++;
		} while (point < n.size());
	}

	void output_path(int end)
	{
		vector<node> stack;
		int past = end;
		while (past != NULL && n.size() != 0)
		{
			if (n.back().index == past)
			{
				stack.push_back(n.back());
				past = n.back().past;
			}
			n.pop_back();
		}

		bool first = true;
		while (stack.size() != 0)
		{
			if (first)
			{
				cout << stack.back().index;
				first = false;
				stack.pop_back();
			}
			else if (stack.size() == 1)
			{
				cout << " " << stack.back().index << endl;
				cout << stack.back().label << endl;
				stack.pop_back();
			}
			else
			{
				cout << " " << stack.back().index;
				stack.pop_back();
			}
		}
	}
};

void node::find_next()
{
	vector<edge> edges = origin->edges;
	for (int i = 0; i < edges.size(); i++)
	{
		if (edges[i].start == index)
		{
			vector<node> nodes = origin->nodes;
			//bool exist = false;
			for (int j = 0; j < nodes.size(); j++)
			{
				if (nodes[j].index == edges[i].end)
				{
					if (nodes[j].label > label + edges[i].weight)
					{
						origin->nodes[j].label = label + edges[i].weight;
						origin->nodes[j].past = index;
					}
					//exist = true;
					break;
				}
			}
		}
	}
}

int main()
{
	int m, n, a, b;
	cin >> m >> n >> a >> b;
	graph g;
	for (int i = 0; i < n; i++)
	{
		int start, end, weight;
		cin >> start >> end >> weight;
		g.insert(start, end, weight);
	}
	//g.n.resize(g.nodes.size());
	g.find_path(a, b);
	g.output_path(b);

	return 0;
}