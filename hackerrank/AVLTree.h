#include <vector>
#include <queue>

// TODO update weight when erasing a node
// TODO balance the tree once an element is inserted or deleted
class AVLTree {
public:
	struct Node{
		Node(int val){
			value = val;
			weight = 0;
			leftChild = NULL;
			rightChild = NULL;
		}

		int value;
		int weight;
		Node* leftChild;
		Node* rightChild;
	};

public:
	AVLTree(){
		root = NULL;
	}

	AVLTree(std::vector<int> values){
		root = NULL;

		for (int i = 0; i < values.size(); ++i){
			insert(values[i]);
		}
	}

	~AVLTree(){
		deleteAll(root);
	}

	void insert(int val){
		if (root == NULL){
			root = new Node(val);
			return;
		}

		insert(val,root);
	}

	Node* find(int val){
		find(val,root);
	}

	void erase(int val){
		if (root == NULL)
			return;
		bool isRootNodeToDelete = root->value == val;
		if (isRootNodeToDelete){
			erase(root,NULL);
			return;
		}

		Node* parentNode = findParent(val,root);
		if (parentNode == NULL){
			return;
		}

		if (parentNode->leftChild != NULL && parentNode->leftChild->value == val){
			erase(parentNode->leftChild,parentNode);
		}
		else{
			erase(parentNode->rightChild,parentNode);
		}
	}

	// DFS
	std::vector<int> traversePostOrder(){
		std::vector<int> out;
		traverseDFS(root,out);
		return out;
	}

	// BFS
	std::vector<int> traverseLevelOrder(){
		std::vector<int> out;
		traverseBFS(root,out);
		return out;
	}

private:

	void traverseDFS(Node* currentNode,std::vector<int>& values){
		if (currentNode == NULL)
			return;

		traverseDFS(currentNode->leftChild,values);
		traverseDFS(currentNode->rightChild,values);

		values.push_back(currentNode->value);
	}

	void traverseBFS(Node* currentNode,std::vector<int>& values){
		if (currentNode == NULL)
			return;

		std::queue<Node*> nodes;
		nodes.push(currentNode);

		while(!nodes.empty()){
			Node* node = nodes.front();
			nodes.pop();

			if (node->leftChild != NULL)
				nodes.push(node->leftChild);

			if (node->rightChild != NULL)
				nodes.push(node->rightChild);

			values.push_back(node->value);
		}
	}

	void erase(Node* nodeToErase,Node* parent){
		if (nodeToErase->leftChild == NULL && nodeToErase->rightChild == NULL){ // no child
			delete nodeToErase;
			nodeToErase = NULL;
			return;
		}

		if (nodeToErase->leftChild == NULL || nodeToErase->rightChild == NULL){ // one child
			eraseOneChildNode(nodeToErase,parent);
			return;
		}

		eraseTwoChildrenNode(nodeToErase,parent);
	}

	void eraseOneChildNode(Node* oneChildNodeToErase,Node* parent){
		Node* child = oneChildNodeToErase->leftChild == NULL ? oneChildNodeToErase->rightChild : oneChildNodeToErase->leftChild;
		if (oneChildNodeToErase == root){
			root = child;
		} else{
			bool isLeftToReplace = parent->leftChild == oneChildNodeToErase;
			if (isLeftToReplace){
				parent->leftChild = child;
			}
			else {
				parent->rightChild = child;
			}
		}

		delete oneChildNodeToErase;
		oneChildNodeToErase = NULL;
	}

	void eraseTwoChildrenNode(Node* twoChildrenNodeToErase,Node* parent){
		Node* lowestParentNode = findLowestValueNodeParent(twoChildrenNodeToErase->rightChild);

		Node* nodeToReplace = (lowestParentNode == NULL) ? twoChildrenNodeToErase->rightChild : lowestParentNode->leftChild;

		if (twoChildrenNodeToErase == root){
			root = nodeToReplace;
		} else{
			bool isLeftToReplace = parent->leftChild == twoChildrenNodeToErase;
			if (isLeftToReplace){
				parent->leftChild = nodeToReplace;
			}
			else {
				parent->rightChild = nodeToReplace;
			}
		}

		if (lowestParentNode != NULL){
			lowestParentNode->leftChild = NULL;
		}

		delete twoChildrenNodeToErase;
		twoChildrenNodeToErase = NULL;
	}

