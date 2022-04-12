Configuration:

First time:
cd lib
git clone https://github.com/google/googletest.git

cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" 

Then in build:
make all