'''
python MovingGantry.py --x # --y # --s #
Threading
'''
from gantry2 import Gantry
import time
import threading
import numpy as np
import Queue

queue = Queue.Queue()
rob = Gantry()
queue.put(rob)

class CMDThreadClass(threading.Thread):
    def run(self):
        args_num = np.zeros((1,3))
        # open file
        fpathin = r'C:\Users\newton\AeroFS\NESL_Software\electrosense\PYTHON\scripts\matlabCOMin.txt'
        fin = open(fpathin,'r')
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
            rob = queue.get()
            rob.move(args_num[index,0],args_num[index,1],args_num[index,2])		
            queue.put(rob)
            time.sleep(0.2)
            cmd = fin.readline()
        fin.close()

class ReadThreadClass(threading.Thread):
    def run(self):
        fpathin = r'C:\Users\newton\AeroFS\NESL_Software\electrosense\PYTHON\scripts\matlabCOMin.txt'
        fin = open(fpathin,'r')
        cmd = fin.readline()
        firsttime = 1
        args_num = np.zeros((1,3))
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
            cmd = fin.readline()
        fin.close()   
        
        size = args_num.shape[0]
        pos = 0 # start is unknown
        fpathout = r'C:\Users\newton\AeroFS\NESL_Software\electrosense\PYTHON\scripts\matlabCOMout.txt'
        fout =  open(fpathout,'w')
        fout.write("{0:.2f}".format(pos))
        fout.close()

        for i in range(size):
            rob = queue.get()
            while(not rob.check_pos(args_num[i,0],args_num[i,1])):
                queue.put(rob)
                time.sleep(0.1)
                rob = queue.get()
            queue.put(rob)
            pos = args_num[i,1]
            print pos
            fout = open(fpathout,'w')
            fout.write("{0:.2f}".format(pos))
            fout.close()
            
def main():
    CMDt = CMDThreadClass()
    Rt = ReadThreadClass()
    CMDt.start()
    Rt.start()
    
main()
