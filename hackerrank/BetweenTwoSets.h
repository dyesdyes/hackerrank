#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class BetweenTwoSets {
public:
	void solve(){
		int n;
		int m;
		cin >> n >> m;
		vector<int> a(n);
		for(int a_i = 0;a_i < n;a_i++){
		   cin >> a[a_i];
		}
		vector<int> b(m);
		for(int b_i = 0;b_i < m;b_i++){
		   cin >> b[b_i];
		}

		std::sort(a.begin(),a.end());
		std::sort(b.begin(),b.end());

		if (a[a.size()-1] > b[0]){
			std::cout << 0 << std::endl;
			return;
		}

		int out = 0;
		for(int i = a[a.size()-1];i <= b[0];++i){
			
			bool shouldContinue = false;
			for(int j = 0;j < a.size();++j){
				if (i % a[j] != 0){
					shouldContinue = true;
					break;
				}
			}
			if (shouldContinue)
				continue;

			for(int k = 0;k < b.size();++k){
				if (b[k] % i != 0){
					shouldContinue = true;
					break;
				}
			}

			if (shouldContinue)
				continue;

			++out;
		}

		std::cout << out << std::endl;
	}
};
