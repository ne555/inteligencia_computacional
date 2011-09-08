cxx = g++
cppflags = -Wall -pedantic-errors -ggdb
libraries = $(addprefix -l,GL GLU glut) 
project = grapher.bin

objects = main.o

objdir = obj
objs = $(addprefix $(objdir)/,$(objects))

$(project) : $(objs)
	$(cxx) $(cppflags) $(libraries) $(objs) -o $@

$(objdir)/%.o : %.cpp
	$(cxx) $< -c -o $@

all: $(objs)

$(objs): | $(objdir)

$(objdir):
	mkdir $(objdir)

.PHONY: clean

clean:
	-rm $(objs) $(project)

