# Files
EXEC:= hw0
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))
# Options
CC := icc 
CXXFLAGS := -std=c++11 -O2 -xHost -qopenmp
# Rules
$(EXEC) : $(OBJ)
		$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^
%.o : %.cpp
		$(CC) $(CXXFLAGS) -c $<
# Useful phony targets
.PHONY: clobber clean neat echo
clobber: clean
	$(RM) $(EXEC)
clean: neat
	$(RM) $(OBJ)
neat:
	$(RM) *~ .*~
echo:
	@echo $(OBJ)
