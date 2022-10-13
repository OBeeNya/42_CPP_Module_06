#include "Convert.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Error" << std::endl << "This program takes one argument" \
		<< std::endl;
		return (1);
	}

	std::string	arg = av[1];
	try
	{
		Convert	convert(arg);
		convert.print();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	return (0);
}
