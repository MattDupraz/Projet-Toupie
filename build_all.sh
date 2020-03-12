#!/bin/bash

printf "\n-= Building project_qt...=-\n"
qmake project_qt.pro && make

printf "\n-= Building project_txt...=-\n"
qmake project_txt.pro && make

printf "\n-= Building project_test...=-\n"
qmake project_test.pro && make

printf "\n-= Finished building all files =-\n\n"
