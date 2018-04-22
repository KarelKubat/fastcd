VER = "0.01"
SRC = $(wildcard *.cc)
OBJ = $(patsubst %.cc, %.o, $(SRC))
BINDIR = ~/bin

fastcd: $(OBJ)
	$(CXX) -g -o fastcd $(OBJ) -lpthread
%.o: %.cc
	$(CXX) -g -c -std=c++11 -Wall -Werror -DVER=\"$(VER)\" $<

usage.o: usage.cc usage.h
usage.h: usage.txt
	echo '#define USAGETXT \' > usage.h
	awk '{printf("\"%s\\n\" \\\n", $$0)}' < usage.txt >> usage.h
	echo '""' >> usage.h
$(OBJ): fastcd.h Makefile

clean:
	rm -f fastcd *.o usage.h

install: fastcd
	install -s fastcd $(BINDIR)/fastcd
