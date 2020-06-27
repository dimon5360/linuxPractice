LINK_TARGET = main


OBJS = \
	main.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)

clean : 
	rm -f $(REBUILDABLES)
	echo Clean done

all: $(LINK_TARGET)
	echo All done

$(LINK_TARGET) : $(OBJS)
	g++ -g -o $@ $^

%.o : %.cpp
	g++ -g -o $@ -c $<

# main.o: main.cpp

