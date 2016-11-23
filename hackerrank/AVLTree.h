#include <vector>
#include <queue>
#include <iostream>

class AVLTree {
public:
	struct Node{
		Node(int val){
			value = val;
			height = 0;
			leftChild = NULL;
			rightChild = NULL;
		}

		int value;
		int height;
		Node* leftChild;
		Node* rightChild;

		int getHeight(){
			return height;
		}

		int getHeightDiff(){
			int leftHeight = (leftChild) ? leftChild->getHeight() + 1 : 0;
			int rightHeight = (rightChild) ? rightChild->getHeight() + 1 : 0;

			return rightHeight - leftHeight;
		}

		void updateHeight(){
			int maxHeight = 0;
			if (leftChild){
				maxHeight = leftChild->getHeight() + 1;
			}
			if (rightChild){
				maxHeight = std::max(rightChild->getHeight() + 1,maxHeight);
			}
			height = maxHeight;
		}

		bool isBalanced(){
			return std::abs(getHeightDiff()) < 2;
		}

		int getNumberOfChildren(){
			int count = 0;
			if (leftChild){
				++count;
			}
			if (rightChild){
				++count;
			}
			return count;
		}
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

		insert(val,root,NULL);
	}

	Node* find(int val){
		return find(val,root);
	}

	void erase(int val){
		erase(val,root,NULL);
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

	void insert(int val,Node* currentNode,Node* parent){
		if (!currentNode)
			return;

		bool useLeft = (val < currentNode->value);
		Node* childToConsider = (useLeft) ? currentNode->leftChild : currentNode->rightChild;

		if (childToConsider != NULL){
			insert(val,childToConsider,currentNode);
		}
		else{
			if (useLeft){
				currentNode->leftChild = new Node(val);
			} else{
				currentNode->rightChild = new Node(val);
			}
		}

		currentNode->updateHeight();
		balanceTree(currentNode,parent);
	}

	void balanceTree(Node* currentNode,Node* parent){
		if (!currentNode)
			return;

		if (currentNode->isBalanced())
			return;

		int heightDiff = currentNode->getHeightDiff();
		if (heightDiff < 0){
			int childHeightDiff = currentNode->leftChild->getHeightDiff();
			if (childHeightDiff < 0){
				leftRotation(currentNode,parent);
			} else{
				rightLeftRotation(currentNode,parent);
			}
		} else {
			int childHeightDiff = currentNode->rightChild->getHeightDiff();
			if (childHeightDiff > 0){
				rightRotation(currentNode,parent);
			} else{
				leftRightRotation(currentNode,parent);
			}
		}
	}

	void leftRotation(Node* currentNode,Node* parent){
		if (!currentNode || !currentNode->leftChild || !currentNode->leftChild->leftChild){
			std::cout << "Couldn't left rotate." << std::endl;
			return;
		}
		if (currentNode->leftChild->rightChild){
			std::cout << "WARNING: The left rotation will remove an element." << std::endl;
		}

		changeParentChildTo(parent,currentNode->leftChild);

		// rotate current node
		currentNode->leftChild->rightChild = currentNode;
		currentNode->leftChild = NULL;
	}

	void rightRotation(Node* currentNode,Node* parent){
		if (!currentNode || !currentNode->rightChild || !currentNode->rightChild->rightChild){
			std::cout << "Couldn't right rotate." << std::endl;
			return;
		}
		if (currentNode->rightChild->leftChild){
			std::cout << "WARNING: The right rotation will remove an element." << std::endl;
		}

		changeParentChildTo(parent,currentNode->rightChild);

		// rotate current node
		currentNode->rightChild->leftChild = currentNode;
		currentNode->rightChild = NULL;
	}

	void rightLeftRotation(Node* currentNode,Node* parent){
		if (!currentNode || !currentNode->leftChild || !currentNode->leftChild->rightChild){
			std::cout << "Couldn't right-left rotate." << std::endl;
			return;
		}

		innerRightRotation(currentNode->leftChild,currentNode);
		leftRotation(currentNode,parent);
	}

	void innerRightRotation(Node* currentNode,Node* parent){
		if (!currentNode || !currentNode->rightChild){
			std::cout << "Couldn't inner-right rotate." << std::endl;
			return;
		}
		if (currentNode->rightChild->leftChild){
			std::cout << "WARNING: The inner-right rotation will remove an element." << std::endl;
		}

		changeParentChildTo(parent,currentNode->rightChild);
		parent->leftChild->leftChild = currentNode;
		currentNode->rightChild = NULL;
	}

	void leftRightRotation(Node* currentNode,Node* parent){
		if (!currentNode || !currentNode->rightChild || !currentNode->rightChild->leftChild){
			std::cout << "Couldn't left-right rotate." << std::endl;
			return;
		}

		innerLeftRotation(currentNode->rightChild,currentNode);
		rightRotation(currentNode,parent);
	}

	void innerLeftRotation(Node* currentNode,Node* parent){
		if (!currentNode || !currentNode->leftChild){
			std::cout << "Couldn't inner-right rotate." << std::endl;
			return;
		}
		if (currentNode->leftChild->rightChild){
			std::cout << "WARNING: The inner-right rotation will remove an element." << std::endl;
		}

		changeParentChildTo(parent,currentNode->leftChild);
		parent->rightChild->rightChild = currentNode;
		currentNode->leftChild = NULL;
	}

	/**
		This will change the parent node child to the newChild, overwritting the previous child
		It is your responsability to handle the previous child
		Note that if parent is NULL, then it will update the root instead
	*/
	void changeParentChildTo(Node* parent,Node* newChild){
		if (!parent){
			root = newChild;
		} else {
			if (newChild->value < parent->value){
				parent->leftChild = newChild;
			} else {
				parent->rightChild = newChild;
			}
		}
	}

	/* Same as changeParentChildTo() but this will nullify the pointer */
	void nullifyLinkFromParentNode(Node* nodeToErase,Node* parent){
		if (!parent){
			root = NULL;
		} else{
			if (nodeToErase->value < parent->value){
				parent->leftChild = NULL;
			} else {
				parent->rightChild = NULL;
			}
		}
	}

	void traverseDFS(Node* currentNode,std::vector<int>& values){
		if (!currentNode)
			return;

		traverseDFS(currentNode->leftChild,values);
		traverseDFS(currentNode->rightChild,values);

		values.push_back(currentNode->value);
	}

	void traverseBFS(Node* currentNode,std::vector<int>& values){
		if (!currentNode)
			return;

		std::queue<Node*> nodes;
		nodes.push(currentNode);

		while(!nodes.empty()){
			Node* node = nodes.front();
			nodes.pop();

			if (node->leftChild)
				nodes.push(node->leftChild);

			if (node->rightChild)
				nodes.push(node->rightChild);

			values.push_back(node->value);
		}
	}

	void erase(int val,Node* currentNode,Node* parent){
		if (!currentNode){
			return;
		}

		if (currentNode->value == val){
			erase(currentNode,parent);
		} else{
			Node* child = val < currentNode->value ? currentNode->leftChild : currentNode->rightChild;
			erase(val,child,currentNode);
		}

		if (currentNode){
			currentNode->updateHeight();
			balanceTree(currentNode,parent);
		}
	}

	/* The method to erase a node will depend on how many children this node has.  */
	void erase(Node*& nodeToErase,Node* parent){
		if (!nodeToErase){
			return;
		}

		int childrenCount = nodeToErase->getNumberOfChildren();
		switch(childrenCount){
			case 0: 
			{
				eraseNoChildNode(nodeToErase,parent);
			} break;

			case 1: 
			{
				eraseOneChildNode(nodeToErase,parent);
			} break;

			case 2: 
			{
				eraseTwoChildrenNode(nodeToErase,parent);
			} break;

			default: 
			{
				std::cout << "Couldn't erase value as we found an impossible number of children for that node." << std::endl;
			} break;
		}
	}

	void eraseNoChildNode(Node*& nodeToErase,Node* parent){
		nullifyLinkFromParentNode(nodeToErase,parent);
		delete nodeToErase;
		nodeToErase = NULL;
	}

	void eraseOneChildNode(Node*& nodeToErase,Node* parent){
		Node* child = nodeToErase->leftChild ? nodeToErase->leftChild : nodeToErase->rightChild;
		changeParentChildTo(parent,child);

		delete nodeToErase;
		nodeToErase = NULL;
	}

	void eraseTwoChildrenNode(Node*& nodeToErase,Node* parent){
		Node* lowestParentNode = findLowestValueNodeParent(nodeToErase->rightChild,nodeToErase);
		Node* nodeToReplace = lowestParentNode == nodeToErase ? nodeToErase->rightChild : lowestParentNode->leftChild;
		changeParentChildTo(parent,nodeToReplace);
		nodeToReplace->leftChild = nodeToErase->leftChild;

		delete nodeToErase;
		nodeToErase = NULL;
	}

	Node* findLowestValueNodeParent(Node *currentNode,Node* parent){
		if (!currentNode || !currentNode->leftChild)
			return parent;

		return findLowestValueNodeParent(currentNode->leftChild,currentNode);
	}

	Node* find(int val,Node* currentNode){
		if (!currentNode)
			return NULL;

		if (currentNode->value == val)
			return currentNode;

		Node* childToConsider = (val > currentNode->value) ? currentNode->rightChild : currentNode->leftChild;
		return find(val,childToConsider);
	}

	Node* findParent(int val,Node* currentNode){
		if (!currentNode)
			return NULL;

		Node* childToConsider = (val > currentNode->value) ? currentNode->rightChild : currentNode->leftChild;
		if (childToConsider && childToConsider->value == val)
			return currentNode;

		return find(val,childToConsider);
	}

	void deleteAll(Node* currentNode){
		if (!currentNode)
			return;

		deleteAll(currentNode->leftChild);
		deleteAll(currentNode->rightChild);

		delete currentNode;
	}

private:
	Node* root;
};