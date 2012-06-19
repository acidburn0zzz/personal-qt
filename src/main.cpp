/*
    Personal-qt
    Copyright (C) 2012 Karasu

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QApplication>
#include "maindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationDomain("ies-sabadell");
    a.setOrganizationName("ies-sabadell");
    a.setApplicationName("personal-qt");

    // a.setWindowIcon(QIcon(":/icons/matricula-qt"));

    // Create seed for the random
    // That is needed only once on application startup
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    MainDialog w;

    w.show();
    
    return a.exec();
}