	Node* findLowestValueNodeParent(Node *currentNode){
		if (currentNode == NULL)
			return NULL;

		if (currentNode->leftChild == NULL)
			return NULL;
		
		if (currentNode->leftChild->leftChild == NULL)
			return currentNode;
		else
			return findLowestValueNodeParent(currentNode->leftChild);
	}

	void insert(int val,Node* currentNode){
		if (currentNode == NULL)
			return;

		bool useLeft = (val < currentNode->value);
		Node* childToConsider = (useLeft) ? currentNode->leftChild : currentNode->rightChild;
		
		currentNode->weight = (useLeft) ? currentNode->weight - 1 : currentNode->weight + 1;

		if (childToConsider != NULL){
			insert(val,childToConsider);
		}
		else{
			if (useLeft){
				currentNode->leftChild = new Node(val);
			} else{
				currentNode->rightChild = new Node(val);
			}
		}
	}

	Node* find(int val,Node* currentNode){
		if (currentNode == NULL)
			return NULL;

		if (currentNode->value == val)
			return currentNode;

		Node* childToConsider = (val > currentNode->value) ? currentNode->rightChild : currentNode->leftChild;
		return find(val,childToConsider);
	}

	Node* findParent(int val,Node* currentNode){
		if (currentNode == NULL)
			return NULL;

		Node* childToConsider = (val > currentNode->value) ? currentNode->rightChild : currentNode->leftChild;
		if (childToConsider != NULL && childToConsider->value == val)
			return currentNode;

		return find(val,childToConsider);
	}

	void deleteAll(Node* currentNode){
		if (currentNode == NULL)
			return;

		deleteAll(currentNode->leftChild);
		deleteAll(currentNode->rightChild);

		delete currentNode;
	}

	void leftRotation(Node* startNode,Node* parentNode){
		if (!has2ConsecutiveRightChildrenOnly(startNode)){
			return;
		}

		if (startNode == root){
			root = startNode->rightChild;
			startNode->rightChild->leftChild = startNode;
		} else{
			parentNode->rightChild = startNode->rightChild;
			startNode->rightChild->leftChild = startNode;
		}
	}

	bool has2ConsecutiveRightChildrenOnly(Node* node){
		return node->rightChild != NULL &&
			node->leftChild == NULL &&
			node->rightChild->rightChild != NULL &&
			node->rightChild->leftChild == NULL;
	}

	void rightRotation(Node* startNode,Node* parentNode){
		if (!has2ConsecutiveLeftChildrenOnly(startNode)){
			return;
		}

		if (startNode == root){
			root = startNode->leftChild;
			startNode->leftChild->rightChild = startNode;
		} else{
			parentNode->leftChild = startNode->leftChild;
			startNode->leftChild->rightChild = startNode;
		}
	}

	bool has2ConsecutiveLeftChildrenOnly(Node* node){
		return node->leftChild != NULL &&
			node->rightChild == NULL &&
			node->leftChild->leftChild != NULL &&
			node->leftChild->rightChild == NULL;
	}

	void leftRightRotation(Node* startNode,Node* parentNode){
		if (!has2ConsecutiveRightThenLeftChildrenOnly(startNode))
			return;

		Node* temp = startNode->rightChild;
		startNode->rightChild = startNode->rightChild->leftChild;
		startNode->rightChild->rightChild = temp;

		leftRotation(startNode,parentNode);
	}

	bool has2ConsecutiveRightThenLeftChildrenOnly(Node* node){
		return node->rightChild != NULL &&
			node->leftChild == NULL &&
			node->rightChild->leftChild != NULL &&
			node->rightChild->rightChild == NULL;
	}

	void rightLeftRotation(Node* startNode,Node* parentNode){
		if (!has2ConsecutiveLeftThenRightChildrenOnly(startNode))
			return;

		Node* temp = startNode->leftChild;
		startNode->leftChild = startNode->leftChild->rightChild;
		startNode->leftChild->leftChild = temp;

		leftRotation(startNode,parentNode);
	}

	bool has2ConsecutiveLeftThenRightChildrenOnly(Node* node){
		return node->leftChild != NULL &&
			node->rightChild == NULL &&
			node->leftChild->rightChild != NULL &&
			node->leftChild->leftChild == NULL;
	}

private:
	Node* root;
};