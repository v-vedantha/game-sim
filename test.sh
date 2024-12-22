set -e
cmake --build build
ctest --test-dir build  --timeout 4 --no-tests=error --output-on-failure
