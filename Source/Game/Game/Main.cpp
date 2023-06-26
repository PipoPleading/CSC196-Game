#include <iostream>
// "#" is preprocessor directive
int main() 
{
#ifdef _DEBUG
	std::cout << "debug!" << std::endl;
#endif
	std::cout << "yo watup" << std::endl;
}
