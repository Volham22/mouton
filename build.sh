#!/usr/bin/bash

cmake . -DCMAKE_BUILD_TYPE=Debug \
    -DASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT=OFF \
    -DASSIMP_BUILD_ASSIMP_TOOLS=OFF \
    -DASSIMP_BUILD_TESTS=OFF

make -j`nproc --all`