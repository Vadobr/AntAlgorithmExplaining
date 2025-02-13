#include "ChangeSizeDilog.h"

ChangeSizeDilog::ChangeSizeDilog(QMainWindow* parent, int N) : QDialog(parent)
{
	ui.setupUi(this);

	this->setWindowFlags(Qt::Window);
	this->setWindowModality(Qt::ApplicationModal);

	setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);

	ui.spinBox->setValue(N);

	connect(ui.OK_Button, &QPushButton::clicked, this, [this]() { done(this->ui.spinBox->value()); });
	connect(ui.Exit_Button, &QPushButton::clicked, this, [this]() { done(-1); });

	this->show();

}

ChangeSizeDilog::~ChangeSizeDilog()
{
}

void ChangeSizeDilog::onOK()
{
	done(ui.spinBox->value());
}

void ChangeSizeDilog::onCancel()
{
	done(-1);
}
