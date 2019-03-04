# I get a compilation with the following command
# g++ -Wreturn-stack-address  src/main.cpp -o main -DSFML_STATIC -I /Users/Hipster/SFML/include -L /Users/Hipster/SFML/lib -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system



CXX = g++
VPATH = src
SFML_FLAGS =  -L /Users/Hipster/SFML/lib -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system 
# MIDI_FLAGS =  -ljack
MIDI_LAGS =  -L -framework CoreMIDI -framework CoreAudio -framework CoreFoundation
# CPPFLAGS =  -L /Users/Hipster/SFML/lib -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system -framework CoreMIDI -framework CoreAudio -framework CoreFoundation
# CXXFLAGS = -Wreturn-stack-address -Wall -Werror -Wextra -pedantic -std=c++17 -g -fsanitize=address -D__UNIX_JACK__
CXXFLAGS = -Wreturn-stack-address -Wall  -D__MACOSX_CORE__ -std=c++11 
# LDFLAGS =  -fsanitize=address

# SRC = 
# OBJ = $(SRC:.cc=.o)
# EXEC = MakeFile

PianoGenerator: main.cpp 
	g++ $(CXXFLAGS) $^ RtMidi.cpp $(MIDI_FLAGS) $(SFML_FLAGS) 

# main.o: main.cpp MIDI.o 
# g++ -c 
