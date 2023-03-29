default:
  just --list

init:
  cmake -S. -B cmake-build 

build: init
  cmake --build cmake-build

build_release: init 
  cmake --build cmake-build --config Release

run: build
  ./cmake-build/graph2_

run_release: build_release
  ./cmake-build/graph2_

clean:
  rm -rf cmake-build