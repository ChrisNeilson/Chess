CXX = g++
CXXFLAGS = -Wall -MMD -Wno-switch -std=c++0x -g
INCLUDES = -I/opt/X11/include
LDFLAGS = -L/opt/X11/lib
LIBS = -lX11
SRCS = main.cc ai.cc ai1.cc ai2.cc ai3.cc ai4.cc bishop.cc cell.cc \
			 gameManager.cc grid.cc human.cc king.cc knight.cc pawn.cc \
			 piece.cc player.cc queen.cc rook.cc setup.cc window.cc
OBJECTS = ${SRCS:.cc=.o}
EXEC = chess

.PHONY: depend clean

all: ${EXEC}

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${INCLUDES} -o ${EXEC} ${OBJECTS} ${LDFLAGS} ${LIBS}

.cc.o:
	${CXX} ${CXXFLAGS} ${INCLUDES} -c $< -o $@

clean:
	rm ${OBJECTS} ${EXEC} *.d

depend: ${SRCS}
	makedepend ${INCLUDES} $^

.PHONY: zip
zip:
	zip chess.zip Makefile *.h *.cc
