#include <climits>
#include <vector>
#include <queue>

#include "consoleInputReader.h"

class KruskalMSTReallySpecialSubtree {
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
		Node(int id){
			this->id = id;
			isProcessed = false;
			pathWeight = INT_MAX;
			pathWeightWithIds = INT_MAX;
		}

		int id;
		int pathWeight;
		int pathWeightWithIds;
		bool isProcessed;
		std::vector<Edge> neighbours;

		void setPathWeight(Edge edge){
			pathWeight = edge.weight;
			pathWeightWithIds = edge.weight + id + edge.destination;
		}

		bool isNodeWeightBigger(int sourceNodeId,Edge edge){
			if (pathWeight > edge.weight){
				return true;
			}
			if (pathWeight == edge.weight){
				return pathWeightWithIds > sourceNodeId + edge.destination + edge.weight;
			}
			return false;
		}
	};

	struct node_comparison {
		bool operator()(const Node& left,const Node& right){
			if (left.pathWeight == right.pathWeight){
				return right.pathWeightWithIds < left.pathWeightWithIds;
			}
			return right.pathWeight < left.pathWeight;
		}
	};


public:
	KruskalMSTReallySpecialSubtree(){}
	~KruskalMSTReallySpecialSubtree(){}

	int solve(){
		std::vector<Node*> nodes;
		int startNode = parseInputs(nodes);

		std::priority_queue<Node,std::vector<Node>,node_comparison> minHeap;
		nodes[startNode]->pathWeight = 0;
		nodes[startNode]->pathWeightWithIds = 0;

		minHeap.push(*nodes[startNode]);
		int totalWeight = 0;
		while(!minHeap.empty()){
			Node* node = nodes[minHeap.top().id];
			minHeap.pop();
			if (node->isProcessed){
				continue;
			}

			totalWeight += node->pathWeight;
			node->isProcessed = true;

			for (int i = 0; i < node->neighbours.size(); ++i){
				Edge edge = node->neighbours[i];
				Node* neighbourNode = nodes[edge.destination];
				
				if (!neighbourNode->isProcessed && neighbourNode->isNodeWeightBigger(node->id,edge)){
					neighbourNode->setPathWeight(edge);
					minHeap.push(*neighbourNode);
				}
			}
		}

		deleteAll(nodes);
		return totalWeight;
	}

private:
	int parseInputs(std::vector<Node*>& nodes){
		int nodeCount = getNextIntInput();
		int edgeCount = getNextIntInput();
		for (int i = 0; i < nodeCount; ++i){
			nodes.push_back(new Node(i));
		}
		for (int i = 0; i < edgeCount; ++i){
			int a = getNextIntInput() - 1;
			int b = getNextIntInput() - 1;
			int weight = getNextIntInput();
			nodes[a]->neighbours.push_back(Edge(b,weight));
			nodes[b]->neighbours.push_back(Edge(a,weight));
		}
		return getNextIntInput() - 1;
	}

	void deleteAll(std::vector<Node*>& nodes){
		for (int i = 0; i < nodes.size(); ++i){
			delete nodes[i];
		}
	}
};