import os, subprocess, sys

def list_files(directory):
    files = []
    for filename in os.listdir(directory):
        path = os.path.join(directory, filename)
        if os.path.isfile(path):
            files.append(filename)
    return files

def run_program_in_shell(program):
    try:
        subprocess.run(program, shell=True, check=True)
    except subprocess.CalledProcessError as e:
        print("Error:", e)

DATASET = sys.argv[1]
FILTERS = ["LDF", "NLF", "GQL", "TSO", "GLFP", "CFL", "DPiso"]

PATH = "./dataset/" + DATASET + "/query_graph/"
FILES = list_files(PATH)

for FILTER in FILTERS:
	i = 1
	for f in FILES:
		print(DATASET,FILTER, i)
		program = "./SubgraphMatching/build/matching/SubgraphMatching.out -d ./dataset/" + DATASET + "/data_graph/" + DATASET + ".graph -q ./dataset/"+ DATASET + "/query_graph/" + f + " -filter " + FILTER +" -order GQL -engine LFTJ -num MAX" +" > ./filter-out/" + DATASET + "-" + FILTER + "-" + f
		run_program_in_shell(program)
		i += 1
