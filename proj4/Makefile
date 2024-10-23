#*****************************
#Name: Isaac Abella
#Collaboration with: Colton Coughlin
#Netid: iabella
#ID: 000641840
#
#Description: Remake test script in order to fit run time testing and compiling of the map_gen files simultaneously
#
#
#
#*****************************

CXX=		g++
CXXFLAGS=	-g -Wall -std=gnu++11
SHELL=		bash
PROGRAMS=	src/dijkstras src/map_gen

all:		src/dijkstras src/map_gen

dijkstras:	src/dijkstras.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# add in compilation script to run mapgen
map_gen: src/map_gen.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY:		test test-output test-memory clean create-map benchmark clean-slate

# remove temp files
clean:
	rm -f $(PROGRAMS)

# create-map runs the map_gen program and generates maps into the data dir.
create-map:
	@echo "GENERATING MAP FILES..."
	@./src/map_gen # Run map_gen as usual
	@mkdir -p data # Ensure the data directory exists
	@mv map_*.txt data/ # Move all generated map files to the data directory
	@echo "MAPS GENERATED AND MOVED TO data/..."


# since the mapgen uses filestream to create fileouts, we have to make global var targets here to run them in benchmark
# List of map sizes for testing
MAP_SIZES=	10 20 50 100 200 500 1000

#benchmark runs usr/bin/time -al in order to collect data for readme.
benchmark:
	@echo "RUNNING BENCHMARK SCRIPT."
	@echo "TESTING DIJKSTRA ALGORITHM WITH USR/BIN/TIME..."
	@for size in $(MAP_SIZES); do \
		map_file="data/map_$${size}x$${size}.txt"; \
		result_file="data/results_$${size}.txt"; \
		if [ -f $$map_file ]; then \
			echo "Running on $$map_file..."; \
			/usr/bin/time ./src/dijkstras < $$map_file 2> $$result_file; \
			echo "Map size: $$size x $$size" >> $$result_file; \
			echo "Results saved to $$result_file"; \
		else \
			echo "Error: $$map_file not found. Please run ./src/map_gen to generate the maps."; \
		fi; \
	done

clean-results:
	@echo "CLEANING UP MAP AND RESULT FILES..."
	rm -f data/map_*.txt data/results_*.txt data/map_list.txt
	@echo "CLEANUP COMPLETE."

test:		test-output test-memory

test-output:	src/dijkstras
	@echo Testing output 0...
	@./src/dijkstras < data/input0.txt | ~semrich/Public/checkproj4 data/input0.txt data/output0.txt
	@echo Testing output 1...
	@./src/dijkstras < data/input1.txt | ~semrich/Public/checkproj4 data/input1.txt data/output1.txt
	@echo Testing output 2...
	@./src/dijkstras < data/input2.txt | ~semrich/Public/checkproj4 data/input2.txt data/output2.txt
	@echo Testing output 3...
	@./src/dijkstras < data/input3.txt | ~semrich/Public/checkproj4 data/input3.txt data/output3.txt

test-memory:	src/dijkstras
	@echo Testing memory...
	@[ `valgrind --leak-check=full ./src/dijkstras < data/input1.txt 2>&1 | grep ERROR | awk '{print $$4}'` = 0 ]
