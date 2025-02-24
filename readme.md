# C++ and Rust interoperability

Make a Rust-Library available in C++

Following the ideas in [optik](https://github.com/kylc/optik/tree/master/crates/optik-cpp)


## Todo



## Building
- Configure `cmake -S . -B build`
- Configure for release `cmake -S . -B build -DCMAKE_BUILD_TYPE=Release`
- Build `cmake --build build`
  - Run Unit Tests `cmake --build build --target <test-target>`, `<test-target>` is e.g. `person-cpp-test`


## Cross Compilation

Cross compilation can be a tricky endeavour. Follwow this guide to cross compile this project for a Raspberry Pi 3 running Debian "Bullseye"

### Toolchain Build

Gather information of the target system. Run this on your target platform.
- `cat /etc/os-release` to get OS information
- `uname -srm` to get Kernel and CPU architecture information
- `ldd --version` to find the version of GLIBC

A sensible way to get a cross build toolchain is using crosstool-NG. It offers a lot of configuration options to match your target system well.

Install crosstool-NG following the [instructions](https://crosstool-ng.github.io/docs/)

Configuring the Toolchain (based on a sample)
- `ct-ng list-samples` and pick your sample (here `aarch64-unknown-linux-gnu`)
- `ct-ng aarch64-unknown-linux-gnu` to build base configuration
- `ct-ng menuconfig` to adapt compiler, GLIBC version, etc. This is important, the base config gives the latest compiler, libraries, etc.
- `ct-ng build` to build the toolchain. It is likely placed in `${HOME}/x-tools/aarch64-rpi3-linux-gnu/`
  - add the toolchain to your path `PATH=$PATH:~/x-tools/aarch64-rpi4-linux-gnu/bin` (to `.bashrc` to make it persistent)

Install the right rust cross compiler with `rustup target add aarch64-unknown-linux-gnu`

### Cross Compilation

- Pass the toolchain file for manual configuration: `cmake -S . -B build_target -DCMAKE_TOOLCHAIN_FILE=aarch64-unknown-linux-gnu.cmake`
- Build `cmake --build build_target`


### Running the binary on target
- Copy the binary to a running Raspberry Pi using scp: `scp <binary> pi@<IP>:/home/pi`
- SSH into target and run the binary


- `sudo apt-get install gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf crossbuild-essential-armhf`
- `rustup target add armv7-unknown-linux-gnueabihf`
