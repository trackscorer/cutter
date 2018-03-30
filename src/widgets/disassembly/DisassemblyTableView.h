#ifndef DISASSEMBLERTABLEVIEW_H
#define DISASSEMBLERTABLEVIEW_H

#include "AbstractTableView.h"
#include "Cutter.h"

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


#endif // DISASSEMBLERTABLEVIEW_H
