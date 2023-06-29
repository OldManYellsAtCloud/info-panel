#ifndef DBUSTEST_H
#define DBUSTEST_H

#include "direction-client-glue.h"
#include "mainwindow.h"

class dbustest : public sdbus::ProxyInterfaces<org::gspine::Gesture_proxy> {
private:
    MainWindow* mw_;
public:
    void onTouchEvent(const std::string& direction) override;
    dbustest(std::string destination, std::string objectPath, MainWindow* mw): ProxyInterfaces(std::move(destination), std::move(objectPath)) {
        mw_ = mw;
        registerProxy();
    }
    ~dbustest(){
        unregisterProxy();
    }
};

#endif // DBUSTEST_H
