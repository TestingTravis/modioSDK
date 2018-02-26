#include "modio.h"

int main(void)
{
	modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

	volatile static bool finished = false;

	auto wait = [&]()
	{
		while (!finished)
		{
			modio_instance.sleep(10);
			modio_instance.process();
		}
	};

	auto finish = [&]()
	{
		finished = true;
	};

	u32 mod_id;
	std::cout << "Enter the mod id: " << std::endl;
	std::cin >> mod_id;

	u32 dependency_id;
	std::cout << "Enter the dependency id: " << std::endl;
	std::cin >> dependency_id;

	std::vector<u32> dependencies;
	dependencies.push_back(dependency_id);

	// We delete dependencies from a mod by providing the mod and dependencies ids
	// Dependencies to be deleted are contained in a vector
	modio_instance.deleteModDependencies(mod_id, dependencies, [&](const modio::Response& response)
	{
		std::cout << "Delete mod dependencies response: " << response.code << std::endl;
		if (response.code == 204)
		{
			std::cout << "Dependencies deleted successfully" << std::endl;
		}
		finish();
	});

	wait();

	std::cout << "Process finished" << std::endl;

	return 0;
}
