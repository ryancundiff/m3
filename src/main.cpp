#include "sys.h"
#include "str.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

// |====> PROTOTYPES <========================================|

/** Output the help message. */
void print_help ();

/** Outputs the version. */
void print_version ();

/** Outputs the user's profiles. */
void print_profiles ();

/** Loads the profile to mods folder. */
void load_profile (const std::string& profile);

/** Removes all mods from mods folder. */
void clear_mods ();


// |====> CONSTANTS <=========================================|

const std::string VERSION = "1.0.0";
const std::string ASCII_ART =
  std::string("___  ___  _____\n")
  + "|  \\/  | |____ |\n"
  + "| .  . |     / /\n"
  + "| |\\/| |     \\ \\\n"
  + "| |  | | .___/ /\n"
  + "\\_|  |_/ \\____/\n\n";

// |====> MAIN <==============================================|

int main (int argc, char* argv[]) {
  // No command passed, print help.
  if (argc < 2) {
    print_help();

    return 0;
  }

  std::string cmd = argv[1];

  try {
    if (argc == 2 && (cmd == "-v" || cmd == "--version")) {
      print_version();
    } else if (cmd == "help") {
      print_help();
    } else if (cmd == "init") {
      sys::create_m3_path();

      std::cout << "Initialized!\n";
    } else if (cmd == "list") {
      print_profiles();
    } else if (cmd == "load") {
      if (argc < 3) {
        throw std::runtime_error("Error: Missing profile name.");
      }

      load_profile(argv[2]);
    } else if (cmd == "clear") {
      clear_mods();
    } else {
      std::cout << "That command does not exist!\n" << "Try using m3 help.\n";
    }
  } catch (std::exception& err) {
    std::cerr << err.what() << '\n';

    return 1;
  }
}

// |====> FUNCTIONS <=========================================|

void print_help () {
  std::cout
    << str::make_bold(ASCII_ART)
    << str::make_bold("Minecraft Mods Manager (M3)")
    << " is a CLI tool to manage your mods in Minecraft.\n\n"
    << str::make_bold("Usage:") << '\n'
    << "  m3 [command]\n"
    << "  m3 [flags]\n\n"
    << str::make_bold("Commands:") << '\n'
    << "  help            Show this menu.\n"
    << "  init            Initialize M3.\n"
    << "  list            List profiles.\n"
    << "  load <profile>  Load a profile into your mods folder.\n"
    << "  clear           Clear your Minecraft mods folder.\n\n"
    << str::make_bold("Arguments:") << '\n'
    << "  <profile>       Name of the profile folder inside your base directory.\n\n"
    << str::make_bold("Options:") << '\n'
    << "  [command]       An M3 command (e.g., help, guide, init).\n"
    << "  [flags]         A flag (see 'Flags').\n\n"
    << str::make_bold("Flags:") << '\n'
    << "  -v, --version   Version of M3 installed on your system.\n";
}

void print_version () {
  std::cout
    << str::make_bold("Minecraft Mods Manager (M3)")
    << ", version " << VERSION << ".\n";
}

void print_profiles () {
  std::vector<std::string> profiles = sys::get_profiles();

  if (profiles.size() < 1) {
    std::cout
      << "There are no profiles to list.\n"
      << "Make sure there are no spaces in the name of your profiles.\n";
  } else {
    std::cout << str::make_bold("Profiles:") << '\n';

    for (std::string profile : profiles) {
      std::cout << "  " << profile << '\n';
    }
  }
}

void load_profile (const std::string& profile) {
  fs::path m3_path = sys::get_m3_path();

  // If M3 path does not exist.
  if (!fs::exists(m3_path)) {
    throw std::runtime_error(
      std::string("Error: M3 path not found.\n")
      + "Did you try running m3 init?"
    );
  }

  fs::path profile_path = m3_path / profile;

  // If profile does not exist.
  if (!fs::exists(profile_path)) {
    throw std::runtime_error(
      std::string("Error: Profile ")
      + profile
      + " does not exist."
    );
  }

  // If there are no .jar files in the profile path.
  if (!sys::has_jar_files(profile_path)) {
    std::cout << "Profile " << profile << " doesn't have any mods to load.\n";

    // Exit immediately.
    std::exit(0);
  }

  fs::path minecraft_path = sys::get_minecraft_path();

  // If minecraft path does not exist.
  if (!fs::exists(minecraft_path)) {
    throw std::runtime_error(
      std::string("Error: Path ")
      + minecraft_path.string()
      + " does not exist."
    );
  }

  fs::path mods_path = sys::get_mods_path();

  // If mods path does not exist.
  if (!fs::exists(mods_path)) {
    throw std::runtime_error(
      std::string("Error: Path ")
      + mods_path.string()
      + " does not exist."
    );
  }

  // If there are .jar files in the mods path.
  if (sys::has_jar_files(mods_path)) {
    std::cout << str::make_bold("Removing old mods:") << '\n';

    // Remove old .jar files.
    for (const auto& entry : fs::directory_iterator(mods_path)) {
      if (entry.is_regular_file() && entry.path().extension() == ".jar") {
        fs::remove(entry.path());

        std::cout << str::make_red("  - ") + entry.path().filename().string() + '\n';
      }
    }

    std::cout << '\n';
  }

  std::cout << str::make_bold("Copying new mods:") << '\n';

  // Copy new .jar files.
  for (const auto& entry : fs::directory_iterator(profile_path)) {
    if (entry.is_regular_file() && entry.path().extension() == ".jar") {
      fs::copy(
        entry.path(),
        mods_path / entry.path().filename(),
        fs::copy_options::overwrite_existing
      );

      std::cout << str::make_green("  + ") + entry.path().filename().string() + '\n';
    }
  }

  std::cout << "\nLoaded profile " << profile << "!\n";
}

void clear_mods () {
  fs::path minecraft_path = sys::get_minecraft_path();

  // If minecraft path does not exist.
  if (!fs::exists(minecraft_path)) {
    throw std::runtime_error(
      std::string("Error: Path ")
      + minecraft_path.string()
      + " does not exist."
    );
  }

  fs::path mods_path = sys::get_mods_path();

  // If mods path does not exist.
  if (!fs::exists(mods_path)) {
    throw std::runtime_error(
      std::string("Error: Path ")
      + mods_path.string()
      + " does not exist."
    );
  }

  // If there are .jar files in the mods path.
  if (sys::has_jar_files(mods_path)) {
    std::cout << str::make_bold("Removing mods:") << '\n';

    // Remove old .jar files.
    for (const auto& entry : fs::directory_iterator(mods_path)) {
      if (entry.is_regular_file() && entry.path().extension() == ".jar") {
        fs::remove(entry.path());

        std::cout << str::make_red("  - ") + entry.path().filename().string() + ".\n";
      }
    }

    std::cout << "\nCleared mods!\n";
  } else {
    std::cout << "There are no mods to remove.\n";
  }
}