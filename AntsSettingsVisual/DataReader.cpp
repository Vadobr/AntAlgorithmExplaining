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
    
    std::ifstream file;

    while (true) {
        file.open(fileInsteadAPI, std::ios::in);
        if (file.is_open()) {
            file.seekg(0, std::ios::end);
            std::streamsize fileSize = file.tellg();
            file.seekg(0, std::ios::beg);

            if (fileSize > 0) {
                break;
            }
        }
        file.close();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Затримка перед повторною спробою
    }

    std::stringstream ss;
    ss << file.rdbuf();

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

    file.close();
    
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