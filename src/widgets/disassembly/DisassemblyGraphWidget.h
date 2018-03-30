#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include "widgets/CutterDockWidget.h"

class MainWindow;
class DisassemblerGraphView;

class DisassemblerGraphWidget : public CutterDockWidget
{
    Q_OBJECT

public:
    explicit DisassemblerGraphWidget(MainWindow *main, QAction *action = nullptr);
    ~DisassemblerGraphWidget();

private:
    DisassemblerGraphView *graphView;

};

#endif // GRAPHWIDGET_H
