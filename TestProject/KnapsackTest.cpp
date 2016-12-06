#include "stdafx.h"

#include "catch.hpp"

#include "Knapsack.h"

TEST_CASE("Knapsack Simple insert, no rotation","[insert][traversePostOrder]") {
	Knapsack k;
	std::string input = 
		"3 50 60 10 100 20 120 30";

	int actual = k.solve(input);
	int expected = 220;

	REQUIRE(actual == expected);
}