#include "DataGeneratorSmart.h"

DataGeneratorSmart::DataGeneratorSmart(QWidget* parent)
{
	ui.setupUi(this);

    randomMin = 0.8;
    randomMax = 1.9;
    dRandomMin = -0.2;
    dRandomMax = 0.2;

	matrix = new AdvancedSmartMatrix();

	ui.gridLayout_2->addWidget(matrix);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DataGeneratorSmart::onTimeout);
    timer->start(500); 

    {
        QFile file(fileInsteadAPI.c_str());
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            int a = 5;

            a += 4;

            a++;
        }

        QTextStream in(&file);
        QString line = in.readLine(); 

        int size = line.toInt();

        if (size == 0)
            size = 1;

        this->Resize(size);

        matrix->leftSideCellArray[0]->setText("USDT");
        matrix->topSideCellArray[0]->setText("USDT");

        double temp;

        if (size > 1) {
            for (int i(0); i < size; i++)
            {
                for (int j(0); j < size; j++)
                {

                    in >> temp;

                    if (i == j)
                        continue;

                    matrix->gridCellArray[i][j]->setText(QString::number(temp));

                }
            }
        }

        file.close();

    }

    connect(ui.action, &QAction::triggered, this, &DataGeneratorSmart::onCustomResize);

    connect(ui.Plus1action, &QAction::triggered, this, &DataGeneratorSmart::Plus1);
    connect(ui.Plus10action, &QAction::triggered, this, &DataGeneratorSmart::Plus10);
    connect(ui.Munus1action, &QAction::triggered, this, &DataGeneratorSmart::Minus1);
    connect(ui.Minus10action, &QAction::triggered, this, &DataGeneratorSmart::Minus10);
 
    connect(ui.All0action, &QAction::triggered, this, &DataGeneratorSmart::AllTo0);
    connect(ui.All1action, &QAction::triggered, this, &DataGeneratorSmart::AllTo1);
    connect(ui.AllRandomaction, &QAction::triggered, this, &DataGeneratorSmart::AllRandom);
    connect(ui.AddRandomaction, &QAction::triggered, this, &DataGeneratorSmart::AddRandom);
    connect(ui.RandomSettingsaction, &QAction::triggered, this, &DataGeneratorSmart::onRandomSettings);

    connect(ui.Clockrandomaction, &QAction::triggered, this, &DataGeneratorSmart::onRandomTimeoutPush);
    

    {
        QFile file("Random.config");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            int a = 5;
            a += 4;
            a++;
        }

        QTextStream in(&file);

        QString line = in.readLine();
        randomMin = line.toDouble();

        line = in.readLine();
        randomMax = line.toDouble();

        line = in.readLine();
        dRandomMin = line.toDouble();

        line = in.readLine();
        dRandomMax = line.toDouble();

        file.close();
    }


}

DataGeneratorSmart::~DataGeneratorSmart()
{

    {
        QFile file("Random.config");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            int a = 5;
            a += 4;
            a++;
        }

        QTextStream out(&file);

        out << QString::number(randomMin) << "\n";

        out << QString::number(randomMax) << "\n";

        out << QString::number(dRandomMin) << "\n";

        out << QString::number(dRandomMax) << "\n";

        file.close();
    }

}

void DataGeneratorSmart::ViewToModel()
{
    for (int i(0); i < matrix->GetSize(); i++) {

        for (int j(0); j < matrix->GetSize(); j++) {

            std::string text = matrix->GetElementAsTextEditText(i, j);

            std::replace(text.begin(), text.end(), ',', '.');

            model.SetIntensitiveElement(std::atof(text.c_str()), i, j);

            model.SetFunctionOfElement(text.c_str(), i, j);

            matrix->ApplyElementChanges(i + 1, j + 1);

        }

    }
}

void DataGeneratorSmart::Plus1()
{
    Resize(model.Size() + 1);
}

void DataGeneratorSmart::Plus10()
{
    Resize(model.Size() + 10);
}

void DataGeneratorSmart::Minus1()
{
    Resize(model.Size() - 1);
}

void DataGeneratorSmart::Minus10()
{
    Resize(model.Size() - 10);
}

void DataGeneratorSmart::onCustomResize()
{
    ChangeSizeDilog dialog(this, model.Size());

    int result = dialog.exec();

    if (result > 0)
    {
        Resize(result);
    }
}

void DataGeneratorSmart::onRandomTimeout()
{

    AllRandom();

}

void DataGeneratorSmart::onRandomTimeoutPush()
{

    static bool on = false;

    if (on)
    {
        ui.Clockrandomaction->setText("On random every 30 sec");
    }
    else
    {
        ui.Clockrandomaction->setText("Off random every 30 sec");
    }
    
    on = !on;

    if (on)
    {

        randomusTimer = new QTimer(this);
        connect(randomusTimer, &QTimer::timeout, this, &DataGeneratorSmart::onRandomTimeout);
        randomusTimer->start(30000);

    }
    else
    {

        randomusTimer->stop();
    
    }
}

void DataGeneratorSmart::Resize(int N)
{
    matrix->Resize(N);
    model.Resize(N);
}

void DataGeneratorSmart::AllTo0()
{

    for (int i(0); i < matrix->GetSize(); i++)
    {
        for (int j(0); j < matrix->GetSize(); j++)
        {
            if (i == j)
                continue;

            matrix->gridCellArray[i][j]->setText("0");

        }
    }
}

void DataGeneratorSmart::AllTo1()
{
    for (int i(0); i < matrix->GetSize(); i++)
    {
        for (int j(0); j < matrix->GetSize(); j++)
        {
            if (i == j)
                continue;

            matrix->gridCellArray[i][j]->setText("1");

        }
    }
}

void DataGeneratorSmart::AllRandom()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    std::uniform_real_distribution<double> dist(randomMin, randomMax);

    for (int i(0); i < matrix->GetSize(); i++)
    {
        for (int j(0); j < matrix->GetSize(); j++)
        {
            if (i == j)
                continue;

            double random_number = dist(gen);

            matrix->gridCellArray[i][j]->setText(QString::number(random_number));

        }
    }
}

void DataGeneratorSmart::AddRandom()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dist(dRandomMin, dRandomMax);

    for (int i(0); i < matrix->GetSize(); i++)
    {
        for (int j(0); j < matrix->GetSize(); j++)
        {
            if (i == j)
                continue;

            double random_number = dist(gen);

            random_number += model.GeteIntensitie(i, j);

            if (random_number < 0.)
            {
                random_number = 0.;
            }

            matrix->gridCellArray[i][j]->setText(QString::number(random_number));

        }
    }
}

void DataGeneratorSmart::onRandomSettings()
{
    RandomSettingsDialoh dialog(this, &randomMin, &randomMax, &dRandomMin, &dRandomMax);

    int result = dialog.exec();

}

void DataGeneratorSmart::onTimeout()
{
    ViewToModel();

    int attempts = 200;

    while (attempts-- > 0) {
        std::ofstream file(fileInsteadAPI, std::ios::out | std::ios::trunc);
        if (file.is_open()) {
            file << model.Size() << "\n";

            for (int i = 0; i < model.Size(); i++) {
                for (int j = 0; j < model.Size(); j++) {
                    file << model.GeteIntensitie(i, j) << " ";
                }
                file << "\n";
            }

            file.close();
            return; // ������� �����
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // �������� ����� ��������� �������
    }
}
