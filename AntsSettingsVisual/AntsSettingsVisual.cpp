#include "AntsSettingsVisual.h"

AntsSettingsVisual::AntsSettingsVisual(QWidget *parent)
    : QMainWindow(parent)
{
    
	Loading();

    AlgorythmsEntry();

}

AntsSettingsVisual::~AntsSettingsVisual()
{
    delete antsFarm;

	delete timer;

    AlgotythmsJoin();
}

void AntsSettingsVisual::Loading()
{
	ui.setupUi(this);

	antsFarm = new AntsFarmWindow;

	this->AASListDirectoryName = QCoreApplication::applicationDirPath() + "/AASList";

	LoadAASList();

	ui.SettingsSetCB->setCurrentIndex(-1);

	connect(ui.NewSetButton, &QPushButton::clicked, this, &AntsSettingsVisual::onNewSet);

	connect(ui.ClearPheromonButton, &QPushButton::clicked, this, &AntsSettingsVisual::onClearPheromones);

	connect(ui.SettingsSetCB,
		QOverload<int>::of(&QComboBox::currentIndexChanged),
		this,
		&AntsSettingsVisual::onChoseSet);

	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &AntsSettingsVisual::onTimeout);
	timer->start(200);
}

void AntsSettingsVisual::AASViewToModel(AlgorythmSettings* dest)
{
	dest->AntsNumber				= ui.AntsNumberSB->value();
	dest->ColoniesNumber			= ui.ColoniesNumberSB->value();
	dest->EvaporationCoefficient	= ui.EvaporationCoefficientSB->value();
	dest->lengthEffect				= ui.lengthEffectSB->value();
	dest->lengthToPheromonEffect	= ui.lengthToPheromonEffectSB->value();
	dest->MaxTransitionsNumber		= ui.MaxTransitionsNumberSB->value();
	dest->pheromonesEffect			= ui.pheromonesEffectSB->value();
	dest->ScoutsNumber				= ui.ScoutsNumberSB->value();
}

void AntsSettingsVisual::AASModelToView(AlgorythmSettings* source)
{
	ui.AntsNumberSB->setValue(				source->AntsNumber);
	ui.ColoniesNumberSB->setValue(			source->ColoniesNumber);
	ui.EvaporationCoefficientSB->setValue(	source->EvaporationCoefficient);
	ui.lengthEffectSB->setValue(			source->lengthEffect);
	ui.lengthToPheromonEffectSB->setValue(	source->lengthToPheromonEffect);
	ui.MaxTransitionsNumberSB->setValue(	source->MaxTransitionsNumber);
	ui.pheromonesEffectSB->setValue(		source->pheromonesEffect);
	ui.ScoutsNumberSB->setValue(			source->ScoutsNumber);
}

void AntsSettingsVisual::AASToFile(AlgorythmSettings* source, QString filename)
{


	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		return;
	}

	QTextStream out(&file);

	out << source->AntsNumber				<< "\n";
	out << source->ColoniesNumber			<< "\n";
	out << source->EvaporationCoefficient	<< "\n";
	out << source->lengthEffect				<< "\n";
	out << source->lengthToPheromonEffect	<< "\n";
	out << source->MaxTransitionsNumber		<< "\n";
	out << source->pheromonesEffect			<< "\n";
	out << source->ScoutsNumber				<< "\n";

	file.close();
}

void AntsSettingsVisual::AASFromFile(AlgorythmSettings* source, QString filename)
{

	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return;
	}

	QTextStream in(&file);
	QString line;
	
	line = in.readLine();
	source->AntsNumber					= line.toInt();

	line = in.readLine();
	source->ColoniesNumber				= line.toInt();

	line = in.readLine();
	source->EvaporationCoefficient		= line.toDouble();

	line = in.readLine();
	source->lengthEffect				= line.toDouble();

	line = in.readLine();
	source->lengthToPheromonEffect		= line.toDouble();

	line = in.readLine();
	source->MaxTransitionsNumber		= line.toInt();

	line = in.readLine();
	source->pheromonesEffect			= line.toDouble();

	line = in.readLine();
	source->ScoutsNumber				= line.toInt();
	
	file.close();
}

void AntsSettingsVisual::onTimeout()
{
	AASViewToModel(&currentSettings);

	QString bestResult = QString::number(output->bestWayLength);

	std::vector<int> bestWay = output->bestWay;

	QString bestResultStr;

	bestResultStr += "0 > ";

	for (int i(1); i < bestWay.size() - 1; i++)
	{
		bestResultStr += QString::number(bestWay[i]);
		bestResultStr += " > ";
	}

	bestResultStr += "0";

	ui.BestResultLabel->setText(bestResult);
	ui.BestWayLabel->setText(bestResultStr);

	QString iteration = QString::number(lastIteration);

	ui.CurrentIterationLabel->setText(iteration);

}

void AntsSettingsVisual::onChoseSet(int index)
{
	QString name = this->AASListDirectoryName + "/" + ui.SettingsSetCB->itemText(index) + ".aas";

	AASFromFile(&currentSettings, name);

	ui.SettingsSetCB->setCurrentIndex(-1);

	AASModelToView(&currentSettings);

}

void AntsSettingsVisual::onNewSet()
{
	QString selectedFile;
	QString fileNameOnly;

	{

		QString directory = this->AASListDirectoryName;
		QString defaultFileName = "New set";
		QString filter = "AAS Files (*.aas)";

		QFileDialog dialog(this, "Save as...", directory, filter);
		dialog.setAcceptMode(QFileDialog::AcceptSave);
		dialog.setFileMode(QFileDialog::AnyFile);
		dialog.setNameFilter(filter);
		dialog.setDirectory(directory);
		dialog.selectFile(defaultFileName);

		dialog.setOption(QFileDialog::DontUseNativeDialog);
		dialog.setOption(QFileDialog::ReadOnly, true);

		if (dialog.exec() == QDialog::Accepted) {
			selectedFile = dialog.selectedFiles().first();
			QFileInfo fileInfo(selectedFile);
			fileNameOnly = fileInfo.completeBaseName();

			if (fileInfo.suffix().isEmpty()) {
				// Якщо немає розширення, додаємо ".aas"
				selectedFile += ".aas";
			}
			else {
				// Якщо розширення є, замінюємо його на ".aas"
				selectedFile = fileInfo.path() + "/" + fileInfo.completeBaseName() + ".aas";
			}
		}
	}

	if (selectedFile.isEmpty())
		return;

	AASToFile(&currentSettings, selectedFile);

	ui.SettingsSetCB->addItem(fileNameOnly);

	ui.SettingsSetCB->setCurrentIndex(-1);

}

void AntsSettingsVisual::onClearPheromones()
{
	doesPheromonsMustBeCleared = true;
}

void AntsSettingsVisual::LoadAASList()
{
	// Директорія
	{
		QString dirPath = this->AASListDirectoryName;
		QDir dir;

		if (dir.exists(dirPath)) {
			;// Уже існує
		}
		else {
			if (dir.mkpath(dirPath)) {
				// Все айс
			}
			else {
				// хуйня
			}
		}
	}

	//Файли
	{
		QString dirPath = this->AASListDirectoryName;
		QDir dir(dirPath);

		QStringList filters;
		filters << "*.aas";
		QStringList fileList = dir.entryList(filters, QDir::Files);

		ui.SettingsSetCB->clear();
		for (const QString& file : fileList) {
			ui.SettingsSetCB->addItem(file.section(".", 0, 0));
		}
	}
}
