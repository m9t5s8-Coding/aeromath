#include <filesystem>
#include <vector>

union test {
  char  c; // 1byte
  int   i; // 4byte
  float f; // 4 byte
}; // 12 byte

struct Test2 {
  int year : 12; // Allocates 12 bits
  int month : 4; // Allocates 4 bits
  int day : 5;   // Allocates 5 bits
};

int
main(int   argc,
     char* argv[]) {

  using Test = std::pair<std::filesystem::path, bool>;
  std::vector<Test>     files;
  std::filesystem::path file;
  files.push_back({file, true});

  return 0;
}
