whatever=`getconf _NPROCESSORS_ONLN`
ok=$(whatever)
all:
	make --no-print-directory spec
server:
	make --no-print-directory spec_server
spec:
	-rm build/CMakeCache.txt
	mkdir -p build && cd build && cmake .. && make -j$(ok)
spec_server:
	-rm build/CMakeCache.txt
	mkdir -p build && cd build && cmake .. -DMAKE_SERVER=1 && make -j$(ok)

install:
	rm -rf JanGeschenk
	git clone https://github.com/ShadowItaly/JanGeschenk
	sudo apt install libwebsocketpp-dev
