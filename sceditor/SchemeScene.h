#ifndef SCHEMESCENE_H
#define SCHEMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QMenu>

#include "ObjectTransformer.h"
#include "ObjectDataSource.h"
#include "ObjectText.h"
#include "ObjectRect.h"
#include "ObjectEllipse.h"
#include "ObjectLine.h"
#include "ObjectTriangle.h"
#include "ObjectConnectionLine.h"
#include "ObjectMeter.h"

class SchemeScene : public QGraphicsScene
{
	Q_OBJECT

	public:
		SchemeScene(const QRectF &rect);

		enum Mode { ModeNormal, ModeInsertItem, ModeSelection };

		void connectObjects(SchemeObject * first, SchemeObject * second);
		void setMode(Mode mode);
		void addItem(SchemeObject * item);

		ObjectEllipse * addEllipse();
		ObjectRect * addRect();
		ObjectText * addText();
		ObjectDataSource * addDataSource();
		ObjectTriangle * addTriangle();
		ObjectMeter * addMeter();


	signals:
		void selectionComplete(const bool &cancel, const QRectF &rect);

	protected:
		void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
		void mousePressEvent(QGraphicsSceneMouseEvent *event);
		void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

		void keyPressEvent(QKeyEvent *event);

	private slots:
		void itemCopied();
		void contextMenuRequest(const QPoint &point);

		void paste();
		void remove();
		void scaleMin();
		void scaleMax();

	private:
		void initializeSelectionRect();
		QGraphicsRectItem * _selection;
		Mode _mode;
		QPointF _presspoint;
		SchemeObject * _buffer;
		QMenu * _menu;
		QPointF _mouse_pos;
};

#endif // SCHEMESCENE_H
