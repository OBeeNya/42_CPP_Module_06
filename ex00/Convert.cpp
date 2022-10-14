#include "Convert.hpp"

Convert::Convert(const std::string arg):
	_arg(arg),
	_type(""),
	_char(""),
	_int(0),
	_double(0.0),
	_float(0.0f)
{
	this->_getType();
	return ;
}

Convert::~Convert(void)
{
	return ;
}

void	Convert::_getType(void)
{
	if (!this->_arg.compare("nan") || !this->_arg.compare("nanf") \
		|| !this->_arg.compare("-inf") || !this->_arg.compare("-inff") \
		|| !this->_arg.compare("+inf") || !this->_arg.compare("+inff"))
		return ;
	if (this->_typeInt())
	{
		this->_type = "int";
		if (atol(this->_arg.c_str()) < std::numeric_limits<int>::min() || \
			atol(this->_arg.c_str()) > std::numeric_limits<int>::max())
			throw (Convert::InputOverflow());
		this->_int = atoi(this->_arg.c_str());
		this->_double = static_cast<double>(this->_int);
		this->_float = static_cast<float>(this->_int);
		if (isprint(this->_int))
			this->_char = this->_int;
		else
			this->_char = "Non displayable";
	}
	else if (this->_typeDouble())
	{
		if (strtold(this->_arg.c_str(), NULL) < - std::numeric_limits<double>::max() - 1 || \
			strtold(this->_arg.c_str(), NULL) > std::numeric_limits<double>::max())
			throw (Convert::InputOverflow());
		this->_type = "double";
		this->_double = strtod(this->_arg.c_str(), NULL);
		this->_int = static_cast<int>(this->_double);
		this->_float = static_cast<float>(this->_double);
		if (isprint(this->_int))
			this->_char = this->_int;
		else
			this->_char = "Non displayable";
	}
	else if (this->_typeFloat())
	{
		if (strtod(this->_arg.c_str(), NULL) < - std::numeric_limits<float>::max() - 1 || \
			strtod(this->_arg.c_str(), NULL) > std::numeric_limits<float>::max())
			throw (Convert::InputOverflow());
		this->_type = "float";
		this->_float = strtof(this->_arg.c_str(), NULL);
		this->_int = static_cast<int>(this->_float);
		this->_double = static_cast<float>(this->_float);
		if (isprint(this->_int))
			this->_char = this->_int;
		else
			this->_char = "Non displayable";
	}
	else if (this->_typeChar())
	{
		this->_type = "char";
		this->_char = this->_arg;
		this->_int = static_cast<int>(this->_char.c_str()[0]);
		this->_double = static_cast<double>(this->_int);
		this->_float = static_cast<float>(this->_int);
		if (isprint(this->_int))
			this->_char = this->_int;
		else
			this->_char = "Non displayable";
	}
	else
		throw (Convert::InvalidInput());
}

bool	Convert::_typeInt(void) const
{
	if (this->_arg.find_first_not_of("-0123456789") == std::string::npos)
	{
		int	countneg = 0;
		for (int i = 0; i < this->_arg.length(); i++)
		{
			if (this->_arg[i] == '-')
				countneg++;
		}
		if (countneg > 1 || (countneg && (this->_arg[0] != '-' \
			|| this->_arg.length() == 1)))
			return (false);
		return (true);
	}
	return (false);
}

bool	Convert::_typeDouble() const
{
	if (!this->_arg.compare("-inf") || !this->_arg.compare("+inf") \
		|| !this->_arg.compare("nan"))
		return (true);
	if (this->_arg.find_first_not_of("-.0123456789") == std::string::npos)
	{
		if (this->_arg.find_first_not_of("-.") == std::string::npos)
			return (false);
		int	countp = 0;
		int	countn = 0;
		for (int i = 0; i < this->_arg.length(); i++)
		{
			if (this->_arg[i] == '.')
				countp++;
			if (this->_arg[i] == '-')
				countn++;
		}
		if (countp > 1 || countn > 1 || (countn && this->_arg[0] != '-'))
			return (false);
		return (true);
	}
	return (false);
}

bool	Convert::_typeFloat() const
{
	if (!this->_arg.compare("-inff") || !this->_arg.compare("+inff") \
		|| !this->_arg.compare("nanf"))
		return (true);
	if (this->_arg.find_first_not_of("-.0123456789f") == std::string::npos)
	{		
		if (this->_arg.find_first_not_of("-.f") == std::string::npos)
			return (false);
		int	countp = 0;
		int	countn = 0;
		int	countf = 0;
		for (int i = 0; i < this->_arg.length(); i++)
		{
			if (this->_arg[i] == '.')
				countp++;
			if (this->_arg[i] == '-')
				countn++;
			if (this->_arg[i] == 'f')
				countf++;
		}
		if (countp > 1 || countn > 1 || countf > 1 \
			|| (countn && this->_arg[0] != '-') \
			|| (this->_arg[this->_arg.length()- 1] != 'f'))
			return (false);
		return (true);
	}
	return (false);
}

bool	Convert::_typeChar() const
{
	if (this->_arg.length() == 1 && isprint(this->_arg[0]))
		return (true);
	return (false);
}

void	Convert::print(void) const
{
	if (!this->_arg.compare("nan") || !this->_arg.compare("nanf"))
	{
		this->printNan();
		return ;
	}
	else if (!this->_arg.compare("-inf") || !this->_arg.compare("-inff") \
		|| !this->_arg.compare("+inf") || !this->_arg.compare("+inff"))
	{
		this->printInf();
		return ;
	}
	std::cout << "char: " << this->_char << std::endl;
	std::cout << "int: " << this->_int << std::endl;
	std::cout.precision(std::numeric_limits<float>::max_digits10);
	std::cout << "float: " << this->_float;
	if (ceilf(this->_float) == this->_float)
		std::cout << ".0";
	std::cout << "f" << std::endl;
	std::cout.precision(std::numeric_limits<double>::max_digits10);
	std::cout << "double: " << this->_double;
	if (ceilf(this->_double) == this->_double)
		std::cout << ".0";
	std::cout << std::endl;
	return ;
}

void	Convert::printNan(void) const
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: nanf" << std::endl;
	std::cout << "double: nan" << std::endl;
	return ;
}

void	Convert::printInf(void) const
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	if (!this->_arg.compare("-inf") || !this->_arg.compare("+inf"))
	{
		if (!this->_arg.compare("-inf"))
			std::cout << "float: -inff" << std::endl;
		else
			std::cout << "float: +inff" << std::endl;
		std::cout << "double: " << this->_arg << std::endl;
	}
	else
	{
		std::cout << "float: " << this->_arg << std::endl;
		if (!this->_arg.compare("-inff"))
			std::cout << "double: -inf" << std::endl;
		else
			std::cout << "double: +inf" << std::endl;
	}
	return ;
}

const char	*Convert::InvalidInput::what(void) const throw()
{
	return ("Invalid input");
}

const char	*Convert::InputOverflow::what(void) const throw()
{
	return ("Input overflow");
}

