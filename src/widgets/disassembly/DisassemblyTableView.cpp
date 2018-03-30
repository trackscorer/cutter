#include "DisassemblyTableView.h"
#include "utils/Configuration.h"
#include "utils/TempConfig.h"
#include "utils/RichTextPainter.h"

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
