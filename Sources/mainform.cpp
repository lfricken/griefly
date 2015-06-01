#include "mainform.h"
#include "ui_mainform.h"

#include <iostream>

#include "MapClass.h"
#include "Debug.h"
#include "Params.h"
#include "MapEditor.h"
#include "Mob.h"
#include "MagicStrings.h"

#include "Metadata.h"

#include "qtopengl.h"

#include "Chat.h"

#include <QDebug>

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    SetTextBrowser(ui->textBrowser);
    QList<int> sizes;
    sizes.push_back(512);
    sizes.push_back(256);
    ui->splitter->setSizes(sizes);

    setWindowTitle("Yet Another Space Station Remake");

    left_column = ui->leftColumn->width();
    right_column = ui->rightColumn->width();

    ui->widget->hide();

    SetMainWidget(this);
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::resizeEvent(QResizeEvent* event) {
    ui->lineEdit->resize(width(), ui->lineEdit->height());
    ui->lineEdit->move(ui->lineEdit->x(), height() - ui->lineEdit->height());
    ui->splitter->resize(width(), ui->lineEdit->y());

    QList<int> sizes;
    sizes.push_back((width() * left_column) / (left_column + right_column));
    sizes.push_back((width() * right_column) / (left_column + right_column));
    ui->splitter->setSizes(sizes);
    on_splitter_splitterMoved(0, 0);
}

void MainForm::startGameLoop()
{
    ui->widget->show();
    on_splitter_splitterMoved(0, 0);

    if (!GetParamsHolder().GetParamBool("-editor"))
    {
        if (GetParamsHolder().GetParamBool("-nodraw"))
            NODRAW = true;

        std::string adrs = "127.0.0.1";
        if (GetParamsHolder().GetParamBool("ip"))
            adrs = GetParamsHolder().GetParam<std::string>("ip");

        if (GetParamsHolder().GetParamBool("name"))
            Debug::SetUniqueName(GetParamsHolder().GetParam<std::string>("name"));

        Manager man(adrs);
        man.initWorld();
        if (GetParamsHolder().GetParamBool("-auto"))
            man.ToogleAutoplay();
        man.process();
        return;
    }
    MapEditor map_editor;
    map_editor.InitWorld();
    map_editor.Run();
}

void MainForm::on_lineEdit_returnPressed()
{
    if (ui->lineEdit->text().toStdString() == "/connect") {
        ui->lineEdit->clear();
        startGameLoop();
        return;
    }
    Message msg;
    msg.type = Net::CHAT_TYPE;
    msg.text = ui->lineEdit->text().toStdString();
    if (msg.text.length() == 0)
        return;
    NetClient::GetNetClient()->Send(msg);
    ui->lineEdit->clear();

    ui->widget->setFocus();
}

void MainForm::on_splitter_splitterMoved(int pos, int index)
{
    ui->textBrowser->resize(
                ui->rightColumn->width(),
                ui->textBrowser->height());

    left_column = ui->leftColumn->width();
    right_column = ui->rightColumn->width();

    int min_size = std::min(ui->leftColumn->width(), ui->leftColumn->height());
    ui->widget->resize(min_size, min_size);

    ui->textBrowser->resize(ui->textBrowser->width(), ui->rightColumn->height());

    if (GetScreen())
    {
        GetScreen()->PerformSizeUpdate();
        GetScreen()->Clear();
        GetScreen()->Swap();
    }

    int x_pos = (ui->leftColumn->width() - min_size) / 2;
    int y_pos = (ui->leftColumn->height() - min_size) / 2;
    ui->widget->move(x_pos, y_pos);
}
