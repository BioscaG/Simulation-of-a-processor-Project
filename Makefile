OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Proceso.o Procesador.o Cluster.o Prioridad.o Area_espera.o
	g++ -o program.exe *.o 

Proceso.o: Proceso.cc
	g++ -c Proceso.cc $(OPCIONS) 

Procesador.o: Procesador.cc
	g++ -c Procesador.cc $(OPCIONS)

Cluster.o: Cluster.cc
	g++ -c Cluster.cc $(OPCIONS)

Prioridad.o: Prioridad.cc
	g++ -c Prioridad.cc $(OPCIONS)

Area_espera.o: Area_espera.cc
	g++ -c Area_espera.cc $(OPCIONS)

program.o: program.cc
	g++ -c program.cc $(OPCIONS)

clean:
	rm -f *.o
	rm -f *.exe



practica.tar: *.cc *.hh
	tar -cvf practica.tar Area_espera.cc Cluster.cc Prioridad.cc Procesador.cc Proceso.cc program.cc Area_espera.hh Prioridad.hh BinTree.hh Cluster.hh Procesador.hh Proceso.hh Makefile html.zip
