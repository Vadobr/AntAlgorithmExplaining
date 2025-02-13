#include "AntsFarmWindow.h"

AntsFarmWindow::AntsFarmWindow()
{
	ui.setupUi(this);

	this->show();

	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, QOverload<>::of(&QWidget::update));
	timer->start(200);

}

AntsFarmWindow::~AntsFarmWindow()
{
	delete timer;
}

void AntsFarmWindow::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	if (input == nullptr || output == nullptr)
	{
		// Чорний квадрат
		{
			QRect rectangle = rect();
			painter.setRenderHint(QPainter::Antialiasing);
			painter.setBrush(Qt::black);
			painter.setPen(Qt::NoPen);

			painter.drawRect(rectangle);
		}
	}

	OutputData outputCpy = *output;

	InputData inputCpy = *input;

	std::vector<QPoint> points;
	std::vector<QPoint> pointsFrontward;
	std::vector<QPoint> pointsBackward;

	// Чорний квадрат
	{
		QRect rectangle = rect();
		painter.setRenderHint(QPainter::Antialiasing);
		painter.setBrush(Qt::black);
		painter.setPen(Qt::NoPen);

		painter.drawRect(rectangle);
	}

	// Розрахуюнки
	{
		QRect rectangle = rect();

		rectangle.setLeft(rectangle.left() + 20);
		rectangle.setRight(rectangle.right() - 20);
		rectangle.setBottom(rectangle.bottom() - 20);
		rectangle.setTop(rectangle.top() + 20);

		QPoint centre;

		centre.setX((rectangle.right() + rectangle.left()) / 2);
		centre.setY((rectangle.bottom() + rectangle.top()) / 2);

		QPoint halfAxis;

		halfAxis.setX((rectangle.right() - rectangle.left()) / 2);
		halfAxis.setY((rectangle.bottom() - rectangle.top()) / 2);

		int N = inputCpy.size;

		points.resize(N);

		for (int i(0); i < N; i++)
		{
			QPoint tempcentre;

			double theta = M_PI_2 - 2.0 * M_PI * i / N;

			tempcentre.setX(centre.x() + halfAxis.x() * std::cos(theta));
			tempcentre.setY(centre.y() + halfAxis.y() * std::sin(theta));

			points[i] = tempcentre;
		}
	}

	{
		QRect rectangle = rect();

		rectangle.setLeft(rectangle.left() + 30);
		rectangle.setRight(rectangle.right() - 30);
		rectangle.setBottom(rectangle.bottom() - 30);
		rectangle.setTop(rectangle.top() + 30);

		QPoint centre;

		centre.setX((rectangle.right() + rectangle.left()) / 2);
		centre.setY((rectangle.bottom() + rectangle.top()) / 2);

		QPoint halfAxis;

		halfAxis.setX((rectangle.right() - rectangle.left()) / 2);
		halfAxis.setY((rectangle.bottom() - rectangle.top()) / 2);

		int N = inputCpy.size;

		pointsFrontward.resize(N);

		for (int i(0); i < N; i++)
		{
			QPoint tempcentre;

			double theta = M_PI_2 - 2.0 * M_PI * i / N;

			tempcentre.setX(centre.x() + halfAxis.x() * std::cos(theta));
			tempcentre.setY(centre.y() + halfAxis.y() * std::sin(theta));

			pointsFrontward[i] = tempcentre;
		}
	}

	{
		QRect rectangle = rect();

		rectangle.setLeft(rectangle.left() + 10);
		rectangle.setRight(rectangle.right() - 10);
		rectangle.setBottom(rectangle.bottom() - 10);
		rectangle.setTop(rectangle.top() + 10);

		QPoint centre;

		centre.setX((rectangle.right() + rectangle.left()) / 2);
		centre.setY((rectangle.bottom() + rectangle.top()) / 2);

		QPoint halfAxis;

		halfAxis.setX((rectangle.right() - rectangle.left()) / 2);
		halfAxis.setY((rectangle.bottom() - rectangle.top()) / 2);

		int N = inputCpy.size;

		pointsBackward.resize(N);

		for (int i(0); i < N; i++)
		{
			QPoint tempcentre;

			double theta = M_PI_2 - 2.0 * M_PI * i / N;

			tempcentre.setX(centre.x() + halfAxis.x() * std::cos(theta));
			tempcentre.setY(centre.y() + halfAxis.y() * std::sin(theta));

			pointsBackward[i] = tempcentre;
		}
	}

	{
		if (points.size() % 2 == 0)
		{
			pointsBackward[points.size() / 2].setX(pointsBackward[points.size() / 2].x() + 10);
			pointsFrontward[points.size() / 2].setX(pointsFrontward[points.size() / 2].x() - 10);

			pointsBackward[0].setX(pointsBackward[0].x() + 10);
			pointsFrontward[0].setX(pointsFrontward[0].x() - 10);
		}
	}

	// Всі шляхи
	{
		painter.setRenderHint(QPainter::Antialiasing);
		painter.setBrush(Qt::NoBrush);

		for (int i(0); i < points.size(); i++)
		{
			for (int j(0); j < points.size(); j++)
			{
				if (i == j)
					continue;

				{
					QPen pen;

					pen.setColor(QColor(255, 255, 255, outputCpy.pheromons[i][j] * 255));

					pen.setWidth(2);

					painter.setPen(pen);
				}
				if (i < j) 
				{
					painter.drawLine(
						pointsBackward[i].x(),
						pointsBackward[i].y(),
						pointsBackward[j].x(),
						pointsBackward[j].y()
					);
				}
				else
				{
					painter.drawLine(
						pointsFrontward[i].x(),
						pointsFrontward[i].y(),
						pointsFrontward[j].x(),
						pointsFrontward[j].y()
					);
				}
			}
		}

	}	

	// Кола
	{

		painter.setRenderHint(QPainter::Antialiasing);
		painter.setBrush(Qt::white);
		painter.setPen(Qt::NoPen);

		{
			QRect temprect;

			QPoint tempcentre = points[0];

			temprect.setLeft(tempcentre.x() - 15);
			temprect.setRight(tempcentre.x() + 15);
			temprect.setTop(tempcentre.y() - 15);
			temprect.setBottom(tempcentre.y() + 15);

			painter.setBrush(Qt::red);

			painter.drawEllipse(temprect);

			painter.setBrush(Qt::white);
		}

		for (int i(1); i < points.size(); i++)
		{
			QRect temprect;

			QPoint tempcentre = points[i];

			temprect.setLeft(tempcentre.x() - 15);
			temprect.setRight(tempcentre.x() + 15);
			temprect.setTop(tempcentre.y() - 15);
			temprect.setBottom(tempcentre.y() + 15);

			painter.drawEllipse(temprect);

		}

	}
    
	// Кращий шлях
	{
		painter.setRenderHint(QPainter::Antialiasing);
		painter.setBrush(Qt::NoBrush);

		QPen halfRedPen;

		QPen quarterRedPen;
		
		{

			halfRedPen.setColor(QColor(255, 0, 0, 128));

			halfRedPen.setWidth(4);

			quarterRedPen.setColor(QColor(255, 0, 0, 220));

			quarterRedPen.setWidth(4);

		}

		painter.setPen(halfRedPen);

		std::vector <int> bestWay = outputCpy.bestWay;

		if (bestWay.size() > 1) {

			for (int i(1); i < bestWay.size(); i++)
			{



				{

					painter.setBrush(QColor(255, 0, 0, 220));
					painter.setPen(Qt::NoPen);



					QPointF start(pointsFrontward[bestWay[i - 1]]);
					QPointF end(pointsFrontward[bestWay[i]]);

					painter.drawEllipse(QRect(start.x() - 3, start.y() - 3, 6, 6));

					painter.setBrush(Qt::NoBrush);
					painter.setPen(halfRedPen);

					painter.drawLine(start, end);

					qreal arrowSize = 10;
					qreal angle = std::atan2(end.y() - start.y(), end.x() - start.x());

					QPointF arrowP1 = end - QPointF(arrowSize * std::cos(angle - M_PI / 6), arrowSize * std::sin(angle - M_PI / 6));
					QPointF arrowP2 = end - QPointF(arrowSize * std::cos(angle + M_PI / 6), arrowSize * std::sin(angle + M_PI / 6));

					painter.setPen(quarterRedPen);

					painter.drawLine(end, arrowP1);
					painter.drawLine(end, arrowP2);

				}

			}

			{

				painter.setBrush(QColor(255, 0, 0, 220));
				painter.setPen(Qt::NoPen);

				QPointF start(pointsBackward[bestWay[bestWay.size() - 1]]);
				QPointF end(pointsBackward[bestWay[0]]);

				painter.drawEllipse(QRect(start.x() - 3, start.y() - 3, 6, 6));

				painter.setBrush(Qt::NoBrush);
				painter.setPen(halfRedPen);

				painter.drawLine(start, end);

				qreal arrowSize = 10;
				qreal angle = std::atan2(end.y() - start.y(), end.x() - start.x());

				QPointF arrowP1 = end - QPointF(arrowSize * std::cos(angle - M_PI / 6), arrowSize * std::sin(angle - M_PI / 6));
				QPointF arrowP2 = end - QPointF(arrowSize * std::cos(angle + M_PI / 6), arrowSize * std::sin(angle + M_PI / 6));

				painter.setPen(quarterRedPen);

				painter.drawLine(end, arrowP1);
				painter.drawLine(end, arrowP2);

			}
		}

	}
}
