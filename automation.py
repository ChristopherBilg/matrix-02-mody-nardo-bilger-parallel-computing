#!/usr/bin/env python3

import os
import csv

pre_cmd = "time "
basic_cmd = "./basic_matrix_multiplication "
simd_cmd = "./basic_simd_multiplication "
openmp_cmd = "./openmp_matrix_multiplication "

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

basic = {}
simd = {}
openmp = {}

for file in os.listdir(file_dir):
	with open(file_dir + file) as current_file:
		for line in current_file:
			if "user" in line:
				time = line.split("user", 1)[0]
				time = float(time)

				print(file + ": " + str(time))
				if "basic" in file:
					number = file[6:]
					number = number.split(".", 1)[0]
					number = int(number)
					basic[number] = time
				if "simd" in file:
					number = file[5:]
					number = number.split(".", 1)[0]
					number = int(number)
					simd[number] = time
				if "openmp" in file:
					number = file[7:]
					number = number.split(".", 1)[0]
					number = int(number)
					openmp[number] = time

print(basic)
print(simd)
print(openmp)

csv_file = "basic.csv"
with open(csv_file, "w+") as csvfile:
	writer = csv.writer(csvfile)
	for k in sorted(basic.keys()):
		writer.writerow([k, basic[k]])

csv_file = "simd.csv"
with open(csv_file, "w+") as csvfile:
	writer = csv.writer(csvfile)
	for k in sorted(simd.keys()):
		writer.writerow([k, simd[k]])

csv_file = "openmp.csv"
with open(csv_file, "w+") as csvfile:
	writer = csv.writer(csvfile)
	for k in sorted(openmp.keys()):
		writer.writerow([k, openmp[k]])

gnuplot_cmd = "gnuplot gnuplot"
os.system(gnuplot_cmd)

os.system("./extraction_auto")
