#include "../include/graph.h"
#include "../include/orbit.h"
#include <iostream>
#include <algorithm>

#ifdef VERBOSE
bool compareOrbits(const Orbit& a, const Orbit& b) {
    return a.type < b.type;
}
#endif

int* countOrbits(Graph graph, int vertex) {
  #ifdef VERBOSE
	  std::cout << "Counting orbits for vertex: " << vertex << std::endl;
  #endif
	int* orbit_count = new int[15]{ 0 };
	
	#ifdef VERBOSE
	std::vector<Orbit> orbits;
	#endif
	
	// Orbit 0 - Degree
	orbit_count[0] = graph.adjacency_list[vertex].size();

	for (int i = 0; i < graph.adjacency_list[vertex].size(); i++) {
		int neighbor = graph.adjacency_list[vertex][i];
		for (int j = 0; j < graph.adjacency_list[neighbor].size(); j++) {
			int second_neighbor = graph.adjacency_list[neighbor][j];
			if (second_neighbor != vertex) {
				orbit_count[1]++;
				// Orbit 1 - Leaf of 3 Line
				#ifdef VERBOSE
				Orbit orbit;
				orbit.type = 1;
				orbit.vertices = new int[3];
				orbit.vertices[0] = vertex;
				orbit.vertices[1] = neighbor;
				orbit.vertices[2] = second_neighbor;
				orbits.push_back(orbit);
				#endif
				
				for (int k = 0; k < graph.adjacency_list[second_neighbor].size(); k++) {
					int third_neighbor = graph.adjacency_list[second_neighbor][k];
					if(third_neighbor != vertex && third_neighbor != neighbor && third_neighbor != second_neighbor) {
						orbit_count[4]++;
						// Orbit 4
						#ifdef VERBOSE
						Orbit orbit;
						orbit.type = 4;
						orbit.vertices = new int[4];
						orbit.vertices[0] = vertex;
						orbit.vertices[1] = neighbor;
						orbit.vertices[2] = second_neighbor;
						orbit.vertices[3] = third_neighbor;
						orbits.push_back(orbit);
						#endif
					}
				}
				
				for (int k = 0; k < graph.adjacency_list[vertex].size(); k++) {
					int prev_neighbor = graph.adjacency_list[vertex][k];
					if(prev_neighbor != neighbor && prev_neighbor != second_neighbor) {
						orbit_count[5]++;
						// Orbit 5
						#ifdef VERBOSE
						Orbit orbit;
						orbit.type = 5;
						orbit.vertices = new int[4];
						orbit.vertices[0] = prev_neighbor;
						orbit.vertices[1] = vertex;
						orbit.vertices[2] = neighbor;
						orbit.vertices[3] = second_neighbor;
						orbits.push_back(orbit);
						#endif
					}
				}
				
				for (int k = j+1; k < graph.adjacency_list[neighbor].size(); k++) {
					int other_neighbor = graph.adjacency_list[neighbor][k];
					if(other_neighbor != vertex && other_neighbor != second_neighbor) {
						orbit_count[6]++;
						// Orbit 6
						#ifdef VERBOSE
						Orbit orbit;
						orbit.type = 6;
						orbit.vertices = new int[4];
						orbit.vertices[0] = vertex;
						orbit.vertices[1] = neighbor;
						orbit.vertices[2] = other_neighbor;
						orbit.vertices[3] = second_neighbor;
						orbits.push_back(orbit);
						#endif
						
						if(std::binary_search(graph.adjacency_list[second_neighbor].begin(),
										graph.adjacency_list[second_neighbor].end(), other_neighbor)) {
							
							orbit_count[9]++;
							// Orbit 9
							#ifdef VERBOSE
							Orbit orbit;
							orbit.type = 9;
							orbit.vertices = new int[4];
							orbit.vertices[0] = vertex;
							orbit.vertices[1] = neighbor;
							orbit.vertices[2] = other_neighbor;
							orbit.vertices[3] = second_neighbor;
							orbits.push_back(orbit);
							#endif
						}
						
					}
				}				
			}
		}
		for (int j = i+1; j < graph.adjacency_list[vertex].size(); j++) {
			int other_neighbor = graph.adjacency_list[vertex][j];
			orbit_count[2]++;
			// Orbit 2  - Middle vertex of 3 Line
			#ifdef VERBOSE
			Orbit orbit;
			orbit.type = 2;
			orbit.vertices = new int[3];
			orbit.vertices[0] = neighbor;
			orbit.vertices[1] = vertex;
			orbit.vertices[2] = other_neighbor;
			orbits.push_back(orbit);
			#endif

			for (int k = 0; k < graph.adjacency_list[vertex].size(); k++) {
				int prev_neighbor = graph.adjacency_list[vertex][k];
				if(prev_neighbor < neighbor && prev_neighbor < other_neighbor) {
					orbit_count[7]++;
					// Orbit 7 - Middle vertex of 3 Star
					#ifdef VERBOSE
					Orbit orbit;
					orbit.type = 7;
					orbit.vertices = new int[4];
					orbit.vertices[0] = prev_neighbor;
					orbit.vertices[1] = vertex;
					orbit.vertices[2] = neighbor;
					orbit.vertices[3] = other_neighbor;
					orbits.push_back(orbit);
					#endif						
				}
				/*if(prev_neighbor < other_neighbor) {				
					if(std::binary_search(graph.adjacency_list[prev_neighbor].begin(),
						graph.adjacency_list[prev_neighbor].end(), neighbor) && 
						std::binary_search(graph.adjacency_list[other_neighbor].begin(),
						graph.adjacency_list[other_neighbor].end(), neighbor)) {
							orbit_count[13]++;
							// Orbit 13
							#ifdef VERBOSE
							Orbit orbit;
							orbit.type = 13;
							orbit.vertices = new int[4];
							orbit.vertices[0] = vertex;
							orbit.vertices[1] = prev_neighbor;
							orbit.vertices[2] = neighbor;
							orbit.vertices[3] = other_neighbor;
							orbits.push_back(orbit);
							#endif
					}
				}*/
			}
			
			std::vector<int> v_intersection;
			std::set_intersection(graph.adjacency_list[neighbor].begin(), graph.adjacency_list[neighbor].end(),
				graph.adjacency_list[other_neighbor].begin(), graph.adjacency_list[other_neighbor].end(),
				std::back_inserter(v_intersection));

			for (int far_neighbor : v_intersection) {
				if(far_neighbor != vertex && far_neighbor != neighbor && far_neighbor != other_neighbor) {
					orbit_count[8]++;
					// Orbit 8
					#ifdef VERBOSE
					Orbit orbit;
					orbit.type = 8;
					orbit.vertices = new int[4];
					orbit.vertices[0] = vertex;
					orbit.vertices[1] = neighbor;
					orbit.vertices[2] = far_neighbor;
					orbit.vertices[3] = other_neighbor;
					orbits.push_back(orbit);
					#endif
					
					
					if(std::binary_search(graph.adjacency_list[vertex].begin(),
						graph.adjacency_list[vertex].end(), far_neighbor) && neighbor < other_neighbor) {
							orbit_count[13]++;
							// Orbit 13
							#ifdef VERBOSE
							Orbit orbit;
							orbit.type = 13;
							orbit.vertices = new int[4];
							orbit.vertices[0] = vertex;
							orbit.vertices[1] = other_neighbor;
							orbit.vertices[2] = neighbor;
							orbit.vertices[3] = far_neighbor;
							orbits.push_back(orbit);
							#endif
					}
				}
			}
			
			
			if(std::binary_search(graph.adjacency_list[neighbor].begin(), graph.adjacency_list[neighbor].end(), other_neighbor)) {
				orbit_count[3]++;
				// Orbit 3 - Triangle
				#ifdef VERBOSE
				Orbit orbit;
				orbit.type = 3;
				orbit.vertices = new int[3];
				orbit.vertices[0] = neighbor;
				orbit.vertices[1] = vertex;
				orbit.vertices[2] = other_neighbor;
				orbits.push_back(orbit);
				#endif
				
				for (int k = 0; k < graph.adjacency_list[vertex].size(); k++) {
					int prev_neighbor = graph.adjacency_list[vertex][k];
					if(prev_neighbor != neighbor && prev_neighbor != other_neighbor) {
						orbit_count[11]++;
						// Orbit 11
						#ifdef VERBOSE
						Orbit orbit;
						orbit.type = 11;
						orbit.vertices = new int[4];
						orbit.vertices[0] = prev_neighbor;
						orbit.vertices[1] = vertex;
						orbit.vertices[2] = neighbor;
						orbit.vertices[3] = other_neighbor;
						orbits.push_back(orbit);
						#endif
					}
				}

				for (int k = 0; k < graph.adjacency_list[neighbor].size(); k++) {
					int far_neighbor = graph.adjacency_list[neighbor][k];
					if(far_neighbor != vertex && far_neighbor != other_neighbor) {
						orbit_count[10]++;
						// Orbit 10 - Side 1
						#ifdef VERBOSE
						Orbit orbit;
						orbit.type = 10;
						orbit.vertices = new int[4];
						orbit.vertices[0] = vertex;
						orbit.vertices[1] = other_neighbor;
						orbit.vertices[2] = neighbor;
						orbit.vertices[3] = far_neighbor;
						orbits.push_back(orbit);
						#endif
					}
				}
				for (int k = 0; k < graph.adjacency_list[other_neighbor].size(); k++) {
					int far_neighbor = graph.adjacency_list[other_neighbor][k];
					if(far_neighbor != vertex && far_neighbor != neighbor) {
						orbit_count[10]++;
						// Orbit 10 - Side 2
						#ifdef VERBOSE
						Orbit orbit;
						orbit.type = 10;
						orbit.vertices = new int[4];
						orbit.vertices[0] = vertex;
						orbit.vertices[1] = neighbor;
						orbit.vertices[2] = other_neighbor;
						orbit.vertices[3] = far_neighbor;
						orbits.push_back(orbit);
						#endif
					}
				}

				std::vector<int> v_intersection;
				std::set_intersection(graph.adjacency_list[neighbor].begin(), graph.adjacency_list[neighbor].end(),
					graph.adjacency_list[other_neighbor].begin(), graph.adjacency_list[other_neighbor].end(),
					std::back_inserter(v_intersection));

				for (int far_neighbor : v_intersection) {
					if(far_neighbor != vertex && far_neighbor != neighbor && far_neighbor != other_neighbor) {
						orbit_count[12]++;
						// Orbit 12
						#ifdef VERBOSE
						Orbit orbit;
						orbit.type = 12;
						orbit.vertices = new int[4];
						orbit.vertices[0] = vertex;
						orbit.vertices[1] = neighbor;
						orbit.vertices[2] = other_neighbor;
						orbit.vertices[3] = far_neighbor;
						orbits.push_back(orbit);
						#endif
						
						if(std::binary_search(graph.adjacency_list[vertex].begin(),
							graph.adjacency_list[vertex].end(), far_neighbor) &&
							neighbor < other_neighbor && other_neighbor < far_neighbor) {
								orbit_count[14]++;
								// Orbit 14 - K4
								#ifdef VERBOSE
								Orbit orbit;
								orbit.type = 14;
								orbit.vertices = new int[4];
								orbit.vertices[0] = vertex;
								orbit.vertices[1] = neighbor;
								orbit.vertices[2] = other_neighbor;
								orbit.vertices[3] = far_neighbor;
								orbits.push_back(orbit);
								#endif
						}
					}
				}
			}
		}
	}

	#ifdef VERBOSE
	std::cout << "---------------------------------------------" << std::endl;
	int vertices_count[15] = {2, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
	std::sort(orbits.begin(), orbits.end(), compareOrbits);
	for (int i = 0; i < orbits.size(); i++) {
		if(orbits[i].type == 13) {
			std::cout << orbits[i].type << " : ";
			for (int j = 0; j < vertices_count[orbits[i].type]; j++) {
				std::cout << orbits[i].vertices[j] << " ";
			}
			std::cout << std::endl;
		}
	}
	std::cout << "---------------------------------------------" << std::endl;
	#endif
	
	return orbit_count;
}

void printOrbits(int* orbit_count) {
    for (int i = 0; i < 15; i++) {
		std::cout << orbit_count[i] << " ";
	}
	std::cout << std::endl;
}

void printOrbitsVector(std::vector<int *> orbit_count) {
  for(int i = 0; i < orbit_count.size(); i++) {
    for (int j = 0; j < 15; j++) {
		  std::cout << orbit_count[i][j];
      if (j != 14) std::cout << ",";
  	}
  	if (i != orbit_count.size()-1) std::cout << std::endl;
  }
}
