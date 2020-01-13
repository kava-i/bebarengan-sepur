all:
	if cd JanGeschenk; then git pull; else git clone https://github.com/ShadowItaly/JanGeschenk; fi
	g++ *.cpp -std=c++17 -lboost_system -lpthread
install:
	sudo apt install libwebsocketpp-dev
