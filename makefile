CXX = g++
CPPFLAGS = -Wall -pedantic-errors -O2 #-ggdb -pg
LIBRARIES_grapher = $(addprefix -l,GL GLU glut)
LIBRARIES_perceptron = 
LIBRARIES_input = 
objdir = obj
headerdir = header
bindir = bin
bin = $(addprefix $(bindir)/,perceptron grapher input)

obj_perceptron = ej1_1.o neurona.o simulator.o capa.o
obj_input = input.o
obj_grapher = grapher.o

object_perceptron = $(addprefix $(objdir)/,$(obj_perceptron))
object_input = $(addprefix $(objdir)/,$(obj_input))
object_grapher = $(addprefix $(objdir)/,$(obj_grapher))

objects = $(object_perceptron) $(object_grapher) $(object_input)

all: $(bin)

test: $(bin) input.txt
	./$(bindir)/perceptron < input.txt 2>debug.log | cat input.txt - | ./$(bindir)/grapher
	grep -Po '(?<=Error ).*$$' debug.log  > error.log
	grep -Po '(?<=Diff ).*$$' debug.log  > diff.log

input.txt: $(bindir)/input
	$< > $@
	

bin/perceptron: $(object_perceptron)
	$(CXX) $(LIBRARIES_perceptron) $(object_perceptron) -o $@

bin/grapher: $(object_grapher)
	$(CXX) $(LIBRARIES_grapher) $(object_grapher) -o $@
	
bin/input: $(object_input)
	$(CXX) $(LIBRARIES_input) $(object_input) -o $@
	

$(objdir)/capa.o: $(addprefix $(headerdir)/,neurona.h math_vector.h capa.h util.h)
$(objdir)/ej1_1.o: $(addprefix $(headerdir)/,simulator.h capa.h math_vector.h neurona.h util.h)
$(objdir)/grapher.o: 
$(objdir)/input.o: $(addprefix $(headerdir)/,util.h math_vector.h)
$(objdir)/neurona.o: $(addprefix $(headerdir)/,neurona.h math_vector.h util.h)
$(objdir)/simulator.o: $(addprefix $(headerdir)/,simulator.h capa.h math_vector.h neurona.h util.h)

	 
$(objdir)/%.o : src/%.cpp
	$(CXX) $< -c $(CPPFLAGS) -I$(headerdir) -o $@

obj/simulator.o : src/simulator.cpp
	$(CXX) $< -c $(CPPFLAGS) -I$(headerdir) -o $@

$(objects): | $(objdir)

$(objdir):
	mkdir $(objdir)

bar:
	@echo $(objdir)/%.o

foo:
	@echo $(objects)

.PHONY: clean test graph

clean:
	-rm $(objects) $(bin)

