import os

rep = 50
constructors = ["random"]
localsearch = ["doubletrx"]

N_opt = "true"
F = [25]
# instance = 'DSP-1000-2'
# instance = 'DSP-1000-4'
# instance = 'DSP-1000-8'
# instance = 'DSP-1000-16'
instance = 'DSP-1000-32'


runnable = '/home/est_posgrado_alexcornejo/StoOpt/StoOpt'
path_instance = '/home/est_posgrado_alexcornejo/StoOpt/homework3/DSP/'

idx_slurm = 1
for c in F:
    for constructor in constructors:
        for search in localsearch:
            for seed in range(1, rep + 1):
                output = ' /home/est_posgrado_alexcornejo/StoOpt/homework3/'
                output += instance + '/F' + str(c) + '_' + constructor + '_' + search + "_" + str(
                    N_opt) + '/output' + str(
                    seed) + '.txt ' + str(constructor) + ' ' + search + ' false ' + str(N_opt)
                task = runnable + ' ' + path_instance + instance + '.ctr ' + str(c) + ' ' + str(seed) + output
                # print(task)

                file_task = "{}/F{}_{}_{}_{}/tasks.txt".format(instance, c, constructor, search, N_opt)

                os.makedirs(os.path.dirname(file_task), exist_ok=True)
                with open(file_task, "a") as file:
                    file.write(task + '\n')

            # create slurm file
            slurm_target = instance + '/F' + str(c) + '_' + constructor + '_' + search + "_" + N_opt + '/tasks.txt'
            slurm_scrip = 'slurm/{}_{}_slurm_{}'.format(instance, N_opt,idx_slurm)
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
