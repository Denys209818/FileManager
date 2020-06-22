#pragma once
void EnterNew(const char* text, int x, int y, char* num);

void SetPos(int x, int y);

bool check_(char p[]);

char** AddArrPos(char** arr, int& size, char str[]);

void SetCol(int a);

char* strcp(char path[]);

void Delete(char p[]);

void CreateDir(char p[]);

void CreateFiles(char p[]);

void Open_files(char path[], int counter_);

bool RemoveRecursDirectory(char p[]);

bool check(char p[]);

bool DeleteDirPath(char path[]);

void DeleteFilesPath(char path[]);

void CreatePathFiles(char p[]);

void cp(char path[], char message[] = {});

void ShowDisk();
