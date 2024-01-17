# Add licensing information to the top of every C++ source and header file.

import os

g_license_text: str = """/*
 * Copyright (C) 2024  David Woodward
 * SPDX-License-Identifier: GPL-3.0-or-later
 */"""


def add_license_comment(file_path: str) -> None:
    with open(file_path, 'r') as file:
        content = file.read()

    if content.startswith(g_license_text):
        return

    with open(file_path, 'w') as file:
        file.write(g_license_text + '\n\n' + content)

    print(f"Licensing information added to '{file_path}'")


def process_files(dir_path: str) -> None:
    for root, _, files in os.walk(dir_path):
        for file in files:
            if not file.endswith(('.cpp', '.h')):
                continue

            file_path: str = os.path.join(root, file)
            add_license_comment(file_path)


def main() -> None:
    src_path: str = os.path.join(os.getcwd(), "src")
    process_files(src_path)


if __name__ == "__main__":
    main()
