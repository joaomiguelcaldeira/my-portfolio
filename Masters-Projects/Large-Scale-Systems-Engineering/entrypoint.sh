#!/bin/sh
git clone http://github.com/brianfrankcooper/YCSB.git
cd YCSB
mvn -pl site.ycsb:zookeeper-binding -am clean package -DskipTests
cd ../
cp -p workloadESLE.txt /YCSB/workloads
cd YCSB
/bin/bash
