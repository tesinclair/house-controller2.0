FROM ubuntu:latest

MAINTAINER taisinclair4@gmail.com

RUN apt update 

COPY . /build
WORKDIR /build

# Install dev basis
RUN apt install -y gcc make
RUN xargs -a deps.txt apt install -y

RUN make
