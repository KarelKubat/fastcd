VER = "0.01"
SRC = $(wildcard *.cc)
OBJ = $(patsubst %.cc, %.o, $(SRC))

fastcd: $(OBJ)
	$(CXX) -o fastcd $(OBJ) -lpthread
%.o: %.cc
	$(CXX) -c -Wall -Werror -DVER=\"$(VER)\" $<

usage.o: usage.cc usage.h
usage.h: usage.txt
	echo '#define USAGETXT \' > usage.h
	awk '{printf("\"%s\\n\" \\\n", $$0)}' < usage.txt >> usage.h
	echo '"\n"' >> usage.h
$(OBJ): fastcd.h Makefile

clean:
	rm -f fastcd *.o usage.h
