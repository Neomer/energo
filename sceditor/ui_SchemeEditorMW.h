/********************************************************************************
** Form generated from reading UI file 'SchemeEditorMW.ui'
**
** Created: Mon 10. Sep 17:00:25 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHEMEEDITORMW_H
#define UI_SCHEMEEDITORMW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QTableWidget>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SchemeEditorMW
{
public:
    QAction *actDbLink;
    QAction *actTextObject;
    QAction *actEditState;
    QAction *actPreviewState;
    QAction *actSave;
    QAction *actOpen;
    QAction *actEllipse;
    QAction *actConnectionLine;
    QAction *actRect;
    QAction *actTriangle;
    QAction *actLine;
    QAction *actOilBreaker;
    QAction *actBreaker;
    QAction *action_2;
    QAction *action_3;
    QAction *action_4;
    QAction *action_6;
    QAction *actMeter;
    QAction *actionDfdf;
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *mainLayout;
    QHBoxLayout *horizontalLayout_2;
    QGraphicsView *graphicsView;
    QVBoxLayout *layoutSettings;
    QTableWidget *twSettings;
    QLabel *lblHelp;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_3;
    QMenu *menu_4;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *SchemeEditorMW)
    {
        if (SchemeEditorMW->objectName().isEmpty())
            SchemeEditorMW->setObjectName(QString::fromUtf8("SchemeEditorMW"));
        SchemeEditorMW->resize(841, 723);
        SchemeEditorMW->setIconSize(QSize(16, 16));
        actDbLink = new QAction(SchemeEditorMW);
        actDbLink->setObjectName(QString::fromUtf8("actDbLink"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/sceditor/toolbox/objects/database-link.png"), QSize(), QIcon::Normal, QIcon::Off);
        actDbLink->setIcon(icon);
        actTextObject = new QAction(SchemeEditorMW);
        actTextObject->setObjectName(QString::fromUtf8("actTextObject"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/sceditor/toolbox/objects/case_smallcaps.png"), QSize(), QIcon::Normal, QIcon::Off);
        actTextObject->setIcon(icon1);
        actEditState = new QAction(SchemeEditorMW);
        actEditState->setObjectName(QString::fromUtf8("actEditState"));
        actEditState->setCheckable(true);
        actEditState->setChecked(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/sceditor/toolbox/objects/applications-development-5.png"), QSize(), QIcon::Normal, QIcon::Off);
        actEditState->setIcon(icon2);
        actEditState->setMenuRole(QAction::TextHeuristicRole);
        actEditState->setIconVisibleInMenu(true);
        actPreviewState = new QAction(SchemeEditorMW);
        actPreviewState->setObjectName(QString::fromUtf8("actPreviewState"));
        actPreviewState->setCheckable(true);
        actPreviewState->setChecked(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/sceditor/toolbox/objects/document-preview.png"), QSize(), QIcon::Normal, QIcon::Off);
        actPreviewState->setIcon(icon3);
        actSave = new QAction(SchemeEditorMW);
        actSave->setObjectName(QString::fromUtf8("actSave"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/sceditor/toolbox/objects/document-save-5.png"), QSize(), QIcon::Normal, QIcon::Off);
        actSave->setIcon(icon4);
        actOpen = new QAction(SchemeEditorMW);
        actOpen->setObjectName(QString::fromUtf8("actOpen"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/sceditor/toolbox/objects/document-open-2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actOpen->setIcon(icon5);
        actEllipse = new QAction(SchemeEditorMW);
        actEllipse->setObjectName(QString::fromUtf8("actEllipse"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/sceditor/toolbox/objects/draw-ellipse-2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actEllipse->setIcon(icon6);
        actConnectionLine = new QAction(SchemeEditorMW);
        actConnectionLine->setObjectName(QString::fromUtf8("actConnectionLine"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/sceditor/toolbox/objects/draw-bezier-curves.png"), QSize(), QIcon::Normal, QIcon::Off);
        actConnectionLine->setIcon(icon7);
        actRect = new QAction(SchemeEditorMW);
        actRect->setObjectName(QString::fromUtf8("actRect"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/sceditor/toolbox/objects/draw-rectangle-2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actRect->setIcon(icon8);
        actTriangle = new QAction(SchemeEditorMW);
        actTriangle->setObjectName(QString::fromUtf8("actTriangle"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/sceditor/toolbox/objects/draw-triangle3.png"), QSize(), QIcon::Normal, QIcon::Off);
        actTriangle->setIcon(icon9);
        actLine = new QAction(SchemeEditorMW);
        actLine->setObjectName(QString::fromUtf8("actLine"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/sceditor/toolbox/objects/draw-line-3.png"), QSize(), QIcon::Normal, QIcon::Off);
        actLine->setIcon(icon10);
        actOilBreaker = new QAction(SchemeEditorMW);
        actOilBreaker->setObjectName(QString::fromUtf8("actOilBreaker"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/sceditor/objects/objects/oil-circuit-breaker.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        actOilBreaker->setIcon(icon11);
        actBreaker = new QAction(SchemeEditorMW);
        actBreaker->setObjectName(QString::fromUtf8("actBreaker"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/sceditor/objects/objects/breaker.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        actBreaker->setIcon(icon12);
        action_2 = new QAction(SchemeEditorMW);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_3 = new QAction(SchemeEditorMW);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        action_4 = new QAction(SchemeEditorMW);
        action_4->setObjectName(QString::fromUtf8("action_4"));
        action_6 = new QAction(SchemeEditorMW);
        action_6->setObjectName(QString::fromUtf8("action_6"));
        actMeter = new QAction(SchemeEditorMW);
        actMeter->setObjectName(QString::fromUtf8("actMeter"));
        actionDfdf = new QAction(SchemeEditorMW);
        actionDfdf->setObjectName(QString::fromUtf8("actionDfdf"));
        centralWidget = new QWidget(SchemeEditorMW);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 90, 541, 361));
        mainLayout = new QHBoxLayout(horizontalLayoutWidget);
        mainLayout->setSpacing(6);
        mainLayout->setContentsMargins(11, 11, 11, 11);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        graphicsView = new QGraphicsView(horizontalLayoutWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QBrush brush(QColor(200, 200, 200, 255));
        brush.setStyle(Qt::NoBrush);
        graphicsView->setBackgroundBrush(brush);
        graphicsView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout_2->addWidget(graphicsView);

        layoutSettings = new QVBoxLayout();
        layoutSettings->setSpacing(6);
        layoutSettings->setObjectName(QString::fromUtf8("layoutSettings"));
        layoutSettings->setContentsMargins(0, -1, -1, -1);
        twSettings = new QTableWidget(horizontalLayoutWidget);
        if (twSettings->columnCount() < 2)
            twSettings->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        twSettings->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        twSettings->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        twSettings->setObjectName(QString::fromUtf8("twSettings"));
        twSettings->setProperty("showDropIndicator", QVariant(false));
        twSettings->setSelectionMode(QAbstractItemView::SingleSelection);
        twSettings->setSelectionBehavior(QAbstractItemView::SelectRows);
        twSettings->horizontalHeader()->setCascadingSectionResizes(true);
        twSettings->horizontalHeader()->setHighlightSections(false);
        twSettings->horizontalHeader()->setStretchLastSection(true);
        twSettings->verticalHeader()->setVisible(false);
        twSettings->verticalHeader()->setDefaultSectionSize(20);

        layoutSettings->addWidget(twSettings);

        lblHelp = new QLabel(horizontalLayoutWidget);
        lblHelp->setObjectName(QString::fromUtf8("lblHelp"));
        lblHelp->setTextFormat(Qt::LogText);
        lblHelp->setScaledContents(true);
        lblHelp->setWordWrap(true);

        layoutSettings->addWidget(lblHelp);


        horizontalLayout_2->addLayout(layoutSettings);

        horizontalLayout_2->setStretch(0, 3);

        mainLayout->addLayout(horizontalLayout_2);

        SchemeEditorMW->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SchemeEditorMW);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 841, 18));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_3 = new QMenu(menu);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        SchemeEditorMW->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SchemeEditorMW);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setMovable(true);
        SchemeEditorMW->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menu->addAction(menu_3->menuAction());
        menu->addAction(actionDfdf);
        menu_3->addAction(action_6);
        menu_4->addAction(actMeter);
        mainToolBar->addAction(actOpen);
        mainToolBar->addAction(actSave);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actEditState);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actTextObject);
        mainToolBar->addAction(actDbLink);
        mainToolBar->addAction(actOilBreaker);
        mainToolBar->addAction(actBreaker);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actEllipse);
        mainToolBar->addAction(actRect);
        mainToolBar->addAction(actTriangle);
        mainToolBar->addAction(actLine);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actConnectionLine);
        mainToolBar->addSeparator();

        retranslateUi(SchemeEditorMW);

        QMetaObject::connectSlotsByName(SchemeEditorMW);
    } // setupUi

    void retranslateUi(QMainWindow *SchemeEditorMW)
    {
        SchemeEditorMW->setWindowTitle(QApplication::translate("SchemeEditorMW", "Energo - \320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200 \321\201\321\205\320\265\320\274", 0, QApplication::UnicodeUTF8));
        actDbLink->setText(QApplication::translate("SchemeEditorMW", "\320\230\321\201\321\202\320\276\321\207\320\275\320\270\320\272 \320\264\320\260\320\275\320\275\321\213\321\205", 0, QApplication::UnicodeUTF8));
        actTextObject->setText(QApplication::translate("SchemeEditorMW", "\320\242\320\265\321\201\321\202\320\276\320\262\321\213\320\271 \321\215\320\273\320\265\320\274\320\265\320\275\321\202", 0, QApplication::UnicodeUTF8));
        actEditState->setText(QApplication::translate("SchemeEditorMW", "\320\240\320\265\320\266\320\270\320\274 \320\264\320\270\320\267\320\260\320\271\320\275\320\265\321\200\320\260", 0, QApplication::UnicodeUTF8));
        actPreviewState->setText(QApplication::translate("SchemeEditorMW", "\320\240\320\265\320\266\320\270\320\274 \320\277\321\200\320\276\321\201\320\274\320\276\321\202\321\200\320\260", 0, QApplication::UnicodeUTF8));
        actSave->setText(QApplication::translate("SchemeEditorMW", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        actOpen->setText(QApplication::translate("SchemeEditorMW", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", 0, QApplication::UnicodeUTF8));
        actEllipse->setText(QApplication::translate("SchemeEditorMW", "\320\255\320\273\320\273\320\270\320\277\321\201", 0, QApplication::UnicodeUTF8));
        actConnectionLine->setText(QApplication::translate("SchemeEditorMW", "\320\241\320\276\320\265\320\264\320\270\320\275\320\270\321\202\320\265\320\273\321\214\320\275\320\260\321\217 \320\273\320\270\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        actRect->setText(QApplication::translate("SchemeEditorMW", "\320\232\320\262\320\260\320\264\321\200\320\260\321\202", 0, QApplication::UnicodeUTF8));
        actTriangle->setText(QApplication::translate("SchemeEditorMW", "\320\242\321\200\320\265\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272", 0, QApplication::UnicodeUTF8));
        actLine->setText(QApplication::translate("SchemeEditorMW", "\320\237\321\200\321\217\320\274\320\260\321\217", 0, QApplication::UnicodeUTF8));
        actOilBreaker->setText(QApplication::translate("SchemeEditorMW", "\320\234\320\260\321\201\320\273\321\217\320\275\320\275\321\213\320\271 \320\262\321\213\320\272\320\273\321\216\321\207\320\260\321\202\320\265\320\273\321\214", 0, QApplication::UnicodeUTF8));
        actBreaker->setText(QApplication::translate("SchemeEditorMW", "\320\222\321\213\320\272\320\273\321\216\321\207\320\260\321\202\320\265\320\273\321\214", 0, QApplication::UnicodeUTF8));
        action_2->setText(QApplication::translate("SchemeEditorMW", "\320\242\321\200\320\260\320\275\321\201\321\204\320\276\321\200\320\274\320\260\321\202\320\276\321\200 \321\202\320\276\320\272\320\260", 0, QApplication::UnicodeUTF8));
        action_3->setText(QApplication::translate("SchemeEditorMW", "\320\242\321\200\320\260\320\275\321\201\321\204\320\276\321\200\320\274\320\260\321\202\320\276\321\200 \320\275\320\260\320\277\321\200\321\217\320\266\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        action_4->setText(QApplication::translate("SchemeEditorMW", "\320\242\320\265\321\201\321\202", 0, QApplication::UnicodeUTF8));
        action_6->setText(QApplication::translate("SchemeEditorMW", "\320\260\320\277", 0, QApplication::UnicodeUTF8));
        actMeter->setText(QApplication::translate("SchemeEditorMW", "\320\241\321\202\321\200\320\265\320\273\320\276\321\207\320\275\321\213\320\271 \320\277\321\200\320\270\320\261\320\276\321\200", 0, QApplication::UnicodeUTF8));
        actionDfdf->setText(QApplication::translate("SchemeEditorMW", "dfdf", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = twSettings->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SchemeEditorMW", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = twSettings->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SchemeEditorMW", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        lblHelp->setText(QApplication::translate("SchemeEditorMW", "\320\235\320\265\321\202 \320\277\320\276\320\274\320\276\321\211\320\270.", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("SchemeEditorMW", "\320\244\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
        menu_3->setTitle(QApplication::translate("SchemeEditorMW", "\320\260\321\201\320\277\321\201", 0, QApplication::UnicodeUTF8));
        menu_4->setTitle(QApplication::translate("SchemeEditorMW", "\320\255\320\273\320\265\320\274\320\265\320\275\321\202\321\213", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SchemeEditorMW: public Ui_SchemeEditorMW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHEMEEDITORMW_H
