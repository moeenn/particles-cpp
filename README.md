## Particles C++
A simple particles procedural animation build using C++ and SFML.


### Build from source

```bash
# install SFML dependency.
$ chmod +x ./scripts/install-sfml.sh
$ ./scripts/install-sfml.sh

# make release build.
$ mkdir build
$ cd ./build
$ cmake .. -D CMAKE_BUILD_TYPE=Release && make
```

**Note**: The compiled binary will be placed in `./build/` directory.


### Screenshot

![Screenshot](./screeshots/01.png "Screenshot")
