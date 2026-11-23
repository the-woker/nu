#include <cstdlib>
#include <iostream>
#include <string>

bool runCommand(const std::string &command) {
  int result = std::system(command.c_str());
  if (result != 0) {
    std::cerr << "Command failed: " << command << '\n';
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: nu <project_name> <os/home>" << std::endl;
    return 1;
  }
  const char *env_p = std::getenv("NH_FLAKE");
  if (env_p == nullptr) {
    std::cerr << "NH_FLAKE variable not found.\n";
    return 1;
  }

  std::string flake_dir{env_p};
  std::string input{argv[1]};
  std::string attr{argv[2]};

  if (attr != "os" && attr != "home") {
    std::cerr << "Usage: nu <project_name> <os/home>" << std::endl;
    return 1;
  }
  std::string update{"nix flake update " + input + " --flake " + flake_dir};

  if (!runCommand(update))
    return 1;

  std::string rebuild{"nh " + attr + " switch"};

  if (!runCommand(rebuild))
    return 1;

  return 0;
}
