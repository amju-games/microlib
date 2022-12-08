all:microlib_tests_exe

clean:
	rm microlib_tests *.o ../*.o 

run:
	./microlib_tests


CC=clang++

WARNINGS=-Wall -Wno-deprecated-declarations

INCLUDES=\
  -I..

CFLAGS=-c $(WARNINGS) $(INCLUDES) -std=c++11   -DMACOSX

LDFLAGS=-framework OpenGL -framework GLUT

SOURCES= \
catch_test_main.cpp \
message_queue_tests.cpp \
../game.cpp \
../game_object.cpp \
../message_queue.cpp \
../timer.cpp

#../sweep_and_prune.cpp \

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=microlib_tests

microlib_tests_exe: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

