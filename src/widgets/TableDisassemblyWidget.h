#ifndef TABLEDISASSEMBLYWIDGET_H
#define TABLEDISASSEMBLYWIDGET_H

#include "Cutter.h"
#include "CutterDockWidget.h"
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QShortcut>

class DisassemblyContextMenu;

class TableDisassemblyWidget : public CutterDockWidget
{
    Q_OBJECT
public:
    explicit TableDisassemblyWidget(MainWindow *main, QAction *action = nullptr);
    QWidget *getTextWidget();

/*public slots:
    void highlightCurrentLine();
    void showDisasContextMenu(const QPoint &pt);
    void refreshDisasm(RVA offset = RVA_INVALID);
    void fontsUpdatedSlot();
    void colorsUpdatedSlot();
    void seekPrev();*/

private slots:
    void on_seekChanged(RVA offset);
    void raisePrioritizedMemoryWidget(CutterCore::MemoryWidgetType type);

    /*void scrollInstructions(int count);
    bool updateMaxLines();

    void cursorPositionChanged();*/

private:
    DisassemblyContextMenu *mCtxMenu;

    void setupFonts();
    void setupColors();
};


#endif // DISASSEMBLYWIDGET_H
