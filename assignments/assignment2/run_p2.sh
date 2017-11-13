#!/bin/bash

make

./BestFirstSearch input.txt output.txt

diff output.txt solution.txt
