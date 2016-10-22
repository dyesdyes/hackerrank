#include <vector>

#include "consoleInputReader.h"


class EvenTree {
	struct Node {
		Node(int id){
			this->id = id;
		}
		int id;
		std::vector<int> neighbours;
	};


public:
	EvenTree(){}
	~EvenTree(){}

	void solve(){
		std::vector<Node*> nodes;
		parseInputs(nodes);

		if (nodes.size() % 2 == 1){
			return;
		}
		int removedEdges = 0;
		getNumberOfChildren(nodes[0],removedEdges,nodes);

		std::cout << removedEdges << std::endl;
	}

	int getNumberOfChildren(Node* current,int& removedEdges,const std::vector<Node*>& nodes){
		int totalNumberOfNode = 1;
		for (int i = 0; i < current->neighbours.size(); ++i){
			int branchHeight = getNumberOfChildren(nodes[current->neighbours[i]],removedEdges,nodes);

			if (branchHeight % 2 == 0){
				++removedEdges;
				continue;
			}

			totalNumberOfNode += branchHeight;
		}
		return totalNumberOfNode;
	}

private:
	void parseInputs(std::vector<Node*>& nodes){
		int nodeCount = getNextIntInput();
		int edgeCount = getNextIntInput();
		for(int i = 0; i < nodeCount; ++i){
			nodes.push_back(new Node(i));
		}
		for(int i = 0; i < edgeCount; ++i){
			int a = getNextIntInput() - 1;
			int b = getNextIntInput() - 1;
			nodes[b]->neighbours.push_back(a);
		}
	}

};