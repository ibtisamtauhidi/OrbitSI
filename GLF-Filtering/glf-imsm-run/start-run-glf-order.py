import pandas as pd
from os import listdir
from os.path import isfile, join
import numpy as np
import sys, os

DATASETS = ["dblp",  "eu2005",  "hprd",  "human",  "patents", "wordnet", "yeast", "youtube"]
ORDER = "GQL"

j = 1
for DATASET in DATASETS:
	PATH = "dataset/"+DATASET+"/query_graph/"
	FILES = [f for f in listdir(PATH) if isfile(join(PATH, f))]
	arr = []
	for f in FILES:	
		mdict = {}
		mdict["Data"] = DATASET
		mdict["Pattern"] = f.split('.')[0]
		mdict["Filter"] = "GLFP"
		mdict["Order"] = ORDER
		mdict["Explore"] = "EXPLORE"
		arr.append(mdict)

	arr = pd.DataFrame(arr)
	arr = arr[["Data", "Pattern", "Filter", "Order", "Explore"]]

	split_arr = np.array_split(arr, int(len(arr)/900))
	for i in range(len(split_arr)):
		split_arr[i].to_csv("./run-list/"+DATASET+"_run_list_"+str(i+1)+".csv", index=False, header=False)

	for i in range(len(split_arr)):
		f_str = """#!/bin/bash
#SBATCH --job-name=SI_run
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --array=1-900%20
#SBATCH --partition=hipri
#SBATCH --time 00:30:00
#SBATCH --output=./output-glf-filter-various-orders/"""+DATASET+"""/R-%x.%j.out
#SBATCH --mem=32G

file_path=./run-list/"""+DATASET+"""_run_list_"""+str(i+1)+""".csv
line=$(sed "${SLURM_ARRAY_TASK_ID}!d" $file_path)
IFS=', ' read -r -a array <<< "$line"
echo "Data: ${array[0]}"
echo "Pattern: ${array[1]}"
echo "Filter: ${array[2]}"
echo "Order: ${array[3]}"
echo "Engine: ${array[4]}"
./SubgraphMatching/build/matching/SubgraphMatching.out -d ./dataset/${array[0]}/data_graph/${array[0]}.graph -q ./dataset/${array[0]}/query_graph/${array[1]}.graph -filter ${array[2]} -order ${array[3]} -engine ${array[4]} -num MAX"""

		with open("./scripts/start-"+str(j)+".sh", "w") as text_file:
			text_file.write(f_str)
			j += 1
	    
os.system("./start-glf-order.sh")
