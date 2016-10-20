#include <queue>
#include <functional>
#include <sstream>
#include <vector>

#include "consoleInputReader.h"

class DijkstraShortestReach2{
public:
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
			distanceFromStart = -1;
			previous = -1;
			id = -1;
		}

		std::vector<Neighbour> neighbours;
		int distanceFromStart;
		int previous;
		int id;

		friend bool operator<(const Node &leftNode,const Node &rightNode) {
			if (leftNode.distanceFromStart != rightNode.distanceFromStart) {
				return leftNode.distanceFromStart < rightNode.distanceFromStart;
			}
			if (leftNode.id != rightNode.id) {
				return leftNode.id < rightNode.id;
			}
			return false;
		}

		friend bool operator>(const Node &leftNode,const Node &rightNode) {
			return rightNode < leftNode;
		}
	};

	template<typename Type, typename Compare = std::greater<Type> >
	struct pgreater : public std::binary_function<Type *, Type *, bool> {
		bool operator()(const Type *x, const Type *y) const
			{ return Compare()(*x, *y); }
	};
	
public:

	std::vector<int> run(){
		int nodeCount = getNextIntInput();
		std::vector<Node> nodes(nodeCount);
		initNodes(nodes);
		int startNode = getNextIntInput() - 1;

		nodes[startNode].distanceFromStart = 0;

		dijkstra(startNode,nodes);

		std::vector<int> out;
		for (int i = 0; i < nodes.size(); ++i){
			if (i != startNode){
				out.push_back(nodes[i].distanceFromStart);
			}
		}
		return out;
	}

private:

	void dijkstra(int startNode,std::vector<Node> &nodes){
		std::vector<bool> isVisited(nodes.size(),false);
		std::priority_queue<Node*, std::vector<Node*>, pgreater<Node>> minHeap;
		minHeap.push(&nodes[startNode]);

		while (!minHeap.empty()) {
			Node* node = minHeap.top();
			minHeap.pop();

			if (isVisited[node->id]){
				continue;
			}

			isVisited[node->id] = true;
			for (int i = 0; i < node->neighbours.size(); ++i){
				Node &neighbourNode = nodes[node->neighbours[i].nodeIndex];
				if (!isVisited[neighbourNode.id]){
					if (neighbourNode.distanceFromStart == -1 || neighbourNode.distanceFromStart > node->distanceFromStart + node->neighbours[i].distance){
						neighbourNode.distanceFromStart = node->distanceFromStart + node->neighbours[i].distance;
						neighbourNode.previous = node->id;
					}
					minHeap.push(&neighbourNode);
				}
			}
		}
	}

	void initNodes(std::vector<Node> &nodes){
		for (int i = 0; i < nodes.size(); ++i){
			nodes[i].id = i;
		}

		int edgeCount = getNextIntInput();
		for(int j = 0; j < edgeCount; ++j){
			int start = getNextIntInput();
			int end = getNextIntInput();
			int weight = getNextIntInput();

			nodes[start-1].neighbours.push_back(Neighbour(end-1,weight));
			nodes[end-1].neighbours.push_back(Neighbour(start-1,weight));
		}
	}
};