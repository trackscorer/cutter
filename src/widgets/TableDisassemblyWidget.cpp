#include "TableDisassemblyWidget.h"
#include "menus/DisassemblyContextMenu.h"
#include "utils/HexAsciiHighlighter.h"
#include "utils/HexHighlighter.h"
#include "utils/Configuration.h"
#include "utils/Helpers.h"
#include "utils/TempConfig.h"

#include <QScrollBar>
#include <QJsonArray>
#include <QJsonObject>
#include <QVBoxLayout>
#include <QRegularExpression>
#include <QLabel>


#include "widgets/AbstractTableView.h"


class DisassemblyTableView: AbstractTableView
{
    virtual QString paintContent(QPainter* painter, dsint rowBase, int rowOffset, int col, int x, int y, int w, int h) override;
};


QString DisassemblyTableView::paintContent(QPainter *painter, dsint rowBase, int rowOffset, int col, int x, int y, int w, int h)
{
    // TODO
    return QString();
}


TableDisassemblyWidget::TableDisassemblyWidget(MainWindow *main, QAction *action)
    :   CutterDockWidget(main, action)
    ,   mCtxMenu(new DisassemblyContextMenu(this))
{
    setWindowTitle(tr("Table Disassembly"));

    QVBoxLayout *layout = new QVBoxLayout();
    //layout->addWidget(mDisasTextEdit);
    //layout->setMargin(0);

    QLabel *testWidget = new QLabel("Test", this);
    setWidget(testWidget);

    setAllowedAreas(Qt::AllDockWidgetAreas);
    setObjectName("TableDisassemblyWidget");

    setupFonts();
    setupColors();

    connect(Core(), SIGNAL(seekChanged(RVA)), this, SLOT(on_seekChanged(RVA)));
    connect(Core(), SIGNAL(raisePrioritizedMemoryWidget(CutterCore::MemoryWidgetType)), this,
            SLOT(raisePrioritizedMemoryWidget(CutterCore::MemoryWidgetType)));

    // connect(Config(), SIGNAL(fontsUpdated()), this, SLOT(fontsUpdatedSlot()));
    // connect(Config(), SIGNAL(colorsUpdated()), this, SLOT(colorsUpdatedSlot()));

    connect(this, &QDockWidget::visibilityChanged, this, [](bool visibility) {
        if (visibility) {
            Core()->setMemoryWidgetPriority(CutterCore::MemoryWidgetType::Disassembly);
        }
    });
}

void TableDisassemblyWidget::on_seekChanged(RVA offset)
{
}

void TableDisassemblyWidget::raisePrioritizedMemoryWidget(CutterCore::MemoryWidgetType type)
{
    if (type == CutterCore::MemoryWidgetType::Disassembly) {
        raise();
        setFocus();
    }
}

void TableDisassemblyWidget::setupFonts()
{
}


void TableDisassemblyWidget::setupColors()
{
}