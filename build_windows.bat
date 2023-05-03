@echo off

if not exist build\ (
	mkdir build && cd build	
) else (
	cd build
)

cmake ..
cmake --build .

pause