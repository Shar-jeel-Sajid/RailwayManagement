all:
	g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lsfml-main -lsfml-audio  -lsfml-graphics   -lsfml-network -lsfml-window -lsfml-system