import glob
import ntpath
import matplotlib.pyplot as plt
import statistics


def read_folder(folder):
    data = []
    folder = folder + "/*"
    all_files = glob.glob(folder)
    for file in all_files:
        basename = ntpath.basename(file)
        if basename.startswith("out"):
            f = open(file, "r")
            data.append(int(f.readline()))
            f.close()
    # print(data)
    return data


data_1 = read_folder("LSB/F34")
data_2 = read_folder("LSB/F39")
data_3 = read_folder("LSB/F49")
data = [data_1, data_2, data_3]

fig7, ax7 = plt.subplots()
ax7.set_title('Random solutions for GSM2-272')
ax7.set_xticklabels(['|F|=34', '|F|=39', '|F|=49'])
ax7.boxplot(data)

plt.show()


print('\ndata 1')
print("{:.1e}".format(max(data_1)))
print("{:.1e}".format(min(data_1)))
print("{:.1e}".format(statistics.mean(data_1)))
print("{:.1e}".format(statistics.stdev(data_1)))

print('data 2')
print("{:.1e}".format(max(data_2)))
print("{:.1e}".format(min(data_2)))
print("{:.1e}".format(statistics.mean(data_2)))
print("{:.1e}".format(statistics.stdev(data_2)))

print('data 3')
print("{:.1e}".format(max(data_3)))
print("{:.1e}".format(min(data_3)))
print("{:.1e}".format(statistics.mean(data_3)))
print("{:.1e}".format(statistics.stdev(data_3)))

