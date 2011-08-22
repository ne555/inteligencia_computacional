cxx = g++
cppflags = -Wall -pedantic-errors -ggdb
libraries = 
project = perceptron_simple.bin
auxiliar = input.bin
input = input.txt

objects = ej1_1.o neurona.o
aux_obj = input.o

$(project) : $(objects)
	$(cxx) $(cppflags) $(libraries) $(objects) -o $@

$(auxiliar) : $(aux_obj)
	$(cxx) $(cppflags) $< -o $@
	./$@ > $(input)

test: $(project) $(auxiliar)
	./$(project) -t 100 -g 0.022 -s 0.999 < $(input)


neurona.o : neurona.h util.h
ej1_1.o : neurona.h util.h
input.o : util.h

.PHONY: clean test

clean:
	-rm $(objects) $(project)
	-rm $(aux_obj) $(auxiliar) $(input)
