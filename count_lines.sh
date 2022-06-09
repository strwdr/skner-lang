#!/bin/bash
a=$(( find ./src \( -name '*.h' -o -name '*.cpp' \) -print0 | xargs -0 cat ) | wc -l)
echo $(($a-6816))