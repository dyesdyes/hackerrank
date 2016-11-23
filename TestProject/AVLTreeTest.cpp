// example_tests.cpp
#include "stdafx.h"
#include <iterator>

#include "catch.hpp"

#include "AVLTree.h"


TEST_CASE("Simple insert, no rotation","[insert][traversePostOrder]") {
	AVLTree avltree;
	avltree.insert(4);
	avltree.insert(3);
	avltree.insert(5);
	avltree.insert(1);

	std::vector<int> actual = avltree.traversePostOrder();
	int arr[] = {1,3,5,4};
	std::vector<int> expected(std::begin(arr), std::end(arr));
	REQUIRE(actual == expected);
}

TEST_CASE("Insert with left rotation","[insert][rotation][traversePostOrder]") {
	AVLTree avltree;
	avltree.insert(5);
	avltree.insert(4);
	avltree.insert(3);
	avltree.insert(1);

	std::vector<int> actual = avltree.traversePostOrder();
	int arr[] = {1,3,5,4};
	std::vector<int> expected(std::begin(arr), std::end(arr));
	REQUIRE(actual == expected);
}

TEST_CASE("Insert with right rotation","[insert][rotation][traversePostOrder]") {
	AVLTree avltree;
	avltree.insert(1);
	avltree.insert(2);
	avltree.insert(3);
	avltree.insert(4);

	std::vector<int> actual = avltree.traversePostOrder();
	int arr[] = {1,4,3,2};
	std::vector<int> expected(std::begin(arr), std::end(arr));
	REQUIRE(actual == expected);
}

TEST_CASE("Insert with right-left rotation","[insert][rotation][traversePostOrder]") {
	AVLTree avltree;
	avltree.insert(4);
	avltree.insert(1);
	avltree.insert(3);
	avltree.insert(2);

	std::vector<int> actual = avltree.traversePostOrder();
	int arr[] = {2,1,4,3};
	std::vector<int> expected(std::begin(arr), std::end(arr));
	REQUIRE(actual == expected);
}

TEST_CASE("Insert with left-right rotation","[insert][rotation][traversePostOrder]") {
	AVLTree avltree;
	avltree.insert(2);
	avltree.insert(4);
	avltree.insert(3);
	avltree.insert(1);

	std::vector<int> actual = avltree.traversePostOrder();
	int arr[] = {1,2,4,3};
	std::vector<int> expected(std::begin(arr), std::end(arr));
	REQUIRE(actual == expected);
}

TEST_CASE("erase with no item","[erase][traversePostOrder]") {
	AVLTree avltree;
	avltree.erase(4);

	std::vector<int> actual = avltree.traversePostOrder();
	std::vector<int> expected;
	REQUIRE(actual == expected);
}

TEST_CASE("erase with one item","[erase][traversePostOrder]") {
	AVLTree avltree;
	avltree.insert(4);
	avltree.erase(4);

	std::vector<int> actual = avltree.traversePostOrder();
	std::vector<int> expected;
	REQUIRE(actual == expected);
}

TEST_CASE("Simple insert, no rotation, erase with one child","[insert][erase][traversePostOrder]") {
	AVLTree avltree;
	avltree.insert(4);
	avltree.insert(3);
	avltree.insert(5);
	avltree.insert(1);
	avltree.insert(6);
	avltree.erase(5);

	std::vector<int> actual = avltree.traversePostOrder();
	int arr[] = {1,3,6,4};
	std::vector<int> expected(std::begin(arr), std::end(arr));
	REQUIRE(actual == expected);
}

TEST_CASE("Simple insert, no rotation, erase with two children","[insert][erase][traversePostOrder]") {
	AVLTree avltree;
	avltree.insert(4);
	avltree.insert(3);
	avltree.insert(5);
	avltree.insert(6);
	avltree.insert(1);
	avltree.insert(7);
	avltree.erase(5);

	std::vector<int> actual = avltree.traversePostOrder();
	int arr[] = {1,3,7,6,4};
	std::vector<int> expected(std::begin(arr), std::end(arr));
	REQUIRE(actual == expected);
}

TEST_CASE("Simple insert, no rotation, erase root node with two children","[insert][erase][root][traversePostOrder]") {
	AVLTree avltree;
	avltree.insert(4);
	avltree.insert(3);
	avltree.insert(5);
	avltree.erase(4);

	std::vector<int> actual = avltree.traversePostOrder();
	int arr[] = {3,5};
	std::vector<int> expected(std::begin(arr), std::end(arr));
	REQUIRE(actual == expected);
}

TEST_CASE("Simple insert, no rotation, erase with rotation","[insert][erase][traversePostOrder]") {
	AVLTree avltree;
	avltree.insert(4);
	avltree.insert(3);
	avltree.insert(5);
	avltree.insert(1);
	avltree.insert(6);
	avltree.erase(6);
	avltree.erase(5);

	std::vector<int> actual = avltree.traversePostOrder();
	int arr[] = {1,4,3};
	std::vector<int> expected(std::begin(arr), std::end(arr));
	REQUIRE(actual == expected);
}

TEST_CASE("Test node height property","[height]") {
	
	SECTION("insert only, No rotation, left branch heavier") {
		AVLTree avltree;
		avltree.insert(4);
		avltree.insert(3);
		avltree.insert(5);
		avltree.insert(1);

		AVLTree::Node* node = avltree.find(4);
		int actual = node->getHeight();
		int expected = 2;
		REQUIRE(actual == expected);
	}

	SECTION("insert only, No rotation, right branch heavier") {
		AVLTree avltree;
		avltree.insert(3);
		avltree.insert(4);
		avltree.insert(1);
		avltree.insert(5);

		AVLTree::Node* node = avltree.find(3);
		int actual = node->getHeight();
		int expected = 2;
		REQUIRE(actual == expected);
	}
}