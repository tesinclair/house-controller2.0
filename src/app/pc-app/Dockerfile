FROM ubuntu:latest

MAINTAINER taisinclair4@gmail.com

RUN apt update 
RUN apt install -y \
    gdb \
    x11-apps \
    sudo

COPY deps.txt /tmp/

RUN xargs -a /tmp/deps.txt apt install -y

COPY . /build
WORKDIR /build

RUN make build

RUN useradd -ms /bin/bash dev && \
    echo 'dev ALL=(ALL) NOPASSWD: ALL' > /etc/sudoers.d/dev

USER dev

WORKDIR /build

