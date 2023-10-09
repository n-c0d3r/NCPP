# NCPP
NCoder's Game Engine Learning Aimed C++ Library

## Features
+ Memory management:
  + Incremental chunk allocator
  + Smart chunk allocator
  + Link allocator
  + Memory helper for aligned memory allocating
+ Logging:
  + eastl::basic_string
  + eastl::vector
  + eastl::array
  + std::initialier_list
+ Utilities:
  + Nth template argument getter
  + Function traits
  + Is derived from checker
  + Is streamable
  + Singleton
  + ...
+ RTTI:
  + Easy to use
  + No memory cost on reflected object
  + Metadata supports 
  + Flexible
  + Highly customizable

## Core Dependencies
+ EASTL
+ Doxygen (Optional)

## Supported Platforms
  + Windows
  + MacOS
  + Unix Platforms

## Building
  + Windows + Visual Studio 2022:
    + Step 1: Clone [NCPP git repository](https://github.com/n-c0d3r/ncpp) from GitHub
    + Step 2: Generate Visual Studio 2022 solution by running **scripts/generate_vs2022.bat**
    + Step 3: Navigate to **build/vs2022**
    + Step 4: Open **npp.sln**
    + Step 5: Set **ncpp.samples.firt_sample** as startup project
    + Step 6: Run and enjoy!
  + MacOS + Xcode:
    + Step 1: Clone [NCPP git repository](https://github.com/n-c0d3r/ncpp) from GitHub
    + Step 2: Generate Xcode solution by running **scripts/generate_xcode.sh**
    + Step 3: Navigate to **build/xcode**
    + Step 4: Open **ncpp.xcodeproj**
    + Step 5: Choose **ncpp.samples.firt_sample** for current scheme
    + Step 6: Run and enjoy!
  + Unix makefiles:
    + Step 1: Clone [NCPP git repository](https://github.com/n-c0d3r/ncpp) from GitHub
    + Step 2: Generate makefiles by running **scripts/generate_unix_makefiles.sh**
    + Step 3: execute **scripts/build_unix_makefiles.sh** to build project
    + Step 4: Navigate to **build/unix_makefiles/ncpp/samples/hello_ncpp**
    + Step 5: Run "ncpp.samples.hello_ncpp" and enjoy!

## License
+ NCPP is licensed under the [MIT license](https://github.com/n-c0d3r/NCPP/blob/main/LICENSE)
