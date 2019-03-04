#What is this
This application is simple logical to physical address translator, as in the x86-64 architecture in long mode.
Page size is 4 kB.
Not filled physical memory defined as zero.
Each physical cell contains 64 bit value.
Each address has 64 bit unsigned value.

#Abbreviations
paddr - physical address
laddr - logical address

m - number of paddr-value pairs have to be stored
q - number of laddr queries
r - CM3 value (see Intel x64 mode paging (long mode))

#How to use

```
mkdir build
cd build
cmake ..
cmake --build .
./App < <input file>
```

#Input file format
m q r
paddr[1] value[1]
...
paddr[m] value[m]
laddr[1]
...
laddr[q]
