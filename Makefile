all: md5_gui
.PHONY: all

md5_gui.o: md5_gui.cpp
	g++ -O3 -Wall -Werror -c md5_gui.cpp -o md5_gui.o

md5_gui: md5_gui.o
	g++ -mwindows md5_gui.o -o md5_gui -lcrypto

dist-clean:
	rm md5_gui.o

clean: dist-clean
	rm md5_gui

format:
	clang-format -i -style="{BasedOnStyle: Google, ColumnLimit: 120, IndentWidth: 4}" md5_gui.cpp
