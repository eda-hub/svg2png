#ifndef SVG2PNG_H
#define SVG2PNG_H

#include <QWidget>

namespace Ui {
    class SVG2PNG;
}

class SVG2PNG : public QWidget
{
    Q_OBJECT

public:
    explicit SVG2PNG(QWidget *parent = 0);
    ~SVG2PNG();

private:
    Ui::SVG2PNG *ui;
    QPixmap svg;
    QString svgDir;
    QString pngDir;
    QString fileName;
};

#endif // SVG2PNG_H
