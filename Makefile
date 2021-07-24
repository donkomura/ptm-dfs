CXX      := g++
FLGEXTERNAL := `pkg-config --cflags thallium quill`
CXXFLAGS := -Wall -std=c++14 $(FLGEXTERNAL)
LDEXTERNAL := `pkg-config --libs thallium quill`
LDFLAGS  := -lboost_program_options-mt $(LDEXTERNAL)
RM       := rm

SRC_MAIN := main.cpp
EXE_MAIN := main

.PHONY: all clean debug

all: $(EXE_MAIN)

debug: $(SRC_MAIN)
	$(CXX) $(CXXFLAGS) -g $< $(LDFLAGS) -o $(EXE_MAIN)

clean:
	$(RM) $(EXE_MAIN)

$(EXE_MAIN): $(SRC_MAIN)
	$(CXX) $(CXXFLAGS) $< $(LDFLAGS) -o $@ 
