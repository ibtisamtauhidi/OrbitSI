import os

import pandas as pd
from pandas.errors import EmptyDataError

import numpy as np
def list_files(directory):
    files = []
    for filename in os.listdir(directory):
        path = os.path.join(directory, filename)
        if os.path.isfile(path):
            files.append(filename)
    return files

DATASETS = ["dblp", "eu2005", "hprd", "human", "patents", "wordnet", "yeast", "youtube"]

append_df = []

for DATASET in DATASETS:
  print("Started:", DATASET)
  PATH = "./out/"+DATASET+"/"
  files = list_files(PATH)

  for f in files:
    try:
      temp_df = pd.read_csv(PATH+f, header=None).drop([0], axis=1).sum()
      temp_df["pattern"] = f.split(".")[0]
      temp_df["data"] = DATASET
      append_df.append(temp_df)
    except EmptyDataError as e:
      continue
      
df = pd.DataFrame(append_df)
df.to_csv("orbit-summary-reduced.csv", index=False)
