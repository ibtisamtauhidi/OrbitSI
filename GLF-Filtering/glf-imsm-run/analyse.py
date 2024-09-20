# -*- coding: utf-8 -*-
from __future__ import print_function
import glob 
import pandas as pd
import sys

def printProgressBar (iteration, total, prefix = '', suffix = '', decimals = 1, length = 100, fill = '█', printEnd = "\r"):
    percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))
    filledLength = int(length * iteration // total)
    bar = fill * filledLength + '-' * (length - filledLength)
    print('\r%s |%s| %s%% %s' % (prefix, bar, percent, suffix), end = printEnd)
    # Print New Line on Complete
    if iteration == total: 
        print()

FILES = glob.glob('./' + sys.argv[1] + '/*/*.out')
arr = []
TOTAL_FILES = len(FILES)
for i, f in enumerate(FILES):
	fp = open(f).readlines()
	if fp[-1].strip() == "End.":
		mdict = {}
		mdict[fp[0].split(" ")[0][:-1]] = fp[0].split(" ")[1].strip()
		mdict[fp[1].split(" ")[0][:-1]] = fp[1].split(" ")[1].strip()
		mdict[fp[2].split(" ")[0][:-1]] = fp[2].split(" ")[1].strip()
		mdict[fp[3].split(" ")[0][:-1]] = fp[3].split(" ")[1].strip()
		mdict[fp[4].split(" ")[0][:-1]] = fp[4].split(" ")[1].strip()
		mdict[fp[-12].split(":")[0]] = fp[-12].split(":")[1].strip()
		mdict[fp[-11].split(":")[0]] = fp[-11].split(":")[1].strip()
		mdict[fp[-10].split(":")[0]] = fp[-10].split(":")[1].strip()
		mdict[fp[-9].split(":")[0]] = fp[-9].split(":")[1].strip()
		mdict[fp[-8].split(":")[0]] = fp[-8].split(":")[1].strip()
		mdict[fp[-7].split(":")[0]] = fp[-7].split(":")[1].strip()
		mdict[fp[-6].split(":")[0]] = fp[-6].split(":")[1].strip()
		mdict[fp[-5].split(":")[0]] = fp[-5].split(":")[1].strip()
		mdict[fp[-4].split(":")[0]] = fp[-4].split(":")[1].strip()
		mdict[fp[-3].split(":")[0]] = fp[-3].split(":")[1].strip()
		mdict[fp[-2].split(":")[0]] = fp[-2].split(":")[1].strip()
		mdict["Query Plan"] = fp[-18].strip().split(":")[1].strip()
		arr.append(mdict)
	printProgressBar(i + 1, TOTAL_FILES, prefix = 'Progress:', suffix = 'Complete', length = 50)
arr = pd.DataFrame(arr)
arr.to_csv("summary-" + sys.argv[1] + ".csv", index=False)
