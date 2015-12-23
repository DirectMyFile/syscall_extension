#!/usr/bin/env bash
if [ ! -d build ]
then
  ./build.sh
fi

dart tests/tests.dart