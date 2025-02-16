#include "PCH.h"
#include "AlgorythmsEntry.h"

/// <summary>
/// 0   - копія нульового покоління
/// 1   - копія лицевої колонії
/// 2-n - мутанти
/// </summary>
std::vector<AlgorythmSettings> generationsSettings;

AlgorythmSettings generationZeroSettings;

/// <summary>
/// 0   - копія нульового покоління
/// 1   - копія лицевої колонії
/// 2-n - мутанти
/// </summary>
std::vector<OutputData> generationsOutputs;

AlgorythmSettings currentSettingsCpy;
InputData inputCpy;

// Random number normal distribution account distortion

double RandomNumberNormalDistributionAccountDistortion()
{
    static const double mean = 0.0;
    static const double stddev = 0.25;
    static const double min = -std::log(2);
    static const double max = std::log(2);

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::normal_distribution<double> dist(mean, stddev);

    double value;
    do {
        value = dist(gen);
    } while (value < min || value > max);  

    return exp(value);
}

void ProcessDataSingleTime(int index)
{
    OutputData *data = &generationsOutputs[index];

    data->iteration = 0;

    data->pheromons.resize(inputCpy.size);
    for (int i(0); i < data->pheromons.size(); i++)
    {
        data->pheromons[i].resize(inputCpy.size);
        for (int j(0); j < data->pheromons.size(); j++)
        {
            data->pheromons[i][j] = 0.5;
        }
    }

    SharedData sd;

    if (index == 0)
    {
        sd.currentSettingsCpy = generationZeroSettings;
    }
    else if(index == 1)
    {
        sd.currentSettingsCpy = currentSettingsCpy;
    }
    else
    {

        double randomMutation;

        sd.currentSettingsCpy = currentSettingsCpy;

        sd.currentSettingsCpy.generation++;

        randomMutation = RandomNumberNormalDistributionAccountDistortion();
        sd.currentSettingsCpy.AntsNumber *= randomMutation;
        if (sd.currentSettingsCpy.AntsNumber < 100)
        {
            sd.currentSettingsCpy.AntsNumber = 100;
        }

        randomMutation = RandomNumberNormalDistributionAccountDistortion();
        sd.currentSettingsCpy.EvaporationCoefficient *= randomMutation;
        if (sd.currentSettingsCpy.EvaporationCoefficient >= 1)
        {
            sd.currentSettingsCpy.EvaporationCoefficient = 0.9999999999;
        }
        else if (sd.currentSettingsCpy.EvaporationCoefficient <= 0)
        {
            sd.currentSettingsCpy.EvaporationCoefficient = 0.0000000001;
        }

        randomMutation = RandomNumberNormalDistributionAccountDistortion();
        sd.currentSettingsCpy.lengthEffect *= randomMutation;
        if (sd.currentSettingsCpy.lengthEffect < 0)
        {
            sd.currentSettingsCpy.lengthEffect = 0.;
        }

        randomMutation = RandomNumberNormalDistributionAccountDistortion();
        sd.currentSettingsCpy.lengthToPheromonEffect *= randomMutation;
        if (sd.currentSettingsCpy.lengthToPheromonEffect <= 0)
        {
            sd.currentSettingsCpy.lengthToPheromonEffect = 0.0000000001;
        }

        randomMutation = RandomNumberNormalDistributionAccountDistortion();
        sd.currentSettingsCpy.pheromonesEffect *= randomMutation;
        if (sd.currentSettingsCpy.pheromonesEffect < 0)
        {
            sd.currentSettingsCpy.pheromonesEffect = 0.;
        }

        randomMutation = RandomNumberNormalDistributionAccountDistortion();
        sd.currentSettingsCpy.ScoutsNumber *= randomMutation;
        if (sd.currentSettingsCpy.ScoutsNumber < 100)
        {
            sd.currentSettingsCpy.ScoutsNumber = 100.;
        }

        randomMutation = RandomNumberNormalDistributionAccountDistortion();
        sd.currentSettingsCpy.ScoutsRandomness *= randomMutation;
        if (sd.currentSettingsCpy.ScoutsRandomness < 0)
        {
            sd.currentSettingsCpy.ScoutsRandomness = 0.;
        }

        generationsSettings[index] = sd.currentSettingsCpy;

    }

    sd.inputCpy = inputCpy;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    sd.rd = &rd;
    sd.gen = &gen;
    sd.dis = &dis;

    sd.currentSettingsCpy.ColoniesNumber = 1;

    for(int i(0); i < currentSettingsCpy.iterationsNumberToMutate; i++)
    {
        SharedPrecalculationOrder1(data, inputCpy.size, sd);
        IndividualCalculationOrder2(data, inputCpy.size, 0, sd);
        SharedPostcalculationOrder3(data, inputCpy.size, sd);
        IndividualCalculationOrder4(data, inputCpy.size, 0, sd);
        SharedPostcalculationOrder5(data, inputCpy.size, sd);
    }

}

void EvolutionEntry()
{

    while (input == nullptr);
    while (output == nullptr);

    std::vector<std::thread*> generation;

    double bestWay = 0;

    int bestWayIndex = -1;

    while (doContinue)
    {
        if (input == nullptr)
        {
            continue;
        }

        currentSettingsCpy = currentSettings;
        inputCpy = *input;

        generationsSettings.resize(currentSettingsCpy.GenerationPopulation + 2);
        generationsOutputs.resize(currentSettingsCpy.GenerationPopulation + 2);
        generation.resize(currentSettingsCpy.GenerationPopulation + 2);

        for (int i(0); i < generation.size(); i++)
        {
            generation[i] = new std::thread(ProcessDataSingleTime, i);
        }
        for (int i(0); i < generation.size(); i++)
        {
            generation[i]->join();
            delete generation[i];
        }

        bestWay = 0;

        bestWayIndex = -1;

        for (int i(0); i < generationsOutputs.size(); i++)
        {
            if (i == 1)
                continue;

            if (generationsOutputs[i].bestWayLength > bestWay)
            {
                bestWayIndex = i;
                bestWay = generationsOutputs[i].bestWayLength;
            }
        }

        if (doMutate)
            continue;

        if (bestWay > generationsOutputs[1].bestWayLength)
        {
            outputCandidate = generationsOutputs[bestWayIndex];
            settingsCandidate = generationsSettings[bestWayIndex];
            doMutate = true;
        }
        else if (
            generationsOutputs[1].bestWayLength > output->bestWayLength         &&
            output->iteration > currentSettings.iterationsNumberToMutate * 3)
        {
            outputCandidate = generationsOutputs[1];
            settingsCandidate = generationsSettings[1];
            doMutate = true;
        }

    }
}