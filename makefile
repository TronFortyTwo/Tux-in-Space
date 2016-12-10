CFLAGS = -Wall -g

objects = math.o color.o debug.o main.o menù.o OnlyPrintfSystem.o OPSo.o\
		setting.o system.o Pengine.o type.o shell.o object.o Parser.o\
		in.o time.o
libraries = math.h color.h debug.h menù.h OnlyPrintfSystem.h OPSo.h\
		setting.h system.h Pengine.h type.h shell.h object.h Parser.h\
		in.h time.h generic.h

cspace: $(objects) $(libraries)
		cc -o cspace $(objects) -lm

$(objects):

clean:
	rm *.o
	rm *.ghc
