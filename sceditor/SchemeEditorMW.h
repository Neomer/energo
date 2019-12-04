#ifndef SCHEMEEDITORMW_H
#define SCHEMEEDITORMW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "../pgredrv/PgreSqlDrv.h"
#include <QTableWidgetItem>
#include <QFile>
#include "SchemeScene.h"

namespace Ui {
	class SchemeEditorMW;
}

class SchemeEditorMW : public QMainWindow
{
		Q_OBJECT
		
	public:
		explicit SchemeEditorMW(QWidget *parent = 0);
		~SchemeEditorMW();
		
	private slots:
		void test();
		void addDbLink();
		void addTextObject();
		void addRectObject();
		void addEllipseObject();
		void addLineObject();
		void addTriangle();
		void addMeter();

		void addConnectionLine();

		void settingItemChanged();
		void settingEdited(QTableWidgetItem * item);

		void stateSwap();

		void saveSchema();
		void openSchema();

	
	private:
		void createToolBox();
		void colorPickerRequest(QTableWidgetItem * item);
		void fontPickerRequest(QTableWidgetItem * item);

		Ui::SchemeEditorMW *ui;
		SchemeScene * _scene;
		PgreSqlDrv * drv;
		QFile _file;
};

#endif // SCHEMEEDITORMW_H
