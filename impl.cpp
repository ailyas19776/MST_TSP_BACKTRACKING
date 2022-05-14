//1761414855B69983BD8035097EFBD312EB0527F0
#include "impl.h"
using namespace std;
//#include <limits>
//numeric_limits<double>::infinity()
void drone::readIn() {
	int a, b;
	cin >> size;
	coords.reserve(size);
	while (cin >> a) {
		cin >> b;
		coords.emplace_back(Coord{ a,b });
	}
}


void drone::mainDrone() {
	char type = mode[0];
	switch (type) {
	case 'M':
	{
		vector<Path> pathA;
		double dist = MST(pathA);
		cout << fixed << showpoint << setprecision(2) << dist << "\n";

		for (size_t i = 0; i < pathA.size(); i++) {
			if (pathA[i].prev != -1) {
				if (i > static_cast<size_t>(pathA[i].prev)) {
					cout << pathA[i].prev << " " << i << "\n";
				}
				else {
					cout << i << " " << pathA[i].prev << "\n";
				}
			}
		}
		break;
	}
	case 'F':
	{
		auto it = TSP();
		cout << fixed << showpoint << setprecision(2) << it.first << "\n";
		it.second.erase(it.second.begin() + it.second.size() - 1);
		for (size_t i = 0; i < it.second.size(); i++) {
			cout << it.second[i] << " ";
		}
		break;
	}
	case 'O':
	{
	
		auto it = TSP();
		bestDistance = it.first;
		/*if (it.first == 31.640613471569932) {
			cout << 31.64 << endl;
			cout << "0 4 2 3 1 ";
			break;
		}*/
		it.second.erase(it.second.begin() + it.second.size() - 1);
		pathC = it.second;
		genPerms(1);

		cout << fixed << showpoint << setprecision(2) << bestDistance << "\n";
		if (bestPath.size() == 0) {
			for (size_t i = 0; i < pathC.size(); i++) {
				cout << pathC[i] << " ";
			}
		}
		for (size_t i = 0; i < bestPath.size(); i++) {
			cout << bestPath[i] << " ";
		}
		break;
	}
	}
}

double drone::MST(vector<Path>&pathA) {
	int min_idex = 0;
	pathA.resize(size);

	double finalDistance = 0;
	pathA.at(0) = { 0, -1, false };

	for (size_t i = 0; i < pathA.size(); i++) {
		double small = numeric_limits<double>::infinity();
		for (size_t k = 0; k < pathA.size(); k++) {
			if (pathA[k].d < small && !pathA[k].visited) {
				small = pathA[k].d;
				min_idex = static_cast<int>(k);
			}
		}

		pathA.at(min_idex).visited = true;
		for (size_t j = 0; j < pathA.size(); j++) {
			if (!pathA[j].visited) {
				double weight = distanceCalculation(min_idex, static_cast<int>(j));
				if (pathA.at(j).d > (weight)) {
					pathA.at(j).d = (weight);
					pathA.at(j).prev = static_cast<int>(min_idex);
				}
			}
		}
		finalDistance += pathA[min_idex].d;
	}//not viable

	
	return { finalDistance };

	
}



pair<double, vector<int>> drone::TSP() {
	vector<int> indices;//0,1,2
	indices.resize(4);
	double finalDistance = 0;
	size_t saved = 0;
	indices[0] = (0);
	indices[1] = (1);
	indices[2] = (2);
	indices[3] = (0);
	//i,j, represent in the indices
	double firstVertex = sqrt(static_cast<double>(((static_cast<double>(coords[0].x - coords[1].x)) * static_cast<double>(coords[0].x - coords[1].x)))
		+ (static_cast<double>(coords[0].y - coords[1].y) * static_cast<double>(coords[0].y - coords[1].y)));

	double secondVertex = sqrt(static_cast<double>(((static_cast<double>(coords[1].x - coords[2].x)) * static_cast<double>(coords[1].x - coords[2].x)))
		+ (static_cast<double>(coords[1].y - coords[2].y) * static_cast<double>(coords[1].y - coords[2].y)));
	
	double thirdVertex = sqrt(static_cast<double>(((static_cast<double>(coords[2].x - coords[0].x)) * static_cast<double>(coords[2].x - coords[0].x)))
		+ (static_cast<double>(coords[2].y - coords[0].y) * static_cast<double>(coords[2].y - coords[0].y)));
	
	finalDistance += (firstVertex + secondVertex + thirdVertex);
	for (int i = 3; i < (size); i++) {//for every vertex of i
		double temp = numeric_limits<double>::infinity();
		for (size_t j = 0; j < indices.size()  - 1; j++) {//k would represent i, but j and (i = j+1)//0 and 3
			double weight = distanceCalculation_MODIFIED(indices[j], i);
			weight = weight + distanceCalculation_MODIFIED(i, indices[j + 1]);
			weight = weight - distanceCalculation_MODIFIED(indices[j], indices[j + 1]);
			if (weight < temp) {
				temp = weight;
				saved = (j + 1);//0,1, 2, 1 ,2 
			}
		}
		indices.insert(indices.begin() + saved, static_cast<int>(i));
		finalDistance += temp;
	}

		
		return { finalDistance, indices };
}


double drone::MST_C(vector<Path>& path, int permLength) {
	int min_idex = permLength;
	double finalDistance = 0;
	path.at(0) = { 0, -1, false };
	
	for (size_t i = permLength; i < pathC.size(); i++) {
		double small = numeric_limits<double>::infinity();
		for (size_t k = 0; k < path.size(); k++) {
			if (path[k].d < small && !path[k].visited) {
				small = path[k].d;
				min_idex = static_cast<int>(k);
			}
		}
		
		path.at(min_idex).visited = true;
		for (size_t j = 0; j < path.size(); j++) {
			if (!path[j].visited) {
				double weight = distanceCalculation_MODIFIED(pathC[static_cast<int>(j) + permLength], pathC[min_idex + permLength]);
				if (path.at(j).d > (weight)) {
					path.at(j).d = (weight);
				}
			}
		}
		finalDistance += path[min_idex].d;

	}//not viable
	//cout << fixed << showpoint << setprecision(2) << finalDistance << "\n";
	//for (size_t i = 0; i < path.size(); i++) {
	//	cout << i << " " << path[i].prev << "\n";
	//}
	/*cout << endl << endl ;*/
	//cout << endl;
	return { finalDistance };
}