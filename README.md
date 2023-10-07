# Graph representations
In this project I implemented topological sort using multiple Graph representations.
[See report comparing pros and cons of each graph representation](https://github.com/BbqGamer/GraphAlgorithms/blob/master/report/Report_Graph_Algorithms.pdf)

## Configuration:
After cloning the repository you should also clone gtest which this project depends on:
```
cd lib
git clone https://github.com/google/googletest.git
```

Type this to generate Makefiles:
```
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" 
```

Built the project (being in build directory) with: 
```
make all
```
or if you want to run tests run this in root directory:
```
sh compileAndTest.sh
```
