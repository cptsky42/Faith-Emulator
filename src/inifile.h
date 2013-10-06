#ifndef INIFILE_H
#define INIFILE_H

#include "common.h"

#if UINT32_MAX < UINT_MAX
#error "The IniFile class requires that a int be of 32-bit."
#endif

class QSettings;

class IniFile
{
public:
    IniFile();
    ~IniFile();

    err_t open(const char* aPath);
    err_t open(const std::string& aPath)
    { return open(aPath.c_str()); }

    void close();

    int8_t readInt8(const char* aKey, int8_t aDefault = 0);
    int8_t readInt8(const std::string& aKey, int8_t aDefault = 0)
    { return readInt8(aKey.c_str(), aDefault); }

    uint8_t readUInt8(const char* aKey, uint8_t aDefault = 0);
    uint8_t readUInt8(const std::string& aKey, uint8_t aDefault = 0)
    { return readUInt8(aKey.c_str(), aDefault); }

    int16_t readInt16(const char* aKey, int16_t aDefault = 0);
    int16_t readInt16(const std::string& aKey, int16_t aDefault = 0)
    { return readInt16(aKey.c_str(), aDefault); }

    uint16_t readUInt16(const char* aKey, uint16_t aDefault = 0);
    uint16_t readUInt16(const std::string& aKey, uint16_t aDefault = 0)
    { return readUInt16(aKey.c_str(), aDefault); }

    int32_t readInt32(const char* aKey, int32_t aDefault = 0);
    int32_t readInt32(const std::string& aKey, int32_t aDefault = 0)
    { return readInt32(aKey.c_str(), aDefault); }

    uint32_t readUInt32(const char* aKey, uint32_t aDefault = 0);
    uint32_t readUInt32(const std::string& aKey, uint32_t aDefault = 0)
    { return readUInt32(aKey.c_str(), aDefault); }

    float readFloat(const char* aKey, float aDefault = 0.0);
    float readFloat(const std::string& aKey, float aDefault = 0.0)
    { return readFloat(aKey.c_str(), aDefault); }

    double readDouble(const char* aKey, double aDefault = 0.0);
    double readDouble(const std::string& aKey, double aDefault = 0.0)
    { return readDouble(aKey.c_str(), aDefault); }

    bool readBoolean(const char* aKey, bool aDefault = false);
    bool readBoolean(const std::string& aKey, bool aDefault = false)
    { return readBoolean(aKey.c_str(), aDefault); }

    std::string readString(const char* aKey, const char* aDefault = "");
    std::string readString(const std::string& aKey, const std::string& aDefault = "")
    { return readString(aKey.c_str(), aDefault.c_str()); }

public:
    bool isOpen() { return mFile != nullptr; }

    //gamemap.childGroups();

private:
    err_t readInteger(int& aOutValue, const char* aKey);
    err_t readUInteger(unsigned int& aOutValue, const char* aKey);
    err_t readDouble(double& aOutValue, const char* aKey);
    err_t readBoolean(bool& aOutValue, const char* aKey);
    err_t readString(std::string& aOutValue, const char* aKey);

private:
    QSettings* mFile;
};

#endif // INIFILE_H
