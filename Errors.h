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
	//����� ����������� ������������ ������
};

void error_log(Errors& Key_Error,	//���� ������
	std::wstring key = L"")		//��������������� ���������, ����������� �� ����� ������ � ����
{
	//�������� ������� �� ������
	switch (Key_Error)
	{
	case NaE:
		return;
		break;


	}
}
