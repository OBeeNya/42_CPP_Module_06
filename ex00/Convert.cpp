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
	std::cout << "type : " << this->_type << std::endl;
	return ;
}

Convert::~Convert(void)
{
	return ;
}

void	Convert::_getType(void)
{
	if (this->_typeInt())
		this->_type = "int";
	else if (this->_typeDouble())
		this->_type = "double";
	else if (this->_typeFloat())
		this->_type = "float";
	// else if (this->_typeChar())
	// 	this->_type = "char";
	else
		this->_type = "char";
		// throw (Convert::InvalidInput());
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
		if (countneg > 1)
			return (false);
		if (countneg && (this->_arg[0] != '-' || this->_arg.length() == 1))
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
		if (countp > 1 || countn > 1)
			return (false);
		if (countn && this->_arg[0] != '-')
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
		if (countp > 1 || countn > 1 || countf > 1)
			return (false);
		if (countn && this->_arg[0] != '-')
			return (false);
		if (this->_arg[this->_arg.length()- 1] != 'f')
			return (false);
		return (true);
	}
	return (false);
}

bool	Convert::_typeChar() const
{
	return (true);
	// return (false);
}

void	Convert::print(void) const
{
	std::cout << "char: " << this->_char << std::endl;
	std::cout << "int: " << this->_int << std::endl;
	std::cout << "float: " << this->_float << std::endl;
	std::cout << "double: " << this->_double << std::endl;
	return ;
}

const char	*Convert::InvalidInput::what(void) const throw()
{
	return ("Invalid input");
}