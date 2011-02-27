#! /bin/bash

third-party/cxxtest/cxxtestgen.py --error-printer -o test/mo_test.cpp \
test/headers/*Test.h \
test/headers/mo/*Test.h \
test/headers/mo/util/*Test.h \
test/headers/mo/exception/*Test.h \
test/headers/mo/reporter/*Test.h \
test/headers/mo/rule/*Test.h
