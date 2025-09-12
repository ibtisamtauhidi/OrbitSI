import os
import glob
import pytest
from orbitsi.search import OrbitSIEngine
from orbitsi.orbit import EVOKEOrbitCounter
from orbitsi.utils import read_graph_from_file

# Paths
DATA_DIR = os.path.join(os.path.dirname(__file__), "datasets")
DATA_GRAPH_PATH = os.path.join(DATA_DIR, "data_graph", "HPRD.graph")
QUERY_DIR = os.path.join(DATA_DIR, "query_graph")
EXPECTED_PATH = os.path.join(os.path.dirname(__file__), "expected_output.res")

def load_expected_results(path):
    expected = {}
    with open(path) as f:
        for line in f:
            if ':' in line:
                key, val = line.strip().split(':')
                expected[key.strip()] = int(val.strip())
    return expected

@pytest.fixture(scope="module")
def data_graph():
    return read_graph_from_file(DATA_GRAPH_PATH)


@pytest.fixture(scope="module")
def expected_results():
    return load_expected_results(EXPECTED_PATH)


# Dynamically collect all query graph files
query_files = sorted(glob.glob(os.path.join(QUERY_DIR, "*.graph")))


@pytest.mark.parametrize("query_path", query_files)
def test_query_matches(data_graph, expected_results, query_path):
    query_name = os.path.splitext(os.path.basename(query_path))[0]
    pattern_graph = read_graph_from_file(query_path)

    engine = OrbitSIEngine(
        data_graph=data_graph,
        orbit_counter_class=EVOKEOrbitCounter,
        graphlet_size=4
    )

    try:
        matches = engine.run(pattern_graph)
    except Exception as e:
        pytest.fail(f"Exception raised during query '{query_name}': {e}")

    expected = expected_results.get(query_name, -1)
    actual = len(matches)

    assert actual == expected, f"❌ {query_name}: Expected {expected}, got {actual}"
