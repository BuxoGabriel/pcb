CC = gcc
CFLAGS = -Wall -Werror -std=c99
OBJECTS = pcb.o scheduler.o main.o rcb.o
SRCDIR = src
OUTDIR = out
TARGET = $(OUTDIR)/main

makeall: $(OUTDIR) $(TARGET)
$(TARGET): $(addprefix $(OUTDIR)/, $(OBJECTS))
	$(CC) $(CFLAGS) -o $@ $^

$(OUTDIR):
	mkdir $(OUTDIR)

$(OUTDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm ./out/*
