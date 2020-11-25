autohide: polybar_autohide.cpp
	g++ -o polybar-autohide polybar_autohide.cpp -lX11

clean:
	rm polybar-autohide
