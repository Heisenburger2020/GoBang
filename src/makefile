CC = g++
ODIR = obj
IDIR = ../include
LDIR = ../lib
CPPFLAGES = -I $(IDIR)
PROGRAM = hwGoBang
all: $(PROGRAM)
DEPS = Consts Human Machine PseudoHeap ChessBoard Game Judge Player UtilityInfo
DEPSO = $(patsubst %, $(ODIR)/%.o, $(DEPS))

# Compile
$(ODIR)/%.o: $(LDIR)/%.cpp
	$(CC) -c -o $@ $< $(CPPFLAGES)

$(ODIR)/%.o: %.cpp
	$(CC) -c -o $@ $< $(CPPFLAGES)

# Link
$(PROGRAM): $(patsubst %, $(ODIR)/%,$(addsuffix .o,  $(PROGRAM))) $(DEPSO)
	$(CC) -o $@ $< $(DEPSO) 

.PHONY: clean
clean:
	rm $(ODIR)/*.o $(PROGRAM)
print:
	echo $(patsubst %, $(ODIR)/%,$(addsuffix .o,  $(PROGRAM)))
