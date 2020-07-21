# Usage
```
$ mkdir build
$ cd build
```
If you want to use debug mode:
```
$ cmake -D CMAKE_BUILD_TYPE=Debug ..
```
Release mode:
```
$ cmake ..
```
Then make and run:
```
$ make
$ ./mgm 2 2
```
MGM parameters:  
`j` (first) - power of matrix size (n = 2^j + 1)  
`ncycle` (second) - V-cycle depth

# Show a plot
Use `gnuplot` to get a 3D plot:
```
$ ./mgm > ../data.dat
$ cd ..
$ gnuplot -p plot.plt
```
