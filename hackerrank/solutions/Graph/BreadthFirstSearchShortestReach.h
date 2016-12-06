#include <queue>
#include <vector>

class BreadthFirstSearchShortestReach {

private:
	struct Node{
		Node(){
			isVisited = false;
		}

		std::vector<int> neighbours;
		bool isVisited;
	};


public:

	std::vector<int> run(int startNode,int nodeCount,std::vector<std::pair<int,int>> edges){
		std::vector<Node> nodes(nodeCount);
		std::vector<int> distanceFromStartNode(nodeCount,-1);// assume unreachable

		populateNodes(nodes,edges);

		breadthFirstSearch(startNode,nodes,distanceFromStartNode);

		distanceFromStartNode.erase(distanceFromStartNode.begin()+startNode);
		return distanceFromStartNode;
	}

	void breadthFirstSearch(int startNode,std::vector<Node>& nodes,std::vector<int>& distanceFromStartNode){
		const int EDGE_LENGTH = 6;
		distanceFromStartNode[startNode] = 0;

		std::queue<int> queue;
		queue.push(startNode);

		while(!queue.empty()){
			int nodeIndex = queue.front();
			queue.pop();
			
			Node &node = nodes[nodeIndex];
			if (node.isVisited){
				continue;
			}

			node.isVisited = true;
			for(int i = 0; i < node.neighbours.size(); ++i){
				int nextNeighbour = node.neighbours[i];
				if (distanceFromStartNode[nextNeighbour] == -1){
					distanceFromStartNode[nextNeighbour] = distanceFromStartNode[nodeIndex] + EDGE_LENGTH;
					queue.push(nextNeighbour);
				}
			}
		}
	}

	void populateNodes(std::vector<Node> &nodes, const std::vector<std::pair<int,int>> &edges){
		for (int i = 0; i < edges.size();++i){
			nodes[edges[i].first].neighbours.push_back(edges[i].second);
			nodes[edges[i].second].neighbours.push_back(edges[i].first);
		}
	}
};
