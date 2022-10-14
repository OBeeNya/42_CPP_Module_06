#ifndef BASE_HPP
# define BASE_HPP

# include <cstdlib>
# include <ctime>
# include <iostream>
# include <sys/time.h>

class	Base
{
	public:
		virtual ~Base(void) {}
};

class	A: public Base {};
class	B: public Base {};
class	C: public Base {};

#endif
