#include "PCH.h"
#include "AlgorythmsEntry.h"

//DeleteIt
#include <Windows.h>
#include "../DataGeneratorSmart/FileThatInsteadAPI.h"
#include <qstring.h>
#include <fstream>
#include <istream>
#include <sstream>
//EndDelete


// REDO |   |   |
//      |   |   |   зіс шит, не змінюючи сигнатуру функції
//      v   v   v
void GetDataSingleTime(InputData* data) 
{
    
    //REDO

    HANDLE hFile = CreateFile(fileInsteadAPI.toStdWString().c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        // TODO
        return;
    }

    WORD fileSize = GetFileSize(hFile, NULL);
    if (fileSize == INVALID_FILE_SIZE || fileSize == 0)
    {
        // TODO
        return;
    }

    std::vector<char> buffer(fileSize + 1, '\0');
    DWORD bytesRead;
    SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
    ReadFile(hFile, buffer.data(), fileSize, &bytesRead, NULL);
    buffer[bytesRead] = '\0';

    std::istringstream ss(buffer.data());
    int N;
    ss >> N;

    data->size = N;
    data->model.resize(N);
    for (int i(0); i < data->model.size(); i++)
    {
        data->model[i].resize(N);
    }

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            ss >> data->model[i][j];

    CloseHandle(hFile);
    
}

void GetDataEntry()
{

	InputData data1;
	InputData data2;

	InputData* front = &data1;
	InputData* background = &data2;

    GetDataSingleTime(&data1);
    GetDataSingleTime(&data2);

    front = &data1;
    background = &data2;

    input = front;

	while (doContinue)
	{
        GetDataSingleTime(background);

        input = background;

        background = front;

        front = input;
	}
}