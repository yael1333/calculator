/* 
	calculator: 
	takes a calculation from the user and performs it,
	printing the result.
	Input should be entered with a space between every 2 characters.
	example :  7 * ( 5 + 8 ) 

*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main()
{
	float evaluate(std::vector<std::string> vector, float current_value, std::string operation);
	std::cout << "ENTER CALCULATION:\n";
	std::string calc;
	getline(std::cin, calc);
	std::stringstream stream(calc); //creating a stream that holds the input
	std::string a;
	char space = ' ';
	std::vector<std::string> calc_vec; //creating a vector
	//separating the input by spaces and pushing into the vector
	while (getline(stream, a, space))
	{
		calc_vec.push_back(a);
	}
	// calling the evaluate function and printing the result
	float result = evaluate(calc_vec, -1000, "");
	printf("result: %f\n", result);
	
	return 0; 
}

bool is_operation(std::string str)
// this function returns true if the recieved string is an operation, false otherwise.
{
	if (str=="+" || str=="-" || str=="*" || str=="/")
		return true;
	return false;
}

float evaluate(std::vector<std::string> vector, float current_value, std::string operation)
// recieves a vector, a float (-1000 by default) and a string, and returns the result of the computation (float)
{
	bool is_operation(std::string str);
	std::string c;
	int i = 0;   // vector index
	
	while (i<vector.size())
	{
		c = vector[i];
		if (c=="(")
		{
			int open_index = i;
			int close_index = 0;
			int pair_count = 1;
			for (int j=i+1; j<vector.size(); j++)
			{
				if (vector[j]=="(")
					pair_count++;
				else if (vector[j] == ")")
				{
					pair_count--;
					if (pair_count==0)
					{
						close_index = j;
						break;
					}
				}
			}
			// now open_index holds the index of our ( , and close_index holds the index of its matching )
			std::vector<std::string> small_vector; // this vector will hold only what's inside the parentheses.
			for (int j=open_index+1; j<close_index; j++)
			{
				small_vector.push_back(vector[j]);
			}
			// if there's a previous value 
			if (current_value!=-1000)
			{
				if (operation=="+")
					current_value= current_value + evaluate(small_vector, -1000, "");
				else if (operation=="-")
					current_value = current_value - evaluate(small_vector, -1000, "");
				else if (operation=="*")
					current_value = current_value * evaluate(small_vector, -1000, "");
				else if (operation=="/")
					current_value = current_value / evaluate(small_vector, -1000, "");
			}
			// if there isn't a previous value to start with
			else
			{
				current_value = evaluate(small_vector, -1000, "");
			}
			i = close_index; // we want the loop to continue running from the end of our parenthesis
		}
		else if (is_operation(c))
		{
			operation=c;
		}
		else
		// c isn't ( or an operation, meaning it's a number
		{
			// if there isn't a previous value to start with
			if (current_value==-1000)
				current_value = std::stof(c);
			// if there's a previous value 
			else
			{
				if (operation=="+" || operation=="-") 
				// because * and / should be executed before + and -, we use a recursive call
				{
					std::vector<std::string> small_vector; // this vector will contain only what's after the operation
					for (int j=i; j<vector.size(); j++)
					{
						small_vector.push_back(vector[j]);
					}
					// recursive calls
					if (operation=="+")
						return current_value + evaluate(small_vector, -1000, " ");
					else if (operation=="-")
						return current_value - evaluate(small_vector, -1000, " ");
				}
				// * and / can be executed immidiately and therefore can also act as the base of our recursion 
				else if (operation=="*")
				{
					current_value = current_value * std::stof(c);  // c is a string so we convert it into a float
				}
				else if (operation=="/")
				{
					current_value = current_value / std::stof(c);  // c is a string so we convert it into a float
				}		
			}
		}
		i++;   //incremating i to move forward in the vector
	}
	return current_value; // returning the result
}








