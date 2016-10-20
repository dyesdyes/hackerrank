#include <climits>
#include <vector>
#include <queue>

#include "consoleInputReader.h"

class PrimsMSTSpecialSubtree {
private:
	struct Edge {
		Edge(int dest,int wei){
			destination = dest;
			weight = wei;
		}
		int destination;
		int weight;
	};

	struct Node {
		Node(){
			id = -1;
			pathWeight = INT_MAX;
			alreadyProcessed = false;
		}
		Node(int id){
			this->id = id;
			pathWeight = INT_MAX;
			alreadyProcessed = false;
		}
		int id;
		int pathWeight;
		bool alreadyProcessed;
		std::vector<Edge> neighbours;
	};
	
	struct node_comparison {
		bool operator () (const Node& left, const Node& right) const{
			return right.pathWeight < left.pathWeight;
		}
	};

public:
	PrimsMSTSpecialSubtree(){}
	~PrimsMSTSpecialSubtree(){}

	int solve(){
		std::vector<Node*> nodes;
		int startNode = parseInput(nodes);
		std::priority_queue<Node, std::vector<Node>, node_comparison> minHeap;
		nodes[startNode]->pathWeight = 0;
		minHeap.push(*nodes[startNode]);

		int totalWeight = 0;
		while(!minHeap.empty()){
			Node* node = nodes[minHeap.top().id];
			minHeap.pop();
			if (node->alreadyProcessed){
				continue;
			}
			
			node->alreadyProcessed = true;
			totalWeight += node->pathWeight;

			for (int i = 0; i < node->neighbours.size();++i){
				Edge edge = node->neighbours[i];
				int neighbourId = edge.destination;
				int weight = edge.weight;
				Node* neighbourNode = nodes[neighbourId];
				
				bool alreadyProcessed = neighbourNode->alreadyProcessed;
				if (!alreadyProcessed && neighbourNode->pathWeight > weight){
					neighbourNode->pathWeight = weight;
					minHeap.push(*neighbourNode);
				}
			}
		}

		return totalWeight;
	}

	int parseInput(std::vector<Node*>& nodes){
		int nodeCount = getNextIntInput();
		int edgeCount = getNextIntInput();
		for(int i = 0; i < nodeCount; ++i){
			nodes.push_back(new Node(i));
		}
		for(int i = 0; i < edgeCount; ++i){
			int a = getNextIntInput() - 1;
			int b = getNextIntInput() - 1;
			int weight = getNextIntInput();
			nodes[a]->neighbours.push_back(Edge(b,weight));
			nodes[b]->neighbours.push_back(Edge(a,weight));
		}
		int startNode = getNextIntInput() - 1;
		return startNode;
	}

};