#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "consoleInputReader.h"

typedef unsigned long long ull;
typedef std::pair<long,long> TrackLimits;

class GridlandMetro {

public:
	void solve(){
		long n = getNextLongInput();
		long m = getNextLongInput();
		int k = getNextIntInput();

		std::unordered_map<long,std::vector<TrackLimits>> boundaries;

		for (int i = 0; i < k; ++i){
			long row = getNextLongInput() - 1;
			long c1 = getNextLongInput() - 1;
			long c2 = getNextLongInput() - 1;

			if (boundaries.count(row) > 0){
				insertNewTrack(boundaries[row],c1,c2);
				mergeOverLappedTracks(boundaries[row]);
			} else {
				std::vector<TrackLimits> limits;
				limits.push_back(TrackLimits(c1,c2));
				boundaries.insert(std::pair<long,std::vector<TrackLimits>>(row,limits));
			}
		}
		ull out = n * m;
		std::unordered_map<long,std::vector<TrackLimits>>::iterator ite = boundaries.begin();

		while(ite != boundaries.end()){
			for (int i = 0; i < ite->second.size(); ++i){
				out -= ite->second[i].second - ite->second[i].first + 1;
			}
			
			ite++;
		}

		std::cout << out << std::endl;
	}

private:
	void insertNewTrack(std::vector<TrackLimits>& limits,long c1, long c2){
		for (int i = 0; i < limits.size(); ++i){
			if (limits[i].first <= c1 && limits[i].second >= c2){
				return;
			}
			if (limits[i].first > c1 && limits[i].second < c2){
				limits[i].first = c1;
				limits[i].second = c2;
				return;
			}
			if (c1 <= limits[i].second + 1 && c1 >= limits[i].first){
				limits[i].second = c2;
				return;
			}
			if (c2 + 1 >= limits[i].first && c2 <= limits[i].second){
				limits[i].first = c1;
				return;
			}
		}
		limits.push_back(TrackLimits(c1,c2));
	}

	void mergeOverLappedTracks(std::vector<TrackLimits>& limits){
		std::sort(limits.begin(),limits.end());
		int tempSize;
		do {
			tempSize = limits.size();
			for (int i = limits.size() - 1; i >= 1; --i){
				if (limits[i - 1].second + 1 >= limits[i].first){ // then overlap
					limits[i - 1].second = std::max(limits[i - 1].second,limits[i].second);
					limits.erase(limits.begin() + i);
				}
			}
		} while (tempSize != limits.size());
	}

};