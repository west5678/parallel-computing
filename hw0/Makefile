# Files
EXEC:= hw0
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))
# Options
CC := icc 
CXXFLAGS := -fp-model precise -std=c++11 #-I$$TACC_GRVY_INC -I$$TACC_BOOST_INC
LDFLAGS := #-L$$TACC_GRVY_LIB -L$$TACC_BOOST_LIB
LDLIBS := #-lgrvy
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
