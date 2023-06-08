CC=clang++
CFLAGS=-Wall -Wextra -Wpedantic -O0 -g3
CFLAGS+=$(shell pkg-config --libs --cflags sdl2)
OBJDIR=./obj
SRCDIR=./src
SRCFN=$(notdir $(wildcard $(SRCDIR)/*.cpp))
OBJFN=$(SRCFN:.cpp=.o)
OBJS= $(addprefix $(OBJDIR)/,$(OBJFN))
MAIN=main


all: $(OBJS) link
.PHONY: all

link: $(addprefix $(OBJDIR)/,$(OBJFN))
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

%.o:
	$(CC) -c $(CFLAGS) -o $@ $(SRCDIR)/$(notdir $(@:.o=.cpp))


clean:
	rm $(OBJDIR)/*.o
