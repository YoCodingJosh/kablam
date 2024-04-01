#!/usr/bin/env python3

import os
import shutil
import sys

def copy_directory(src_dir, dest_dir):
    try:
        shutil.copytree(src_dir, dest_dir)
        print(f"Directory '{src_dir}' copied to '{dest_dir}'")
    except FileExistsError:
        print(f"Error: Destination directory '{dest_dir}' already exists.")
        sys.exit(1)
    except shutil.Error as e:
        print(f"Error: {e}")
        sys.exit(1)
    except Exception as e:
        print(f"An unexpected error occurred: {e}")
        sys.exit(1)

def main():
    if len(sys.argv) != 3:
        print("Usage: python copy_dir_to_build.py <source_directory> <build_directory>")
        sys.exit(1)

    src_dir = sys.argv[1]
    dest_dir = sys.argv[2]

    if not os.path.exists(src_dir):
        print(f"Error: Source directory '{src_dir}' does not exist.")
        sys.exit(1)

    copy_directory(src_dir, dest_dir)

if __name__ == "__main__":
    main()

