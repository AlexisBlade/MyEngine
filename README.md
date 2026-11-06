# MyEngine
 Experimental C++ Graphics Engine


## Source checkpoint — 2026-11-06

The source is a Visual Studio C++/SFML experiment, not a qualified portable build.
The existing project configuration still contains machine-specific SFML paths.
A Windows MSBuild Debug/x64 check currently stops at missing `SFML/Window.hpp`;
no executable or runtime behavior was validated. Check include/library paths
before continuing. IDE databases and generated binaries are not source updates.
