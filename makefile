all: project2_first.out project2_second.out

project2_first.out: Dictionary.cpp project2_first.cpp Hash24.cpp
	g++ -std=c++11 $^ -o $@

project2_second.out: Dictionary.cpp project2_second.cpp Hash24.cpp
	g++ -std=c++11 $^ -o $@

clean:
	rm -f *.out