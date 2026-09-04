# cpptrace

[cpptrace](https://github.com/jeremy-rifkin/cpptrace) for bake — stack traces
with symbol demangling, and "from_current_exception"-style exception traces.
v1.0.4.

Backend wiring mirrors kotatsu's CMake: unix resolves symbols via libdwarf —
its own bake-pkgs package (`bake-pkgs/libdwarf`, the libdwarf-lite fork
cpptrace v1.0.4 pins, with zlib + zstd for compressed debug sections) —
unwinds via `_Unwind`, demangles via cxxabi. Windows uses dbghelp
(StackWalk64 + UnDecorateSymbolName) and pulls none of the unix stack: the
libdwarf dependency is target-scoped to unix triples.

## Verification

Built and smoke-tested on `aarch64-apple-darwin`: `generate_trace()` returns
fully symbolized frames (`deep::leaf() at main.cpp:6:34`), exercising unwind
+ libdwarf + demangle end to end. Cross-compile-checked via kotatsu's `zest`
feature on musl / gnu / windows-gnu.
