#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <complex>
#include <map>
#include <algorithm>
#include <io.h>
#include <fcntl.h>

enum Errors
{
	NaE,		//Not a Error
	//Здесь расположены наименования ошибок
};

void error_log(Errors& Key_Error,	//Ключ ошибки
	std::wstring key = L"")		//Вспомогательное сообщение, указывающее на место ошибки в коде
{
	//Ответная реакция на ошибку
	switch (Key_Error)
	{
	case NaE:
		return;
		break;


	}
}
