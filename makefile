objects = math.o color.o debug.o main.o menù.o OnlyPrintfSystem.o OPSo.o Parser.o in.o time.o\
		setting.o system.o Pengine.o SDL_core.o shell.o type.o object.o SDL_interface.o

cspace: $(objects)
		cc -o cspace $(objects) -O2 -Wall -lm -lSDL2

$(objects):

clean:
	rm $(objects)
