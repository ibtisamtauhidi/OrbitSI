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

DATASETS = ["dblp", "eu2005", "hprd", "human", "patents", "wordnet", "yeast", "youtube"]

for DATASET in DATASETS:
	PATH = "./output/" + DATASET + "/"
	FILES = list_files(PATH)
	for FILE in FILES:
		f = open(PATH + FILE).readlines()
		idx = f.index("Enumerate...\n")
		marr = [int(i) for i in f[idx - 2].strip().split(":")[1].strip().split()]
		print(marr)
		break
