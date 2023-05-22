CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla
OBJECTS = academic.o controller.o coopfee.o dctims.o goose.o gotims.o grid.o gym.o main.o needleshall.o osap.o ownable.o player.o property.o residence.o slc.o tuition.o unownable.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = a_watopoly

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
