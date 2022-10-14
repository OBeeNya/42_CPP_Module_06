#include "Base.hpp"

Base	*generate(void)
{
	int	r;

	srand(time(NULL));
	r = rand() % 100;
	std::cout << std::endl;
	std::cout << "Real type: ";
	if (!(r % 3))
	{
		std::cout << "A" << std::endl;
		return (new A);
	}
	else if (!(r % 2))
	{
		std::cout << "B" << std::endl;
		return (new B);
	}
	else
	{
		std::cout << "C" << std::endl;
		return (new C);
	}
}

void	identify(Base *p)
{
	std::cout << "Identified type: ";
	A	*a = dynamic_cast<A *>(p);
	if (a)
		std::cout << "A" << std::endl;
	B	*b = dynamic_cast<B *>(p);
	if (b)
		std::cout << "B" << std::endl;
	C	*c = dynamic_cast<C *>(p);
	if (c)
		std::cout << "C" << std::endl;
}

void	identify(Base &p)
{
	std::cout << "Identified type: ";
	try
	{
		A	a = dynamic_cast<A &>(p);
		std::cout << "A" << std::endl;
	}
	catch (std::bad_cast &e) {}
	try
	{
		B	b = dynamic_cast<B &>(p);
		std::cout << "B" << std::endl;
	}
	catch (std::bad_cast &e) {}
	try
	{
		C	c = dynamic_cast<C &>(p);
		std::cout << "C" << std::endl;
	}
	catch (std::bad_cast &e) {}
}

int	main(void)
{
	std::cout << std::endl;
	std::cout << " *** Identification through ptr *** " << std::endl;
	{
		Base	*base = generate();
		identify(base);
		delete base;
	}

	std::cout << std::endl;
	std::cout << " *** Identification through ref *** " << std::endl;
	{
		Base	&base = *generate();
		identify(base);
		delete &base;
	}

	std::cout << std::endl;
	return (0);
}
