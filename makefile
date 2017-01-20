CXXFLAGS = -Wall -g

# write them in logic order
objects = \
		generic.o\
		setting.o\
		in.o\
		math.o\
		color.o\
		main.o\
		OnlyPrintfSystem.o\
		type.o\
		typeSTR.o\
		time.o\
		object.o\
		system.o\
		Parser.o\
		shell.o\
		OPSo.o\
		menù.o\
		debug.o\
# like object but whit .h but without main.h and with generic.h
libraries = \
		generic.h\
		setting.h\
		in.h\
		math.h\
		color.h\
		OnlyPrintfSystem.h\
		type.h\
		typeSTR.h\
		time.h\
		object_data.h\
		object.h\
		system.h\
		Parser.h\
		shell.h\
		OPSo.h\
		menù.h\
		debug.h\

cspace: $(objects) $(libraries)
		g++ -o cspace $(CXXFLAGS) $(objects)

$(objects):

clean:
	rm *.o
	rm *.ghc
	rm *.h.ghc
	rm cspace
