#include <QErrorMessage>

#include "message.h"

std::function<void()> Message::showMessage(QString message)
{
    return [message]() {
        QErrorMessage msg;
        msg.showMessage(message);
        msg.show();
    };
}
