all : main
 
main : 
	g++ -std=c++1z -Wall -Wextra -Werror -Ofast -pthread src/main.cpp src/Mandelbrot.cpp -o Mandelbrot -I inc -lsfml-graphics -lsfml-window -lsfml-system
clean :
	rm -f Mandelbrot