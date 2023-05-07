# **NCPP**
A Game Engine Learning Aimed C++ Library

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

## **Documentations**
+ NCPP has 2 documentations pages:
  + [External Documentations](https://n-c0d3r.github.io/project_docs/ncpp/external/ncpp/html) :
    + Hide private members.
    + For who just want to use ncpp.
  + [Internal Documentations](https://n-c0d3r.github.io/project_docs/ncpp/internal/ncpp/html) :
    + Show private members.
    + For who want to use ncpp or contribute to ncpp project.