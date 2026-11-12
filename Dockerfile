FROM ubuntu:24.04

RUN apt update
RUN apt install -y git cmake g++ make

WORKDIR /app
COPY . .

RUN cmake -S . -B build
RUN cmake --build build
RUN ctest --test-dir build --output-on-failure