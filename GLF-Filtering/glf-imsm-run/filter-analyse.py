import os, subprocess
import numpy as np
import pandas as pd


def list_files(directory):
    files = []
    for filename in os.listdir(directory):
        path = os.path.join(directory, filename)
        if os.path.isfile(path):
            files.append(filename)
    return files
    
PATH = "./filter-out/"

FILES = list_files(PATH)
arr = []
for FILE in FILES:
	mdict = {}
	mdict["data"] = FILE.split("-")[0]
	mdict["filter"] = FILE.split("-")[1]
	mdict["pattern"] = FILE.split("-")[2]
	f = open(PATH+FILE).readlines()
	idx = f.index('SYED-CS-BEGIN\n')
	cs_size = []
	for cs in f[idx+1:-2]:
		cs_size.append(int(cs.split(":")[1]))
	mdict["cs_mean"] = 	sum(cs_size) / float(len(cs_size))
	mdict["cs_std"] = 	np.std(cs_size)
	arr.append(mdict)

df = pd.DataFrame(arr)
df = df[["data","pattern","filter","cs_mean","cs_std"]]
df.sort_values(['data', 'pattern'], ascending=[True, True], inplace=True)
print(df.head())
df.to_csv("filter-cc-size-summary.csv", index=False)
