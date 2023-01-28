@echo off

if not exist .\build\vs2022 (
    rem
    mkdir .\build\vs2022
)

cmake -G "Visual Studio 17 2022" -S . -B build\vs2022