import glob
import ntpath
import statistics

from matplotlib import pyplot as plt


def read_folder(folder, rows=2):
    data = []
    for row in range(rows):
        data.append([])
    folder = folder + "/*"
    all_files = glob.glob(folder)
    for file in all_files:
        basename = ntpath.basename(file)
        if basename.startswith("out"):
            f = open(file, "r")
            for row in range(rows):
                data[row].append(int(f.readline()))
            f.close()
    # print(data)
    return data


F = [25]
instance = "DSP-1000-16"


N_opt = "true"
constructive_methods = ['random']
local_search_methods = ['doubletrx']

data = []
times = []

for constructive in constructive_methods:
    for local_search in local_search_methods:
        for Fi in F:
            folder_path = 'LSB/{}/F{}_{}_{}_{}'.format(instance, Fi, constructive, local_search, N_opt)

            data.append(read_folder(folder_path, 2)[0])
            times.append(read_folder(folder_path, 2)[1])

# fig7, ax7 = plt.subplots()
# ax7.set_title('Double change local search for {}'.format(instance))
# ax7.set_xticklabels(["|F|={}".format(F[0]), "|F|={}".format(F[1]), "|F|={}".format(F[2])])
# ax7.boxplot(data)
#
# plt.show()

print('\ndata 1')
print(min(data[0]))
print(statistics.mean(data[0]))
print(statistics.stdev(data[0]))
print(statistics.mean(times[0]) / 1000)

