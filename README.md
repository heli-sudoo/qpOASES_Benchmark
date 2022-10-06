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
