#ifndef TABLEDISASSEMBLYWIDGET_H
#define TABLEDISASSEMBLYWIDGET_H

#include "Cutter.h"
#include "CutterDockWidget.h"
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QShortcut>
#include "widgets/AbstractTableView.h"

class DisassemblyContextMenu;

class DisassemblyTableView: public AbstractTableView
{
    virtual QString paintContent(QPainter* painter, long long rowBase, int rowOffset, int col, int x, int y, int w, int h) override;

public:
    DisassemblyTableView(QWidget *parent = nullptr);
    virtual void updateColors() override;
    virtual void prepareData() override;

private:
    QList<DisassemblyLine> mInstBuffer;
};

class TableDisassemblyWidget : public CutterDockWidget
{
    Q_OBJECT
public:
    explicit TableDisassemblyWidget(MainWindow *main, QAction *action = nullptr);
    QWidget *getTextWidget();

private:
    DisassemblyContextMenu *mCtxMenu;
    DisassemblyTableView *disassemblyTable;
    void setupColors();

private slots:
    void on_seekChanged(RVA offset);
    void raisePrioritizedMemoryWidget(CutterCore::MemoryWidgetType type);

    /*void scrollInstructions(int count);
    bool updateMaxLines();

    void cursorPositionChanged();*/
};


#endif // DISASSEMBLYWIDGET_H
