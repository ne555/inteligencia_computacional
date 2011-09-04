cxx = g++
cppflags = -Wall -pedantic-errors -ggdb
libraries = 
project = perceptron_simple.bin
auxiliar = input.bin
input = input.txt

objects = ej1_1.o neurona.o simulator.o capa.o
aux_obj = input.o

objdir = obj
objs = $(addprefix $(objdir)/,$(objects))

#$(project) : $(objects)
$(project) : $(objs)
	$(cxx) $(cppflags) $(libraries) $(objs) -o $@

$(auxiliar) : $(aux_obj)
	$(cxx) $(cppflags) $< -o $@
	./$@ > $(input)

test: $(project) $(auxiliar)
	#./$(project) -t 100 -g 0.2 -s 0.99 -d 0.5 < $(input)
	./$(project) < $(input)
	#gnuplot recta.txt

$(objdir)/capa.o: neurona.h math_vector.h util.h
$(objdir)/ej1_1.o: simulator.h neurona.h math_vector.h capa.h util.h
$(objdir)/input.o: util.h
$(objdir)/neurona.o: math_vector.h util.h
$(objdir)/simulator.o: neurona.h math_vector.h capa.h util.h

$(objdir)/%.o : %.cpp
	$(cxx) $< -c -o $@

all: $(objs)

$(objs): | $(objdir)

$(objdir):
	mkdir $(objdir)

foo:
	echo $(objs)
	echo $(objdir)

.PHONY: clean test foo

clean:
	-rm $(objs) $(project)
	-rm $(aux_obj) $(auxiliar) $(input)
