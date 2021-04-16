#!/bin/bash

# compile the cfind.c file from Makefile instructions
make

# find command with directory 
./cfind testdir > log/out_dir.txt

# find command with directory and -n flag
./cfind testdir -n "test7" > log/out_name_flag.txt

# find command with directory and -inum flag
./cfind testdir -inum 43302 > log/out_inum_flag.txt

# find command with directory and negative -mmin flag
./cfind testdir -mmin -10 > log/out_mmin_neg_flag.txt

# find command with directory and positive -mmin flag
./cfind testdir -mmin +10 > log/out_mmin_pos_flag.txt

# find command with directory and neutral -mmin flag
./cfind testdir -mmin 10 > log/out_mmin_neutral_flag.txt
