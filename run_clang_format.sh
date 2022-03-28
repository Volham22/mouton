#!/usr/bin/env bash

FILES=$(find Mouton/src Sandbox -name '*.cpp' -o -name '*h')

clang-format -i ${FILES}
