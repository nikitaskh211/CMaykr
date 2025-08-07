#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// String constant for usage
#define STRING_USAGE                                                           \
  "[INF] Usage: cmaykr [flags] [directories]\n"                                \
  "[INF] Flags:\n"                                                             \
  "      -h or --help = This flag displays usage of the program.\n"            \
  "      -v or --version = This flag displays version of the program.\n"       \
  "      -m or --make = This flag makes each project.\n"                       \
  "      -d or --debug = This flag builds debug version of the projects.\n"    \
  "      -r or --release = This flag builds release version of the "           \
  "projects.\n"

/// Integer constants for version
#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_PATCH 1

int make_project();
int build_debug();
int build_release();

int main(int argc, char *argv[]) {
  // Skipping the first argument, which is the name of the program
  argv++;
  argc--;
  // Variables for flags
  int f_err = 0;
  int f_help = 0, f_version = 0, f_make = 0, f_debug = 0, f_release = 0;
  // Failsafe in case only the name of the program is used
  if (argc == 0) {
    fprintf(stderr, "[ERR] No arguments provided to the program.\n");
    f_help = 1;
    f_err = 1;
  }
  // Variables for directories
  int dirc = 64;
  char *dirv[64];
  // Parsing arguments
  while (argc > 0) {
    if ((*argv)[0] == '-') {
      // Parsing flags
      if (!strcmp(*argv, "-h") || !strcmp(*argv, "--help"))
        f_help = 1;
      else if (!strcmp(*argv, "-v") || !strcmp(*argv, "--version"))
        f_version = 1;
      else if (!strcmp(*argv, "-m") || !strcmp(*argv, "--make"))
        f_make = 1;
      else if (!strcmp(*argv, "-d") || !strcmp(*argv, "--debug"))
        f_debug = 1;
      else if (!strcmp(*argv, "-r") || !strcmp(*argv, "--release"))
        f_release = 1;
      else {
        fprintf(stderr, "[ERR] Unknown flag: %s\n", *argv);
        f_help = 1;
        f_err = 1;
      }
    } else {
    }
    // Going through each argument
    argv++;
    argc--;
  }
  if (f_help)
    fprintf(stdout, STRING_USAGE);
  if (f_version) {
    fprintf(stdout, "[INF] CMaykr version : ");
    fprintf(stdout, "%d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
  }
  if (f_debug && f_release) {
    fprintf(stderr, "[ERR] Cannot build both release and debug version.\n");
    f_err = 1;
  }
  if (f_make) {
  }
  if (f_debug) {
  }
  if (f_release) {
  }
  if (f_err)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
