all:microlib_tests_exe

clean:
	rm microlib_tests *.o ../*.o 

run:
	./microlib_tests


CC=clang++

WARNINGS=-Wall -Wextra -Werror -Wno-deprecated-declarations

INCLUDES=\
  -I..

CFLAGS=-c $(WARNINGS) $(INCLUDES) -std=c++2a -DMACOSX

LDFLAGS=-framework Carbon

SOURCES= \
catch_test_main.cpp \
config_file_tests.cpp \
directory_tests.cpp \
double_dispatcher_tests.cpp \
file_string_utils_tests.cpp \
message_queue_tests.cpp \
multi_manager_tests.cpp \
resource_manager_tests.cpp \
string_utils_tests.cpp \
../config_file.cpp \
../directory.cpp \
../file.cpp \
../file_string_utils.cpp \
../game.cpp \
../game_object.cpp \
../message_queue.cpp \
../string_utils.cpp \
../timer.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=microlib_tests

microlib_tests_exe: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

