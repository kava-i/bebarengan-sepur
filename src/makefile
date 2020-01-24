whatever=`getconf _NPROCESSORS_ONLN`
ok=$(whatever)
all:
	make --no-print-directory spec
server:
	make --no-print-directory spec_server
debug:
	make --no-print-directory spec_debug
spec: install
	-rm build/CMakeCache.txt
	mkdir -p build && cd build && cmake .. && make -j$(ok)
spec_server: install
	-rm build/CMakeCache.txt
	mkdir -p build && cd build && cmake .. -DMAKE_SERVER=1 && make -j$(ok)

spec_debug: install
	-rm build/CMakeCache.txt
	mkdir -p build && cd build && cmake .. -DMAKE_DEBUG=1 && make -j$(ok)

install:
	git submodule init
	git submodule update
