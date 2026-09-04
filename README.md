# cpptrace

[cpptrace](https://github.com/jeremy-rifkin/cpptrace) for bake — stack traces
with symbol demangling, and "from_current_exception"-style exception traces.
v1.0.4.

Backend wiring mirrors kotatsu's CMake: unix resolves symbols via libdwarf
(the exact libdwarf-lite rev cpptrace v1.0.4 pins — 5dfb2cd = v2.1.0 —
compiled into this same archive with a hand-maintained `config/config.h`,
zlib + zstd for compressed debug sections from bake-pkgs), unwinds via
`_Unwind`, demangles via cxxabi. Windows uses dbghelp (StackWalk64 +
UnDecorateSymbolName) and pulls none of the unix stack — the libdwarf/zstd/
zlib dependencies are target-scoped to unix triples.

## Verification

Built and smoke-tested on `aarch64-apple-darwin`: `generate_trace()` returns
fully symbolized frames (`deep::leaf() at main.cpp:6:34`), exercising unwind
+ libdwarf + demangle end to end. Cross-compile-checked via kotatsu's `zest`
feature on musl / gnu / windows-gnu.
