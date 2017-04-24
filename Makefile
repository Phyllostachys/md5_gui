all: md5sum_gui
.PHONY: all

md5sum_gui.o: md5sum_gui.cpp
	g++ -O3 -Wall -Werror -c md5sum_gui.cpp -o md5sum_gui.o

md5sum_gui: md5sum_gui.o
	g++ -mwindows md5sum_gui.o -o md5sum_gui -lcrypto

dist-clean:
	rm md5sum_gui.o

clean: dist-clean
	rm md5sum_gui

format:
	clang-format -i -style="{BasedOnStyle: Google, ColumnLimit: 120, IndentWidth: 4}" md5sum_gui.cpp
