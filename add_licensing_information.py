import os

g_license_text: str = """
/*
 * Copyright (C) 2024  David Woodward
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
"""

def add_license(file_path: str) -> None:
    with open(file_path, 'r') as file:
        content = file.read()

    with open(file_path, 'w') as file:
        file.write(g_license_text + '\n\n' + content)


def main() -> None:
    cwd: str = os.getcwd()

    for root, _, files in os.walk(cwd):
        for file in files:
            if file.endswith(('.cpp', '.h')):
                file_path: str = os.path.join(root, file)
                add_license(file_path)
                print(f"Licensing text added to {file_path}")


if __name__ == "__main__":
    main()
