<img src="https://i.ibb.co/VxJhd4b/BG4-wide-0-25x.png" border="0" width="100%"/>

## **Features**
+ Memory management:
  + Native memory:
    + Tagged heap, tagged heap allocator
    + Stack heap, stack heap allocator
    + Pool heap, pool heap allocator
    + Aligned allocator (default native allocator)
    + Current runtime allocator
    + Memory counting (not supports crt_allocator)
      + Allocated memory counting
      + Used heap memory counting
+ Logging:
  + Vector
  + Handle map
+ Utilities:
  + First template argument getter
  + Function traits
  + Is derived from checker
  + Left value reference wrapper
  + Templated for loop
  + ...
+ Containers:
  + Fixed vector queue
  + Fixed vector stack
  + Concurrent fixed vector queue
  + Free list supported vector
  + Handle map
  + Native containers (std containers and ncpp containers)
+ PAC (parallelism and concurrency):
  + Thread (Windows platform only)
  + Fiber (Windows platform only)
  + Locks:
    + Spinlock
    + Nonelock
    + Weaklock
  + Semaphore
+ RTTI:
  + Object reflection:
    + Member variable reflection
    + Member function reflection
    + Member arguments
    + Class representation object

## **Getting Started**
### Requirements:
  + Windows (**only support Windows**):
    + CMake
    + Visual Studio 2022 with essential C++, SDK Installation
### Building:
  + Windows (**only support Windows**):
    + Step 1: Clone [NCPP git repository](https://github.com/n-c0d3r/ncpp) from GitHub
        ```
        git clone https://github.com/n-c0d3r/ncpp.git --recurse-submodules
        cd ncpp
        ```
        or
        ```
        git clone https://github.com/n-c0d3r/ncpp.git
        cd ncpp
        git submodule update --init --recursive
        ```
    + Step 2: Generate Visual Studio 2022 solution by running `generate_vs2022.bat`
    + Step 3: Navigate to `/build/vs2022`
    + Step 4: Open `npp.sln`
    + Step 5: Set `ncpp.samples.firt_sample` as startup project
    + Step 6: Run and enjoy!

## **Documentations**
+ NCPP has 2 documentations pages:
  + [External Documentations](https://n-c0d3r.github.io/project_docs/ncpp/external/ncpp/html) :
    + Hide private members.
    + For who just want to use ncpp.
  + [Internal Documentations](https://n-c0d3r.github.io/project_docs/ncpp/internal/ncpp/html) :
    + Show private members.
    + For who want to use ncpp or contribute to ncpp project.

## **License**
+ NCPP is licensed under the [MIT license](https://github.com/n-c0d3r/NCPP/blob/main/LICENSE)
