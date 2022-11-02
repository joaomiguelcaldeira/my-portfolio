#!/bin/sh
sudo docker service rm zk-server
sudo docker network rm esle-network
sudo docker swarm leave --force
