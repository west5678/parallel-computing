set(CMAKE_CXX_COMPILER "/opt/apps/intel16/cray_mpich/7.3.0/bin/mpicxx")
set(CMAKE_CXX_COMPILER_ARG1 "")
set(CMAKE_CXX_COMPILER_ID "Intel")
set(CMAKE_CXX_COMPILER_VERSION "16.0.1.20151021")
set(CMAKE_CXX_STANDARD_COMPUTED_DEFAULT "98")
set(CMAKE_CXX_COMPILE_FEATURES "")
set(CMAKE_CXX98_COMPILE_FEATURES "")
set(CMAKE_CXX11_COMPILE_FEATURES "")
set(CMAKE_CXX14_COMPILE_FEATURES "")

set(CMAKE_CXX_PLATFORM_ID "Linux")
set(CMAKE_CXX_SIMULATE_ID "")
set(CMAKE_CXX_SIMULATE_VERSION "")

set(CMAKE_AR "/opt/apps/gcc/4.9.3/bin/ar")
set(CMAKE_RANLIB "/opt/apps/gcc/4.9.3/bin/ranlib")
set(CMAKE_LINKER "/opt/apps/gcc/4.9.3/bin/ld")
set(CMAKE_COMPILER_IS_GNUCXX )
set(CMAKE_CXX_COMPILER_LOADED 1)
set(CMAKE_CXX_COMPILER_WORKS TRUE)
set(CMAKE_CXX_ABI_COMPILED TRUE)
set(CMAKE_COMPILER_IS_MINGW )
set(CMAKE_COMPILER_IS_CYGWIN )
if(CMAKE_COMPILER_IS_CYGWIN)
  set(CYGWIN 1)
  set(UNIX 1)
endif()

set(CMAKE_CXX_COMPILER_ENV_VAR "CXX")

if(CMAKE_COMPILER_IS_MINGW)
  set(MINGW 1)
endif()
set(CMAKE_CXX_COMPILER_ID_RUN 1)
set(CMAKE_CXX_IGNORE_EXTENSIONS inl;h;hpp;HPP;H;o;O;obj;OBJ;def;DEF;rc;RC)
set(CMAKE_CXX_SOURCE_FILE_EXTENSIONS C;M;c++;cc;cpp;cxx;mm;CPP)
set(CMAKE_CXX_LINKER_PREFERENCE 30)
set(CMAKE_CXX_LINKER_PREFERENCE_PROPAGATES 1)

# Save compiler ABI information.
set(CMAKE_CXX_SIZEOF_DATA_PTR "8")
set(CMAKE_CXX_COMPILER_ABI "ELF")
set(CMAKE_CXX_LIBRARY_ARCHITECTURE "")

if(CMAKE_CXX_SIZEOF_DATA_PTR)
  set(CMAKE_SIZEOF_VOID_P "${CMAKE_CXX_SIZEOF_DATA_PTR}")
endif()

if(CMAKE_CXX_COMPILER_ABI)
  set(CMAKE_INTERNAL_PLATFORM_ABI "${CMAKE_CXX_COMPILER_ABI}")
endif()

if(CMAKE_CXX_LIBRARY_ARCHITECTURE)
  set(CMAKE_LIBRARY_ARCHITECTURE "")
endif()

set(CMAKE_CXX_CL_SHOWINCLUDES_PREFIX "")
if(CMAKE_CXX_CL_SHOWINCLUDES_PREFIX)
  set(CMAKE_CL_SHOWINCLUDES_PREFIX "${CMAKE_CXX_CL_SHOWINCLUDES_PREFIX}")
endif()




set(CMAKE_CXX_IMPLICIT_LINK_LIBRARIES "dl;mpichcxx_intel;mpich_intel;rt;ugni;pmi;dl;xpmem;pthread;udreg;imf;svml;irng;m;ipgo;decimal;cilkrts;stdc++;irc;svml;c;irc_s;dl;c")
set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES "/opt/cray/xpmem/default/lib64;/opt/cray/ugni/default/lib64;/opt/cray/udreg/default/lib64;/opt/cray/pmi/default/lib64;/opt/cray/dmapp/default/lib64;/opt/cray/mpt/7.3.0/gni/mpich-intel/14.0/lib;/opt/apps/intel/16.0.1.150/compilers_and_libraries_2016.1.150/linux/compiler/lib/intel64_lin;/opt/apps/intel/16.0.1.150/compilers_and_libraries_2016.1.150/linux/tbb/lib/intel64_lin/gcc4.4;/opt/apps/intel/16.0.1.150/compilers_and_libraries_2016.1.150/linux/daal/lib/intel64_lin;/opt/apps/intel/16.0.1.150/compilers_and_libraries_2016.1.150/linux/tbb/lib/intel64/gcc4.1;/opt/apps/intel/16.0.1.150/compilers_and_libraries_2016.1.150/linux/mkl/lib/intel64;/opt/apps/intel/16.0.1.150/compilers_and_libraries_2016.1.150/linux/compiler/lib/intel64;/opt/apps/intel/16.0.1.150/compilers_and_libraries_2016.1.150/linux/ipp/lib/intel64;/opt/apps/gcc/4.9.3/lib/gcc/x86_64-unknown-linux-gnu/4.9.3;/opt/apps/gcc/4.9.3/lib64;/lib64;/usr/lib64;/opt/apps/gcc/4.9.3/x86_64-unknown-linux-gnu/lib;/opt/apps/gcc/4.9.3/lib;/lib;/usr/lib")
set(CMAKE_CXX_IMPLICIT_LINK_FRAMEWORK_DIRECTORIES "")
