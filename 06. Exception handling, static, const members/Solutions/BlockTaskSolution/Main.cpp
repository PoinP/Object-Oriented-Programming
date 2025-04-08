#include <iostream>

#include "Block.h"
#include "Person.h"
#include "Encryptor.h"


int main()
{
	BasicString encryptionKey = "a'vP0d*DY^&MU_vN=!5^bhNhO4^`3'";
	Encryptor e(encryptionKey.getString(), 12);

	Person p("Ivan", "Kolev", "0423123421");

	Block block0(p, "VerySecretPassword", e);
	Block block1(p, "VerySecretPassword2", block0);
	Block block2(p, "VerySecretPassword3", block1);

	BlockData* lastBlockData = block2.getReport("VerySecretPassword3");
	const Block* rootBlock = block2.getRoot();
	BlockData* invalidBlockData = rootBlock->getReport("Wrong Password");
	BlockData* rootBlockData = rootBlock->getReport("VerySecretPassword");

	std::cout << "Expected: " << "VerySecretPassword3" << " | Actual: " << lastBlockData->getBlockPassword().getString() << "\n";
	std::cout << "Expected: " << "VerySecretPassword" << " | Actual: " << rootBlockData->getBlockPassword().getString() << "\n";
	std::cout << "Nullptr: " << std::boolalpha << (invalidBlockData == nullptr);

	delete lastBlockData;
	delete invalidBlockData;
	delete rootBlockData;
}