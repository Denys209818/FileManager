#include "libs.h";
#include "functions.h";


void main()
{
	setlocale(LC_CTYPE, "ukr");

	int ch = 1;
	int counter_ = 1;
	bool file = false;
	char path[255] = "D:\\";
	while (true)
	{
		system("cls");
		int size = 0;
		char** names = new char* [size];
		int counter = 0;
		//Формування масиву з файлів
		WIN32_FIND_DATA fd;
		char p[255] = {};
		strcpy_s(p, strlen(path) + 1, path);
		if (!file) strcat_s(p, "*.*");
		HANDLE hFind = ::FindFirstFile(p, &fd);
		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				names = AddArrPos(names, size, fd.cFileName);
				counter++;
			} while (::FindNextFile(hFind, &fd));
			::FindClose(hFind);
		}
		//Вивід на екран
		cout << "------------------------------" << endl;
		for (int i = 0; i < counter; i++)
		{
			if (i == counter_) SetCol(12);
			if (i != 0)cout << "|  (" << i << ")";
			cout <<  names[i] << endl;
			SetCol(7);
		}
		cout << "------------------------------" << endl;
		//Декор
		SetCol(14);
		ShowDisk();
		SetCol(7);

		//Меню (функціонал)
		ch = _getch();
		switch (ch)
		{
		case 224:
		{
			switch (_getch())
			{
			case 72: counter_ > 1 ? counter_-- : counter_ = counter - 1; break;
			case 80: counter_ < counter - 1 ? counter_++ : counter_ = 1; break;
			}
		}
		}


		//Перевірка варіантів введення з клавіатури
		if (ch == 13)
		{
			int i = strlen(names[counter_]);
			while (i > 0)
			{
				if (names[counter_][i] == '.' && !strstr(names[counter_], ".."))
				{
					file = true;
					break;
				}
				i--;
			}



			if (!file)
			{

				strcat_s(path, names[counter_]);
				strcat_s(path, "\\");
				counter_ = 1;
			}
			else
			{
				char pat[255] = {};
				strcpy_s(pat, strlen(path) + 1, path);
				strcat_s(pat, names[counter_]);
				Open_files(pat, counter_);
				file = false;
			}

		}


		if (ch == 99)
		{
			CreateDir(path);

		}

		if (ch == 100)
		{
			char path_[255] = {};
			strcpy_s(path_, strlen(path) + 1, path);
			strcat_s(path_, names[counter_]);
			Delete(path_);
			counter_ > 1 ? counter-- : counter_ = counter - 2;
		}

		if (ch == 102)
		{
			CreateFiles(path);
		}

		if (ch == 107) 
		{
			int k = 0;
			char pat[255] = {};
			strcpy_s(pat, strlen(path)+1, path);
			strcat_s(pat, names[counter_]);
			cp(pat);
		}

		for (int i = 0; i < counter; i++) 
		{
			delete[]names[i];
		}
		delete[]names;
	}



}