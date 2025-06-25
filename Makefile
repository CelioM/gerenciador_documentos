tp_execution: build/documentmanager.o build/documento.o build/usuario.o build/util.o build/main.o
	c++ build/documentmanager.o build/documento.o build/usuario.o build/util.o build/main.o -o tp_execution

build/documentmanager.o: src/documentmanager.cpp include/documentmanager.h
	c++ -c src/documentmanager.cpp -o build/documentmanager.o -I include/

build/documento.o: src/documento.cpp include/documento.h
	c++ -c src/documento.cpp -o build/documento.o -I include/

build/usuario.o: src/usuario.cpp include/usuario.h
	c++ -c src/usuario.cpp -o build/usuario.o -I include/

build/util.o: src/util.cpp include/util.h
	c++ -c src/util.cpp -o build/util.o -I include/

build/main.o: src/main.cpp 
	c++ -c src/main.cpp -o build/main.o -I include/

clean : 
	rm -f build/*.o