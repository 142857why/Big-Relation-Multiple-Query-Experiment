#!/bin/zsh
# Ask for a input of batch size as a parameter when running the bash script
# Example: ./run_ex01.sh 100000
# The default batch size is 100000 if not specified
if [ $# -eq 0 ]
  then
    BATCH_SIZE=100000
  else
    BATCH_SIZE=$1
fi

./run_backend.sh --batch -o cpp/retailer/retailer_01_01.hpp m3/retailer/retailer_01_01.m3 && \
g++ -O3 -Wall -Wno-unused-variable -std=c++17 \
-pedantic src/main.cpp \
-I backend/lib \
-I src \
-I src/lib \
-DBATCH_SIZE=$BATCH_SIZE \
-include cpp/retailer/retailer_01_01.hpp \
-include src/application/retailer/application_retailer.hpp \
-o bin/retailer/retailer_01_01_BATCH && \
./bin/retailer/retailer_01_01_BATCH > out/retailer_01_01_BATCH$BATCH_SIZE.out && \

./run_backend.sh --batch -o cpp/retailer/retailer_01_02.hpp m3/retailer/retailer_01_02.m3 && \
g++ -O3 -Wall -Wno-unused-variable -std=c++17 \
-pedantic src/main.cpp \
-I backend/lib \
-I src \
-I src/lib \
-DBATCH_SIZE=$BATCH_SIZE \
-include cpp/retailer/retailer_01_02.hpp \
-include src/application/retailer/application_retailer.hpp \
-o bin/retailer/retailer_01_02_BATCH && \
./bin/retailer/retailer_01_02_BATCH > out/retailer_01_02_BATCH$BATCH_SIZE.out && \
