FROM ubuntu:latest

MAINTAINER taisinclair4@gmail.com

RUN apt-get update 

# Install dev basis
RUN apt-get install -y gcc make

COPY . /build
WORKDIR /build

# Install dev deps
RUN chmod u+x require.sh && ./require.sh

RUN make
