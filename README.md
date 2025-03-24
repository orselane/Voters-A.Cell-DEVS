# Voters-cell-DEVS
Cell devs implementation of a voters model. Repository located at:
https://github.com/orselane/Voters-cell-DEVS

# Author
- Name: Alexandre
- ID: 101189743

# Usage
0. Install cadmium_v2 on a linux system (see https://github.com/SimulationEverywhere/cadmium_v2)
1. Clone this repo
```git clone https://github.com/orselane/Voters-cell-DEVS.git```
2. Build the project in bash
```source build.sh```
3. Run one of the test scripts (see test frames). Example:
```./testScripts/evenDistributionTest.sh```
4. Grab grid_log.csv file, and put it in visualizer (at https://devssim.carleton.ca/cell-devs-viewer/)
5. Add config/voterVisualizer_config.json in visualizer
6. Optionally, rename grid_log.csv and move it to logs to store this test outcome in version controll.

# Test frames
The testScripts folder has three possible experimental frames.
Between the frames, the controlled variable is the initial proportional distribution of preferences on the board. 
Note: The inital positions are randomly distributed, according to the determined proportions.

## evenDistributionTest.sh
This test distribution spreads the preferences equally for the main preferences, 
leaving a few with the neutral preference: (R: 0.45, B:0.45, N:0.1)
```./testScripts/evenDistributionTest.sh```

## noNeutralityTest.sh
This test distribution spreads the preferences equally for the main preferences, 
but with no cells with a neutral preference: (R: 0.5, B:0.5, N:0.0)
```./testScripts/noNeutralityTest.sh```

## skewedDistributionTest.sh
This test distribution skews the preferences towards Red initially: (R: 0.7, B:0.2, N:0.1)
```./testScripts/skewedDistributionTest.sh```
