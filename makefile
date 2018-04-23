.PHONY: vectorizedtree clean

vectorizedtree: main.cpp unittests.cpp
	g++ -std=c++14 -o vectorizedtree main.cpp unittests.cpp -I.