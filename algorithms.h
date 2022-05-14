#ifndef  IMPL_H
#define IMPL_H
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include "getopt.h"
#include <queue>
#include <limits>
#include <cmath>
#include <climits>

struct Path {
	double d = std::numeric_limits<double>::infinity();
	int prev = -1;
	bool visited = false;
};
struct Coord {
	int x = 0, y = 0;
};
//distance is a single integer

//(0,1)---10---(1,5)
//             /
// (2,5)------15

//         3

class drone {
private:
	std::string mode;
	std::vector<Coord> coords;
	int size = 0;
public:
	void getMode(int argc, char* argv[]);
	void readIn();
	double MST_C(std::vector<Path>&, int);
	void mainDrone();
	double MST(std::vector<Path>&);
	std::pair<double, std::vector<int>> TSP();
protected:
	double distanceCalculation_MODIFIED(int min_idex, int j) {
		double weight = sqrt(static_cast<double>(((static_cast<double>(coords[min_idex].x - coords[j].x)) * static_cast<double>(coords[min_idex].x - coords[j].x)))
			+ (static_cast<double>(coords[min_idex].y - coords[j].y) * static_cast<double>(coords[min_idex].y - coords[j].y)));
		return weight;//calculate weight and return
	}
	double distanceCalculation_C(int min_idex, int j) {
		double weight = sqrt(static_cast<double>(((static_cast<double>(coordsC[min_idex].x - coordsC[j].x)) * static_cast<double>(coordsC[min_idex].x - coordsC[j].x)))
			+ (static_cast<double>(coordsC[min_idex].y - coordsC[j].y) * static_cast<double>(coordsC[min_idex].y - coordsC[j].y)));
		return weight;//calculate weight and return
	}

	double distanceCalculation(int min_idex, int j) {
		if ((coords[min_idex].x < 0 && coords[min_idex].y < 0 && coords[j].x > 0 && coords[j].y > 0) ||
			(coords[min_idex].x > 0 && coords[min_idex].y > 0 && coords[j].x < 0 && coords[j].y < 0) ||
			(coords[min_idex].x >= 0 && coords[min_idex].y > 0 && coords[j].x < 0 && coords[j].y < 0) ||
			(coords[min_idex].x < 0 && coords[min_idex].y < 0 && coords[j].x >= 0 && coords[j].y > 0) ||
			(coords[min_idex].x < 0 && coords[min_idex].y < 0 && coords[j].x < 0 && coords[j].y > 0) ||
			(coords[min_idex].x < 0 && coords[min_idex].y > 0 && coords[j].x < 0 && coords[j].y < 0) ||
			(coords[min_idex].x < 0 && coords[min_idex].y < 0 && coords[j].x > 0 && coords[j].y < 0) ||
			(coords[min_idex].x > 0 && coords[min_idex].y < 0 && coords[j].x < 0 && coords[j].y < 0)
			) {
			//check coordinates!!!
			return std::numeric_limits<double>::infinity();
		}
		else {
			double weight = sqrt(static_cast<double>(((static_cast<double>(coords[min_idex].x - coords[j].x)) * static_cast<double>(coords[min_idex].x - coords[j].x)))
				+ (static_cast<double>(coords[min_idex].y - coords[j].y) * static_cast<double>(coords[min_idex].y - coords[j].y)));
			return weight;//calculate weight and return
		}
	}
public:
	//MST() LOWER BOUND
	//TSP() UPPER BOUND initializing starting path
	bool promising( size_t permLength) {
		std::vector<Path> temp;
		/*	for (size_t i = permLength; i < pathC.size(); i++) {
			coordsC.push_back(coords[pathC[i]]);
		}*/
		temp.resize(pathC.size() - permLength);
		double mst = MST_C(temp, static_cast<int>(permLength));

		double weight1 = std::numeric_limits<double>::infinity();
		double weight2 = std::numeric_limits<double>::infinity();
		for (size_t j = permLength; j < pathC.size(); j++) {//k would represent i, but j and (i = j+1)//0 and 3
			double weight = distanceCalculation_MODIFIED(pathC[j], 0);
			if (weight < weight1) {
				weight1 = weight;
			}

			weight = distanceCalculation_MODIFIED(pathC[j], pathC[permLength-1]);
			if (weight < weight2) {
				weight2 = weight;
			}
		}
		//double val = currLength + weight1 + weight2 + mst;
		//std::cout << currLength << " " << weight1 << " " << weight2 << " " << mst << std::endl;
		if (currLength + weight1 + weight2 + mst < bestDistance) {
			return true;
		}
		
		return false;

	}


	void genPerms(size_t permLength) {//part C
		if (permLength == pathC.size()) {
			currLength += distanceCalculation_MODIFIED(pathC.back(), pathC[0]);//original
			if (currLength < bestDistance) {
				bestDistance = currLength;
				bestPath = pathC;
			}
			currLength -= distanceCalculation_MODIFIED(pathC.back(), pathC[0]);//original
			return;
		} // if

		if (!promising(permLength))
			return;
		for (size_t i = permLength; i < pathC.size(); ++i) {
			std::swap(pathC[permLength], pathC[i]);
			currLength += distanceCalculation_MODIFIED(pathC[permLength], pathC[permLength - 1]);
			genPerms(permLength + 1);
			currLength -= distanceCalculation_MODIFIED(pathC[permLength], pathC[permLength - 1]);
			std::swap(pathC[permLength], pathC[i]);
		} // for
	} // genPerms()
private:
	double bestDistance = 0;
	double currLength = 0;//currLength
	std::vector<int> bestPath;
	std::vector<int> pathC;
	std::vector<Coord> coordsC;

};


#endif // ! IMPL_H
