BUILD_PATH 			= build

init:
	@cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="Release" -Wno-dev -B ${BUILD_PATH} .
init_d:
	@cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="Debug" -Wno-dev -B ${BUILD_PATH}_debug .

build:
	@cmake --build ${BUILD_PATH} --target godison --parallel 8
build_d:
	@cmake --build ${BUILD_PATH}_debug --target godison --parallel 8

open:
	./${BUILD_PATH}/godison_main
open_d:
	./${BUILD_PATH}_debug/godison_main

main: init
	@cmake --build ${BUILD_PATH} --target godison_main --parallel 8
main_d: init_d
	@cmake --build ${BUILD_PATH}_debug --target godison_main --parallel 8