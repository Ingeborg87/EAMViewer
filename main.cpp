#include <QApplication>
#include "eamviewer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EAMViewer w;
    w.show();
    
    return a.exec();
}
