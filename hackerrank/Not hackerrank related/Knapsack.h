
#include <vector>
#include <string>
#include <sstream>
#include <array>

struct KnapsackItem {
	KnapsackItem(int v,int w) : value(v), weight(w) {}
	int value;
	int weight;
};


class Knapsack {

public:
	int solve(const std::string& input){
		std::vector<KnapsackItem> items;
		const int W = parse(input,items);
		return knapsack(items.size(),W,items);
	}

private:

	int knapsack(int N,int W,std::vector<KnapsackItem>& items){
		std::vector<std::vector<int>> values(N+1,std::vector<int>(W+1,0));

		for (int i = 1; i <= N; ++i){
			for (int j = 1; j <= W; ++j){
				if (items[i-1].weight > j){
					values[i][j] = values[i-1][j];
				} else {
					values[i][j] = std::max(values[i-1][j],values[i-1][j-items[i-1].weight] + items[i-1].value);
				}
			}
		}

		return values[N][W];
	}

	/*
		The first line consists of N the number of items.
		The second line consists of W, the maximum capacity of the knapsack.
		Then in the next N lines, you have 2 integers, first being the value, second being the weight
	*/
	int parse(const std::string& input, std::vector<KnapsackItem>& items){
		std::istringstream iss(input);
		int N, W;
		iss >> N >> W;

		for(int i = 0; i < N; ++i){
			int weight, value;
			iss >> value >> weight;

			items.push_back(KnapsackItem(value,weight));
		}
		return W;
	}
};