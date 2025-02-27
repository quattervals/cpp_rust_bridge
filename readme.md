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


## Bindings with CXX

Instead of manually implementing the C-ABI files (`lib.cpp`, `lib.rs`), we can generate the bindings using the CXX-Crate.
- [cxx documentation](https://cxx.rs)
- [cxx on GitHub](https://github.com/dtolnay/cxx)

The core is this ffi definition:
```rust
#[cxx::bridge(namespace = "prs")]
mod ffi {

    extern "Rust" {

        type Person;
        fn new_person(name: &str, zip: &str, dob: u32) -> Box<Person>;
        fn get_age(&self) -> u32;
        fn get_zip(&self) -> &str;
        fn update_zip(&mut self, zip: &str);

    }
}
```
The building of the ffi-bridge binary is taken care of by corrosion
```cmake
corrosion_add_cxxbridge(
  <bridge-target>
  CRATE
  <bridge-library>
  MANIFEST_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}
  FILES
  <lib-with-ffi-definitions.rs>)
```

### Advantage
- Only one point where bindings are defined.
- High level concepts like strings and smart pointers are possible

### Disadvantage
- The `person.rs` file needs to be in the same package as the ffi-Bridge. Otherwise, we need to write a wrapper or put the ffi definition together with the person to the person crate.
- Some ugly generated types show up in the C++ wrapper class (`::rust::Box<::prs::Person> _inner;`). But only in private fields. The interface exposed to the rest of the C++ project is free of generated types.
