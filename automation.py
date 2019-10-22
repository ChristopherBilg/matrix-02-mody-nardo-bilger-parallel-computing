#!/usr/bin/env python3

import os

pre_cmd = "time "
basic_cmd = "./basic_matrix_multiplication "
simd_cmd = "./basic_simd_multiplication "
openmp_cmd = "./openmp_matrix_multiplication"

file_dir = "automation_files/"
os.system("mkdir " + file_dir)

for i in range(100, 1001, 100):
	cmd1 = str(pre_cmd + basic_cmd + str(i) + " > " + file_dir + "basic_" + str(i) + ".txt 2>&1")
	print("Running: " + cmd1)
	os.system(cmd1)

	cmd2 = str(pre_cmd + simd_cmd + str(i) + " > " + file_dir + "simd_" + str(i) + ".txt 2>&1")
	print("Running: " + cmd2)
	os.system(cmd2)

	cmd3 = str(pre_cmd + openmp_cmd + str(i) + " > " + file_dir + "openmp_" + str(i) + ".txt 2>&1")
	print("Running: " + cmd3)
	os.system(cmd3)
