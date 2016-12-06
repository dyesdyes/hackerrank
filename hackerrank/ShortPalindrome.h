#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>

typedef unsigned long long ull;

typedef std::vector<std::vector<int>> FrequenceByPair;
typedef std::unordered_map<char,FrequenceByPair> AllCharFrequenceByPair;

class ShortPalindrome {

public:
	ull solve(std::string val){
		AllCharFrequenceByPair frequence;
		init(frequence);

		ull out = 0;
		for (int i = 0; i < val.length(); ++i){
			char currentChar = val[i];

			for (char ch = 'a'; ch <= 'z'; ++ch){
				if (ch != currentChar && frequence[ch].size() > 0){
					++frequence[ch][0][currentChar-'a'];
				}
			}

			// cash in pair using current char
			for (int charIndex = 0; charIndex < frequence[currentChar].size(); ++charIndex){
				for (char ch = 'a'; ch <= 'z'; ++ch){
					if (ch != currentChar){
						ull all = frequence[currentChar][0][ch-'a'];
						int occurence = charIndex == 0 ? all : all - frequence[currentChar][charIndex][ch-'a'];
						if (occurence >= 2){
							out += NChooseK(occurence,2);
						}
					}
				}
			}

			// take the values from the first occurence, they will be substracted when cashing
			if (frequence[currentChar].size() > 0){
				std::vector<int> vec = frequence[currentChar][0];
				frequence[currentChar].push_back(vec);
			} else {
				std::vector<int> vec(26,0);
				frequence[currentChar].push_back(vec);
			}
		}

		AllCharFrequenceByPair::iterator ite = frequence.begin();
		while (ite != frequence.end()){
			if (ite->second.size() >= 4){
				out += NChooseK(ite->second.size(),4);
			}
			ite++;
		}

		return out % 1000000007;
	}


private:
	void init(AllCharFrequenceByPair& frequence){
		for (int ch = 'a'; ch <= 'z'; ++ch){
			FrequenceByPair freq;
			frequence.insert(std::pair<char,FrequenceByPair>(ch,freq));
		}
	}

	ull NChooseK(int n,int k){
		if (n < k)
			return 0;

		int index = k == 2 ? 0 : 1;

		if (cachedNChooseK.count(n) > 0){
			if (cachedNChooseK[n][index] > 0){
				return cachedNChooseK[n][index];
			} else {
				ull val = NChooseKImpl(n,k);
				cachedNChooseK[n][index] = val;
				return val;
			}
		} else {
			std::vector<ull> vec(2,0);

			ull val = NChooseKImpl(n,k);
			vec[index] = val;
			cachedNChooseK.insert(std::pair<int,std::vector<ull>>(n,vec));
			return val;
		}
	}

	ull NChooseKImpl(int n,int k){
		if (k == 0) 
			return 1;
		return (n * NChooseKImpl(n - 1, k - 1)) / k;
	}

	// k == 2 or k == 4 only
	std::unordered_map<int,std::vector<ull>> cachedNChooseK;
};
