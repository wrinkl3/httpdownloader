CC=gcc
CFLAGS=-I. -g -Wall
DEPS = DownloadManager.h
OBJ = httpdownloader.o DownloadManager.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

httpdownloader: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o *~ core *~