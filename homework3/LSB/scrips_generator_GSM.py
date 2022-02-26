import os

rep = 50
constructors = ["random"]
localsearch = ["doubletrx"]

# instance = 'GSM2-184'
# F = [39, 49, 52]

# instance = 'GSM2-227'
# F = [29, 39, 49]

instance = 'GSM2-272'
F = [34, 39, 49]

runnable = '/home/est_posgrado_alexcornejo/StoOpt/StoOpt'
path_instance = '/home/est_posgrado_alexcornejo/StoOpt/FAP08/'

idx_slurm = 1
for c in F:
    for constructor in constructors:
        for search in localsearch:
            for seed in range(1, rep + 1):
                output = ' /home/est_posgrado_alexcornejo/StoOpt/homework3/'
                output += instance + '/F' + str(c) + '_' + constructor + '_' + search + '/output' + str(
                    seed) + '.txt ' + str(constructor) + ' ' + search + ' false true'
                task = runnable + ' ' + path_instance + instance + '.ctr ' + str(c) + ' ' + str(seed) + output
                # print(task)

                file_task = instance + '/F' + str(c) + '_' + constructor + '_' + search + '/tasks.txt'

                os.makedirs(os.path.dirname(file_task), exist_ok=True)
                with open(file_task, "a") as file:
                    file.write(task + '\n')

            # create slurm file
            slurm_target = instance + '/F' + str(c) + '_' + constructor + '_' + search + '/tasks.txt'
            slurm_scrip = 'slurm/{}_slurm_{}'.format(instance, idx_slurm)
            idx_slurm += 1
            print(slurm_scrip)
            # opening the file in read mode
            file = open("slurm_master", "r")
            replacement = ""
            # using the for loop
            for line in file:
                line = line.strip()
                if line.startswith("Tasks"):
                    line = "Tasks=/home/est_posgrado_alexcornejo/StoOpt/homework3/" + slurm_target
                replacement = replacement + line + "\n"

            file.close()
            # opening the file in write mode
            os.makedirs(os.path.dirname(slurm_scrip), exist_ok=True)
            fout = open(slurm_scrip, "w")
            fout.write(replacement)
            fout.close()
