#include "graph.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <unordered_map>

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

bool isEveryElementGEQ(const std::vector<unsigned long>& vec1, const std::vector<unsigned long>& vec2) {
    if (vec1.size() != vec2.size()) {
        std::cerr << "Vectors have different sizes" << std::endl;
        return false;
    }

    for (size_t i = 0; i < vec1.size(); ++i) {
        if (vec1[i] < vec2[i]) {
            return false;
        }
    }
    return true;
}

bool isEveryElementGEQ_NLF(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    if (vec1.size() != vec2.size()) {
        std::cerr << "Vectors have different sizes" << std::endl;
        return false;
    }

    for (size_t i = 0; i < vec1.size(); ++i) {
        if (vec1[i] < vec2[i]) {
            return false;
        }
    }
    return true;
}

std::vector<std::vector<int>> LDF_Filter(Graph data, Graph pattern) {
    int unique_label_count = *std::max_element(std::begin(data.vertex_labels), std::end(data.vertex_labels))+1;
    std::vector<std::vector<int>> data_vec_by_labels(unique_label_count);

	for(int i = 0; i < data.vertex_labels.size(); i++) {
		data_vec_by_labels[data.vertex_labels[i]].push_back(i);		
	}   
    
    std::vector<std::vector<int>> LDF_candidates(pattern.vertex_labels.size());    
    for(int i = 0; i < pattern.vertex_labels.size(); i++) {
		for(int j=0; j < data_vec_by_labels[pattern.vertex_labels[i]].size(); j++) {
			if(pattern.vertex_degrees[i] <= data.vertex_degrees[data_vec_by_labels[pattern.vertex_labels[i]][j]]) {
				LDF_candidates[i].push_back(data_vec_by_labels[pattern.vertex_labels[i]][j]);
			}
		}				
	}
	return LDF_candidates;
}

std::vector<std::vector<int>> NLF_Filter(Graph data, Graph pattern, std::vector<std::vector<int>> LDF_candidates) {
    int unique_label_count = *std::max_element(std::begin(data.vertex_labels), std::end(data.vertex_labels))+1;
 	std::unordered_map<int, std::vector<int>> data_NLF_counts;
 	for(int i = 0; i < LDF_candidates.size(); i++) {
 		for(int j = 0; j < LDF_candidates[i].size(); j++) {
 			if(data_NLF_counts.find(LDF_candidates[i][j]) == data_NLF_counts.end()) {
 				int candidate = LDF_candidates[i][j];
 				data_NLF_counts[candidate] = std::vector<int>(unique_label_count, 0);
 				for(int k = 0; k < data.adjacency_list[candidate].size(); k++) {
 					data_NLF_counts[candidate][data.vertex_labels[data.adjacency_list[candidate][k]]]++;
 				}
 			}
 		}
 	}
    std::vector<std::vector<int>> NLF_candidates(pattern.vertex_labels.size());    
	for(int i = 0; i < pattern.vertex_degrees.size(); i++) {
		std::vector<int> NLF = std::vector<int>(unique_label_count, 0);
		for(int j = 0; j < pattern.adjacency_list[i].size(); j++) {
			NLF[pattern.vertex_labels[pattern.adjacency_list[i][j]]]++; 
		}
        for(int j = 0; j < LDF_candidates[i].size(); j++) {
        	int candidate = LDF_candidates[i][j];
 			if(isEveryElementGEQ_NLF(data_NLF_counts[candidate], NLF)) {
 				NLF_candidates[i].push_back(candidate);
 			}       	
        }       
	}
	return NLF_candidates;
}

void printCandidates(std::vector<std::vector<int>> candidates) {
	for(int i = 0; i < candidates.size(); i++) {
		for(int j = 0; j < candidates[i].size(); j++) {
			std::cout << candidates[i][j];
			if(j!=candidates[i].size()-1) std::cout  << ",";
		}
		std::cout << std::endl;
	}
}

std::string getOrbitPath(std::string graphPath) {
    size_t pos_1 = graphPath.find("dataset");
    if (pos_1 != std::string::npos) {
        graphPath.replace(pos_1, 7, "orbit_out");
    }
    size_t pos_2 = graphPath.find(".graph");
    if (pos_2 != std::string::npos) {
        graphPath.replace(pos_2, std::string::npos, ".orbit");
    }
    return graphPath;
}


std::vector<std::vector<unsigned long>> readOrbits(const std::string& filename) {
    std::vector<std::vector<unsigned long>> data;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<unsigned long> row;
        std::istringstream iss(line);
        std::string token;
        while (std::getline(iss, token, ',')) {
            try {
                int value = std::stoul(token);
                row.push_back(value);
            } catch (const std::exception& e) {
                std::cerr << "Error: Invalid unsigned long value in CSV: " << token << std::endl;
            }
        }
        data.push_back(row);
    }

    file.close();
    return data;
}

int main(int argc, char** argv) {
   	Graph data = readGraph(argv[1]);
    Graph pattern = readGraph(argv[2]);
    
    preProcess(pattern);
    preProcess(data);
    
    #ifdef VERBOSE
      std::cout << "Pattern:" << std::endl;
      printGraph(pattern);
    #endif
    
    std::vector<std::vector<int>> LDF_candidates = LDF_Filter(data, pattern);
    //std::cout << "LDF Candidates:" << std::endl;
    //printCandidates(LDF_candidates);

	std::vector<std::vector<int>> NLF_candidates = NLF_Filter(data, pattern, LDF_candidates);
    //std::cout << "NLF Candidates:" << std::endl;
	//printCandidates(NLF_candidates);
	
	std::vector<std::vector<unsigned long>> data_orbits = readOrbits(getOrbitPath(argv[1]));
	std::vector<std::vector<unsigned long>> pattern_orbits = readOrbits(getOrbitPath(argv[2]));
	
	std::unordered_map<int, std::vector<int>> GLF_filter_hits;

	std::vector<std::vector<int>> GLF_candidates(pattern.vertex_labels.size());
	for(int i = 0; i < pattern.vertex_degrees.size(); i++) {
        for(int j = 0; j < NLF_candidates[i].size(); j++) {
        	int candidate = NLF_candidates[i][j];
 			if(isEveryElementGEQ(data_orbits[candidate], pattern_orbits[i])) {
 				GLF_candidates[i].push_back(candidate);
 			} else {
 				GLF_filter_hits[candidate] = std::vector<int>(15, 0);
 				for(int k = 0; k < 15; k++) {
 					if(data_orbits[candidate][k] < pattern_orbits[i][k]) GLF_filter_hits[candidate][k] = 1;
 				}
 			}       	
        }       
	}
	//printCandidates(GLF_candidates);

    for (const auto& entry : GLF_filter_hits) {
        std::vector<int> hits = entry.second;
        std::cout << entry.first << ",";
        for (int i = 0; i < 15; i++) {
            std::cout << hits[i];
            if (i != 14) std::cout << ",";
        }
        std::cout << std::endl;
    }

	return 0;
}
