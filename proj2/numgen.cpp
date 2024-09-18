// random number generation

#include <iostream>
#include <cstdlib>
#include <ctime>

int main(){
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	for(int i = 0; i <= 10000; ++i){
	
		std::cout << (std::rand() % 1000) + 1 << '\t';
		if(i % 1 == 0){
			std::cout << '\n';
		}	
	}
	return 0;
}

