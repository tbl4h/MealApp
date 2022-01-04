Requre Conan manager or aproprieate steps listed below(Not tested). To install visit: https://conan.io/ 
In some cases you need to change remote repository in conan or set apropriate compiler standard:
    conan remote add conancenter https://center.conan.io --> to set new remote repository
    conan profile new default --detect --> to create default conan profile if not exist
    conan profile update settings.compiler.libcxx=libstdc++11 default --> to update ABI
To install GNU MPC --> BigNum library:
Download: https://gmplib.org/download/gmp/gmp-6.2.1.tar.xz
          https://www.mpfr.org/mpfr-current/mpfr-4.1.0.tar.xz
          https://ftp.gnu.org/gnu/mpc/mpc-1.2.1.tar.gz
Install in chronological order:
          tar xfv package-name
          cd package-name
          ./configure
          make
          make check
          sudo make install-recursive
If some test fails while installing mpfr lib use:
          sudo ldconfig --> to update cache for the linker  

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
For some reason to use mpc lib after downloading it by Conan is necessary to copy the definition's header into the headers directory and link them directly in CMakeList.txt
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Potentially should install hdf5 package manualy due to conan don't install them use:
    sudo apt-get install libhdf5-dev --> on linux(ubuntu) machine 
    download aproprieate file from: https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-1.13/hdf5-1.13.0/bin/windows/
To install:
1) mkdir build
2) cd build
3) conan install ..
4) cmake ..
5) make
6) Binary will be in ./build/bin directory

Second way - usng raw CMake - Not Tested yet
1) Uncoment aproprieate code in CMakeList.txt
2) mkdir build
3) cmake ..
4) make
