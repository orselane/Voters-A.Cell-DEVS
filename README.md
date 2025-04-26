# Voters-A.Cell-DEVS
Asymmetric Cell devs implementation of a voters model. Repository located at:
https://github.com/orselane/Voters-A.Cell-DEVS

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
4. Visually inspect log.csv (Could not manage to make a visualizer work for asymmetric cell devs)

# Test frames
The testScripts folder has three possible experimental frames.
Between the frames, the controlled variable is the weight between cr1, cb1 (red cell 1, blue cell 1).
There are three cells initially blue (cb1, cb2, cb3) and three intially red (cr1, cr2, cr3).
All cells are linked to their same colored neighbors at a standard weight of 3, 
plus the link between cr1 and cb1 which varies depeding on the test case.

## evenTest.sh
This test defines an equal weight between all links, including the one between cr1, cb1 (weight of 3 both ways).
```./testScripts/evenTest.sh```

## skewedTest.sh
This test defines a skewed weight between cr1, and cb1.
There is a weight of 1 influencing cb1 from cr1.
There is a weight of 6 influencing cr1 from cb1.
```./testScripts/skewedTest.sh```

## unilateralTest.sh
This test defines a unilateral weight between cr1, and cb1.
There is a weight of 1 influencing cb1 from cr1.
There is no influence on cr1 from cb1.
```./testScripts/unilateralTest.sh```
