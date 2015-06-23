// Taken and customized from Durante's DSFix

#include "stdafx.h"

#include "Settings.h"

#include <fstream>
#include <string>

Settings Settings::instance;

void Settings::load()
{
    std::ifstream sfile;
    sfile.open("DSNA.ini", std::ios::in);
    char buffer[128];
    while (!sfile.eof())
    {
        sfile.getline(buffer, 128);
        if (buffer[0] == '#') {
            continue;
        }
        if (sfile.gcount() <= 1) {
            continue;
        }
        std::string bstring(buffer);

#define SETTING(_type, _var, _inistring, _defaultval) \
        if (bstring.find(_inistring) == 0) { \
            read(buffer + strlen(_inistring) + 1, _var); \
                                }
#include "Settings.def"
#undef SETTING
    }
    sfile.close();
}

void Settings::report()
{
    printf("= Settings read:\n");
#define SETTING(_type, _var, _inistring, _defaultval) \
    log(_inistring, _var);
#include "Settings.def"
#undef SETTING
    printf("=============\n");
}

void Settings::init()
{
    if (!inited) {
        inited = true;
    }
}

void Settings::shutdown()
{
    if (inited) {
        inited = false;
    }
}

// reading --------------------------------------------------------------------

void Settings::read(char *source, bool &value)
{
    std::string ss(source);
    if (ss.find("true") == 0 || ss.find("1") == 0 || ss.find("TRUE") == 0 || ss.find("enable") == 0) {
        value = true;
    }
    else {
        value = false;
    }
}

void Settings::read(char *source, int &value)
{
    sscanf_s(source, "%d", &value);
}

void Settings::read(char *source, unsigned &value)
{
    sscanf_s(source, "0x%x", &value);
}

void Settings::read(char *source, float &value)
{
    sscanf_s(source, "%f", &value);
}

void Settings::read(char *source, std::string &value)
{
    value.assign(source);
}

// logging --------------------------------------------------------------------

void Settings::log(const char *name, bool value)
{
    printf(" - %s : %s\n", name, value ? "true" : "false");
}

void Settings::log(const char *name, int value)
{
    printf(" - %s : %d\n", name, value);
}

void Settings::log(const char *name, unsigned value)
{
    printf(" - %s : %#x\n", name, value);
}

void Settings::log(const char *name, float value)
{
    printf(" - %s : %f\n", name, value);
}

void Settings::log(const char *name, const std::string &value)
{
    printf(" - %s : %s\n", name, value.c_str());
}