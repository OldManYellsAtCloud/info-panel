#include "dbusListener.h"
#include "brightness.h"
#include "logger.h"

void dbusListener::onTouchEvent(const std::string &direction)
{
    LOG(LOG_DEBUG, "Direction arrived: " + direction);
    if (direction == "TOP_TO_BOTTOM") {
        mw_->show();
    } else {
        mw_->hide();
    }
}
