COMMONFLAGS = -Wall -Wextra -march=native -O3
CFLAGS = -std=c11 $(COMMONFLAGS)
CXXFLAGS = -std=c++14 $(COMMONFLAGS)
LDLIBS = -pthread
EXE = morris

$(EXE): wave.o main.o output.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

wave.o: wave.c wave.h
	$(CC) $(CFLAGS) -c -o $@ $<

main.o: main.cc symbol_queue.hh wave.h output.hh
	$(CXX) $(CXXFLAGS) -c -o $@ $<

output.o: output.cc output.hh symbol_queue.hh wave.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	$(RM) *.o $(EXE)
