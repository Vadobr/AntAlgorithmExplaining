#include "RandomSettingsDialoh.h"

RandomSettingsDialoh::RandomSettingsDialoh(QMainWindow* parent, double* randMin, double* randMax, double* dRandMin, double* dRandMax)
{
	ui.setupUi(this);

	this->setWindowFlags(Qt::Window);
	this->setWindowModality(Qt::ApplicationModal);

	setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);

	this->randMin = randMin;
	this->randMax = randMax;
	this->dRandMin = dRandMin;
	this->dRandMax = dRandMax;

	ui.randMinSB->setValue(*randMin);
	ui.randMaxSB->setValue(*randMax);
	ui.dRandMinSB->setValue(*dRandMin);
	ui.dRandMaxSB->setValue(*dRandMax);


	connect(ui.OKButtom, &QPushButton::clicked, this, 
		[this]() 
		{ 

			*this->randMin = ui.randMinSB->value();
			*this->randMax = ui.randMaxSB->value();
			*this->dRandMin = ui.dRandMinSB->value();
			*this->dRandMax = ui.dRandMaxSB->value();

			done(0); 

		});

	connect(ui.CacelButton, &QPushButton::clicked, this, [this]() { done(0); });

	this->show();
}

RandomSettingsDialoh::~RandomSettingsDialoh()
{
}
