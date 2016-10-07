#pragma once

#include <vector>

class AbsolutePermutation {
public:
	std::vector<int> getAbsolutePermutation(int n, int k){
		std::vector<int> permutation;
		if (k == 0){
			for(int i = 1; i <= n; ++i){
				permutation.push_back(i);
			}
			return permutation;
		}

		if (n % 2 == 1){
			return permutation;
		}

		if (n / k % 2 == 0 && n % k == 0){
			bool goUp = true;
			for(int i = 1; i <= n; ++i){
				int value = goUp ? i + k : i - k;
				permutation.push_back(value);
				if (i % k == 0){
					goUp = !goUp;
				}
			}

			return permutation;
		}

		return permutation;
	}
};