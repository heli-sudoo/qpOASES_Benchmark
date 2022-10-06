Set the path to the qpOASES library using the environment variable, which should be the directory containing
`libqoases.a`

```
export QPOASES_LIB_PATH = DIR_TO_QPOASES_LIB
```

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
