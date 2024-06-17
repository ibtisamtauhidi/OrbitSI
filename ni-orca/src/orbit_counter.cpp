#include "../include/graph.h"
#include "../include/orbit.h"
#include <iostream>
#include <sstream>

int parseInt(char* str) {
	std::istringstream ss(str);
	int vertex_id;
	if (!(ss >> vertex_id)) {
	  std::cerr << "Invalid number: " << str << '\n';
	} else if (!ss.eof()) {
	  std::cerr << "Trailing characters after number: " << str << '\n';
	}
	return vertex_id;
}

int main(int argc, char** argv) {
    Graph graph = readGraph(argv[1]);
    preProcess(graph);
    
    #ifdef VERBOSE
      printGraph(graph);
    #endif

    if(argc == 2) {
      int num_vertices = graph.vertex_labels.size();
      std::vector<int *> orbit_count(num_vertices);
      for (int i = 0; i < num_vertices; i++) {
        orbit_count[i] = countOrbits(graph, i);
      }
      printOrbitsVector(orbit_count);
      //delete[] orbit_count;

    } else if(argc == 3) {
      int* orbit_count = countOrbits(graph, parseInt(argv[2]));
      printOrbits(orbit_count);
      delete[] orbit_count;
    } else {
      std::cout << "Invalid number of arguments." << std::endl;
    }
    return 0;
}
