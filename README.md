<img src="https://i.ibb.co/VxJhd4b/BG4-wide-0-25x.png" border="0" width="100%"/>

## Features
+ Memory management:
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
+ Containers:
+ PAC (parallelism and concurrency):

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
      ```batch
      git clone https://github.com/n-c0d3r/ncpp.git --recurse-submodules
      cd ncpp
      ```
      or
      ```batch
      git clone https://github.com/n-c0d3r/ncpp.git
      cd ncpp
      git submodule update --init --recursive
      ```
    + Step 2: Generate Visual Studio 2022 solution by running **generate_vs2022.bat**
    + Step 3: Navigate to **path/to/your/ncpp/build/vs2022**
    + Step 4: Open **npp.sln**
    + Step 5: Set **ncpp.samples.firt_sample** as startup project
    + Step 6: Run and enjoy!

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
