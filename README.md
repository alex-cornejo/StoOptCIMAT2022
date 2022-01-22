# CIMAT 2022: Stochasting Optimization

## Install cmake
```
sudo apt install cmake
```

## Compile program
```
cmake -DCMAKE_BUILD_TYPE=Release .
cmake --build .
```
The binary file will be generated onto the root folder with the name ```StoOpt```.

## Run
```
./StoOpt [input_file] [F] [seed] [output_file]
```

### Where,

| Parameter       | Description                                                      |
|-----------------|------------------------------------------------------------------|
| `[input_file]`  | (string) Instance file path with a valid format.                 |
| `[F]`           | (int) number of frecuency channels.                              |
 | `[seed]`        | (int) seed for random generation.                                |
| `[output_file]` | (string) File located in an existing folder to print the result. |

## Example 1
```
./StoOpt FAP08/GSM2-272.ctr 49 47 out1.txt
```
