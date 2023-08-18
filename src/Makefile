#####################
# Simplist Make file
#####################
# # make command : dependencies
# httprequestmake: main.c http_request.c
# #   command to execute
# 	gcc main.c http_request.c -o ../out/http.out


#####################
# Make file 2       #
#####################
# CC=gcc
# # make command : since object files auto compile corresponding c files
# httprequestmake: main.o http_request.o 
# 	$(CC) -o http main.o http_request.o

############################
# Make file 3			   #
# Compile on header change #
############################
# CC=gcc
# DEPS = http_request.h
# CFLAGS=-Iinclude

# %.o: %.c $(DEPS)
# 	$(CC) -c -o $@ $< $(CFLAG)

# httprequestmake: main.o http_request.o 
# 	$(CC) -o http.o main.o http_request.o


IDIR   = include
CC     = gcc
CFLAGS = -I$(IDIR)

ODIR   = ../out
LDIR   = ../lib

LIBS   = -lm

_DEPS  = http_request.h
DEPS   = $(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ   = main.o http_request.o
OBJ    = $(patsubst %, $(ODIR)/%, $(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

http: $(OBJ)
	$(CC) -o ../build/$@ $^ $(CFLAGS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

