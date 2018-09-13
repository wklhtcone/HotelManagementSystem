#include "tableaquery.h"
#include "ui_tableaquery.h"
#include "managerfunc.h"
#include <QMessageBox>
#include "head.h"
tableaquery::tableaquery(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tableaquery)
{
    ui->setupUi(this);
    QButtonGroup *operatingModeGroup = new QButtonGroup(this);
    operatingModeGroup->addButton(ui->upButton);
    operatingModeGroup->addButton(ui->downButton_2);
    QButtonGroup *operatingModeGroup1 = new QButtonGroup(this);
    operatingModeGroup1->addButton(ui->ridButton);
    operatingModeGroup1->addButton(ui->cidButton_2);
    operatingModeGroup1->addButton(ui->cnameButton_3);
    operatingModeGroup1->addButton(ui->startTButton_4);
    operatingModeGroup1->addButton(ui->endTButton_5);
    operatingModeGroup1->addButton(ui->nowTButton_6);

    QBrush brush;
    QTextCharFormat cf;
    former=QDate::currentDate();
    later=QDate::currentDate();

    brush.setColor( Qt::blue );
    cf = ui->calendarWidget->dateTextFormat( QDate::currentDate() );
    cf.setBackground( brush );
    ui->calendarWidget->setDateTextFormat( QDate::currentDate(), cf );

    QDate pale;
    pale=QDate::currentDate().addDays(1);

    brush.setColor( Qt::gray );
    for(;QDate::currentDate().daysTo(pale)<=QDate::currentDate().daysInMonth();pale=pale.addDays(1))
    {
        cf = ui->calendarWidget->dateTextFormat( pale );
        cf.setBackground( brush );
        ui->calendarWidget->setDateTextFormat( pale, cf );
    }

    QObject::connect(ui->calendarWidget,SIGNAL(clicked(QDate)),this,SLOT(selectdate()));
}

tableaquery::~tableaquery()
{
    delete ui;
}

void tableaquery::on_pushButton_clicked()
{


    QString keyworda;
    keyworda=ui->textEdit->toPlainText();
    QueryKeyCode updown2;
    QueryKeyCode order2;
    if(ui->upButton->isChecked()==1)
    {
        updown2=_ascend;
    }
    if(ui->downButton_2->isChecked()==1)
    {
        updown2=_descend;
    }
    if(ui->ridButton->isChecked()==1)
    {
        order2=_order_by_rid;
    }
    if(ui->cidButton_2->isChecked()==1)
    {
        order2=_order_by_cid;
    }
    if(ui->cnameButton_3->isChecked()==1)
    {
        order2=_order_by_name;
    }
    if(ui->startTButton_4->isChecked()==1)
    {
        order2=_order_by_start_time;
    }
    if(ui->endTButton_5->isChecked()==1)
    {
        order2=_order_by_end_time;
    }
    if(ui->nowTButton_6->isChecked()==1)
    {
        order2=_order_by_now_time;
    }
    if(tcount==0)
    {
        if(queryReservationLog(res_log,keyworda,order2,updown2,"1900-01-01",QDate::currentDate().toString("yyyy-MM-dd")))
        {
            QMessageBox::information(this, "结果", "查询成功",QMessageBox::Ok);
            this->close();
        }
        else
        {
            QMessageBox::information(this, "结果", "查询失败",QMessageBox::Ok);
        }

    }
    else
    {
        if(queryReservationLog(res_log,keyworda,order2,updown2,former.toString("yyyy-MM-dd"),later.toString("yyyy-MM-dd")))
        {
            QMessageBox::information(this, "结果", "查询成功",QMessageBox::Ok);
            this->close();
        }
        else
        {
            QMessageBox::information(this, "结果", "查询失败",QMessageBox::Ok);
        }
    }
    queryReservationLog(res_log,keyworda,order2,updown2,former.toString("yyyy-MM-dd"),later.toString("yyyy-MM-dd"));
}

