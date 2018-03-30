#ifndef TABLEDISASSEMBLYWIDGET_H
#define TABLEDISASSEMBLYWIDGET_H

#include "Cutter.h"
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QShortcut>
#include "AbstractTableView.h"
#include "../CutterDockWidget.h"
#include "widgets/disassembly/DisassemblyTableView.h"

class DisassemblyContextMenu;

class DisassemblyTableWidget : public CutterDockWidget
{
    Q_OBJECT
public:
    explicit DisassemblyTableWidget(MainWindow *main, QAction *action = nullptr);
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
