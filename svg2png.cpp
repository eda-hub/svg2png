#include "svg2png.h"
#include "ui_svg2png.h"
#include <QPixmap>
#include <QFileDialog>
#include <QDebug>
#include <QDir>
#include <QComboBox>

SVG2PNG::SVG2PNG(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SVG2PNG)
{
    ui->setupUi(this);

    connect(ui->pushButtonOpen,&QPushButton::clicked,this,[this](){

        fileName = QFileDialog::getOpenFileName(this, "打开Svg文件",
                                                              "",
                                                              "Images (*.svg)");
        if(!fileName.isEmpty()){
            int w = ui->comboBoxWidth->currentText().toInt();
            int h = ui->comboBoxHeight->currentText().toInt();

            svg = QIcon(fileName).pixmap(w,h);
            ui->labelSvg->setPixmap(svg);
            ui->pushButtonSave->setEnabled(true);
        }
    });

    connect(ui->pushButtonSave,&QPushButton::clicked,this,[this](){

        const QString fileName = QFileDialog::getSaveFileName(this, "保存PNG文件",
                                                              this->fileName.replace(".svg",".png"),
                                                              "Images (*.png)");
        if(!fileName.isEmpty()){
            svg.toImage().save(fileName);
        }
    });

    connect(ui->comboBoxHeight, &QComboBox::currentTextChanged,this,[this](){

        if(!fileName.isEmpty()){
            int w = ui->comboBoxWidth->currentText().toInt();
            int h = ui->comboBoxHeight->currentText().toInt();

            svg = QIcon(fileName).pixmap(w,h);
            ui->labelSvg->setPixmap(svg);
        }
    });

    connect(ui->pushButtonSelectIn,&QPushButton::clicked,this,[this](){
        svgDir = QFileDialog::getExistingDirectory(this, "Svg目录",
                                                          "",
                                                          QFileDialog::ShowDirsOnly
                                                          | QFileDialog::DontResolveSymlinks);
        if(!svgDir.isEmpty()){
            ui->lineEditIn->setText(svgDir);
        }
    });

    connect(ui->pushButtonSelectOut,&QPushButton::clicked,this,[this](){
        pngDir = QFileDialog::getExistingDirectory(this, "PNG保存目录",
                                                          "",
                                                          QFileDialog::ShowDirsOnly
                                                          | QFileDialog::DontResolveSymlinks);
        if(!pngDir.isEmpty()){
            ui->lineEditOut->setText(pngDir);
            ui->pushButtonConvert->setEnabled(true);
        }
    });

    connect(ui->pushButtonConvert,&QPushButton::clicked,this,[this](){
        int w = ui->comboBoxWidth->currentText().toInt();
        int h = ui->comboBoxHeight->currentText().toInt();
        int scale = ui->comboBoxScale->currentText().toInt();
        if (scale) {
            w = w * scale;
            h = h * scale;
        }

        QFileInfoList svgFiles = QDir(svgDir).entryInfoList({"*.svg"},QDir::Files);
        for(const QFileInfo &svgfile : svgFiles){
            QString fileName = scale ?  QString("/%1@%2x.png").arg(svgfile.baseName()).arg(scale)
                                      : QString("/%1.png").arg(svgfile.baseName());

            svg = QIcon(svgfile.filePath()).pixmap(w,h);
            svg.toImage().save(pngDir + fileName);
        }
    });
}

SVG2PNG::~SVG2PNG()
{
    delete ui;
}
