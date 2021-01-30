CXX     = g++
CXXFLAGS = -Wall -g -std=c++11
CCLINK = $(CXX)
OBJS   = main.o libfirewall.so libinput.so field.o string.o ip.o port,o 
EXEC  =  firewall.exe
RM = rm -fr *.o *.exe

$(EXEC): main.o libfirewall.so libinput.so
	$(CCLINK) main.o libfirewall.so libinput.so -o $(EXEC)

main.o: main.cpp input.h
	$(CCLINK) $(CXXFLAGS) -c main.cpp


field.o: field.cpp field.h
	$(CCLINK) $(CXXFLAGS) -c -fpic field.cpp
	
string.o: string.cpp string.h
	$(CCLINK) $(CXXFLAGS) -c -fpic string.cpp

ip.o: ip.cpp ip.h
	$(CCLINK) $(CXXFLAGS) -c -fpic ip.cpp

port.o: port.cpp port.h
	$(CCLINK) $(CXXFLAGS) -c -fpic port.cpp

libfirewall.so: ip.o field.o port.o string.o
	$(CCLINK) -shared ip.o field.o port.o string.o -o libfirewall.so



clean:
	$(RM)

