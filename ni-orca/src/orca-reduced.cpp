#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <iostream>
#include <fstream>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;


typedef long long int64;
typedef pair<int,int> PII;
typedef struct { int first, second, third; } TIII;

struct PAIR {
	int a, b;
	PAIR(int a0, int b0) { a=min(a0,b0); b=max(a0,b0); }
};
bool operator<(const PAIR &x, const PAIR &y) {
	if (x.a==y.a) return x.b<y.b;
	else return x.a<y.a;
}
bool operator==(const PAIR &x, const PAIR &y) {
	return x.a==y.a && x.b==y.b;
}
struct hash_PAIR {
	size_t operator()(const PAIR &x) const {
		return (x.a<<8) ^ (x.b<<0);
	}
};

struct TRIPLE {
	int a, b, c;
	TRIPLE(int a0, int b0, int c0) {
		a=a0; b=b0; c=c0;
		if (a>b) swap(a,b);
		if (b>c) swap(b,c);
		if (a>b) swap(a,b);
	}
};
bool operator<(const TRIPLE &x, const TRIPLE &y) {
	if (x.a==y.a) {
		if (x.b==y.b) return x.c<y.c;
		else return x.b<y.b;
	} else return x.a<y.a;
}
bool operator==(const TRIPLE &x, const TRIPLE &y) {
	return x.a==y.a && x.b==y.b && x.c==y.c;
}
struct hash_TRIPLE {
	size_t operator()(const TRIPLE &x) const {
		return (x.a<<16) ^ (x.b<<8) ^ (x.c<<0);
	}
};

unordered_map<PAIR, int, hash_PAIR> common2;
unordered_map<TRIPLE, int, hash_TRIPLE> common3;
unordered_map<PAIR, int, hash_PAIR>::iterator common2_it;
unordered_map<TRIPLE, int, hash_TRIPLE>::iterator common3_it;

#define common3_get(x) (((common3_it=common3.find(x))!=common3.end())?(common3_it->second):0)
#define common2_get(x) (((common2_it=common2.find(x))!=common2.end())?(common2_it->second):0)

int n,m; // n = number of nodes, m = number of edges
int *deg; // degrees of individual nodes
PAIR *edges; // list of edges

int **adj; // adj[x] - adjacency list of node x
PII **inc; // inc[x] - incidence list of node x: (y, edge id)
bool adjacent_list(int x, int y) { return binary_search(adj[x],adj[x]+deg[x],y); }
int *adj_matrix; // compressed adjacency matrix
const int adj_chunk = 8*sizeof(int);
bool adjacent_matrix(int x, int y) { return adj_matrix[(x*n+y)/adj_chunk]&(1<<((x*n+y)%adj_chunk)); }
bool (*adjacent)(int,int);
int getEdgeId(int x, int y) { return inc[x][lower_bound(adj[x],adj[x]+deg[x],y)-adj[x]].second; }

int64 **orbit; // orbit[x][o] - how many times does node x participate in orbit o


