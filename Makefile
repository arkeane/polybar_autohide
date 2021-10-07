autohide: polybar_autohide.cpp
	g++ -o polybar_autohide polybar_autohide.cpp -lX11

clean:
	rm polybar_autohide
