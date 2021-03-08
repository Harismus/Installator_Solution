#pragma once

#include <QString>

#include <functional>

class Message
{
public:
    static std::function<void()> showMessage(QString);
};
