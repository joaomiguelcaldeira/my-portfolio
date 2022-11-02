#extend the original ubuntu image
FROM ubuntu:20.04
#copy the starting script to the container image
COPY entrypoint.sh /entrypoint.sh
COPY workloadESLE.txt /workloadESLE.txt
ENV TZ=Europe/Lisbon
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN  apt-get update -y && apt-get install git -y && apt-get install maven -y && apt-get install python -y
CMD ["sh", "/entrypoint.sh"]
