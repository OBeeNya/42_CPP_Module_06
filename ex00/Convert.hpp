#ifndef CONVERT_HPP
# define CONVERT_HPP

# include <iostream>
# include <stdexcept>
# include <limits>
# include <cmath>

class	Convert
{

	private:

		Convert(void);
		Convert(const Convert &src);

		Convert	&operator=(const Convert &rhs);

		void	_getType(void);
		bool	_typeInt(void) const;
		bool	_typeDouble(void) const;
		bool	_typeFloat(void) const;
		bool	_typeChar(void) const;

		std::string	_arg;
		std::string	_char;
		int			_int;
		double		_double;
		float		_float;

	public:

		Convert(const std::string arg);
		~Convert(void);

		void	print(void) const;
		void	printNan(void) const;
		void	printInf(void) const;

		class	InvalidInput:
			public std::exception
		{
			public:
				virtual const char*	what(void) const throw();
		};

		class	InputOverflow:
			public std::exception
		{
			public:
				virtual const char*	what(void) const throw();
		};
};

#endif