void tableaquery::selectdate()
{
    QBrush brush;
    QTextCharFormat cf;
    QDate pale;

    if(ui->calendarWidget->selectedDate().daysTo(QDate::currentDate())<0)
        return;

    tcount++;
    int t=ui->calendarWidget->selectedDate().daysTo(former);
    if(tcount%2==1&&t>0)
    {
        //清除画图
        brush.setColor( Qt::white );
        cf = ui->calendarWidget->dateTextFormat( former );
        cf.setBackground( brush );
        ui->calendarWidget->setDateTextFormat( former, cf );
        pale=former.addDays(1);
        for(;pale.daysTo(later)>0;pale=pale.addDays(1))
        {
            cf = ui->calendarWidget->dateTextFormat( pale );
            cf.setBackground( brush );
            ui->calendarWidget->setDateTextFormat( pale, cf );
        }
        cf = ui->calendarWidget->dateTextFormat( later );
        cf.setBackground( brush );
        ui->calendarWidget->setDateTextFormat( later, cf );

        later=former;
        former=ui->calendarWidget->selectedDate();


    }
    else if(tcount%2==1&&t<0)
    {
        //清除画图
        brush.setColor( Qt::white );
        cf = ui->calendarWidget->dateTextFormat( former );
        cf.setBackground( brush );
        ui->calendarWidget->setDateTextFormat( former, cf );
        pale=former.addDays(1);
        for(;pale.daysTo(later)>0;pale=pale.addDays(1))
        {
            cf = ui->calendarWidget->dateTextFormat( pale );
            cf.setBackground( brush );
            ui->calendarWidget->setDateTextFormat( pale, cf );
        }
        cf = ui->calendarWidget->dateTextFormat( later );
        cf.setBackground( brush );
        ui->calendarWidget->setDateTextFormat( later, cf );

        former=later;
        later=ui->calendarWidget->selectedDate();
    }

    else if(tcount%2==0&&t>0)
    {
        //清除画图
        brush.setColor( Qt::white );
        cf = ui->calendarWidget->dateTextFormat( former );
        cf.setBackground( brush );
        ui->calendarWidget->setDateTextFormat( former, cf );
        pale=former.addDays(1);
        for(;pale.daysTo(later)>0;pale=pale.addDays(1))
        {
            cf = ui->calendarWidget->dateTextFormat( pale );
            cf.setBackground( brush );
            ui->calendarWidget->setDateTextFormat( pale, cf );
        }
        cf = ui->calendarWidget->dateTextFormat( later );
        cf.setBackground( brush );
        ui->calendarWidget->setDateTextFormat( later, cf );


        later=former;
        former=ui->calendarWidget->selectedDate();
    }
    else if(tcount%2==0&&t<0)
    {
        //清除画图
        brush.setColor( Qt::white );
        cf = ui->calendarWidget->dateTextFormat( former );
        cf.setBackground( brush );
        ui->calendarWidget->setDateTextFormat( former, cf );
        pale=former.addDays(1);
        for(;pale.daysTo(later)>0;pale=pale.addDays(1))
        {
            cf = ui->calendarWidget->dateTextFormat( pale );
            cf.setBackground( brush );
            ui->calendarWidget->setDateTextFormat( pale, cf );
        }
        cf = ui->calendarWidget->dateTextFormat( later );
        cf.setBackground( brush );
        ui->calendarWidget->setDateTextFormat( later, cf );

        if(tcount!=2)
            former=later;
        later=ui->calendarWidget->selectedDate();

    }
    else if(t==0)
    {
        //清除画图
        brush.setColor( Qt::white );
        cf = ui->calendarWidget->dateTextFormat( former );
        cf.setBackground( brush );
        ui->calendarWidget->setDateTextFormat( former, cf );
        pale=former.addDays(1);
        for(;pale.daysTo(later)>0;pale=pale.addDays(1))
        {
            cf = ui->calendarWidget->dateTextFormat( pale );
            cf.setBackground( brush );
            ui->calendarWidget->setDateTextFormat( pale, cf );
        }
        cf = ui->calendarWidget->dateTextFormat( later );
        cf.setBackground( brush );
        ui->calendarWidget->setDateTextFormat( later, cf );

        later=ui->calendarWidget->selectedDate();
        former=later;
    }

    //画former和later
    brush.setColor( Qt::green );
    cf = ui->calendarWidget->dateTextFormat( former );
    cf.setBackground( brush );
    ui->calendarWidget->setDateTextFormat( former, cf );

    if(former.daysTo(later)!=0)
    {
        brush.setColor( Qt::yellow );
        pale=former.addDays(1);
        for(;pale.daysTo(later)>0;pale=pale.addDays(1))
        {
            cf = ui->calendarWidget->dateTextFormat( pale );
            cf.setBackground( brush );
            ui->calendarWidget->setDateTextFormat( pale, cf );
        }

        brush.setColor( Qt::blue );
        cf = ui->calendarWidget->dateTextFormat( later );
        cf.setBackground( brush );
        ui->calendarWidget->setDateTextFormat( later, cf );
    }

}