void orbit_count() {
	int frac,frac_prev;

	int *tri = (int*)calloc(m,sizeof(int));
	frac_prev=-1;
	for (int i=0;i<m;i++) {
		frac = 100LL*i/m;
		if (frac!=frac_prev) {
			printf("%d%%\r",frac);
			frac_prev=frac;
		}
		int x=edges[i].a, y=edges[i].b;
		for (int xi=0,yi=0; xi<deg[x] && yi<deg[y]; ) {
			if (adj[x][xi]==adj[y][yi]) { tri[i]++; xi++; yi++; }
			else if (adj[x][xi]<adj[y][yi]) { xi++; }
			else { yi++; }
		}
	}

	int64 *C4 = (int64*)calloc(n,sizeof(int64));
	int *neigh = (int*)malloc(n*sizeof(int)), nn;
	frac_prev=-1;
	for (int x=0;x<n;x++) {
		frac = 100LL*x/n;
		if (frac!=frac_prev) {
			printf("%d%%\r",frac);
			frac_prev=frac;
		}
		for (int nx=0;nx<deg[x];nx++) {
			int y=adj[x][nx];
			if (y >= x) break;
			nn=0;
			for (int ny=0;ny<deg[y];ny++) {
				int z=adj[y][ny];
				if (z >= y) break;
				if (adjacent(x,z)==0) continue;
				neigh[nn++]=z;
			}
			for (int i=0;i<nn;i++) {
				int z = neigh[i];
				for (int j=i+1;j<nn;j++) {
					int zz = neigh[j];
					if (adjacent(z,zz)) {
						C4[x]++; C4[y]++; C4[z]++; C4[zz]++;
					}
				}
			}
		}
	}

	int *common = (int*)calloc(n,sizeof(int));
	int *common_list = (int*)malloc(n*sizeof(int)), nc=0;
	frac_prev=-1;
	for (int x=0;x<n;x++) {
		frac = 100LL*x/n;
		if (frac!=frac_prev) {
			printf("%d%%\r",frac);
			frac_prev=frac;
		}

		int64 f_12_14=0, f_10_13=0;
		int64 f_13_14=0, f_11_13=0;
		int64 f_7_11=0, f_5_8=0;
		int64 f_6_9=0, f_9_12=0, f_4_8=0, f_8_12=0;
		int64 f_14=C4[x];

		for (int i=0;i<nc;i++) common[common_list[i]]=0;
		nc=0;

		orbit[x][0]=deg[x];
		// x - middle node
		for (int nx1=0;nx1<deg[x];nx1++) {
			int y=inc[x][nx1].first, ey=inc[x][nx1].second;
			for (int ny=0;ny<deg[y];ny++) {
				int z=inc[y][ny].first, ez=inc[y][ny].second;
				if (adjacent(x,z)) { // triangle
					if (z<y) {
						f_12_14 += tri[ez]-1;
						f_10_13 += (deg[y]-1-tri[ez])+(deg[z]-1-tri[ez]);
					}
				} else {
					if (common[z]==0) common_list[nc++]=z;
					common[z]++;
				}
			}
			for (int nx2=nx1+1;nx2<deg[x];nx2++) {
				int z=inc[x][nx2].first, ez=inc[x][nx2].second;
				if (adjacent(y,z)) { // triangle
					orbit[x][3]++;
					f_13_14 += (tri[ey]-1)+(tri[ez]-1);
					f_11_13 += (deg[x]-1-tri[ey])+(deg[x]-1-tri[ez]);
				} else { // path
					orbit[x][2]++;
					f_7_11 += (deg[x]-1-tri[ey]-1)+(deg[x]-1-tri[ez]-1);
					f_5_8 += (deg[y]-1-tri[ey])+(deg[z]-1-tri[ez]);
				}
			}
		}
		// x - side node
		for (int nx1=0;nx1<deg[x];nx1++) {
			int y=inc[x][nx1].first, ey=inc[x][nx1].second;
			for (int ny=0;ny<deg[y];ny++) {
				int z=inc[y][ny].first, ez=inc[y][ny].second;
				if (x==z) continue;
				if (!adjacent(x,z)) { // path
					orbit[x][1]++;
					f_6_9 += (deg[y]-1-tri[ey]-1);
					f_9_12 += tri[ez];
					f_4_8 += (deg[z]-1-tri[ez]);
					f_8_12 += (common[z]-1);
				}
			}
		}

		// solve system of equations
		orbit[x][14]=(f_14);
		orbit[x][13]=(f_13_14-6*f_14)/2;
		orbit[x][12]=(f_12_14-3*f_14);
		orbit[x][11]=(f_11_13-f_13_14+6*f_14)/2;
		orbit[x][10]=(f_10_13-f_13_14+6*f_14);
		orbit[x][9]=(f_9_12-2*f_12_14+6*f_14)/2;
		orbit[x][8]=(f_8_12-2*f_12_14+6*f_14)/2;
		orbit[x][7]=(f_13_14+f_7_11-f_11_13-6*f_14)/6;
		orbit[x][6]=(2*f_12_14+f_6_9-f_9_12-6*f_14)/2;
		orbit[x][5]=(2*f_12_14+f_5_8-f_8_12-6*f_14);
		orbit[x][4]=(2*f_12_14+f_4_8-f_8_12-6*f_14);


		orbit[x][15]=f_14;
		orbit[x][16]=f_12_14;
		orbit[x][17]=f_10_13;
		orbit[x][18]=f_13_14;
		orbit[x][19]=f_11_13;
		orbit[x][20]=f_7_11;
		orbit[x][21]=f_5_8;
		orbit[x][22]=f_6_9;
		orbit[x][23]=f_9_12;
		orbit[x][24]=f_4_8;
		orbit[x][25]=f_8_12;	
	}
}

