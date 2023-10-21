# Memory Management

Having designed for game engine learning purposes, we focus on high performance and powerful debuggable allocators with special mechanism and functionalities.

---

## Memory Alignment
    To ensure optimal performance, we have implemented a flexible memory alignment strategy. It is designed to cater both customized and stardard memory alignment approach. 
        + For customized memory alignment, developers can specify their preferred alignment mechanism, allowing for fine-tuned control over memory allocation. This can be particularly useful in scenarios where a specific allocator implementation can align memory by a faster way.
        + On the other hand, our standard memory alignment approach is supported for all custom allocators but can be slower than the customized memory alignment when used with some allocators, such as our smart chunk allocator. For more technical details, it stores the raw allocated memory address as the memory allocation header before the aligned memory block (or before the allocation debug info with allocator name or memory counting is enabled). Despite being slower, it provides a reliable and consistent method for memory alignment that works across different scenarios.
        + Moreover, the memory alignment approach can be choosen at compiletime and won't take any branching cost.

---

## Memory Counting and Memory Debugging
    + **Memory counting**: NCPP has its own functionalities and flexible approach for parallel memory counting.
    + **Debug info**: stores the info of allocator name, memory size, etc, and is embedded before the allocated memory block if the allocator name or memory counting is enabled.

---

## Chunk Based Allocators
    