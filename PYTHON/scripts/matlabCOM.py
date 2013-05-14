from gantry import Gantry
import argparse
import time

filepath = 'matlabCOMin.txt'
f = open(filepath,'r')
while(1):
	time.sleep(1)
	print f.readline()
