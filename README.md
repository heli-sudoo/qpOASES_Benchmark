Set the path to the qpOASES library using the environment variable, which should be the directory containing
`libqpOASES.a`

```
export QPOASES_LIB_PATH = DIR_TO_QPOASES_LIB
export QPOASES_INCLUDE = INCLUDE_DIR_TO_QPOASES
```

Edit the line below to point to your file:
https://github.com/heli-sudoo/qpOASES_Benchmark/blob/2da997bb5242d203d5328edb15e28b93c7a06211/time_benchmark.cpp#L18


Build and compile

```
mkdir build && cd build
cmake ..
make -j
```

Run

```
./time_benchmark
```

| Platform | Mean (ms) | Min (ms) | Max (ms) | Std (ms) |
| ----------- | ----------- | --- | -------|---|
| ThinkPat X1 2020 | 0.043 | 0.041 |0.070 |0.002 
| Lab Desktop | 0.072 | 0.066 | 0.1 | 0.007
| MC UpBoard |  | 