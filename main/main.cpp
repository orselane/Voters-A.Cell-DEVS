#include "nlohmann/json.hpp"
#include <cadmium/modeling/celldevs/grid/coupled.hpp>
#include <cadmium/simulation/logger/csv.hpp>
#include <cadmium/simulation/root_coordinator.hpp>
#include <chrono>
#include <fstream>
#include <string>
#include "include/voterCell.hpp"

using namespace cadmium::celldevs;
using namespace cadmium;

std::shared_ptr<GridCell<voterState, double>> addGridCell(const coordinates & cellId, const std::shared_ptr<const GridCellConfig<voterState, double>>& cellConfig) {
	auto cellModel = cellConfig->cellModel;

	if (cellModel == "voter") {
		return std::make_shared<voter>(cellId, cellConfig);
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

	std::string configFilePath = argv[1];
	double simTime = (argc > 2)? std::stod(argv[2]) : 500;

	auto model = std::make_shared<GridCellDEVSCoupled<voterState, double>>("voter", addGridCell, configFilePath);
	model->buildModel();
	
	auto rootCoordinator = RootCoordinator(model);
	rootCoordinator.setLogger<CSVLogger>("grid_log.csv", ";");
	
	rootCoordinator.start();
	rootCoordinator.simulate(simTime);
	rootCoordinator.stop();
}
