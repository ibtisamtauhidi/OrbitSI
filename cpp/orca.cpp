#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "ORCA/orca_core.h"  // We'll refactor orca.cpp core logic into this

namespace py = pybind11;

std::vector<std::vector<int>> orca_count(const std::vector<std::vector<int>>& adj_list, int k) {
    n = adj_list.size();
    m = 0;

    // Store vectors to hold the data for global raw pointers
    static std::vector<int> deg_vec;
    static std::vector<PAIR> edges_vec;
    static std::vector<std::vector<int>> adj_vec;
    static std::vector<std::vector<PII>> inc_vec;
    static std::vector<std::vector<int64>> orbit_vec;

    deg_vec.resize(n);
    adj_vec.resize(n);
    inc_vec.resize(n);
    if (k==4) orbit_vec.resize(n, std::vector<int64>(15, 0));
    else if (k==5) orbit_vec.resize(n, std::vector<int64>(73, 0));
    else throw std::invalid_argument("Only graphlet size 4 is supported in current ORCA implementation");
    
    
    // Fill degree and count m
    for (int i = 0; i < n; ++i) {
        deg_vec[i] = adj_list[i].size();
        m += deg_vec[i];
    }
    m /= 2;

    // Fill edge list without duplicates
    edges_vec.clear();
    std::set<std::pair<int, int>> added_edges;

    for (int u = 0; u < n; ++u) {
        std::vector<int> neighbors = adj_list[u];
        std::sort(neighbors.begin(), neighbors.end());
        adj_vec[u] = neighbors;
        inc_vec[u].resize(neighbors.size());

        for (size_t j = 0; j < neighbors.size(); ++j) {
            int v = neighbors[j];
            if (u < v && !added_edges.count({u, v})) {
                edges_vec.emplace_back(u, v);
                added_edges.insert({u, v});
            }
            inc_vec[u][j] = {v, 0};  // Dummy edge ID
        }
    }

    // Assign to global raw pointers used by ORCA core
    deg = deg_vec.data();

    edges = edges_vec.data();

    adj = new int*[n];
    inc = new PII*[n];
    for (int i = 0; i < n; ++i) {
        adj[i] = adj_vec[i].data();
        inc[i] = inc_vec[i].data();
    }

    orbit = new int64*[n];
    for (int i = 0; i < n; ++i) {
        orbit[i] = orbit_vec[i].data();
    }

    if (k == 4) {
        count4();
    } else if (k == 5) {
        count5();
    }
    int ORBIT_COUNTS = (k == 4)? 15: 73;
    // Return result in Python-friendly format
    std::vector<std::vector<int>> result(n, std::vector<int>(ORBIT_COUNTS));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < ORBIT_COUNTS; ++j)
            result[i][j] = static_cast<int>(orbit_vec[i][j]);

    // Cleanup temporary heap arrays (but not vector-backed ones)
    delete[] adj;
    delete[] inc;
    delete[] orbit;

    return result;
}

PYBIND11_MODULE(_orca_cpp, m) {
    m.doc() = "ORCA node orbit count module";
    m.def("orca_count", &orca_count, "ORCA orbit counting function");
}