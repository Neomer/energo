#include "SchemeScene.h"
#include <QMessageBox>


SchemeScene::SchemeScene(const QRectF &rect) :
	QGraphicsScene(rect)
{
	_selection = 0;
	_buffer = 0;

	_mode = ModeNormal;
	_menu = new QMenu();
	_menu->addAction(QIcon(":/sceditor/popup/objects/edit-past.png"), tr("Вставить"), this, SLOT(paste()));
	_menu->addAction(QIcon(":/sceditor/popup/objects/document-close-2.png"), tr("Удалить"), this, SLOT(remove()));
	_menu->addAction(QIcon(), tr("Уменьшить"), this, SLOT(scaleMin()));
	_menu->addAction(QIcon(), tr("Увеличить"), this, SLOT(scaleMax()));

//	_selection = new QGraphicsRectItem();
//	_selection->setBrush(QBrush(QColor(0, 0, 200, 125), Qt::Dense7Pattern));
//	_selection->setPen(QPen(Qt::DashLine));
//	_selection->setRect(0, 0, 0, 0);

}

void SchemeScene::connectObjects(SchemeObject *first, SchemeObject *second)
{
	ObjectConnectionLine * line = new ObjectConnectionLine(first, second);
	QGraphicsScene::addItem((QGraphicsItem *)line);
	first->connectWith(second, line);
}

void SchemeScene::setMode(SchemeScene::Mode mode)
{
	_mode = mode;
}

void SchemeScene::addItem(SchemeObject *item)
{
	connect(item, SIGNAL(copied()), this, SLOT(itemCopied()));
	QGraphicsScene::addItem(item);
}


void SchemeScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	// Запоминаем позицию нажатия кнопки
	_presspoint = event->scenePos();

	switch (event->buttons())
	{
		case Qt::LeftButton:
			if (!itemAt(event->scenePos()))
			{
				if (!_selection)
					initializeSelectionRect();

				_selection->setPos(event->scenePos());
			}
			else
			{
				if (event->modifiers() == Qt::CTRL)
				{
					itemAt(event->scenePos())->setSelected(true);
				}
			}
			break;

		case Qt::RightButton:
			if (!itemAt(event->scenePos()))
				contextMenuRequest(event->screenPos());
			break;

		default:
			emit selectionComplete(true, QRectF());
	}

	QGraphicsScene::mousePressEvent(event);
}

void SchemeScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		if (_selection)
		{
			_selection->setRect(QRect(QPoint(0, 0), event->scenePos().toPoint() - _selection->scenePos().toPoint()));
		}
	}
	else
	{
	}
	QGraphicsScene::mouseMoveEvent(event);
}

void SchemeScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->buttons() == Qt::NoButton)
	{
		if (_selection)
		{
			if (_mode == ModeInsertItem)
			{
				emit selectionComplete(false, QRectF(_presspoint, event->scenePos()));
			}
			else
			{
				QList<QGraphicsItem *> il = items(_selection->pos().x(),
												  _selection->pos().y(),
												  _selection->rect().width(),
												  _selection->rect().height(),
												  Qt::ContainsItemBoundingRect,
												  Qt::AscendingOrder);
				foreach (QGraphicsItem * item, il)
				{
					item->setSelected(true);
				}

				//_selection->setRect(0, 0, 0, 0);
				removeItem(_selection);
				_selection = 0;
			}
		}
		else
		{
			if ((!itemAt(event->scenePos())) && (event->modifiers() != Qt::CTRL))
				foreach (QGraphicsItem * item, selectedItems())
				{
					item->setSelected(false);
				}
		}
	}
	// нахуй это надо????
	//_presspoint = QPointF(-1, -1);
	QGraphicsScene::mouseReleaseEvent(event);
}

void SchemeScene::keyPressEvent(QKeyEvent *event)
{
	QGraphicsItem * item;

	switch (event->key())
	{
		case Qt::Key_Delete:
			foreach (item, selectedItems())
			{
				removeItem(item);
			}
			break;
	}

	QGraphicsScene::keyPressEvent(event);
}

void SchemeScene::itemCopied()
{
	_buffer = (SchemeObject *)sender();
}

void SchemeScene::contextMenuRequest(const QPoint &point)
{
	_menu->exec(point);
}

void SchemeScene::paste()
{
	if (!_buffer)
		return;

	ObjectRect * orect;
	ObjectEllipse * ol;
	ObjectDataSource * ods;
	ObjectText * ot;
	ObjectMeter * om;

	switch (_buffer->objType())
	{
		case SOT_Rect:
			orect = addRect();
			orect->setSettings(_buffer->settings());
			orect->setPos(_presspoint);
			orect->updateObject();
			break;

		case SOT_Text:
			ot = addText();
			ot->setSettings(_buffer->settings());
			ot->setPos(_presspoint);
			ot->updateObject();
			break;

		case SOT_Ellipse:
			ol = addEllipse();
			ol->setSettings(_buffer->settings());
			ol->setPos(_presspoint);
			ol->updateObject();
			break;

		case SOT_DataSource:
			ods = addDataSource();
			ods->setSettings(_buffer->settings());
			ods->setPos(_presspoint);
			ods->updateObject();
			break;
			
		case SOT_Meter:
			om = addMeter();
			om->setSettings(_buffer->settings());
			om->setPos(_presspoint);
			om->updateObject();
			break;

		default:
			QMessageBox::critical(0, tr("Ошибка вставки"), tr("Объект не поддерживает операцию копирования!"));
	}
}

void SchemeScene::remove()
{
	foreach (QGraphicsItem * gi, selectedItems())
	{
		SchemeObject * o = qgraphicsitem_cast<SchemeObject *>(gi);
		removeItem(o);
		delete o;
	}
}

void SchemeScene::scaleMin()
{
	foreach (QGraphicsItem * gi, items())
	{
		SchemeObject * o = qgraphicsitem_cast<SchemeObject *>(gi);
		o->setDetalization(o->detalization() * 0.5);
	}
}

void SchemeScene::scaleMax()
{
	foreach (QGraphicsItem * gi, items())
	{
		SchemeObject * o = qgraphicsitem_cast<SchemeObject *>(gi);
		o->setDetalization(o->detalization() * 2);
	}
}

void SchemeScene::initializeSelectionRect()
{
	_selection = QGraphicsScene::addRect(QRectF(0, 0, 0, 0), QPen(Qt::DashLine), QBrush(QColor(150, 150, 255, 50), Qt::SolidPattern));
}

ObjectRect * SchemeScene::addRect()
{
	ObjectRect * item = new ObjectRect();
	addItem(item);
	return item;
}

ObjectText *SchemeScene::addText()
{
	ObjectText * item = new ObjectText();
	addItem(item);
	return item;
}

ObjectDataSource *SchemeScene::addDataSource()
{
	ObjectDataSource * item = new ObjectDataSource();
    item->setVisible(true);
	addItem(item);
	return item;
}

ObjectTriangle *SchemeScene::addTriangle()
{
	ObjectTriangle * item = new ObjectTriangle();
	addItem(item);
	return item;
}

ObjectMeter *SchemeScene::addMeter()
{
	ObjectMeter * item = new ObjectMeter();
	addItem(item);
	return item;
}

ObjectEllipse *SchemeScene::addEllipse()
{
	ObjectEllipse * item = new ObjectEllipse();
	addItem(item);
	return item;
}

