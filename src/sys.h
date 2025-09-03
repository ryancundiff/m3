#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

namespace sys {
  fs::path get_m3_path ();
  fs::path get_minecraft_path ();
  fs::path get_mods_path ();
  std::vector<std::string> get_profiles();
  void create_m3_path ();
  bool has_jar_files (const fs::path& path);
}