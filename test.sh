set -e
cmake --build build
ctest --test-dir build
