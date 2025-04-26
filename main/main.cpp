#include "nlohmann/json.hpp"
#include <cadmium/simulation/logger/csv.hpp>
#include <cadmium/simulation/root_coordinator.hpp>
#include <chrono>
#include <fstream>
#include <string>
#include "include/voterCouppling.hpp"

using namespace cadmium::celldevs;
using namespace cadmium;

int main(int argc, char ** argv) {
	if (argc < 2) {
		std::cout << "Program used with wrong parameters. The program must be invoked as follows:";
		std::cout << argv[0] << " SCENARIO_CONFIG.json [MAX_SIMULATION_TIME (default: 500)]" << std::endl;
		return -1;
	}
	// seed rand
	srand (static_cast <unsigned> (time(0)));

	std::string configFilePath = argv[1];
	double simTime = (argc > 2)? std::stod(argv[2]) : 500;

	auto model = VoterCoupled("voter_graph", configFilePath) 
	model->buildModel();
	
	auto rootCoordinator = RootCoordinator(model);
	rootCoordinator.setLogger<CSVLogger>("log.csv", ";");
	rootCoordinator.start();
	rootCoordinator.simulate(simTime);
	rootCoordinator.stop();
}
