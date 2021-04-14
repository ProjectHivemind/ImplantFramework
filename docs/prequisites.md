## Prerequisites

### Windows

#### Boost
Boost setup required for Windows

Download from [here](https://www.boost.org/users/history/version_1_75_0.html) and extract boost to your desired location. 
The project currently assumes it's in `C:\boost_1_75_0\boost_1_75_0` but this can be changed.

Bootstrap and build boost.
```
cd C:\boost_1_75_0\boost_1_75_0
.\bootstrap
.\b2.exe variant=debug link=static threading=multi runtime-link=static
.\b2.exe variant=release link=static threading=multi runtime-link=static
```

#### Buildchain
* MSVC/cmake/make
    * Install by following the documentation found [here](https://visualstudio.microsoft.com/vs/features/cplusplus/). 
This will also install cmake and make for you. 

### Linux
#### Boost
Install boost development libraries through your package manager.

For example on ubuntu:
```bash
apt-get install -y libboost-all-dev 
```

#### Buildchain
Install all of these through your package manager
* GCC/G++ version 8 or higher
* cmake 
* make

For example on Ubuntu:
```bash
apt-get install -y gdb clang cmake doxygen
```





