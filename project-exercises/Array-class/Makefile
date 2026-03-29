CXX = g++
CXXFLAGS = -Wall -std=c++17

TARGET = app
OBJS = app.o array.o

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

app.o : app.cpp array.h
	$(CXX) $(CXXFLAGS) -c app.cpp

array.o : array.cpp array.h
	$(CXX) $(CXXFLAGS) -c array.cpp

clean:
	rm -f $(OBJS) $(TARGET)