#include "Data.hpp"

uintptr_t	serialize(Data *ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data	*deserialize(uintptr_t	raw)
{
	return (reinterpret_cast<Data *>(raw));
}

int	main(void)
{
	Data		data;
	uintptr_t	u;

	data.str = "0123456789_abcdef";

	std::cout << std::endl;
	std::cout << " *** Checking data before serialization *** " << std::endl;
	std::cout << "Data1 address: " << &data << std::endl;
	std::cout << "Data1 str: " << data.str << std::endl;

	std::cout << std::endl;
	std::cout << " *** Serialization... *** " << std::endl;;
	u = serialize(&data);

	std::cout << std::endl;
	std::cout << " *** Deserialization on the same instance of Data... *** " << std::endl;;
	data = *deserialize(u);

	std::cout << std::endl;
	std::cout << " *** Deserialization on an other instance of Data... *** " << std::endl;;
	Data data2 = *deserialize(u);

	std::cout << std::endl;
	std::cout << " *** Rechecking data *** " << std::endl;
	std::cout << "Data1 address: " << &data << std::endl;
	std::cout << "Data1 str: " << data.str << std::endl;
	std::cout << "Data2 address: " << &data2 << std::endl;
	std::cout << "Data2 str: " << data2.str << std::endl;

	std::cout << std::endl;
	return (0);
}
