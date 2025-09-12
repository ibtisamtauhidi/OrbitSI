# OrbitSI Test Suite

This directory contains tests to validate the correctness and consistency of:

- Subgraph isomorphism enumeration using OrbitSI.
- Orbit counting via `EVOKEOrbitCounter` and `ORCAOrbitCounter`.
- Induced orbit counts using the reference [`orbit-counter`](https://github.com/BorgwardtLab/orbit-count) package.

---

## Directory Structure

The required datasets are expected to follow this layout:

```
tests/
├── datasets/
│   ├── data\_graph/
│   │   └── HPRD.graph
│   ├── query\_graph/
│   │   └── query\_dense\_16\_\*.graph
├── expected\_output.res
├── orbit\_counter.py
└── subiso\_search.py
```

---

## Download Required Files

You must download benchmark graphs and expected results from [RapidsAtHKUST/SubgraphMatching](https://github.com/RapidsAtHKUST/SubgraphMatching). Run in root directory:

```bash
# Clone source repo
git clone https://github.com/RapidsAtHKUST/SubgraphMatching.git

# Prepare datasets in correct structure
mkdir -p tests/datasets
cp -r SubgraphMatching/test/data_graph tests/datasets/
cp -r SubgraphMatching/test/query_graph tests/datasets/
cp SubgraphMatching/test/expected_output.res tests/

# Remove downloaded repo
rm -rf SubgraphMatching/
```

---

## Install Dependencies

To validate induced orbit counts, install [`orbit-counter`](https://github.com/BorgwardtLab/orbit-count):

```bash
pip install orbit-counter
```

> This is the only additional testing dependency beyond those listed in the main `setup.py`.

---

## Running Tests

Run all tests from the root directory using:

```bash
pytest tests/
```

### What is tested?

* **`orbit_counter.py`**

  * Validates orbit matrix shapes and values for both `EVOKE` and `ORCA`.
  * Ensures induced orbit counts match those from the `orbit-counter` library.
  * Checks against randomly generated graphs of various sizes and densities.

* **`subiso_search.py`**

  * Performs subgraph isomorphism search for 200+ real benchmark queries.
  * Asserts the number of matches matches `expected_output.res`.

---

### Expected Output

On success, all tests should pass with no errors or assertion failures.

---

## Credits

Tests are based on datasets and benchmarks from:

> [https://github.com/RapidsAtHKUST/SubgraphMatching](https://github.com/RapidsAtHKUST/SubgraphMatching)
>
> Sun, Shixuan, and Qiong Luo. "In-memory subgraph matching: An in-depth study." In *Proceedings of the 2020 ACM SIGMOD International Conference on Management of Data*, pp. 1083-1098. 2020. [https://doi.org/10.1145/3318464.3380581](https://doi.org/10.1145/3318464.3380581)

Additional validation is done using:

> [`orbit-counter`](https://github.com/BorgwardtLab/orbit-count)