#include <iostream>
#include "dbustest.h"
#include "brightness.h"

void dbustest::onTouchEvent(const std::string &direction)
{
    std::cout << "Direction arrived: " << direction << std::endl;
    if (mw_->isHidden()) {
        mw_->show();
    } else {
        mw_->hide();
    }
}
