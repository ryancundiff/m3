<div align=center>
  <img src=assets/logo.png />
  <h1>Minecraft Mods Manager (M3)</h1>
  <p>Unlike most managers, this one makes life easier.</p>

  <a href=https://github.com/ryancundiff/m3/releases>
    <img src=https://img.shields.io/github/v/release/ryancundiff/m3 />
  </a>
  <a href=https://github.com/ryancundiff/m3/blob/main/LICENSE>
    <img src=https://img.shields.io/github/license/ryancundiff/m3 />
  </a>
  <a href=https://github.com/ryancundiff/m3/issues>
    <img src=https://img.shields.io/github/issues/ryancundiff/m3 />
  </a>
  <img src=https://img.shields.io/github/repo-size/ryancundiff/m3 />
</div>

## Features
- Command-line interface (CLI) tool
- Manage mod *profiles*

## Installation

### Option 1: Download Prebuilt Binary (Windows)
Go to [Releases](https://github.com/ryancundiff/m3/releases) and download the `m3.exe` executable file.

#### Adding to Path
1. Copy the path to the directory your `m3.exe` file is located
2. Press `Win` + `X` and click `System`
3. Scroll down and click `Advanced system settings`
4. Click `Environment variables...` at the bottom of the menu
5. Find `Path` under either `User variables` or `System variables` (Depends on whether you want the m3 command to be for your user or all users on your system)
6. Click on `Path` and click `Edit`
7. Click `New` at the top right
8. Paste the directory you copied earlier
9. Click `OK` on the popout window and then click `OK` on the environment variables window
10. Close out your terminal and reopen it to use the command!

### Option 2: Build from Source (Linux/macOS/Windows)
If you want to build M3 yourself or run it on non-Windows platforms.

#### Prerequisites
- **CMake** 4.1.1+ (Older versions may work, but are untested)
- **C++17 Compiler**
  - **Windows**: MSVC 2019+ or MinGW
  - **Linux**: GCC 7+ or Clang 7+
  - **macOS**: Apple Clang 10+

#### Build Steps
**Windows**
1. Open project folder
2. Double-click `build.bat`
3. Binary will appear in `build\Release`

**Linux/macOS**
1. Open terminal in project folder
2. Run script ./build.sh
3. Binary will appear in `build/Release`

#### Adding to PATH (Linux/macOS)
1. Determine the path to your `build/Release` directory. For example:

```bash
/home/your-name/programs/m3/build/Release
```

2. Determine whether your system is <u>Bash</u> or <u>Zsh</u>. You can do this by running the following command:

```bash
echo $SHELL
```
3. This will output either `/bin/bash` or `/bin/zsh`
  - If it output `bash`, then you would run:

```bash
nano ~/.bashrc
```

- If it output `zsh`, then you would run:

```bash
nano ~/.zshrc
```

- This command will open your shell configuration file.

4. Add the following line to the end of the file (replace `/path/to/m3/build/Release` with the actual path):

```bash
export PATH="$PATH:/path/to/m3/build/Release"
```

> [!TIP]
> For Linux/macOS, you don't need to close the terminal, running `source ~/.bashrc` (or `source ~/.zshrc`) reloads your PATH in the current session.

5. Test by running:

```bash
m3 -v
```

Once finished with installation, initialize M3 by running:
```bash
m3 init
```

## Usage

### TL;DR (Quick Start)
- `m3 init` sets up `.m3` folder in `AppData\Roaming` (Windows) or `$HOME` (Linux/macOS)
- `m3 list` shows available *profiles*
- `m3 load <profile>` loads a profile to your Minecraft mods folder
- `m3 clear` clears the Minecraft mods folder 
- `m3 -v` or `m3 --version` checks the version of M3 currently installed on your system

### Deep Dive
After you ran the `m3 init` command, it has created a `.m3` folder in `AppData\Roaming` (Windows) or `$HOME` (Linux/macOS).

#### Accessing the `.m3` Folder in `AppData\Roaming` (Windows)
1. Press `Win` + `R` to open the Run Dialog
2. Type `%appdata%` and press `Enter`
3. You can find the `.m3` folder near the top

#### Accessing the `.m3` Folder in `$HOME` (Linux/macOS)

1. Open your terminal
2. Navigate to your home directory by running:

```bash
cd $HOME
```

3. List the contents to confirm the .m3 folder exists by running:

```bash
ls -a
```

- You should see a folder named `.m3` in the list.
- The `-a` flag ensures hidden folders (starting with a `.`) are shown.

4. Enter the `.m3` folder by running:

```bash
cd .m3
```

5. From here, you can create *profile* folders and fill it with your mods.

> [!TIP]
> You can also open `.m3` in your file manager:
> - **Linux:** `xdg-open $HOME/.m3`
> - **macOS:** `open $HOME/.m3`

#### Creating a *Profile*
1. Once you have located your `.m3` folder, create a folder
2. This folder will be what we call a *profile*
3. Name the folder something distinctive (e.g., `hypixel`)

> [!WARNING]
> Profile names can't contain any spaces (e.g., use `hypixel` instead of `hypixel mods`).

4. Fill the folder with your mods of choice (`.jar` files)

> [!TIP]
> You can create as many profiles as you want!

#### Loading a *Profile*
1. Open your terminal
2. Run the command `m3 load hypixel` (replace 'hypixel' with the name of your profile)

```bash
Removing mods:
  - some-mod-1.jar
  - some-mod-2.jar

Copying mods:
  + other-mod-1.jar
  + other-mod-2.jar

Loaded profile hypixel!
```

M3 displays the mods removed and copied to your Minecraft mods folder.

#### Clearing Your Minecraft Mods Folder
- Run the command `m3 clear`

```bash
Removing mods:
  - some-mod-1.jar
  - some-mod-2.jar

Cleared mods!
```

M3 displays the mods removed from your Minecraft mods folder.

#### Displaying a List of Your *Profiles*
- Run the command `m3 list`

```bash
Profiles:
  hypixel
```

M3 displays all available profiles detected in the `.m3` folder.

#### Checking the Version of M3 on Your System
- Run the command `m3 -v` or `m3 --version`.

```bash
Minecraft Mods Manager (M3), version 1.0.0.
```

M3 displays the version of M3 currently installed on your system.

#### Needing Help
You can use the `m3 help` command to view a comprehensive help message with all available commands listed as long as their arguments, options, and brief description.

You can also join the [M3 Support Discord Server](https://discord.gg/qFuENNNrEs) to get help and updates!

## Contributions
Any contributions are welcome! I only have a few rules:
- Use modern, idiomatic C++
- Favor low time complexity solutions
- Favor low memory usage
- Use `snake_case` for variables and functions