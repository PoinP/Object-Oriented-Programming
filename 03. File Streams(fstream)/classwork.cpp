// Този файлсъдържа интересни особености и подробности при
// работа с тесктови и биарни файлове, обработка на динамична памет
// и работа с бинарни файлове под Windows

// Правилно четене на тесктови файлове
int main()
{
	std::ifstream ifs("text.txt");

    int num;
	while (ifs >> num)
	{
		std::cout << num << "\n";
	}
}

// или
int main()
{
	std::ifstream ifs("text.txt");

	while (ifs)
	{
		int num;
		ifs >> num;

		if (!ifs.good())
			break;

		std::cout << num << "\n";
	}
}

int main()
{
	std::ifstream ifs("text.txt");

	char buff[256];

	while (ifs.getline(buff, 256))
	{
		std::cout << buff << "\n";
	}
}


// Пробелмът ако изпуснем std::ios::binary при бинарните файлове под Windows
// Под Linux и MacOS този проблем не съществува
// При Windows, ако запишем '\n'(10) без да вдигнем флага std::ios::binary, то ще се запишат два сивмола CR(Carrage Return) и LF(Нов ред)
// Това ще доведе до проблеми ако четем файла с вдигнат std::ios::binary или се чете от Linux или MacOS
int main()
{
	int numberArray[4]{ 23, '\n', 7, 10};
	int number = 10;

	std::ofstream ofs("numbers.bin", std::ios::binary);
	ofs.write(reinterpret_cast<const char*>(numberArray), 4 * sizeof(int));
	ofs.write(reinterpret_cast<const char*>(&number), sizeof(int));
	ofs.close();

	int readNumbers[4];
	int readNumber;
	std::ifstream ifs("numbers.bin", std::ios::binary);
	ifs.read(reinterpret_cast<char*>(readNumbers), 4 * sizeof(int));
	ifs.read(reinterpret_cast<char*>(&readNumber), sizeof(int));
	ifs.close();

	for (int i = 0; i < 4; i++)
	{
		std::cout << readNumbers[i] << " ";
	}
}

// Писане и четене от файл, който съдържа само масива ни
int main()
{
    int dynamicArrSize = 3;
    int* dynamicArr = new int[dynamicArrSize] { 3, 4, 5 };

    std::ofstream ofs("dynamicArr.bin", std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(dynamicArr), 3 * sizeof(int));
    ofs.close();

    std::ifstream ifs("dynamicArr.bin", std::ios::binary);
    ifs.seekg(0, std::ios::end);                        /////////
    unsigned arraySize = ifs.tellg() / sizeof(int);     // Работи само ако файла е пълен с елемнти от един и същ тип. Тоест ако сме записали само маисва във файла.
    ifs.seekg(0, std::ios::beg);                        /////////

    int* newDynamicArr = new int[arraySize];
    ifs.read(reinterpret_cast<char*>(newDynamicArr), arraySize * sizeof(int));
    ifs.close();

    for (int i = 0; i < arraySize; i++)
    {
        std::cout << newDynamicArr[i] << " ";
    }

    delete[] newDynamicArr;
    delete[] dynamicArr;
}

// Стандартен начин за писане и четене на динамичен масив от файл
int main()
{
	int dynamicArrSize = 3;
	int* dynamicArr = new int[dynamicArrSize] { 3, 4, 5 };

	std::ofstream ofs("dynamicArr.bin", std::ios::binary);
	ofs.write(reinterpret_cast<const char*>(&dynamicArrSize), sizeof(int));
	ofs.write(reinterpret_cast<const char*>(dynamicArr), 3 * sizeof(int));
	ofs.close();

	std::ifstream ifs("dynamicArr.bin", std::ios::binary);

	int arraySize;
	ifs.read(reinterpret_cast<char*>(&arraySize), sizeof(int));

	int* newDynamicArr = new int[arraySize];
	ifs.read(reinterpret_cast<char*>(newDynamicArr), arraySize * sizeof(int));
	ifs.close();

	for (int i = 0; i < arraySize; i++)
	{
		std::cout << newDynamicArr[i] << " ";
	}

	delete[] newDynamicArr;
	delete[] dynamicArr;
}

// Писане и четене на деинамичен низ
// Можем да го запишем и без да слагаме размера в началото и да се водим по
// терминиращата нула. Или да го запишем без терминиращата нула и да се водим
// само по размера зададен преди съдъражението на самия низ
int main()
{
	char str[] = "Hello world";
	int strSize = strlen(str) + 1;

	std::ofstream ofs("dynamicArr.bin", std::ios::binary);
	ofs.write(reinterpret_cast<const char*>(&strSize), sizeof(int));
	ofs.write(str, strSize);
	ofs.close();

	std::ifstream ifs("dynamicArr.bin", std::ios::binary);

	int newStrSize;
	ifs.read(reinterpret_cast<char*>(&newStrSize), sizeof(int));
	char* newDynamicString = new char[newStrSize];

	ifs.read(newDynamicString, newStrSize);
	ifs.close();

	std::cout << newDynamicString;

	delete[] newDynamicString;
}