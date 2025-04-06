#define NOB_STRIP_PREFIX
#define NOB_IMPLEMENTATION
#include "./src/nob.h"

Proc build_program(const char *source_path, const char *output_path)
{
    Cmd cmd = {0};
    cmd_append(&cmd, "cc");
    cmd_append(&cmd, "-Wall", "-Wextra", "-ggdb");
    cmd_append(&cmd, "-I./raylib/", "-I./zlib/", "-I./stb/");
    cmd_append(&cmd, "-O3");
    cmd_append(&cmd, "-o", output_path);
    cmd_append(&cmd, source_path);
    cmd_append(&cmd, "-L./raylib/", "-L./zlib/");
    cmd_append(&cmd, "-lraylib", "-lm", "-lz", "-ldl", "-lpthread");
    return cmd_run_async(cmd);
}

int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);
    if (!mkdir_if_not_exists("./build/")) return 1;
    Procs procs = {0};
    da_append(&procs, build_program("./src/2d.c", "./build/2d"));
    da_append(&procs, build_program("./src/3d.c", "./build/3d"));
    da_append(&procs, build_program("./src/knn.c", "./build/knn"));
    if (!procs_wait(procs)) return 1;
    return 0;
}
