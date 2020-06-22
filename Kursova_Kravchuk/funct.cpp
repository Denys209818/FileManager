#include "libs.h";
void SetPos(int x, int y) 
{
	COORD cPos;
	cPos.X = x;
	cPos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cPos);
}

void EnterNew(const char* text, int x, int y, char* num)
{
	int width = strlen(text);
	SetPos(x, y);
	for (int i = 0; i < width + 20; i++)
		cout << char(220);
	SetPos(x, y + 1);
	cout << char(219) << " " << text << "                 " << char(219);
	SetPos(x, y + 2);
	cout << char(219);
	for (int i = 0; i < strlen(text) + 18; i++)
		cout << char(220);

	cout << char(219);
	SetPos(x + width + 2, y + 1);
	cin >> num;
}


char** AddArrPos(char** arr, int& size, char str[])
{
	size++;
	char** temp = new char* [size];
	if (size - 1 != 0)
	{
		for (int i = 0; i < size - 1; i++)
		{
			temp[i] = new char[255];
			strcpy_s(temp[i], strlen(arr[i]) + 1, arr[i]);
		}
	}
	temp[size - 1] = new char[255];
	strcpy_s(temp[size - 1], strlen(str) + 1, str);

	arr = temp;
	return arr;
	delete[] temp;
}

bool check(char p[])
{
	int t = strlen(p) + 1;
	for (int i = t; t > 0; t--)
	{
		if (p[t] == '\\')
		{
			break;
		}
		else
		{
			if (p[t] == '.')
			{
				return true;
			}
		}
	}



	return false;
}

bool DeleteDirPath(char path[])
{
	system("cls");
	if (RemoveDirectory(path))
	{
		cout << "directory is remove!" << endl;
	}
	else
	{
		cout << "Error!" << endl;
		return false;
	}
	//_getch();
	return true;
	Sleep(500);
}


void DeleteFilesPath(char path[])
{
	if (!RemoveDirectory(path))
	{
		remove(path);
	}
}

bool RemoveRecursDirectory(char p[])
{
	char path[255];
	strcpy_s(path, strlen(p) + 1, p);
	strcat_s(path, "\\*.*");
	int counter = 0;
	char names[255][255] = {};
	system("cls");
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(path, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			strcpy_s(names[counter], fd.cFileName);
			counter++;
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	//cout << "ARRAY" << endl;
	//for (int i = 0; i < counter; i++) 
	//{
	//	cout << names[i] << endl;
	//}
	//_getch();

	for (int i = 2; i < counter; i++)
	{
		char path_2[255] = {};
		strcpy_s(path_2, strlen(p) + 1, p);
		strcat_s(path_2, "\\");
		//cout << "counter - "<< names[i] << endl;
		strcat_s(path_2, names[i]);
		/*cout << "path_2 - " << path_2 << endl;
		_getch();*/
		if (check(path_2))
		{
			DeleteFilesPath(path_2);
		}
		else
		{
			while (!DeleteDirPath(path_2))
			{
				//тут повторення 
				RemoveRecursDirectory(path_2);
			}
		}
	}
	return true;
}

void SetCol(int a)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}

char* strcp(char path[])
{
	char p[255];
	strcpy_s(p, strlen(path) + 1, path);
	strcat_s(p, strlen(p) + strlen("*.*") + 1, "*.*");
	return p;
}

void Delete(char p[])
{
	//Це видалення файла і папки 
	system("cls");
	if (RemoveDirectory(p))
	{
		cout << "directory is remove!" << endl;
	}
	else
	{
		if (!RemoveDirectory(p))
		{
			remove(p);
		}
	}
	if (!check(p))
	{
		RemoveRecursDirectory(p);
		RemoveDirectory(p);
	}
	Sleep(500);
}

void CreateDir(char p[])
{
	system("cls");
	char path[255] = {};
	strcpy_s(path, strlen(p) + 1, p);
	char dir[255] = {};
	cout << "Enter directory name - ";
	cin >> dir;
	strcat_s(path, dir);
	//cout << path << endl;
	//_getch();
	if (CreateDirectory(path, NULL))
		cout << "directory create" << endl;
	else
		cout << "error create directory" << endl;
	Sleep(500);
}

void CreateFiles(char p[])
{
	system("cls");
	char path[255] = {};
	strcpy_s(path, strlen(p) + 1, p);
	char file[255] = {};
	EnterNew("Enter new file:", 5, 1, file);
	if (!strpbrk(file, "."))
	{
		strcat_s(file, ".txt");
	}
	strcat_s(path, file);
	ofstream fs;

	fs.open(path);

	if (fs.is_open())
	{
		system("cls");
		cout << "File is created!" << endl;
		Sleep(500);
	}
	Sleep(0);

	fs.close();

	Sleep(500);
}

void Open_files(char path[], int counter_)
{
	system("cls");
	ifstream fs;
	//cout << "path1 - " << path << endl;
	fs.open(path);

	if (!fs.is_open())
	{
		cout << "No file! This is Folder. The Folder is delete!" << endl;
		RemoveDirectory(path);
	}
	else
	{
		if (strstr(path, ".txt")) {
			char cht[255];
			while (!fs.eof())
			{
				fs.getline(cht, 255);
				cout << cht << endl;
			}
		}
		else
		{
			cout << "File can you not open!" << endl;
		}
	}
	fs.close();
	_getch();
	//system("cls");

}



	//Це для копіювання функції
