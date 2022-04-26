#!/bin/sh

for i in $(seq 0 999); do
    g++ -E data/$i.cpp | tail -$(wc -l data/$i.cpp | awk '{print $1}') > expanded/$i.cpp
done
