
include(NCPP/SetGlobal)



if(MSVC)
    NCPP_SetGlobal(NCPP_COMPILER_FLAG_SSE "-msse")
    NCPP_SetGlobal(NCPP_COMPILER_FLAG_AVX "-mavx")
    NCPP_SetGlobal(NCPP_COMPILER_FLAG_AVX2 "-mavx2")
    NCPP_SetGlobal(NCPP_COMPILER_FLAG_ARM_NEON "-mfpu=neon")
else()
    NCPP_SetGlobal(NCPP_COMPILER_FLAG_SSE "/arch:SSE")
    NCPP_SetGlobal(NCPP_COMPILER_FLAG_AVX "/arch:AVX")
    NCPP_SetGlobal(NCPP_COMPILER_FLAG_AVX2 "/arch:AVX2")
    NCPP_SetGlobal(NCPP_COMPILER_FLAG_ARM_NEON "")
endif()