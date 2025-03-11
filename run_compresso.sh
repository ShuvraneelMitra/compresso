rm -rf build
mkdir build
cd build
cmake .. --log-level=WARNING
cmake --build . -- --quiet

echo " "

LD_PRELOAD=/lib/x86_64-linux-gnu/libpthread.so.0 ./compresso