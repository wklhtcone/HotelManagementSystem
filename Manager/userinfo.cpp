#include "userinfo.h"
#include "ui_userinfo.h"
#include <QPainter>
#include <QDebug>
#include <QTableWidget>
#include "add.h"
#include "ui_add.h"
#include "queryroom.h"
#include "ui_queryroom.h"
#include "modify.h"
#include "ui_modify.h"
#include <QDebug>
#include "managerfunc.h"
#include <QMessageBox>
#include "head.h"
#include "changeprice.h"
#include "ui_changeprice.h"
#include <QTableWidgetItem>
#include "modify.h"
QString old_r_id;
userinfo::userinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userinfo)
{
    ui->setupUi(this);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止修改
    int RowCont;//打印
    for(RowCont=0;RowCont<room.size();RowCont++)
    {
        ui->tableWidget->insertRow(RowCont);//增加一行
        ui->tableWidget->setItem(RowCont,0,new QTableWidgetItem(QString::fromStdString(room[RowCont][0])));
        ui->tableWidget->setItem(RowCont,1,new QTableWidgetItem(QString::fromStdString(room[RowCont][1])));
        ui->tableWidget->setItem(RowCont,2,new QTableWidgetItem(QString::fromStdString(room[RowCont][2])));
        if(room[RowCont][3]=="0")
        {
             ui->tableWidget->setItem(RowCont,3,new QTableWidgetItem("否"));
        }
        else
        {
             ui->tableWidget->setItem(RowCont,3,new QTableWidgetItem("是"));
        }
    }
    vector<vector<string>>init_room;
    if(!queryRoomPrice(init_room))
    {
        return;
    }
    for(int i=0;i<init_room.size();i++)
    {
        if(init_room[i][0]=="单人间")
        {
            single_room_price =QString::fromStdString(init_room[i][1]).toFloat();
        }
        if(init_room[i][0]=="大床房")
        {
            big_room_price =QString::fromStdString(init_room[i][1]).toFloat();
        }
        if(init_room[i][0]=="双人间")
        {
            double_room_price =QString::fromStdString(init_room[i][1]).toFloat();
        }
        if(init_room[i][0]=="总统套房")
        {
            pres_room_price =QString::fromStdString(init_room[i][1]).toFloat();
        }
    }
}

userinfo::~userinfo()
{
    delete ui;
}
//背景图
void userinfo::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix4;
    pix4.load("../SubAD/456.jpg");
    painter.drawPixmap(10, 10, 680, 480, pix4);
}
void userinfo::on_deleteButton_2_clicked()
{
        QTableWidgetItem * item = ui->tableWidget->currentItem();
        if(item==Q_NULLPTR)return;
        int row1=ui->tableWidget->currentItem()->row();//获取行号
        item=ui->tableWidget->item(row1,0);
        QString r_id1=item->text();
        qDebug()<<"****"<<r_id1;
        //ui->tableWidget->removeRow(item->row());
        if(deleteRoom(r_id1))
        {
            ui->tableWidget->removeRow(item->row());
            QMessageBox::information(this, "结果", "删除成功",QMessageBox::Ok);
        }
        else
        {
            QMessageBox::information(this, "结果", "删除失败",QMessageBox::Ok);
        }
}

void userinfo::on_addButton_clicked()
{
   add addwindow;
   addwindow.exec();
   ui->tableWidget->clearContents();
   int RowCont;//打印
   for(RowCont=0;RowCont<room.size();RowCont++)
   {
       ui->tableWidget->insertRow(RowCont);//增加一行
       ui->tableWidget->setItem(RowCont,0,new QTableWidgetItem(QString::fromStdString(room[RowCont][0])));
       ui->tableWidget->setItem(RowCont,1,new QTableWidgetItem(QString::fromStdString(room[RowCont][1])));
       ui->tableWidget->setItem(RowCont,2,new QTableWidgetItem(QString::fromStdString(room[RowCont][2])));
       if(room[RowCont][3]=="0")
       {
            ui->tableWidget->setItem(RowCont,3,new QTableWidgetItem("否"));
       }
       else
       {
            ui->tableWidget->setItem(RowCont,3,new QTableWidgetItem("是"));
       }
   }
}


void userinfo::on_modifyButton_3_clicked()
{
    QTableWidgetItem * item = ui->tableWidget->currentItem();
    if(item==Q_NULLPTR)return;
    int row2=ui->tableWidget->currentItem()->row();
    item=ui->tableWidget->item(row2,0);
    old_r_id=item->text();
    qDebug()<<old_r_id;
    modify modifywindow;
    modifywindow.exec();
    ui->tableWidget->clearContents();
    int RowCont2;//打印
    for(RowCont2=0;RowCont2<room.size();RowCont2++)
    {
        ui->tableWidget->setItem(RowCont2,0,new QTableWidgetItem(QString::fromStdString(room[RowCont2][0])));
        ui->tableWidget->setItem(RowCont2,1,new QTableWidgetItem(QString::fromStdString(room[RowCont2][1])));
        ui->tableWidget->setItem(RowCont2,2,new QTableWidgetItem(QString::fromStdString(room[RowCont2][2])));
        if(room[RowCont2][3]=="0")
        {
             ui->tableWidget->setItem(RowCont2,3,new QTableWidgetItem("否"));
        }
        else
        {
             ui->tableWidget->setItem(RowCont2,3,new QTableWidgetItem("是"));
        }
    }

}


void userinfo::on_queryButton_clicked()
{
    queryroom qroomwindow;
    qroomwindow.exec();
    ui->tableWidget->clearContents();
    int RowCont;//打印
    for(RowCont=0;RowCont<room.size();RowCont++)
    {
        ui->tableWidget->insertRow(RowCont);//增加一行
        ui->tableWidget->setItem(RowCont,0,new QTableWidgetItem(QString::fromStdString(room[RowCont][0])));
        ui->tableWidget->setItem(RowCont,1,new QTableWidgetItem(QString::fromStdString(room[RowCont][1])));
        ui->tableWidget->setItem(RowCont,2,new QTableWidgetItem(QString::fromStdString(room[RowCont][2])));
        if(room[RowCont][3]=="0")
        {
             ui->tableWidget->setItem(RowCont,3,new QTableWidgetItem("否"));
        }
        else
        {
             ui->tableWidget->setItem(RowCont,3,new QTableWidgetItem("是"));
        }
    }
}

void userinfo::on_rpriceButton_clicked()
{
    changeprice cpwindow;
    cpwindow.exec();
    ui->tableWidget->clearContents();
    int RowCont;//打印
    for(RowCont=0;RowCont<room.size();RowCont++)
    {
        ui->tableWidget->insertRow(RowCont);//增加一行
        ui->tableWidget->setItem(RowCont,0,new QTableWidgetItem(QString::fromStdString(room[RowCont][0])));
        ui->tableWidget->setItem(RowCont,1,new QTableWidgetItem(QString::fromStdString(room[RowCont][1])));
        ui->tableWidget->setItem(RowCont,2,new QTableWidgetItem(QString::fromStdString(room[RowCont][2])));
        if(room[RowCont][3]=="0")
        {
             ui->tableWidget->setItem(RowCont,3,new QTableWidgetItem("否"));
        }
        else
        {
             ui->tableWidget->setItem(RowCont,3,new QTableWidgetItem("是"));
        }
    }
}
