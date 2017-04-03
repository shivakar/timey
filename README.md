### Timey

`Timey` provides a convenient wrapper around `chrono` for timing computations
using named timers.


### Installation

`Timey` needs the following dependencies to be satisfied:

* CMake >= 3.0
* C++11 compiler

By default, the installation script below installs to the global location:
`/opt/apps/timey/<timey-version>`

```
mkdir -p ~/Projects/dandelion
cd ~/Projects/dandelion
git clone ssh://git@repos.cogizo.com:7999/dan/timey.git
mkdir build
cd build
cmake ..
make
make test
sudo make install
```

