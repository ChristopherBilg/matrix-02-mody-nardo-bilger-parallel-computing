#!/usr/bin/env python3

import os

pre_cmd = "time "
basic_cmd = "./basic_matrix_multiplication "
simd_cmd = "./basic_simd_multiplication "

file_dir = "automation_files/"
os.system("mkdir " + file_dir)

for i in range(100, 1001, 100):
	full_cmd = str(pre_cmd + basic_cmd + str(i) + " > " + file_dir + "basic_" + str(i) + ".txt 2>&1")
	print("Running: " + full_cmd)
	os.system(full_cmd)

	full_cmd = str(pre_cmd + simd_cmd + str(i) + " > " + file_dir + "simd_" + str(i) + ".txt 2>&1")
	print("Running: " + full_cmd)
	os.system(full_cmd)
