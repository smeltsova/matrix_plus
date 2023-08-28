#!/bin/bash

cd ../../../
docker rmi -f geniezan/valgrind/matrix
docker build . -t geniezan/valgrind/matrix -f materials/build/Valgrind/Dockerfile
docker run --rm geniezan/valgrind/matrix
