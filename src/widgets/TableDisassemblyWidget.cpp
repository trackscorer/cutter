#include "TableDisassemblyWidget.h"
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


DisassemblyTableView::DisassemblyTableView(QWidget *parent)
    : AbstractTableView(parent)
{
    // Update fonts immediately because they are used in calculations
    updateFonts();

    setRowCount(100);

    addColumnAt(getCharWidth() * 2 * sizeof(dsint) + 8, "", false); //address
    addColumnAt(getCharWidth() * 2 * 12 + 8, "", false); //bytes
    addColumnAt(getCharWidth() * 40, "", false); //disassembly
    addColumnAt(1000, "", false); //comments
}


void DisassemblyTableView::updateColors()
{
    qDebug() << "Updating colors";
    AbstractTableView::updateColors();
    backgroundColor = ConfigColor("gui.background");
}


void DisassemblyTableView::prepareData()
{
    ut64 viewableRowsCount = getViewableRowsCount();
    mInstBuffer.clear();
    mInstBuffer.reserve(viewableRowsCount);

    ut64 addr = getTableOffset();

    QList<DisassemblyLine> disassemblyLines;
    {
        TempConfig tempConfig;
        tempConfig.set("scr.html", true)
        .set("scr.color", COLOR_MODE_16M);
        disassemblyLines = Core()->disassembleLines(addr, viewableRowsCount);
    }

    mInstBuffer = disassemblyLines;
    setNbrOfLineToPrint(viewableRowsCount);
}


QString DisassemblyTableView::paintContent(QPainter *painter, dsint rowBase, int rowOffset, int col, int x, int y, int w, int h)
{
    qDebug() << "Painting !" << rowBase << rowOffset << col << x << y << w << h;

    ut64 cur_addr = mInstBuffer.at(rowOffset).offset;
    // TODO Change mInstBuffer list type

    switch(col)
    {
    case 0: // Draw address (+ label)
    {
        QString addrText = QString("%1").arg(cur_addr);
        QColor background = backgroundColor;
        painter->fillRect(QRect(x, y, w, h), QBrush(background));
        painter->drawText(QRect(x + 4, y, w - 4, h), Qt::AlignVCenter | Qt::AlignLeft, addrText);
    }
    break;

    case 1: //draw bytes (TODO: some spaces between bytes)
    {
        //TODO Yeah cf the other TODO above mInst type
        QTextDocument textDoc;
        textDoc.setHtml(mInstBuffer.at(rowOffset).text);
        RichTextPainter::List richText = RichTextPainter::fromTextDocument(textDoc);
        RichTextPainter::paintRichText(painter, x, y, getColumnWidth(col), getRowHeight(), 10, richText, mFontMetrics);
    }
    break;

    case 3: //draw comments
    {
    }
    break;
    }
    return QString();
}


TableDisassemblyWidget::TableDisassemblyWidget(MainWindow *main, QAction *action)
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

void TableDisassemblyWidget::on_seekChanged(RVA offset)
{
    Q_UNUSED(offset);
    disassemblyTable->repaint();
}

void TableDisassemblyWidget::raisePrioritizedMemoryWidget(CutterCore::MemoryWidgetType type)
{
    if (type == CutterCore::MemoryWidgetType::Disassembly) {
        raise();
        setFocus();
    }
}

void TableDisassemblyWidget::setupColors()
{
    disassemblyTable->updateColors();
}
