#include "sys.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

fs::path sys::get_m3_path () {
  return fs::path(std::getenv("APPDATA")) / ".m3";
}

fs::path sys::get_minecraft_path () {
  return fs::path(std::getenv("APPDATA")) / ".minecraft";
}

fs::path sys::get_mods_path () {
  return get_minecraft_path() / "mods";
}

std::vector<std::string> sys::get_profiles () {
  fs::path m3_path = get_m3_path();

  // If M3 path does not exist.
  if (!fs::exists(m3_path)) {
    throw std::runtime_error(
      std::string("Error: M3 path not found.\n")
      + "Did you try running m3 init?"
    );
  }

  std::vector<std::string> profiles;

  for (auto& entry : fs::directory_iterator(m3_path)) {
    if (entry.is_directory() && entry.path().filename().string().find(' ') == std::string::npos) {
      profiles.push_back(entry.path().filename().string());
    }
  }

  return profiles;
}

void sys::create_m3_path () {
  auto m3_path = get_m3_path();

  try {
    // If path does not exist.
    if (!fs::exists(m3_path)) {
      std::cout << "M3 path not found! Creating.\n";
      
      // Create directory.
      fs::create_directories(m3_path);

      std::cout << "Created path at " << m3_path << "!\n";
    }
  } catch (const std::exception& err) {
    throw std::runtime_error(
      std::string("File System Error: ")
      + err.what() + '\n'
    );
  }
}

bool sys::has_jar_files(const fs::path& path) {
  // If path doesn't exist or not a directory.
  if (!fs::exists(path) || !fs::is_directory(path)) {
    return false;
  }

  for (const auto& entry : fs::directory_iterator(path)) {
    // If entry is a file and has a .jar extension.
    if (entry.is_regular_file() && entry.path().extension() == ".jar") {
      return true;
    }
  }

  // No files with a .jar extension found.
  return false;
}