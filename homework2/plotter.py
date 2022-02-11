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


F = 49
instance = 'GSM2-272'
constructive_methods = ['random', 'HEDGE']
local_search_methods = ['swap', 'circular']

data = []
times = []
times_greedy = []
labels = []
for constructive in constructive_methods:
    for local_search in local_search_methods:
        folder_path = 'homework2/{}/F{}_{}_{}'.format(instance, F, constructive, local_search)
        if constructive == 'HEDGE':
            data.append(read_folder(folder_path, 3)[0])
            times.append(read_folder(folder_path, 3)[1])
            times_greedy.append(read_folder(folder_path, 3)[2])
        else:
            data.append(read_folder(folder_path, 2)[0])
            times.append(read_folder(folder_path, 2)[1])
            times_greedy.append([])

        labels.append('{}_{}'.format(constructive, local_search))

# data = [data_1, data_2, data_3]
# for d in data:
#     d.remove(max(d))

fig7, ax7 = plt.subplots()
ax7.set_title('Local search for {} with |F|={}'.format(instance, F))
ax7.set_xticklabels(labels)
ax7.boxplot(data)

plt.show()

print('Local search for {} with |F|={}'.format(instance, F))
for i in range(0, len(labels)):

    print(labels[i])
    print("min fitness: {}".format(min(data[i])))
    print("mean fitness: {}".format(statistics.mean(data[i])))
    print("mean time: {}".format(statistics.mean(times[i])))
    print("max time: {}".format(max(times[i])))

    if 'HEDGE' in labels[i]:
        print("mean time greedy: {}".format(statistics.mean(times_greedy[i])))
        print("max time greedy: {}".format(max(times_greedy[i])))




