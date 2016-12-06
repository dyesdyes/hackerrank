#include <vector>
#include "consoleWritter.h"
#include "consoleInputReader.h"

class SynchronousShopping{

public:
	struct Edge{
		Edge(int start, int end, int weight){
			this->start = start;
			this->end = end;
			this->weight = weight;
		}

		int start;
		int end;
		int weight;
	};

	struct Neighbour{
		Neighbour(int index,int dis){
			nodeIndex = index;
			distance = dis;
		}
		int nodeIndex;
		int distance;
	};

	struct Node{
		Node(){
			isVisited = false;
		}

		std::vector<int> fishTypes;
		std::vector<Neighbour> neighbours;

		bool isVisited;
	};

public:

	void runFromConsole(){
		SynchronousShopping a;

		int nodeCount = getNextIntInput();
		int edgeCount = getNextIntInput();
		int totalTypeCount = getNextIntInput();
		std::vector<std::vector<int>> typesPerNode;
		std::vector<SynchronousShopping::Edge> edges;
		for(int i = 0; i < nodeCount; ++i){
			int typeCount = getNextIntInput();
			std::vector<int> types;
			for (int j = 0; j < typeCount; ++j){
				int type = getNextIntInput() - 1;
				types.push_back(type);
			}
			typesPerNode.push_back(types);
		}
		for(int i = 0; i < edgeCount; ++i){
			int start = getNextIntInput() - 1;
			int end = getNextIntInput() - 1;
			int weight = getNextIntInput();

			edges.push_back(SynchronousShopping::Edge(start,end,weight));
		}
		std::cout << a.run(totalTypeCount,typesPerNode,edges) << std::endl;
	}

private:
	int run(int fishTypes, const std::vector<std::vector<int>>& typesPerNode,const std::vector<Edge>& edges){
		std::vector<Node> nodes(typesPerNode.size());
		initNodes(nodes,typesPerNode,edges);

		// to implement

		return 0;
	}

	void initNodes(std::vector<Node> &nodes,const std::vector<std::vector<int>>& typesPerNode,const std::vector<Edge>& edges){
		for (int i = 0; i < typesPerNode.size(); ++i){
			nodes[i].fishTypes = typesPerNode[i];
		}
		for (int i = 0; i < edges.size(); ++i){
			nodes[edges[i].start].neighbours.push_back(Neighbour(edges[i].end,edges[i].weight));
			nodes[edges[i].end].neighbours.push_back(Neighbour(edges[i].start,edges[i].weight));
		}
	}

};