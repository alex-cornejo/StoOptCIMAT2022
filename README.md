# CIMAT 2022: Stochasting Optimization

## Install c++ boost libraries
```
sudo apt install libboost-all-dev
```


## Install cmake
```
sudo apt install cmake
```

## Remove cache file (if exists)
```
rm CMakeCache.txt
```

## Compile program
```
cmake -DCMAKE_BUILD_TYPE=Release .
cmake --build .
```
The binary file will be generated onto the root folder with the name ```StoOpt```.

## Run
```
./StoOpt [input_file] [F] [seed] [output_file] [construction] [localsearch] [restart]
```

### Where,

| Parameter        | Description                                                                                |
|------------------|--------------------------------------------------------------------------------------------|
| `[input_file]`   | (string) Instance file path with a valid format.                                           |
| `[F]`            | (int) number of frecuency channels.                                                        |
 | `[seed]`         | (int) seed for random generation.                                                          |
| `[output_file]`  | (string) File located in an existing folder to print the result.                           |
| `[construction]` | (string) Method to create initial solution ('random' or 'HEDGE').                          |
| `[localsearch]`  | (string) Local search method to be used ('swap' or 'circular').                            |
| `[restart]`      | (bool) 'true' to create a new solution during one hour everytime a local optimal is reach. |

## Example 1
```
./StoOpt FAP08/GSM2-272.ctr 49 47 LSB/F49/out1.txt
```
