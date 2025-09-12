#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>

#include "Escape/Graph.h"
#include "Escape/OrbitStructure.h"
#include "Escape/FourVertexOrbit.h"
#include "Escape/FiveVertexOrbit.h"
#include "Escape/GetAllOrbitCounts.h"

namespace py = pybind11;
using namespace Escape;

using GraphInput = std::unordered_map<int, std::vector<int>>;
using OrbitMap = std::unordered_map<int, std::vector<int>>;

CGraph* convert_to_cgraph(const GraphInput& adj, std::vector<int>& node_ids_out) {
    VertexIdx n = adj.size();
    std::vector<EdgeIdx> offsets(n + 1);
    std::vector<VertexIdx> nbors;

    node_ids_out.reserve(n);
    for (const auto& [node, _] : adj)
        node_ids_out.push_back(node);
    std::sort(node_ids_out.begin(), node_ids_out.end());

    std::unordered_map<int, VertexIdx> remap;
    for (VertexIdx i = 0; i < node_ids_out.size(); ++i)
        remap[node_ids_out[i]] = i;

    VertexIdx idx = 0;
    offsets[0] = 0;
    for (int node : node_ids_out) {
        for (int nbr : adj.at(node)) {
            if (remap.find(nbr) == remap.end())
                throw std::runtime_error("Invalid neighbor found: not in graph.");
            nbors.push_back(remap[nbr]);
        }
        offsets[++idx] = nbors.size();
    }

    CGraph* g = new CGraph();
    g->nVertices = n;
    g->nEdges = nbors.size();
    g->offsets = new EdgeIdx[n + 1];
    g->nbors = new VertexIdx[nbors.size()];
    std::copy(offsets.begin(), offsets.end(), g->offsets);
    std::copy(nbors.begin(), nbors.end(), g->nbors);
    g->sortById();
    return g;
}

OrbitMap evoke_count(const GraphInput& adj, int size, bool parallel = false) {
    std::vector<int> node_ids;
    CGraph* G_raw = convert_to_cgraph(adj, node_ids);

    VertexIdx* mapping;
    VertexIdx* inverse;
    CGraph G_relabel = G_raw->renameByDegreeOrder(mapping, inverse);
    G_relabel.sortById();

    CDAG dag = degreeOrdered(&G_relabel);
    dag.outlist.sortById();
    dag.inlist.sortById();

    int num_node_orbits = 0, num_edge_orbits = 0;
    if (size == 4) {
        num_node_orbits = 15;
        num_edge_orbits = 12;
    } else if (size == 5) {
        num_node_orbits = 73;
        num_edge_orbits = 68;
    } else {
        throw std::invalid_argument("Only size 4 and 5 are supported in EVOKE.");
    }

    OrbitInfo orbit_counts(&(dag.outlist), num_node_orbits, num_edge_orbits);

    get_all_three_orbits(&G_relabel, &dag, orbit_counts);
    if (size == 4) {
        get_all_four_orbits_node_only(&G_relabel, &dag, orbit_counts);
    } else if (size == 5) {
        get_all_four_orbits(&G_relabel, &dag, orbit_counts);
        get_all_five_orbits(&G_relabel, &dag, orbit_counts, parallel ? 1 : 0);
    }

    OrbitMap result;
    for (VertexIdx i = 0; i < G_relabel.nVertices; ++i) {
        std::vector<int> counts;
        for (int orbit = 0; orbit < num_node_orbits; ++orbit) {
            counts.push_back(static_cast<int>(orbit_counts.per_vertex_[orbit][mapping[i]]));
        }
        result[node_ids[i]] = counts;
    }

    delete[] mapping;
    delete[] inverse;
    delete[] G_raw->offsets;
    delete[] G_raw->nbors;
    delete G_raw;

    return result;
}

PYBIND11_MODULE(_evoke_cpp, m) {
    m.def("evoke_count", &evoke_count, R"pbdoc(
        Count node orbits of size 4 or 5 using EVOKE.
        Parameters:
            adj (dict): adjacency list (int → list of ints)
            size (int): graphlet size (4 or 5)
            parallel (bool): enable parallelism for 5-node
    )pbdoc",
    py::arg("adj"), py::arg("size"), py::arg("parallel") = false);
}
