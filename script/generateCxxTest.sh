#! /bin/bash

third-party/cxxtest/cxxtestgen.py --error-printer -o test/mo_test.cpp \
test/headers/*.h \
test/headers/mo/*.h \
test/headers/mo/util/*.h \
test/headers/mo/exception/*.h
