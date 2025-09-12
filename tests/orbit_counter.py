import pytest
import networkx as nx
import numpy as np
from orbitsi.orbit import EVOKEOrbitCounter, ORCAOrbitCounter
import orbit_count  # Provides only induced counts


@pytest.mark.parametrize("size", [4, 5])
@pytest.mark.parametrize("induced", [True, False])
@pytest.mark.parametrize("num_nodes", [5, 10, 20, 30, 40, 50, 60, 100, 150, 200, 300, 500, 750, 1000, 3000, 5000, 10000])
@pytest.mark.parametrize("seed", list(range(10)))
def test_orbit_counters(size, induced, num_nodes, seed):
    # Generate sparse Erdos-Renyi graph
    p = min(0.01 / num_nodes, 0.03)
    G = nx.erdos_renyi_graph(num_nodes, p, seed=seed)

    if not nx.is_connected(G):
        return  # Skip disconnected graphs to simplify relabeling

    num_orbits = 15 if size == 4 else 73

    # === EVOKE ===
    evoke = EVOKEOrbitCounter(G, size=size)
    evoke_matrix = evoke.get_orbits(induced=induced)
    assert evoke_matrix.shape == (G.number_of_nodes(), num_orbits)

    # === ORCA ===
    orca = ORCAOrbitCounter(G, size=size)
    orca_matrix = orca.get_orbits(induced=induced)
    assert orca_matrix.shape == (G.number_of_nodes(), num_orbits)

    assert np.allclose(evoke_matrix, orca_matrix)

    if induced:
        # Compare with external Python ORCA (induced-only)
        pip_orca = orbit_count.node_orbit_counts(G, graphlet_size=size)
        pip_matrix = np.array([pip_orca[n] for n in sorted(G.nodes())])
        assert pip_matrix.shape == (G.number_of_nodes(), num_orbits)
        assert np.allclose(evoke_matrix, pip_matrix)
        assert np.allclose(orca_matrix, pip_matrix)