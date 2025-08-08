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
  "      -bd or --debug = This flag builds debug version of the projects.\n"   \
  "      -br or --release = This flag builds release version of the "          \
  "projects.\n"                                                                \
  "      -c or --clean = This flag removes old object files and "              \
  "executables.\n"                                                             \
  "      -r or --run = This flags executes built program.\n"

/// Integer constants for version
#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_PATCH 1

/// Integer constant for maximum directories
#define DIRECTORIES_MAX 128

/// Integer constant for the size of the line buffer
#define LINE_BUFFER_MAX 128

/// This function is responsible for parsing the config.cmaykr file
int make_project(char *dirv) {
  // Constan string
  const char *config_name = "config.cmaykr";
  // Variable for error
  int f_err = 0;
  // Variables for file location

  size_t dir_length = strlen(dirv);
  size_t config_name_length = strlen(config_name);
  size_t file_location_length = dir_length + 1 + config_name_length + 1;
  char *file_location = (char *)malloc(file_location_length * sizeof(char));
  if (!file_location) {
    fprintf(stderr, "[ERR] Could not buffer: [directory]/config.cmaykr\n");
    fprintf(stderr, "[ERR] Error code: %d\n", errno);
    f_err = 1;
  }
  // Joining the string
  strcpy(file_location, dirv);
  if (dir_length == 0 || dirv[dir_length - 1] != '/') {
    strcat(file_location, "/");
  }
  strcat(file_location, config_name);
  // Opening the config.cmaykr file and checking the sources seciton
  FILE *config_file = fopen(file_location, "r");
  // Error opening the file
  if (!config_file) {
    fprintf(stderr, "[ERR] Could not open config.cmaykr in %s", dirv);
    f_err = 1;
  } else {
    // Closing the file
    fclose(config_file);

    fprintf(stdout, "[INF] Successfully opened: %s\n", file_location);
  }
  // Freeing the memory
  free(file_location);
  return f_err ? EXIT_FAILURE : EXIT_SUCCESS;
}

/// This function is responsible for building a project
int build_project(int f_debug, int f_release, char *dirv);

int main(int argc, char *argv[]) {
  // Skipping the first argument, which is the name of the program
  argv++;
  argc--;
  // Variables for flags
  int f_err = 0;
  int f_help = 0, f_version = 0, f_make = 0, f_clean = 0;
  int f_debug = 0, f_release = 0, f_run = 0;
  // Failsafe in case only the name of the program is used
  if (argc == 0) {
    fprintf(stderr, "[ERR] No arguments provided to the program.\n");
    f_help = 1;
    f_err = 1;
  }
  // Variables for directories
  int dirc = 0;
  char *dirv[DIRECTORIES_MAX];
  // Parsing arguments
  while (argc > 0) {
    if ((*argv)[0] == '-') {
      // Parsing flags
      if (!strcmp(*argv, "-h") || !strcmp(*argv, "--help"))
        f_help = 1;
      else if (!strcmp(*argv, "-v") || !strcmp(*argv, "--version"))
        f_version = 1;
      else if (!strcmp(*argv, "-c") || !strcmp(*argv, "--clean"))
        f_clean = 1;
      else if (!strcmp(*argv, "-m") || !strcmp(*argv, "--make"))
        f_make = 1;
      else if (!strcmp(*argv, "-bd") || !strcmp(*argv, "--debug"))
        f_debug = 1;
      else if (!strcmp(*argv, "-br") || !strcmp(*argv, "--release"))
        f_release = 1;
      else if (!strcmp(*argv, "-r") || !strcmp(*argv, "--run"))
        f_run = 1;
      else {
        fprintf(stderr, "[ERR] Unknown flag: %s\n", *argv);
        f_help = 1;
        f_err = 1;
      }
    } else {
      // Parsing directories
      if (dirc >= DIRECTORIES_MAX) {
        fprintf(stderr, "[ERR] Too many project directories.");
        fprintf(stderr, " (maximum is %d).\n", DIRECTORIES_MAX);
        f_err = 1;
      } else {
        dirv[dirc] = *argv;
        fprintf(stdout, "[INF] Project directory #%d: %s\n", dirc, *dirv);
        dirc++;
      }
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
    for (int project_num = 0; project_num < dirc; project_num++) {
      make_project(dirv[project_num]);
    }
  }
  if (f_debug) {
  }
  if (f_release) {
  }
  return f_err ? EXIT_FAILURE : EXIT_SUCCESS;
}
