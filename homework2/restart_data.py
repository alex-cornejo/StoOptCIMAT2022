import glob
import ntpath
import statistics

from matplotlib import pyplot as plt


def read_folder(file_path, rows=2):
    data = []
    for row in range(rows):
        data.append([])
    file_r = open(file_path, 'r')
    line = file_r.readline()
    while line != '':
        data[0].append(int(line))
        for row in range(1, rows):
            data[row].append(int(file_r.readline()))
        line = file_r.readline()
    file_r.close()
    return data


file_path = 'homework2/GSM2-272/F49_random_swap/restart_output.txt'
# file_path = 'homework2/GSM2-272/F49_HEDGE_swap/restart_output.txt'
data = read_folder(file_path, 2)
print(' ')
print(len(data[0]))
print("min fitness: {}".format(min(data[0])))
print("mean fitness: {}".format(statistics.mean(data[0])))
# print("mean time: {}".format(statistics.mean(times[i])))
# print("max time: {}".format(max(times[i])))
