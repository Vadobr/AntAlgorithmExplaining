#pragma once

#include "PCHNames.h"

#include "ui_AntsSettingsVisual.h"
#include "AntsFarmWindow.h"
#include "AlgorythmsEntry.h"


class AntsSettingsVisual : public QMainWindow
{
    Q_OBJECT

public:
    AntsSettingsVisual(QWidget *parent = nullptr);
    ~AntsSettingsVisual();

private:

    QString AASListDirectoryName;

    Ui::AntsSettingsVisualClass ui;

    AntsFarmWindow* antsFarm;

    QTimer* timer;

    void Loading();

private:

    void AASViewToModel(AlgorythmSettings* dest);

    void AASModelToView(AlgorythmSettings* source);

    void AASToFile(AlgorythmSettings* source, QString filename);

    void AASFromFile(AlgorythmSettings* source, QString filename);

private slots:

    void onAnythingChanged();

    void onTimeout();

    void onChoseSet(int index);

    void onNewSet();

    void onClearPheromones();

private:

    void LoadAASList();

private slots:

    void onAntsNumberSBChanged();
    void onColoniesNumberSBChanged();
    void onEvaporationCoefficientSBChanged();
    void onlengthEffectSBChanged();
    void onGenerationsPopulationSBChanged();
    void onlengthToPheromonEffectSBChanged();
    void onMaxTransitionsNumberSBChanged();
    void onMutationIterationsNumberSBChanged();
    void onScoutsRandomnessSBChanged();
    void onScoutsNumberSBChanged();
    void onpheromonesEffectSBChanged();

private slots:

    void onGenerationZero();

    void onNewGenerationZero();

};
