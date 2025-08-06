#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Metadata
#define USAGE_STRING                                                           \
  "[INF] Usage: `cmaykr` [flag] [directories]\n"                               \
  "[INF] Flags:\n"                                                             \
  "        -h == Show help\n"                                                  \
  "        -v == Show version\n"                                               \
  "        -d == Debug build\n"                                                \
  "        -r == Release build\n"
#define VERSION_STRING "0.1.0\n" // major.minor.patch

/// Maximum amount of projects that can be made and build.
#define MAX_PROJECTS 128

/// Srting length for a path to config.maykr
#define CONFIG_PATH_LENGTH 512

int main(int argc, char *argv[]) {
  /// Main variables
  int flag_help = 0, flag_version = 0, flag_debug = 0, flag_release = 0;
  char *projects[MAX_PROJECTS];
  char **project = projects;
  /// Skipping the first argument as it is the program name
  argv++;
  argc--;
  /// Main CLI argument processor
  if (argc == 0) {
    flag_help = 1;
    fprintf(stderr, "[ERR] The program has no arguments.\n");
  }
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
        fprintf(stderr, "[ERR] Unknown flag: -%c\n", (*argv)[1]);
        return EXIT_FAILURE;
      }
    } else { // If it is not flag we write it into a table of projects to make
      if (project - projects >= MAX_PROJECTS) {
        fprintf(stderr, "[ERR] Too many projects (max %d),\n", MAX_PROJECTS);
        return EXIT_FAILURE;
      }
      size_t argv_length = strlen(*argv) + 1;
      *project = (char *)malloc(argv_length * sizeof(char));
      if (*project == NULL) {
        fprintf(stderr, "[ERR] The 'malloc' function failed for: %s\n", *argv);
        for (char **cleanup = projects; cleanup < project; cleanup++) {
          free(*cleanup);
        }
        return EXIT_FAILURE;
      }
      strncpy(*project, *argv, argv_length);
      project++;
    }
    argv++;
  }
  /// Main CLI response processor
  if (flag_help) {
    fprintf(stdout, USAGE_STRING);
    return EXIT_SUCCESS;
  }
  if (flag_version) {
    fprintf(stdout, "[INF] CMaykr version: " VERSION_STRING);
    return EXIT_SUCCESS;
  }
  if (flag_debug && flag_release) {
    fprintf(stderr, "[ERR] Cannot use both -d and -r flags.\n");
    return EXIT_FAILURE;
  }
  if (flag_debug)
    fprintf(stdout, "[INF] Producing debug build. -> TODO!\n");
  if (flag_release)
    fprintf(stdout, "[INF] Producing release build. -> TODO!\n");
  /// Making the projects (parser to config.cmaykr file)
  for (char **config_pointer = projects; config_pointer < project;
       config_pointer++) {
    char config_path[CONFIG_PATH_LENGTH];
    snprintf(config_path, sizeof(config_path), "%s/config.maykr",
             *config_pointer);
    FILE *config_file = fopen(config_path, "r");
    if (!config_file) {
      fprintf(stderr, "[ERR] Could not open config file: %s\n", config_path);
      continue; // We will skip a project that does not have a configuration file
    }
    fprintf(stdout, "[INF] Parsing config: %s\n", config_path);

    fclose(config_file);
  }
  /// Correct cleanup
  for (char **cleanup = projects; cleanup < project; cleanup++) {
    free(*cleanup);
  }
  return EXIT_SUCCESS;
}
