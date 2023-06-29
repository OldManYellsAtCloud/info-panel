#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include <fstream>
#include <iostream>
#include <QObject>

class Brightness : public QObject
{
    Q_OBJECT
private:
    std::fstream brightnessFile;
    static std::string BRIGHTNESS_PATH;
    static double MAX_BRIGHTNESS;
    Brightness(); // singleton, this class should not be instantiated multiple times

public:
    static Brightness& brightnessHandler(){
        static Brightness brightness {};
        return brightness;
    }

    Brightness(Brightness const&) = delete;
    void operator=(Brightness const&) = delete;

    ~Brightness() {
        brightnessFile.close();
    }

    int getBrightness();

public slots:
    void setBrightness(int brightness);
};

#endif // BRIGHTNESS_H
