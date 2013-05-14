'''
python MovingGantry.py --x # --y # --s #
'''
from gantry2 import Gantry
import time
import threading
import numpy as np

rob = Gantry()

fpathout = r'C:\Users\newton\Dropbox\echidna2\scripts\echidna_client\newton_source\matlabCOMout.txt'
fpathin = r'C:\\Users\newton\Dropbox\echidna2\scripts\echidna_client\newton_source\matlabCOMin.txt'
fin = open(fpathin,'r')

args_num = np.zeros((1,3))
cmd = fin.readline()
firsttime = 1
while cmd != '':
    args_str = cmd.split(' ')
    if firsttime == 1:
        firsttime = 0
        args_num = np.array([[float(args_str[0]),
                              float(args_str[1]),
                              float(args_str[2])]])
    else:
        tmp = np.array([[float(args_str[0]),
                         float(args_str[1]),
                         float(args_str[2])]])
        args_num = np.concatenate((args_num,tmp))
    index = args_num.shape[0]-1;
    print args_num[index,0],args_num[index,1],args_num[index,2]
    rob.move(args_num[index,0],args_num[index,1],args_num[index,2])		
    time.sleep(0.2)
    cmd = fin.readline()
fin.close()

size = args_num.shape[0]
pos = 0 # start is unknown
fout = open(fpathout,'w')
fout.write("{0:.2f}".format(pos))
fout.close()

for i in range(size):
    while(not rob.check_pos(args_num[i,0],args_num[i,1])):
        time.sleep(0.2)
    pos = args_num[i,1]
    fout = open(fpathout,'w')
    fout.write("{0:.2f}".format(pos))
    fout.close()