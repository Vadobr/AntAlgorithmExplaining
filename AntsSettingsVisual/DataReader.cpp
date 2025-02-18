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
void GetDataSingleTime(std::shared_ptr<InputData> data) 
{    //REDO
    
    HANDLE hFile;
    WORD fileSize;

    //{
    //    data->model.clear();

    //    data->size = 10;
    //    data->model = std::vector < std::vector<double>>
    //        ({
    //            {0, 1.446, 1.160, 1.057, 1.054, 0.888, 0.706, 0.518, 1.125, 0.903},
    //            {1.007, 0, 0.790, 0.837, 0.656, 1.274, 1.138, 0.746, 1.073, 1.136},
    //            {0.961, 1.100, 0, 0.508, 1.426, 1.212, 0.678, 0.773, 0.500, 0.944},
    //            {0.709, 1.486, 0.982, 0, 0.604, 1.153, 1.195, 0.777, 1.004, 0.667},
    //            {0.982, 1.259, 1.465, 0.815, 0, 0.543, 1.305, 1.417, 1.264, 0.538},
    //            {1.142, 0.537, 0.904, 1.252, 1.319, 0, 0.985, 0.630, 0.726, 0.598},
    //            {1.203, 0.879, 0.706, 0.991, 0.887, 0.888, 0, 0.833, 0.958, 0.607},
    //            {0.664, 0.715, 0.921, 1.169, 0.737, 1.130, 0.818, 0, 0.779, 0.653},
    //            {0.921, 1.193, 1.044, 0.648, 1.430, 1.003, 1.071, 1.492, 0, 0.844},
    //            {0.679, 1.301, 1.452, 0.618, 1.208, 0.881, 0.785, 1.453, 0.936, 0}
    //        });
    //}

    //return;

    do {
        do {
            hFile = CreateFile(fileInsteadAPI.toStdWString().c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        } while (hFile == INVALID_HANDLE_VALUE);

        fileSize = GetFileSize(hFile, NULL);

    } while (fileSize == INVALID_FILE_SIZE || fileSize == 0);

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

//    std::this_thread::sleep_for(std::chrono::seconds(1));


    std::shared_ptr<InputData> background;

	while (doContinue)
	{

        background = std::make_shared<InputData>();

        GetDataSingleTime(background);

        std::atomic_store(&input, background);

//        input.store(background, std::memory_order_release);

	}
}