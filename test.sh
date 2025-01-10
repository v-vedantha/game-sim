set -e
cmake --build build -j8
ctest --test-dir build -j8 --timeout 4 --no-tests=error --output-on-failure
