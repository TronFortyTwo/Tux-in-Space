CXXFLAGS = -Wall -g -std=gnu++17 -lstdc++fs

# write them in logic order
objects = \
		debug.o\
		math.o\
		generic.o\
		setting.o\
		in.o\
		color.o\
		main.o\
		OnlyPrintfSystem.o\
		type.o\
		typeSTR.o\
		time.o\
		Pengine.o\
		object.o\
		system.o\
		Parser.o\
		running.o\
		OPSo.o\
		menu.o
# like object but whit .h but without main.h and with generic.h
libraries = \
		debug.h\
		math.h\
		generic.h\
		setting.h\
		in.h\
		color.h\
		OnlyPrintfSystem.h\
		type.h\
		typeSTR.h\
		time.h\
		Pengine.h\
		object.h\
		system.h\
		Parser.h\
		running.h\
		OPSo.h\
		menu.h

Tux in Space: $(objects) $(libraries)
		g++ -o tuxinspace $(CXXFLAGS) $(objects) -lstdc++fs

$(objects):

clean:
	rm *.o
	rm *.ghc
	rm *.h.ghc
	rm Tux in Space
