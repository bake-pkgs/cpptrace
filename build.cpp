import bake.build;
import std;

// cpptrace for bake. Upstream compiles the whole src/** tree unconditionally
// (platform/backend files are #ifdef-gated internally) and selects backends
// purely via CPPTRACE_* defines — set per-target in bake.toml. libdwarf
// lives in its own bake-pkgs package (the fork cpptrace v1.0.4 pins); its
// public headers provide <libdwarf/libdwarf.h> and its archive links
// transitively.

int main() {
    bake::Builder b;
    const auto upstream = std::string(b.dep_src_dir("upstream"));

    // src/ on the include path: cpptrace's own TUs reach headers as
    // "utils/common.hpp", "symbols/dwarf/dwarf.hpp", ...
    b.sources(upstream + "/src/**/*.cpp")
        .include_dirs(upstream + "/src")
        .public_headers(upstream + "/include");
    return b.build();
}
