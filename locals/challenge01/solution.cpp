// Challenge 01: Rotating Arrays; null solution

/*
 Name: Isaac Abella
 netid iabella
 id 000641840

Description: given an input of n integers, a number r, and a direction d (left or right)
we want to be able to shift the array the correct amount of times to match expected output
do not use stl functions like swap or rotate, just the stl container for vector

*/

#include <iostream>
#include <vector>

void Rotate_Left(std::vector<int>& numbers_in_array, int size, int rotations){
		int modify = rotations % size;
		std::vector<int> temp(size);

		// store rotate result in temp vector
		for (int i = 0; i < size; i++){
			temp[i] = numbers_in_array[(i + modify) % size];
		}


		// output new vector
		for(int i = 0; i < size; i++){
			if(i > 0) std::cout << ' '; // I made this change based on the discussion on piazza about not having a space at the
						    // end of the vector
			std::cout << temp[i];
		}
		std::cout << std::endl;
}

void Rotate_Right(std::vector<int>& numbers_in_array, int size, int rotations){
		int modify = rotations % size;
		std::vector<int> temp(size);

		// store rotate result in temp vector
		for (int i = 0; i < size; i++){
			temp[i] = numbers_in_array[(i - modify + size) % size];
		}

		// output new vector
		for(int i = 0; i < size; i++){
			if(i > 0) std::cout << ' ';
			std::cout << temp[i];		
		}
		std::cout << std::endl;
}


int main(int argc, char *argv[]) {	
  int size, rotations;
  char direction;

  // use a while loop to process input until eof
  while(std::cin >> size >> rotations >> direction){
  	std::vector<int> numbers_in_array(size);
 	
       	// populate vector
 	 for(int i = 0; i < size; ++i){
  		std::cin >> numbers_in_array[i];
 	 }

  	// now we have to do the logic of the rotations for left or right.

  	if(direction != 'L' && direction != 'R'){
  		std::cerr << "Error, bad input for rotations";
		return 1;
 	 }
  	if(direction == 'L'){
  		Rotate_Left(numbers_in_array, size, rotations);
  	}else {
  		Rotate_Right(numbers_in_array, size, rotations);
 	}
	// I think that you guys said not to error check to hard, but we could add a continue or std::err if direction wasn't fed in properly
	
    }

  return 0;
}
