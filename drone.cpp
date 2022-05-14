#include "impl.h"
using namespace std;


int main(int argc, char *argv[]) {
	ios_base::sync_with_stdio(false);
	drone drones;
	drones.getMode(argc, argv);
	drones.readIn();
	drones.mainDrone();
}
