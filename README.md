
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
  + ...
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
+ EASTL
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

## Documentations
+ NCPP has 2 documentations pages:
  + [External Documentations](https://n-c0d3r.github.io/project_docs/ncpp/external/ncpp/html) :
    + Hide private members.
    + For who just want to use ncpp.
  + [Internal Documentations](https://n-c0d3r.github.io/project_docs/ncpp/internal/ncpp/html) :
    + Show private members.
    + For who want to use ncpp or contribute to ncpp project.

## License
+ NCPP is licensed under the [MIT license](https://github.com/n-c0d3r/NCPP/blob/main/LICENSE)
