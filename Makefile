# fichero Makefile
#
# nombre del fichero ejecutable
#
TARGETS= practica

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuración
#
CFLAGS=    -g -DXWINDOWS -DSHM -I/usr/include -I.
CXXFLAGS=  -g -DXWINDOWS -DSHM -I/usr/include -I.

# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
LDFLAGS=  -lGLU -lGL -lglut

# definicion del compilador
#
CC = g++

# orden que sera ejecutada por defecto
#
default : $(TARGETS)

# regla de ejecucion
#
$(TARGETS) : practica1.o file_ply_stl.o figura.o socom.o mine.o Cocacola.o jpg_imagen.o jpg_memsrc.o jpg_readwrite.o textura_imagen.o fuente_luz.o Materiales.o
	$(CC) -o $@ $(CXXFLAGS) practica1.o file_ply_stl.o figura.o socom.o mine.o Cocacola.o jpg_imagen.o jpg_memsrc.o jpg_readwrite.o textura_imagen.o fuente_luz.o Materiales.o $(LDFLAGS)
#	./practica beethoven.ply
#
#
clean:
	rm -f *.o
	rm -f $(TARGETS)

#
#
redo:
	touch *.cc
	make

#
#
superclean:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)

#
#
tgz:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)
	tar -zcvf $(TARGETS).tgz *

