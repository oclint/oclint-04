#! /bin/bash

third-party/cxxtest/cxxtestgen.py --error-printer -o test/oclint_test.cpp \
test/headers/*Test.h \
test/headers/oclint/*Test.h \
test/headers/oclint/rule/*Test.h \
test/headers/oclint/helper/*Test.h \
test/headers/oclint/exception/*Test.h \
test/headers/oclint/reporter/*Test.h
