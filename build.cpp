import bake.build;
import std;

// cpptrace for bake. Upstream compiles the whole src/** tree unconditionally
// (platform/backend files are #ifdef-gated internally) and selects backends
// purely via CPPTRACE_* defines — set per-target in bake.toml. On unix the
// libdwarf backend needs libdwarf-lite's 59 C files in the same archive; the
// generated config.h is provided by this package's config/ dir.

int main() {
    bake::Builder b;
    const auto upstream = std::string(b.dep_src_dir("upstream"));
    const auto target = b.target();
    const bool is_windows = target.find("windows-gnu") != std::string_view::npos;

    // src/ on the include path: cpptrace's own TUs reach headers as
    // "utils/common.hpp", "symbols/dwarf/dwarf.hpp", ...
    b.sources(upstream + "/src/**/*.cpp")
        .include_dirs(upstream + "/src")
        .public_headers(upstream + "/include");

    if (!is_windows) {
        const auto libdwarf = std::string(b.dep_src_dir("libdwarf"));
        b.sources(libdwarf + "/src/lib/libdwarf/*.c")
            // cpptrace's dwarf.hpp includes <libdwarf/libdwarf.h> (include
            // root is src/lib, whose libdwarf/ subdir holds the headers); the
            // .c files include <config.h> and flat "dwarf_*.h" siblings
            // (same-dir, no include path needed).
            .include_dirs({libdwarf + "/src/lib", "config"});
    }
    return b.build();
}
