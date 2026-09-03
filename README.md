# URL File Wizard

## Overview

URL File Wizard is a modular C++17 command-line application designed to create custom Windows `.url` internet shortcuts cleanly and efficiently. It features a color-coded CLI interface, smart domain-to-name parsing, shell icon assignment, and interactive input verification.

Built for users looking to organize web links locally on their filesystem rather than clogging browser bookmark spaces, URL File Wizard streamlines shortcut creation and remembers your recent destination folders across sessions.

## Features

- **Smart Domain Parsing:** Automatically extracts and formats clean website names from URLs.
- **ANSI Color Output:** Color-coded console output for intuitive visual feedback.
- **Persistent History:** Automatically saves destination history to `%LOCALAPPDATA%\URLFileWizard\history.txt`.
- **Quick-Select Menu:** Interactive selection for your 5 most recent export locations.
- **Shell Icon Integration:** Custom Windows shortcut icons assigned via `shell32.dll`.
- **Space Handling:** Full support for file paths and custom website names containing spaces.
- **Custom Branding:** Set console tab title dynamically using native Win32 APIs.

## Requirements

- **OS:** Windows 10 or Windows 11
- **Compiler:** MSVC (`cl.exe`) with C++17 support *(only required if building from source)*

## Installation & Building

### Running the Prebuilt Executable
1. Download the latest release from the **Releases** section.
2. Run `URL_File_Wizard.exe`.

### Compiling from Source
1. Open the **Developer Command Prompt x64 for Visual Studio**.
2. Navigate to the folder containing your source code and resources.
3. Build using `cl.exe` with C++17 mode enabled:

```cmd
cl /std:c++17 Exec_Link_Source.cpp resource.res shell32.lib
