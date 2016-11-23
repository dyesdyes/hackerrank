#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <functional>

#define FIRST_STR "First"
#define SECOND_STR "Second"
#define FIRST 0
#define SECOND 1

typedef unsigned long long ull;
typedef std::pair<ull,ull> StonePile; // value - number of piles
typedef std::pair<ull,std::unordered_map<ull,ull>*> TurnWithStonePile;

/*
class StoneDivision {
public:
	void solve(){
		ull n;
		std::cin >> n;
		std::vector<ull> values;
		parseInputs(values);

		for (int i = 0; i < values.size();++i){
			if (values[i] == n){
				std::cout << FIRST_STR << std::endl;
				return;
			}
		}
		std::sort(values.begin(),values.end(),std::greater<ull>());

		std::unordered_map<ull,ull> stonePiles;
		stonePiles.insert(StonePile(n,1));

		int winner = rec(0,stonePiles,values);
		std::string winnerStr = winner == 0 ? FIRST_STR : SECOND_STR;
		std::cout << winnerStr << std::endl;
	}

private:

	int rec(ull currentTurn,std::unordered_map<ull,ull>& stonePiles,const std::vector<ull>& values){
		bool currentTurnLoses = true;
		std::unordered_map<ull,ull>::iterator ite = stonePiles.begin();
		for (; ite != stonePiles.end();++ite){
			if (ite->second != 0){
				for (int j = 0; j < values.size(); ++j){
					if (ite->first % values[j] == 0){
						ull pileSize = ite->first;
						currentTurnLoses = false;
						std::unordered_map<ull,ull> stonePilesTemp(stonePiles.begin(),stonePiles.end());

						ull countTemp = ite->second;
						if (atLeastOneOddAndOneEvenDivider(pileSize,values)){
							countTemp = ite->second > 1 ? ite->second - 1 : 1;
						}

						ull newVal = pileSize/values[j];
						ull newCount = values[j]*countTemp;

						if (stonePilesTemp.count(newVal) == 0){
							stonePilesTemp.insert(StonePile(newVal,newCount));
						} else{
							stonePilesTemp[newVal] += newCount;
						}
						stonePilesTemp[pileSize] -= countTemp;

						int winner = rec(currentTurn+countTemp,stonePilesTemp,values);
						if (winner == FIRST){
							return FIRST;
						}
					}
				}
			}
		}
		if (currentTurnLoses){
			return currentTurn % 2 == 0 ? SECOND : FIRST;
		}
		return SECOND;
	}

	bool atLeastOneOddAndOneEvenDivider(ull stones,const std::vector<ull>& values){
		bool atLeastOneOdd = false;
		bool atLeastOneEven = false;

		for (int i = 0; i < values.size(); ++i){
			if (stones % values[i] == 0){
				if (values[i] % 2 == 0)
					atLeastOneEven = true;
				else
					atLeastOneOdd = true;
			}
		}
		return atLeastOneOdd && atLeastOneEven;
	}

	void parseInputs(std::vector<unsigned long long>& values){
		int m;
		std::cin >> m;
		for (int i = 0; i < m; ++i){
			unsigned long long val;
			std::cin >> val;
			values.push_back(val);
		}
	}
};
*/


int main()
{
	const int N = 10;
	int T[N] = {5,6,8,9,5,6,7,4,5};
	std::sort(T,T+N,std::greater<int>());

    return 0;
}