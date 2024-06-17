#ifndef ORBIT_H
#define ORBIT_H

#ifdef VERBOSE
struct Orbit {
    int type;
    int* vertices;
};
bool compareOrbits(const Orbit& a, const Orbit& b);
#endif

int* countOrbits(Graph graph, int vertex);
void printOrbits(int* orbit_count);
void printOrbitsVector(std::vector<int *>);

#endif /* ORBIT_H */

