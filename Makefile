CC = gcc
CFLAGS = -Wall -Werror -std=c99
OBJECTS = pcb.o scheduler.o main.o
OUTDIR = out

$(OUTDIR)/main: $(addprefix $(OUTDIR)/, $(OBJECTS))
	$(CC) $(CFLAGS) -o $@ $^

$(OUTDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm ./out/*
