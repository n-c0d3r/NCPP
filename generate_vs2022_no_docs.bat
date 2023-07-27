@echo off

if not exist %0\..\build\vs2022 (
    rem
    mkdir %0\..\build\vs2022
)

cmake -G "Visual Studio 17 2022" -S %0\.. -B %0\..\build\vs2022 -D NCPP_GENERATE_DOCS=OFF