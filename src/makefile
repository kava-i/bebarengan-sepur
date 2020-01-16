all:
	make --no-print-directory spec
spec:
	mkdir -p build && cd build && cmake .. && cmake --build . --parallel 4
install:
	rm -rf JanGeschenk
	git clone https://github.com/ShadowItaly/JanGeschenk
	sudo apt install libwebsocketpp-dev
