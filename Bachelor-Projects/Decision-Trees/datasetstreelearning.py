
import numpy as np
import random

def dataset(datasetnumb):
    
    nl = [9, 9, 17, 9, 9, 9, 17, 9, 17, 9, 17, 9, 9, 9, 17, 9, 9, 17, 41, 25, 57, 49, 90, 25, 33, 25, 41]
    ol = [9, 9, 17, 9, 9, 9, 17, 9, 17, 9, 17, 9, 9, 9, 17, 9, 9, 17, 41, 25, 25, 49, 67, 25, 33, 25, 41]
    
    D2 = np.array([
                  [0,0],
                  [0,1],
                  [1,0],
                  [1,1]])
    D3 = np.array([
              [0,0,0],
              [0,0,1],
              [0,1,0],
              [0,1,1],
              [1,0,0],
              [1,0,1],
              [1,1,0],
              [1,1,1]])
    D4 = np.array([
              [1,0,0,0],
              [0,0,0,1],
              [1,0,1,0],
              [0,0,1,1],
              [1,1,0,0],
              [0,1,0,1],
              [1,1,1,0],
              [0,1,1,1]])    
    
    if datasetnumb<16:
        D = D2
        Y = (np.array([datasetnumb%16,datasetnumb%8,datasetnumb%4,datasetnumb%2])>0).astype('int32')
    elif datasetnumb==16:
        D = D3
        Y = np.array([0,1,0,1,0,1,0,1])
    elif datasetnumb==17:
        D = D3
        Y = np.array([0,1,0,1,1,1,1,1])
    elif datasetnumb==18:
        D = D3
        Y = np.array([1,0,0,0,0,0,0,1])
    elif datasetnumb==19:
        D = D3
        Y = np.array([0,0,1,1,1,1,0,0])
    elif datasetnumb==20:
        D = D3
        Y = np.array([0,1,1,0,0,1,1,0])
    elif datasetnumb==21:
        np.random.seed(13102020)
        D = np.random.rand(1000,10)>0.5
        Y = ((D[:,1] == 0) & (D[:,6] == 0)) | ((D[:,3] == 1) & (D[:,4] == 1))        
    elif datasetnumb==22:
        np.random.seed(13102020)
        D = np.random.rand(5000,12)>0.5
        Y = ((D[:,1] == 0) & (D[:,6] == 0)) | ((D[:,3] == 1) & (D[:,4] == 1) | ((D[:,11] == 1) & (D[:,6] == 1)))
    elif datasetnumb==23:
        D = D4
        Y = (np.array([datasetnumb%2,datasetnumb%4,datasetnumb%2,datasetnumb%8,datasetnumb%16,datasetnumb%8,datasetnumb%23,datasetnumb%2])>0).astype('int32')        
    elif datasetnumb==24:
        D = D4
        Y = (np.array([datasetnumb%2,datasetnumb%4,datasetnumb%16,datasetnumb%8,datasetnumb%16,datasetnumb%8,datasetnumb%4,datasetnumb%2])>0).astype('int32')        
    elif datasetnumb==25:
        D = D4
        Y = (np.array([datasetnumb%2,datasetnumb%4,datasetnumb%2,datasetnumb%8,datasetnumb%16,datasetnumb%25,datasetnumb%4,datasetnumb%2])>0).astype('int32')        
    elif datasetnumb==26:
        D = D4
        Y = (np.array([datasetnumb%2,datasetnumb%4,datasetnumb%16,datasetnumb%8,datasetnumb%16,datasetnumb%8,datasetnumb%4,datasetnumb%2])>0).astype('int32')        
    
    return D,Y,nl[datasetnumb],ol[datasetnumb]

def datasetnoise(datasetnumb):

    nl = [0.0006, 0.0418, 0.0348, 0.0115]
    ol = [0.0, 0.006, 0.0064, 0.0014]
    
    if datasetnumb==0:
        np.random.seed(13102020)
        D = np.random.rand(10000,10)>0.5
        Y = ((D[:,1] == 0) & (D[:,6] == 0)) | ((D[:,3] == 1) & (D[:,4] == 1))                
        Yt = ((D[:,1] == 0) & (D[:,6] == 0)) | ((D[:,3] == 1) & (D[:,4] == 1))     
        Dt = D
        ii = np.random.randint(0, high=10000, size=1000)
        Y[ii] = Y[ii]^Y[ii]
        
                
    elif datasetnumb==1:
        np.random.seed(13102020)
        D = np.random.rand(10000,12)>0.5
        Dt = D
        Yt = ((D[:,1] == 0) & (D[:,6] == 0)) | ((D[:,3] == 1) & (D[:,4] == 1) | ((D[:,11] == 1) & (D[:,6] == 1)))        
        Y = ((D[:,1] == 0) & (D[:,6] == 0)) | ((D[:,3] == 1) & (D[:,4] == 1) | ((D[:,11] == 1) & (D[:,6] == 1)))        
        ii = np.random.randint(0, high=10000, size=1000)
        Y[ii] = Y[ii]^Y[ii]
        
    
    elif datasetnumb==2:
        np.random.seed(13102020)
        D = np.random.rand(10000,12)>0.5
        Dt = D
        Yt = ((D[:,3] == 1) & (D[:,6] == 0)) | ((D[:,3] == 1) & (D[:,4] == 1) | ((D[:,0] == 0) & (D[:,2] == 1)))
        Y = ((D[:,3] == 1) & (D[:,6] == 0)) | ((D[:,3] == 1) & (D[:,4] == 1) | ((D[:,0] == 0) & (D[:,2] == 1)))
        ii = np.random.randint(0, high=10000, size=1000)
        Y[ii] = Y[ii]^Y[ii]
        
    elif datasetnumb==3:
        np.random.seed(13102020)
        D = np.random.rand(10000,11)>0.5
        Dt = D
        Yt = ((D[:,3] == 1) & (D[:,6] == 0)) | ((D[:,3] == 1) & (D[:,4] == 1) | ((D[:,0] == 0) & (D[:,2] == 1)))
        Y = ((D[:,3] == 1) & (D[:,6] == 0)) | ((D[:,3] == 1) & (D[:,4] == 1) | ((D[:,0] == 0) & (D[:,2] == 1)))
        ii = np.random.randint(0, high=10000, size=1000)
        Y[ii] = Y[ii]^Y[ii]

    
    return D,Y,Dt,Yt,nl[datasetnumb],ol[datasetnumb]

if __name__ == "__main__":
    D,Y,Dt,Yt,nl,ol = datasetnoise(2)
