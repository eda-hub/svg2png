#include "svg2png.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qSetMessagePattern("%{type}:[%{file}:%{line}]  %{message}");

    QApplication a(argc, argv);
    SVG2PNG w;
    w.show();

    return a.exec();
}
