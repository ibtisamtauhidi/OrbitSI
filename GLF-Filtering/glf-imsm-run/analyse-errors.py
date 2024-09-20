# -*- coding: utf-8 -*-
from __future__ import print_function
import glob 
import sys

def printProgressBar (iteration, total, prefix = '', suffix = '', decimals = 1, length = 100, fill = '█', printEnd = "\r"):
    percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))
    filledLength = int(length * iteration // total)
    bar = fill * filledLength + '-' * (length - filledLength)
    print('\r%s |%s| %s%% %s' % (prefix, bar, percent, suffix), end = printEnd)
    # Print New Line on Complete
    if iteration == total: 
        print()

FILES = glob.glob('./' + sys.argv[1] + '/*.out')
arr = []
TOTAL_FILES = len(FILES)
for i, f in enumerate(FILES):
	fp = open(f).readlines()
	if fp[-1].strip() == "End.":
		continue
	else:
		if not "DUE TO TIME LIMIT" in fp[-1]:
			print(fp[-1])
