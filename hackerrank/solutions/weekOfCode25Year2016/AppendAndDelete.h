#include <string>
#include <algorithm>
#include <iostream>


class AppendAndDelete {
public:
	void solve(){
		std::string initialString;
		std::cin >> initialString;
		std::string desiredString;
		std::cin >> desiredString;
		int operationCount;
		std::cin >> operationCount;

		if (initialString.length() + desiredString.length() <= operationCount){
			std::cout << "Yes" << std::endl;
			return;
		}

		int firstDifferenceIndex = -1;
		int size = std::min(initialString.length(),desiredString.length());
		for(int i = 0; i < size;++i){
			if (initialString[i] != desiredString[i]){
				firstDifferenceIndex = i;
				break;
			}
		}
		if (firstDifferenceIndex == -1){
			firstDifferenceIndex = size;
		}
		int neededDeleteOp = initialString.length() - firstDifferenceIndex;
		int neededAppendOp = desiredString.length() - firstDifferenceIndex;
		int totalOp = neededDeleteOp + neededAppendOp;

		if (operationCount > totalOp && (operationCount - totalOp) % 2 == 0){
			std::cout << "Yes" << std::endl;
			return;
		}

		std::string ans = (totalOp == operationCount) ? "Yes" : "No";
		std::cout << ans << std::endl;
	}
};