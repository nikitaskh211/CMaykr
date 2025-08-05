#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Metadata
#define USAGE_STRING "[INF] Usage: `cmaykr` [flag] [directories]\n"
#define VERSION_STRING "0.1.0\n" // major.minor.patch

/// Maximum amount of projects that can be made and build.
#define MAX_PROJECTS 128

int main(int argc, char *argv[]) {
  /// Main variables
  int flag_help = 0, flag_version = 0, flag_debug = 0, flag_release = 0;
  int flag_unknown = 0;
  char (*projects)[MAX_PROJECTS];
  /// Main CLI argument processor
  if (argc > 1) {
    while (*argv != NULL) {
      if ((*argv)[0] == '-') {
        switch ((*argv)[1]) {
        case 'h': // -h = help flag
          flag_help = 1;
          break;
        case 'v': // -v = version flag
          flag_version = 1;
          break;
        case 'd': // -d = debug build flag
          flag_debug = 1;
          break;
        case 'r': // -r = release build flag
          flag_release = 1;
          break;
        default: // -??? = any unknown flag is displayed as unknown
          flag_unknown = 1;
          fprintf(stderr, "[ERR] Unknown flag: -%c\n", (*argv)[1]);
          break;
        }
      } else {
      }
      argv++; // incrementing the pointer for arguments
    }
  } else {
    flag_help = 1;
    fprintf(stderr, "[ERR] The program has no arguments.\n");
  }
  /// Main CLI response processor
  if (flag_help)
    fprintf(stdout, USAGE_STRING);
  if (flag_version)
    fprintf(stdout, "[INF] CMaykr version: " VERSION_STRING);
  if (flag_debug)
    fprintf(stdout, "[INF] Producing debug build. -> TODO!\n");
  if (flag_release)
    fprintf(stdout, "[INF] Producing release build. -> TODO!\n");
  return EXIT_SUCCESS;
}
