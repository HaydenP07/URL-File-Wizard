URL File Wizard
Overview
URL File Wizard is a modular C++17 command-line application designed to create custom Windows .url internet shortcuts cleanly and efficiently. It features a color-coded CLI interface, smart domain-to-name parsing, shell icon assignment, and interactive input verification.

Built for users looking to organize web links locally on their filesystem rather than clogging browser bookmark spaces, URL File Wizard streamlines shortcut creation and remembers your recent destination folders across sessions.

Features
Smart URL domain parsing to automatically generate clean shortcut names

Color-coded ANSI terminal output for intuitive user feedback

Persistent destination history tracking stored safely in %LOCALAPPDATA%

Quick-select menu for your 5 most recent export locations

Custom Windows shell icon integration via shell32.dll

Robust input handling supporting file paths and names containing spaces

Custom console window title branding

Requirements
Windows 10 or 11 operating system

MSVC compiler (cl.exe) supporting C++17 or later (required only if compiling from source)

Installation & Building
Running the Prebuilt Executable
Download the latest release from the GitHub Releases page.

Extract the downloaded archive.

Run URL_File_Wizard.exe.

Compiling from Source
Open the Developer Command Prompt for Visual Studio.

Navigate to the project directory containing your source files and resources.

Compile using MSVC with C++17 enabled:

DOS
cl /std:c++17 Exec_Link_Source.cpp resource.res shell32.lib
Usage
Launch URL_File_Wizard.exe.

Paste the target website URL when prompted.

Review the automatically generated website name and enter yes, link, or name to make corrections.

Select a recent export folder by typing its number (1–5) or paste a new file path.

The wizard will create your formatted .url shortcut in the selected destination.

Screenshots
Add screenshots of the CLI interface here.

Download
The latest version of URL File Wizard can be found under the Releases section of this repository.

Only downloads from the official GitHub repository are authorized.

License
URL File Wizard is created by Hayden Price.

Distributed under the included license terms. See LICENSE.txt for full details.
