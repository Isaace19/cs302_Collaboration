CXX=		g++
CXXFLAGS=	-g -Wall -std=gnu++11 -pg
SHELL=		bash
PROGRAMS=	src/dijkstras src/mapgen

# List of map sizes for testing
MAP_SIZES=	10 20 50 100 200 500 1000

all:		src/dijkstras src/mapgen

# Compile Dijkstra's algorithm
dijkstras:	src/dijkstras.cpp
	$(CXX) $(CXXFLAGS) -o src/dijkstras src/dijkstras.cpp

# Compile map generator
mapgen:	src/mapgen.cpp
	$(CXX) $(CXXFLAGS) -o src/mapgen src/mapgen.cpp

# Clean target to remove generated programs
.PHONY: clean
clean:
	rm -f $(PROGRAMS)

# Clean target to remove benchmark results and map files
.PHONY: clean-results
clean-results:
	rm -f map_*.txt results_*.txt

# Run Dijkstra's on each generated map and output timing stats, CPU, and memory usage
.PHONY: run-benchmark
run-benchmark: src/dijkstras
	@echo "Running benchmarks for Dijkstra's algorithm..."
	@for size in $(MAP_SIZES); do \
		map_file="map_$${size}x$${size}.txt"; \
		result_file="results_$${size}.txt"; \
		if [ -f $$map_file ]; then \
			echo "Running on $$map_file..."; \
			/usr/bin/time ./src/dijkstras < $$map_file 2> $$result_file; \
			echo "Map size: $$size x $$size" >> $$result_file; \
			echo "Results saved to $$result_file"; \
		else \
			echo "Error: $$map_file not found. Please run ./src/mapgen to generate the maps."; \
		fi; \
	done

# General placeholder for other tests
.PHONY: test
test:
	@echo "No tests defined. Use 'make run-benchmark' for benchmarking."
