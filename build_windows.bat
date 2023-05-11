@echo off

if not exist build\ (
	mkdir build && cd build	
) else (
	cd build
)

cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .

pause