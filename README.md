# Grid Pathfinding Visualizer

![Project Logo](doc/pathfinder_logo.webp)

## Overview

The Grid Pathfinding Visualizer is a powerful and flexible tool designed to visualize various grid-based pathfinding algorithms. It is an educational and research-focused project aimed at helping users understand how different algorithms work and how they can be applied to solve pathfinding problems.

### Working example: Dijkstra and A* algorithms.
![Project Screenshot](doc/path_finder.gif)

## Features

- **Map creation tool**: Before running create the map using your cursor.
- **Support for Multiple Algorithms**: Visualize popular pathfinding algorithms such as A*, Dijkstra, BFS, and DFS.
- **Interactive Grid**: Create, edit, and manipulate grid layouts with obstacles, start, and end points.
- **Step-by-Step Visualization**: Watch algorithms in action step by step, highlighting the decision-making process.
- **Performance Metrics**: View performance metrics like time complexity, space complexity, and number of nodes expanded.
- **Customizable Settings**: Adjust algorithm parameters and grid properties to see how they affect the outcome.

## Installation

To get started with the Pathfinding Visualization Framework, follow these steps:

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/perchess/gpviz
    cd gpviz
    ```

2. **Install Dependencies**:
    ```bash
    sudo apt update
    sudo apt install 
    ```

3. **Build package**
   ```bash
   mkdir build && cd build
   cmake .. && make
   ```

4. **Run the Application**:
    ```bash
    ./Pathfinding
    ```

## Usage

1. **Launching the Framework**:
    - After installation, run the application to launch the visualization framework.

2. **Creating the Grid**:
    - Use the interactive interface to create a grid layout. Add start and end points, and place obstacles as needed (mouse left button).

3. **Selecting an Algorithm**:
    - Choose a pathfinding algorithm from the list of supported algorithms (main.cpp).

4. **Running the Visualization**:
    - Start the visualization by closing the window with map creation.

5. **Analyzing the Results**:
    - Observe the path found by the algorithm, and review performance metrics displayed on the screen (stdout).

## Algorithms Supported

- **Dijkstra**: A classic algorithm for finding the shortest paths from a single source node to all other nodes.
- **A\***: A popular and efficient pathfinding algorithm using heuristics to find the shortest path.

## Customization

The framework is designed to be easily extendable. You can add new algorithms or customize existing ones by modifying the relevant files in the `algorithms` directory.

You need to implement a child class from the PathFinder class. You could use Dijkstra or A\* as examples.

## Contributing

Contributions are welcome!

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.


## Contact

For questions, suggestions, or feedback, please open an issue or contact us at [denis.sokolov48@gmail.com].