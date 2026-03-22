CXX = g++
CXXFLAGS = -Wall -std=c++17

myprogram : Course.o app.o
	g++ Course.o app.o -o myprogram

Course.o : Course.cpp Course.h
	$(CXX) $(CXXFLAGS) -c Course.cpp

app.o : app.cpp Course.h
	${CXX} ${CXXFLAGS} -c -c app.cpp

clean :
	rm -f *.o myprogram
	