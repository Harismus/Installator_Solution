#include <QErrorMessage>

#include "message.h"

void Message::showMessage(QString message)
{
    QErrorMessage msg;
    msg.showMessage(message);
    msg.exec();
}
