#include <Mage.h>
#include <iostream>
#include <Environment.h>
#include <EnvironmentManager.h>

int main(int argc, char ** argv)
{
	tw::Environment * environment = tw::EnvironmentManager::getInstance()->getRandomEnvironment();
	Mage * mageTest = new Mage(environment, 1, 0, 0);

	std::cout << mageTest->getBaseAttack() << std::endl;

	delete mageTest;
	delete environment;
	return 0;
}