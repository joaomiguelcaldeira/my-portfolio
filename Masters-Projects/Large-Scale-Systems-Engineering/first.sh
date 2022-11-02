#!/bin/sh
sudo docker swarm init --advertise-addr 192.168.1.135
sudo docker network create --driver overlay --attachable esle-network
sudo docker volume create esle-volume
sudo docker service create --name zk-server --publish published=8083,target=83 --replicas $1 --network esle-network --mount source=esle-volume,target=/data zookeeper:latest
sudo docker build --network esle-network -t mycontainer:latest .
sudo docker run -it --network esle-network -v esle-volume:/data mycontainer
