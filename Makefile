OBJ = rpg_server.o DB_Object.o DBfile.o screen.o
HEADERS = DB_Object.h DBfile.h screen.h

main: $(OBJ)
	c++ -o main $(OBJ)

clean:
	rm -f main $(OBJ) *.7z *.zip
