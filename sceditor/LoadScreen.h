#ifndef LOADSCREEN_H
#define LOADSCREEN_H

#include <QWidget>

namespace Ui {
class LoadScreen;
}

class LoadScreen : public QWidget
{
		Q_OBJECT
		
	public:
		explicit LoadScreen(QWidget *parent = 0);
		~LoadScreen();
		
	private:
		Ui::LoadScreen *ui;
};

#endif // LOADSCREEN_H
