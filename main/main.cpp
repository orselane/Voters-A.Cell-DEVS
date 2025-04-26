#include "nlohmann/json.hpp"
#include <cadmium/simulation/logger/csv.hpp>
#include <cadmium/simulation/root_coordinator.hpp>
#include <cadmium/modeling/celldevs/asymm/coupled.hpp>
#include <chrono>
#include <fstream>
#include <string>
#include "include/voterCell.hpp"

using namespace cadmium::celldevs;
using namespace cadmium;


std::shared_ptr<AsymmCell<voterState, double>> addAsymmCell(const std::string& cellId, const std::shared_ptr<const AsymmCellConfig<voterState, double>>& cellConfig) {
	auto cellModel = cellConfig->cellModel;
	if (cellModel == "default" || cellModel == "voter") {
		// return std::make_shared<voterCell>(cellId, cellConfig);
		return NULL;
	} else {
		throw std::bad_typeid();
	}
}


int main(int argc, char ** argv) {
	if (argc < 2) {
		std::cout << "Program used with wrong parameters. The program must be invoked as follows:";
		std::cout << argv[0] << " SCENARIO_CONFIG.json [MAX_SIMULATION_TIME (default: 500)]" << std::endl;
		return -1;
	}
	// seed rand
	srand (static_cast <unsigned> (time(0)));

	// std::string configFilePath = argv[1];
	// double simTime = (argc > 2)? std::stod(argv[2]) : 500;

	// auto model = VoterCoupled("voter_graph", configFilePath) 
	// model->buildModel();
	
	// auto rootCoordinator = RootCoordinator(model);
	// rootCoordinator.setLogger<CSVLogger>("log.csv", ";");
	// rootCoordinator.start();
	// rootCoordinator.simulate(simTime);
	// rootCoordinator.stop();
}
