#ifndef DBUSLISTENER_H
#define DBUSLISTENER_H

#include "direction-client-glue.h"
#include "mainwindow.h"

class dbusListener : public sdbus::ProxyInterfaces<org::gspine::Gesture_proxy> {
private:
    MainWindow* mw_;
public:
    void onTouchEvent(const std::string& direction) override;
    dbusListener(std::string destination, std::string objectPath, MainWindow* mw): ProxyInterfaces(std::move(destination), std::move(objectPath)) {
        mw_ = mw;
        registerProxy();
    }
    ~dbusListener(){
        unregisterProxy();
    }
};

#endif // DBUSLISTENER_H
