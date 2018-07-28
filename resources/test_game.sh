#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
cd ${DIR}
LD_LIBRARY_PATH=$(readlink -f ../lib) ./test_game