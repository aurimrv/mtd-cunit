# System Configuration

Experiment was carried out in a AVELL A70 MOB notebook:

## Linux Version and System Information

```
System:
  Kernel: 6.8.0-88-generic arch: x86_64 bits: 64 compiler: gcc v: 13.3.0 clocksource: tsc
  Desktop: Cinnamon v: 6.4.8 tk: GTK v: 3.24.41 wm: Muffin v: 6.4.1 vt: 7 dm: LightDM v: 1.30.0
    Distro: Linux Mint 22.2 Zara base: Ubuntu 24.04 noble
Machine:
  Type: Laptop System: Avell High Performance product: A70 MOB v: Standard
    part-nu: A70 MOB uuid: <superuser required> UEFI: American Megatrends LLC. v: N.1.07AVE00
    date: 07/23/2021
CPU:
  Info: 8-core model: 11th Gen Intel Core i7-11800H bits: 64 type: MT MCP smt: enabled
    arch: Tiger Lake rev: 1 cache: L1: 640 KiB L2: 10 MiB L3: 24 MiB
  Speed (MHz): avg: 1136 high: 1400 min/max: 800/4600 cores: 1: 1400 2: 974 3: 800 4: 1385
Graphics:
  Device-1: Intel TigerLake-H GT1 [UHD Graphics] vendor: Tongfang Hongkong driver: i915 v: kernel
  Device-2: NVIDIA GA106M [GeForce RTX 3060 Mobile / Max-Q] vendor: Tongfang Hongkong
    driver: nvidia v: 555.42.06 arch: Ampere pcie: speed: 16 GT/s lanes: 16 ports: active: none
```

## GNU Compiler Version

```
$ gcc -v
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/libexec/gcc/x86_64-linux-gnu/13/lto-wrapper
OFFLOAD_TARGET_NAMES=nvptx-none:amdgcn-amdhsa
OFFLOAD_TARGET_DEFAULT=1
Target: x86_64-linux-gnu
Configured with: ../src/configure -v --with-pkgversion='Ubuntu 13.3.0-6ubuntu2~24.04' --with-bugurl=file:///usr/share/doc/gcc-13/README.Bugs --enable-languages=c,ada,c++,go,d,fortran,objc,obj-c++,m2 --prefix=/usr --with-gcc-major-version-only --program-suffix=-13 --program-prefix=x86_64-linux-gnu- --enable-shared --enable-linker-build-id --libexecdir=/usr/libexec --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --enable-bootstrap --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=new --enable-libstdcxx-backtrace --enable-gnu-unique-object --disable-vtable-verify --enable-plugin --enable-default-pie --with-system-zlib --enable-libphobos-checking=release --with-target-system-zlib=auto --enable-objc-gc=auto --enable-multiarch --disable-werror --enable-cet --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --enable-multilib --with-tune=generic --enable-offload-targets=nvptx-none=/build/gcc-13-fG75Ri/gcc-13-13.3.0/debian/tmp-nvptx/usr,amdgcn-amdhsa=/build/gcc-13-fG75Ri/gcc-13-13.3.0/debian/tmp-gcn/usr --enable-offload-defaulted --without-cuda-driver --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu --with-build-config=bootstrap-lto-lean --enable-link-serialization=2
Thread model: posix
Supported LTO compression algorithms: zlib zstd
gcc version 13.3.0 (Ubuntu 13.3.0-6ubuntu2~24.04) 
```


## ProteumIM Version 1.2

## Pre-requirements for using ProteumIM

```
sudo apt install build-essential libncurses5-dev fakeroot xz-utils libelf-dev bison flex dwarves tcl tk csh gcc-multilib
```

## Installation

```
mkdir $HOME/tools
cd $HOME/tools
tar zxvf ProteumIM64.tgz
```

After that edit you `$HOME/.bashrc` file and includes the following lines:

```
export PROTEUMIMHOME=$HOME/tools/ProteumIM64/bin 
export PATH=$PATH:PROTEUMIMHOME
```