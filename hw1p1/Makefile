# Files
EXEC:= hw1
SRC := hw1.cpp
OBJ := hw1.o
# Options
CC := icpc 
CXXFLAGS := -std=c++11 -O2 -xHost -qopenmp
# Rules
$(EXEC) : $(SRC)
		$(CC) $(CXXFLAGS) -o $@ $^
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
