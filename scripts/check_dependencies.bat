@echo off

set SOURCE_DIR=%0\..\..\
set CMAKE_DIR=%SOURCE_DIR%\cmake



cmake -S %SOURCE_DIR% -P %CMAKE_DIR%/NCPP/CheckDependencies.cmake