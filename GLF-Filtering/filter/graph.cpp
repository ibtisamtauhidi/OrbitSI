#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

Graph readGraph(const char* file_name) {
	Graph graph;
	int vertex_count, edge_count;

	std::ifstream graph_file(file_name);

	if (graph_file.is_open()) {
		while (graph_file) {
			std::string input_line;
			std::getline(graph_file, input_line);
			std::istringstream iss(input_line);
			char type = input_line[0];
			if(type == 't') {
				char character;
				iss >> character >> vertex_count >> edge_count;
			} else if(type == 'v') {
				char character;
				int vertex_id, vertex_label, vertex_degree;
				if (iss >> character >> vertex_id >> vertex_label >> vertex_degree) {
					graph.vertex_labels.push_back(vertex_label);
					graph.vertex_degrees.push_back(vertex_degree);
					std::vector<int> vec;
					graph.adjacency_list.push_back(vec);
				}
			} else if(type == 'e') {
				char character;
				int edge_start, edge_end;
				if (iss >> character >> edge_start >> edge_end) {
					graph.adjacency_list[edge_start].push_back(edge_end);
					graph.adjacency_list[edge_end].push_back(edge_start);
				} 
			}
		}
	} else {
		std::cout << "Couldn't open file: " << file_name << std::endl;
	}
	return graph;
}

void formatVF3(Graph graph) {
  std::cout << graph.vertex_labels.size() << std::endl;;
	for (int i = 0; i < graph.vertex_labels.size(); i++) {
		std::cout << i << " " << graph.vertex_labels[i] << std::endl;
    }
	for (int i = 0; i < graph.adjacency_list.size(); i++) {
		std::cout << graph.adjacency_list[i].size() << std::endl;
		for (int j = 0; j < graph.adjacency_list[i].size(); j++) {
			std::cout << i << " " << graph.adjacency_list[i][j] << " 0" << std::endl;
		}
	}
}

void preProcess(Graph graph) {
	for (int i = 0; i < graph.adjacency_list.size(); i++) { 
		if(!std::is_sorted(graph.adjacency_list[i].begin(), graph.adjacency_list[i].end())) {
			std::sort(graph.adjacency_list[i].begin(), graph.adjacency_list[i].end());
		}		
	}
}

void printGraph(Graph graph) {
  std::cout << "Labels: ";
	for (int i = 0; i < graph.vertex_labels.size(); i++) {
		std::cout << graph.vertex_labels[i] << " ";
    }	
    std::cout << std::endl;
	std::cout << "Degrees: ";
	for (int i = 0; i < graph.vertex_degrees.size(); i++) {
		std::cout << graph.vertex_degrees[i] << " ";
    }
    std::cout << std::endl;
	
	std::cout << "Adjacency List: ";
	for (int i = 0; i < graph.adjacency_list.size(); i++) {
		std::cout << std::endl;
 		std::cout << i << ": ";
		for (int j = 0; j < graph.adjacency_list[i].size(); j++) {
			std::cout << graph.adjacency_list[i][j] << " ";
		}
	}
	std::cout << std::endl;
}
