# -*- coding: utf-8 -*-
"""
Decision Trees

Created on Wed Oct  7 10:45:40 2020

@author: mlopes
"""

import numpy as np

import datasetstreelearning

import os
import imp
import pickle

origindir = "solutions/"
files = os.listdir(origindir)
            
        
#console color
W  = '\033[0m'  # white (normal)
R  = '\033[31m' # red
G  = '\033[32m' # green
O  = '\033[33m' # orange
B  = '\033[34m' # blue
P  = '\033[35m' # purple



def classify(T,data):
    
    data = np.array(data)
    out = []
    for el in data:
        #print("el",el,"out",out,"\nT",T)
        wT = T
        for ii in range(len(el)):
            #print(T[0],el[T[0]],T)
            if el[wT[0]]==0:
                if not isinstance(wT[1], list):
                    out += [wT[1]]
                    break
                else:
                    wT = wT[1]
            else:
                if not isinstance(wT[2], list):
                    out += [wT[2]]
                    break
                else:
                    wT = wT[2]
    return np.array(out)


files = os.listdir(origindir)
C = []
for file in files:

    cot = 0
    try:
        if file[0]=='a' or file[0]=='t':
            print(file)
            
            M = imp.load_source(file,origindir+file)

            E = 0
            Ec = 0
            L = 0
            Lc = 0
            
            points = 0
            pointsshort = 0

            for idataset in range(0,27):     
                D,Y,nl,ol = datasetstreelearning.dataset(idataset)        
                                    
                print("<", idataset, "> #points >", D.shape[0], "#feat >", D.shape[1])
                try:
                    T = M.createdecisiontree(D,Y,noise=0)
                    Yp = classify(T,D)
                
                    
                    err = np.mean(np.abs(Yp-Y))
                    l = len(str(T))
                    if err==0:
                        points += 1
                        if l>nl:
                            res = R+'TOO BIG (0)'+W
                            points -= 2
                        elif l<nl:
                            res = G+'GOOD SMALL TREE (1+bonus)'+W
                            pointsshort += 1
                        else:
                            if ol<nl:
                                res = O+'OK but it is possible to make it shorter! (1)'+W
                            else:
                                res = G+'OK (1)'+W
                    else:
                        res = R+'Erro (0)r'+W
                    print("    errors > ", err, "tree length", l, " ", res  )
                    #print("\nD", D, "\nY", Y)
                    #print("tree > ", T)
                except:
                    print(R+"Test failed")
            print("points", points, "/27", "short", pointsshort, "/2")
            
            # DATASETS WITH NOISE
            print("\n\n\t Testing robustness to noise\n\n")
            
            points2 = 0
            pointsgen = 0
            for idataset in [0,1,2,3]:
            #for idataset in []:
                D,Y,Dt,Yt,nl,ol = datasetstreelearning.datasetnoise(idataset)        
                                    
                print("dataset > ", idataset, "#points >", D.shape[0], "#feat >", D.shape[1])
                #print("\nD", D, "\nY", Y)
                try:
                    Tc = M.createdecisiontree(D,Y,noise=0.1)
                    Ytrain = classify(Tc,D)
                    Ytest = classify(Tc,Dt)
                    errtrain = np.mean(np.abs(Ytrain-Yt))
                    errtest = np.mean(np.abs(Ytest-Yt))
                    lc = len(str(Tc))    
                    
                    if errtest>nl:
                        res = R+'TOO BIG ERROR(0)'+W
                    elif errtest==nl:
                        res = O+'ERROR OK BUT LACKING GENERALIZATION'+W
                        points2 += 1
                    elif errtest<nl:
                        res = G+'ERROR OK IN THE TEST SET'+W
                        points2 += 1
                        pointsgen += 1
                    print("  error training > ", errtrain, "length", lc, " error test > ", errtest, "/", ol, "\n", res )
                except:
                    print(R+"Test failed")            
            
            print("points", points2, "/4", "good in test", pointsgen, "/4")
            
            
            
            print(P+"\n\n\t Result\n\n"+W)
            print("tree no noise", points, "/27", "short", pointsshort, "/2")
            print("tree noise", points2, "/4", "good in test", pointsgen, "/4")
            print("points",round(points/27*8,1),"+ reduced tree ", round(pointsshort/2*3,1), "+ noise", round(pointsgen/4*3,1))
            C.append([file,round(points/27*8,1),round(pointsshort/2*3,1),round(pointsgen/4*3,1)])
            print("\nExpected grade:\t", round(points/27*8,1)+round(pointsshort/2*3,1)+round(pointsgen/4*3,1),"(/14)+hidden tests (4pt)+report (2pt)")
    except:
            print(R+"Error loading file, or running!")
            