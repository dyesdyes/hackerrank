#include <vector>
#include <sstream>

#include "consoleInputReader.h"

class WhatsNext {
public:
	void solve(){
		int caseCount = getNextIntInput();
		for(int i = 0; i < caseCount; ++i){
			std::vector<unsigned long long int> values = parseInputs();
			std::vector<unsigned long long int> out;

			int j = values.size() - 1;
			if (j % 2 == 1){ // finishing by 0s
				if (values[j-1] - 1 > 0){
					out.push_back(values[j-1] - 1);
				}
				out.push_back(values[j] + 1);
				out.push_back(1);
				if (j-2 >= 0){
					if (values[j-2] - 1 > 0){
						out.push_back(values[j-2] - 1);
					} else if (j-3 >= 0) {
						out[out.size() - 1] += values[j-3];
						j -= 1;
					}
				}
				j -= 3;
			} else {  // finishing by 1s
				if (values[j] - 1 > 0){
					out.push_back(values[j] - 1);
				}
				out.push_back(1);

				if (j-2 >= 0 && values[j-1] == 1){
					out.push_back(values[j-2] + 1);
					j -= 1;
				} else {
					out.push_back(1);
					if (j-1 >= 0 && values[j-1] - 1 > 0){
						out.push_back(values[j-1] - 1);
					}
				}
				j -= 2;
			}

			for (; j >= 0; --j){
				out.push_back(values[j]);
			}

			std::cout << out.size() << std::endl;
			printOut(out);
		}
	}

private:
	void printOut(std::vector<unsigned long long int>& out){
		std::stringstream ss;
		for(int k = out.size() - 1; k >= 0; k--){
			if (k < out.size() - 1){
				ss << " ";
			}
			ss << out[k];
		}
		std::cout << ss.str() << std::endl;
	}

	std::vector<unsigned long long int> parseInputs(){
		int size = getNextIntInput();
		std::vector<unsigned long long int> values;
		for(int i = 0; i < size; ++i){
			unsigned long long val = getNextUnsignedLongLongInput();
			values.push_back(val);
		}
		return values;
	}
};