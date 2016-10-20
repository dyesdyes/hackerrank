#include <vector>
#include <string>

class HappyLadybugs{

public:
	std::string run(std::string &board){
		const int ALPHABET_SIZE = 26;
		std::vector<int> ladybugs(ALPHABET_SIZE,0);
		bool onlyLadyBugs = true;
		bool onlySpaces = true;

		bool happyLadybugs = true;
		for(int i = 0; i < board.length(); ++i){
			if (board[i] != '_'){
				ladybugs[board[i] - 'A']++;
				onlySpaces = false;
			}
			else{
				onlyLadyBugs = false;
			}

			bool isLadyBugHappy = (i > 0 && board[i - 1] == board[i]) || (i < board.length() - 1 && board[i] == board[i + 1]);
			if (!isLadyBugHappy){
				happyLadybugs = false;
			}
		}

		if (onlySpaces || happyLadybugs){
			return "YES";
		}

		if (onlyLadyBugs){
			return "NO";
		}

		for(int i = 0; i < ladybugs.size();++i){
			if (ladybugs[i] == 1){
				return "NO";
			}
		}

		return "YES";
	}
};