
import os
import argparse
import subprocess
import shutil
import platform


def write_file(path, content):
    # Create directory if not exists
    directory = os.path.dirname(path)
    if not os.path.exists(directory):
        os.makedirs(directory)

    # Write to the file
    with open(path, 'w') as file:
        file.write(content)


def open_clion():
    # Get the path of this script
    script_path = os.path.realpath(__file__)
    # Get the project root directory (assuming the script is in /project_root/scripts/)
    project_root = os.path.dirname(os.path.dirname(os.path.dirname(script_path)))

    clion_exe_command_args = None
    if platform.system() == "Darwin":
        clion_exe_command_args = 'open -na "CLion.app"'
    elif os.nt():
        clion_exe_command_args = 'clion64.exe'

    if not clion_exe_command_args:
        raise Exception("CLion executable not found")

    # setup project dir
    project_dir = f"{project_root}/build/clion/ncpp"
    root_cmake_lists_path = f"{project_dir}/CMakeLists.txt"
    root_cmake_lists_content = '''
            cmake_minimum_required(VERSION 3.12)

            add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../../.." "${CMAKE_CURRENT_LIST_DIR}")
        '''
    write_file(
        root_cmake_lists_path, 
        root_cmake_lists_content
    )

    # open clion
    os.system(f'{clion_exe_command_args} "{project_dir}"')


if __name__ == "__main__":
    open_clion()