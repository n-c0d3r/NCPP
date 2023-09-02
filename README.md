# NCPP
A Game Engine Learning Aimed C++ Library

## Features
+ Memory management:
  + Chunk allocator
  + Link allocator
+ Logging:
  + eastl::basic_string
  + eastl::vector
  + eastl::array
  + std::initialier_list
  + reflected object
+ Utilities:
  + First template argument getter
  + Function traits
  + Is derived from checker
  + Left value reference wrapper
  + Templated for loop
  + ...
+ RTTI:
  + Easy to use
  + No object memory cost
  + Metadata supports 
  + Flexible

## Core Dependencies
+ EASTL (Not required)
+ Doxygen

## Getting Started
### Requirements:
  + Windows:
    + Visual Studio 2022 with essential C++, SDK Installation
    + CMake
    + Doxygen
    + C++ 17 or later
  + Unix Platforms:
    + CMake
    + Doxygen
    + C++ 17 or later
### Building:
  + Windows:
    + Step 1: Clone [NCPP git repository](https://github.com/n-c0d3r/ncpp) from GitHub
    + Step 2: Check for submodules by running **scripts/check_submodules.bat**
    + Step 3: Generate Visual Studio 2022 solution by running **scripts/generate_vs2022.bat**
    + Step 4: Navigate to **build/vs2022**
    + Step 5: Open **npp.sln**
    + Step 6: Set **ncpp.samples.firt_sample** as startup project
    + Step 7: Run and enjoy!
  + Unix:
    + Step 1: Clone [NCPP git repository](https://github.com/n-c0d3r/ncpp) from GitHub
    + Step 2: Check for submodules by running **scripts/check_submodules.sh**
    + Step 3: Generate makefiles by running **scripts/generate_unix_makefiles.sh**
    + Step 4: execute **scripts/build_unix_makefiles.sh** to build project
    + Step 5: Navigate to **build/unix_makefiles/ncpp/tests/hello_ncpp**
    + Step 6: Run "ncpp.tests.hello_ncpp" and enjoy!

## License
+ NCPP is licensed under the [MIT license](https://github.com/n-c0d3r/NCPP/blob/main/LICENSE)