void CreatePathFiles(char p[])
{
	system("cls");
	char path[255] = {};
	strcpy_s(path, strlen(p) + 1, p);
	
	ofstream fs;

	fs.open(path);
	/*cout << "path - " << path << endl;
	_getch();*/
	if (fs.is_open())
	{
		/*cout << "File is created!" << endl;
		_getch();*/
		Sleep(500);
	}
	
	Sleep(0);

	fs.close();

	//Sleep(500);
}

bool check_(char p[])
{
	int i = strlen(p);
	for (int l = i; l > 0; l--) 
	{
		if (p[l] == '\\') 
		{
			/*cout << "Tochka 1" << endl;*/
			break;
		}
		if (p[l] == '.') 
		{
			/*cout << "Tochka" << endl;
			_getch();*/
			return false;
			break;
		}
	}


		return true;
}

void cp(char path[], char message[] = {})
{  
	char* t = strstr(path, "\\"); 
	while (strstr(t+1, "\\")) 
	{
		t = strstr(t+1, "\\");
	}
	if (!strstr(t, "-copy")) {
		int size = 0;
		char pat[255] = {};
		bool file = false;
		strcpy_s(pat, strlen(path) + 1, path);
		/*cout << "pat - " << pat << endl;
		_getch();*/
		if (check_(pat))
		{
			strcat_s(pat, "-copy");
			CreateDirectory(pat, NULL);
		}
		else
		{
			/*char* x = strstr(pat,".");
			if (strstr(x, "-copy"))
			{
			char* u = strstr(x, "-copy");
			*u = '\0';
			}*/
			/*cout << "pat_file" << pat << endl;
			_getch();*/
			CreatePathFiles(pat);
			file = true;

		}




		char masiv[255] = {};
		strcpy_s(masiv, strlen(path) + 1, path);

		while (strstr(masiv, "-copy"))
		{
			char* h = strstr(masiv, "-copy");
			*h = '\0';
			int s = strlen(masiv);
			strcat_s(masiv, h + 5);
		}
		ifstream fs;
		fs.open(masiv);
		if (!fs.is_open()) {

			char** names = new char* [size];
			int counter = 0;
			WIN32_FIND_DATA fd;
			char p[255] = {};
			strcpy_s(p, strlen(path) + 1, path);
			strcat_s(p, "\\");
			if (strstr(p, "-copy"))
			{
				for (int i = 0; i < strlen(p); i++)
				{
					if (p[i] == '-' && p[i + 1] == 'c' && p[i + 2] == 'o' && p[i + 3] == 'p' && p[i + 4] == 'y')
					{
						int k = i + 6;
						char arr[255] = {};
						strcpy_s(arr, strlen(p + i + 6) + 1, p + i + 6);
						p[i] = '\0';
						strcat_s(p, "\\");
						strcat_s(p, arr);

					}
				}
			}
			if (!file) strcat_s(p, "*.*");
			/*cout << "p - "<< p << endl;
			_getch();*/
			HANDLE hFind = ::FindFirstFile(p, &fd);
			if (hFind != INVALID_HANDLE_VALUE) {
				do {
					names = AddArrPos(names, size, fd.cFileName);
					counter++;
				} while (::FindNextFile(hFind, &fd));
				::FindClose(hFind);

			}



			if (counter > 2) {
				for (int i = 2; i < counter; i++)
				{
					char pp[255] = {};

					strcpy_s(pp, strlen(pat) + 1, pat);

					strcat_s(pp, "\\");

					strcat_s(pp, names[i]);

					//CreateDirectory(pp, NULL);


					char ppp[255] = {};
					strcpy_s(ppp, strlen(pat) + 1, pat);
					strcat_s(ppp, "\\");
					strcat_s(ppp, names[i]);
					cp(ppp);
					/*cout << ppp << endl;
					_getch();*/
				}
			}
		}
		else
		{



			if (strstr(path, ".txt")) {
				char cht[255];
				while (!fs.eof())
				{
					fs.getline(cht, 255);
					ofstream foot;
					foot.open(path);
					if (foot.is_open())
					{
						foot << cht << "\n";
					}
				}
			}
		}

		fs.close();

	}
	else 
{
system("cls");
cout << "Нельзя копировать копию!" << endl;
_getch();
}
}

void ShowDisk() 
{
	SetPos(70, 1);
	cout << R"(________  .__        __     ________ )" << endl;
	SetPos(70, 2);
	cout << R"(\______ \ |__| _____|  | __ \______ \)" << endl;
	SetPos(70, 3);

	cout << R"( |    |  \|  |/  ___/  |/ /  |    |  \)" << endl;
	SetPos(70, 4);

	cout << R"( |    `   \  |\___ \|    <   |    `   \)" << endl;
	SetPos(70, 5);

	cout << R"(/_______  /__/____  >__|_ \ /_______  /)" << endl;
	SetPos(70, 6);

	cout << R"(        \/        \/     \/         \/ )" << endl;

}











