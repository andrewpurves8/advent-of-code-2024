# Advent of code 2024

This is a repository for my solutions to the Advent of Code 2024 challenges.

## Building

To build the project, you can use the following commands:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Running

To run any of the solutions:

```bash
./build/bin/day<x>_part<x>
```

e.g.

```bash
./build/bin/day1_part1
```

Note: this will use the example input in e.g. example_inputs/day1/part1.txt. To use the real input 
in e.g. inputs/day1/part1.txt, you can specify the `--real` flag. These real input have not been
committed as per the rules of the challenge.
