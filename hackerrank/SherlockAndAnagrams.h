#include <string>
#include <vector>

#include "consoleInputReader.h"

class SherlockAndAnagrams {
public:
	void solve(){
		int testCases = getNextIntInput();
		std::vector<std::string> values;
		for (int i = 0; i < testCases; ++i){
			std::string val;
			std::cin >> val;
			values.push_back(val);
		}
		for(int i = 0; i < values.size(); ++i){
			solveCase(values[i]);
		}
	}

private:
	void solveCase(const std::string& value){
		int count = 0;
		for(int strLength = 1; strLength < value.length(); ++strLength){
			for(int i = 0; i < value.length() - strLength; ++i){
				for(int j = i+1; j <= value.length() - strLength; ++j){
					if (isAnagram(value.substr(i,strLength),value.substr(j,strLength))){
						count++;
					}
				}
			}
		}
		std::cout << count << std::endl;
	}

	bool isAnagram(const std::string& a,const std::string& b){
		if (a.length() != b.length())
			return false;

		std::vector<int> aFreq(26,0),bFreq(26,0);
		for(int i = 0; i < a.length();++i){
			aFreq[a[i] - 'a']++;
			bFreq[b[i] - 'a']++;
		}
		for(int i = 0; i < aFreq.size();++i){
			if (aFreq[i] != bFreq[i])
				return false;
		}
		return true;
	}
};
