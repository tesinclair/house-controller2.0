FROM ubuntu:latest

MAINTAINER taisinclair4@gmail.com

RUN apt update 
RUN apt install -y gcc make

COPY deps.txt /tmp/

RUN xargs -a /tmp/deps.txt apt install -y

COPY . /build
WORKDIR /build

RUN make build
