OBJS := main.o Chooser.o Pairs.o Snake/Snake.o Snake/main.o
DEPS := $(OBJS:.o=.d)
CXXFLAGS := -O2 -Wall -Wextra -Wpedantic -MMD -MP
LDFLAGS := -lncursesw

run: out
	./out

all: out

out: $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

clean:
	@-rm **/*.o
	@-rm *.o
	@-rm **/*.d
	@-rm *.d
	@-rm ./out
.PHONY: clean

crun: clean out
	./out

debug: clean
	make out CXXFLAGS="-g -Wall -Wextra -Wpedantic -MMD -MP"
	gdb out

-include $(DEPS)