fstream fin;
int GS=4;

int init(int argc, char *argv[]) {
	// open input, output files
	if (argc!=2) {
		cerr << "Incorrect number of arguments." << endl;
		cerr << "Usage: orca.exe [graph - input file]" << endl;
		return 0;
	}
	fin.open(argv[1], fstream::in);
	if (fin.fail()) {
		cerr << "Failed to open file " << argv[2] << endl;
		return 0;
	}
	// read input graph
	char temp;
	fin >> temp >> n >> m;
	if (temp != 't') exit(0);
	int a,b,c;
	for (int i=0;i<n;i++) {
		fin >> temp >> a >> b >> c;
	}
	int d_max=0;
	edges = (PAIR*)malloc(m*sizeof(PAIR));
	deg = (int*)calloc(n,sizeof(int));
	for (int i=0;i<m;i++) {
		int a,b;
        fin >> temp >> a >> b;
   		if (!(0<=a && a<n) || !(0<=b && b<n)) {
			cerr << "Node ids should be between 0 and n-1." << endl;
			return 0;
		}
		if (a==b) {
			cerr << "Self loops (edge from x to x) are not allowed." << endl;
			return 0;
		}
		deg[a]++; deg[b]++;
		edges[i]=PAIR(a,b);
	}
	for (int i=0;i<n;i++) d_max=max(d_max,deg[i]);
	fin.close();
	if ((int)(set<PAIR>(edges,edges+m).size())!=m) {
		cerr << "Input file contains duplicate undirected edges." << endl;
		return 0;
	}
	// set up adjacency matrix if it's smaller than 100MB
	if ((int64)n*n < 100LL*1024*1024*8) {
		adjacent = adjacent_matrix;
		adj_matrix = (int*)calloc((n*n)/adj_chunk+1,sizeof(int));
		for (int i=0;i<m;i++) {
			int a=edges[i].a, b=edges[i].b;
			adj_matrix[(a*n+b)/adj_chunk]|=(1<<((a*n+b)%adj_chunk));
			adj_matrix[(b*n+a)/adj_chunk]|=(1<<((b*n+a)%adj_chunk));
		}
	} else {
		adjacent = adjacent_list;
	}
	// set up adjacency, incidence lists
	adj = (int**)malloc(n*sizeof(int*));
	for (int i=0;i<n;i++) adj[i] = (int*)malloc(deg[i]*sizeof(int));
	inc = (PII**)malloc(n*sizeof(PII*));
	for (int i=0;i<n;i++) inc[i] = (PII*)malloc(deg[i]*sizeof(PII));
	int *d = (int*)calloc(n,sizeof(int));
	for (int i=0;i<m;i++) {
		int a=edges[i].a, b=edges[i].b;
		adj[a][d[a]]=b; adj[b][d[b]]=a;
		inc[a][d[a]]=PII(b,i); inc[b][d[b]]=PII(a,i);
		d[a]++; d[b]++;
	}
	for (int i=0;i<n;i++) {
		sort(adj[i],adj[i]+deg[i]);
		sort(inc[i],inc[i]+deg[i]);
	}
	// initialize orbit counts
	orbit = (int64**)malloc(n*sizeof(int64*));
	for (int i=0;i<n;i++) orbit[i] = (int64*)calloc(73,sizeof(int64));
	return 1;
}

void writeResults() {
	for (int i=0;i<n;i++) {
		for (int j=0;j<15;j++) {
			if (j!=0) std::cout << ",";
			std::cout << orbit[i][j];
		}
		std::cout << endl;
	}
}

int main(int argc, char *argv[]) {
	if (!init(argc, argv)) {
		cerr << "Stopping!" << endl;
		return 0;
	}
	orbit_count();
	writeResults();
	return 0;
}
