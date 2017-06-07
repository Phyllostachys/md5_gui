all: md5_gui md5_str
.PHONY: all

md5_gui.o: md5_gui.cpp
	g++ -O3 -Wall -Werror -c md5_gui.cpp -o md5_gui.o

md5_gui: md5_gui.o
	g++ -static md5_gui.o -o md5_gui -lcrypto

md5_str.o: md5_gui.cpp
	g++ -O3 -Wall -Werror -DMD5_STR -c md5_gui.cpp -o md5_str.o

md5_str: md5_str.o
	g++ -static md5_str.o -o md5_str -lcrypto

dist-clean:
	rm md5_gui.o

clean: dist-clean
	rm md5_gui

format:
	clang-format -i -style="{BasedOnStyle: Google, ColumnLimit: 120, IndentWidth: 4}" md5_gui.cpp
