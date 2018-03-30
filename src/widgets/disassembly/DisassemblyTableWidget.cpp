#include "DisassemblyTableWidget.h"
#include "menus/DisassemblyContextMenu.h"
#include "utils/HexAsciiHighlighter.h"
#include "utils/HexHighlighter.h"
#include "utils/Configuration.h"
#include "utils/Helpers.h"
#include "utils/TempConfig.h"
#include "utils/RichTextPainter.h"

#include <QScrollBar>
#include <QJsonArray>
#include <QJsonObject>
#include <QVBoxLayout>
#include <QRegularExpression>
#include <QLabel>

DisassemblyTableWidget::DisassemblyTableWidget(MainWindow *main, QAction *action)
    :   CutterDockWidget(main, action),
      mCtxMenu(new DisassemblyContextMenu((QWidget*) this))
{
    this->setObjectName("TableDisassemblyWidget");
    this->setAllowedAreas(Qt::AllDockWidgetAreas);
    this->setWindowTitle(tr("Table Disassembly"));
    this->disassemblyTable = new DisassemblyTableView(this);
    setWidget(disassemblyTable);

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

void DisassemblyTableWidget::on_seekChanged(RVA offset)
{
    Q_UNUSED(offset);
    disassemblyTable->repaint();
}

void DisassemblyTableWidget::raisePrioritizedMemoryWidget(CutterCore::MemoryWidgetType type)
{
    if (type == CutterCore::MemoryWidgetType::Disassembly) {
        raise();
        setFocus();
    }
}

void DisassemblyTableWidget::setupColors()
{
    disassemblyTable->updateColors();
}
