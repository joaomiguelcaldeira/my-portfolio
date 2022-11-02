#Project Authors João Caldeira; Diogo Santos; Sebastião Sotto Mayor
Final Grade 15/20

After cloning the git repo, type in your console:  
chmod +x first.sh   
chmod +x clean.sh  

The group results used in the analysing of the zookeeper service are in the folder throughput_results.
All the tools used to build the graphs and the graphs are on this repo.

WARNING: if you have more than one ip address in your machine you should edit first.sh indicating the ip that you want to use to start your swarm

The script first.sh builds the environment to start testing zookeeper, building a docker network named esle-network, a docker volume named esle-volume, a docker service with n replicas of zookeeper servers and builds a ycsb client. The script ends inside the ycsb bash ready to deploy the commands to start testing and deploying workload. 
To run first.sh you also need to provide the number of replicas you wish to have on the zookeeper side. 

WARNING: you need to specify the number of replicas, you can't run just "./first.sh"

Ex: "./first.sh 5" builds 5 replicas.

If you wish to clean the environment run:
"./clean.sh"

Before any test you need to load the container.

#Load  
./bin/ycsb load zookeeper -s -P workloads/workloadb -p zookeeper.connectString="container-ip":2181/zookeeper -p recordcount=10000

#Single leader test  
./bin/ycsb run zookeeper -P workloads/workloadb -p zookeeper.connectString="container-ip":2181/zookeeper

#cluster test  
./bin/ycsb run zookeeper -P workloads/workloadb -p zookeeper.connectString="container-ip":2181,"container-ip":2181,(...)/zookeeper

If you wish to use our chosen workload, instead of using "workloaddb", use "workloadESLE.txt"

SIMPLE DEMO   
(host)$ ./first.sh 1  

(Open other terminal)  
(host)$ docker ps  
(Get container ID)  
(host)$ docker inspect "container-id" |grepIPAddress  
(Get container IP)

(ycsb_cliente)/YCSB$ ./bin/ycsb load zookeeper -s -P workloads/workloadb -p zookeeper.connectString=container-ip:2181/zookeeper -p recordcount=20000  
(ycsb_cliente)/YCSB$ ./bin/ycsb run zookeeper -P workloads/workloadb -p zookeeper.connectString=container-ip:2181/zookeeper  
