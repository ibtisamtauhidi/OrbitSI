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

DATASETS = [sys.argv[1]] #"dblp", "hprd", "human", "patents", 
for DATASET in DATASETS:
	PATH = "./dataset/" + DATASET + "/query_graph/"
	files = list_files(PATH)
	i = 0
	for f in files:
		print(DATASET, i)
		program = "./filter ./dataset/" + DATASET + "/data_graph/" + DATASET + ".graph "+ PATH + f +" > ./out/"+DATASET + "/" + f
		run_program_in_shell(program)
		i += 1
