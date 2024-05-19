#include"WinFile.h"
#include<stdio.h>

using namespace HSLL;

BOOL isWord(BYTE in)
{
	return (in >= 'a' && in <= 'z') || (in >= 'A' && in <= 'Z') || (in >= '0' && in <= '9');
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("�����в�����������ȷ");
		return 0;
	}

	char* c1 = argv[1];

	BYTE Mode = 0;

	if (!lstrcmpA(c1, "-c"))
	{
		Mode = 1;
	}
	else if(!lstrcmpA(c1, "-w"))
	{
		Mode = 2;
	}
	else
	{
		printf("�����в���2��ʽ����ȷ");
		return 0;
	}

	char* c2 = argv[2];

	WinFile File;
	if (!File.OpenFile(c2,WIN_FILE_READ_MODE_Read,WIN_FILE_CREATE_FLAG_Open_Existing,WIN_FILE_SHARE_MODE_Prevent))
	{
		printf("�����ڸ��ļ�");
		return 0;
	}

	if (Mode == 1)
	{
		printf("�ַ�����Ϊ%u", File.GetFileSize());
		return 0;
	}

	BYTE* Buffer = new BYTE[File.GetFileSize()];
	File.ReadFile(File.GetFileSize(), Buffer, nullptr);

	DWORD Count = 0;

	for (int i = 0; i < File.GetFileSize(); i++)
	{
		if (i != 0&& i!= File.GetFileSize()-1)
		{
			if (Buffer[i] == ',' || Buffer[i] == '��' || Buffer[i] == ' ')
			{
				if(isWord(Buffer[i-1])&& isWord(Buffer[i + 1]))
				Count++;
			}
		}
		else if(i==File.GetFileSize()-1)
		{
			if (isWord(Buffer[i]))
				Count++;
		}
	}
	File.CloseFile();
	delete Buffer;

	printf("��������Ϊ����Ϊ%u", Count);
	return 0;
}