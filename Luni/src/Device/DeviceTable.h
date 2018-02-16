
#ifndef DeviceTable_h
#define DeviceTable_h

#include <Device/DeviceDriver.h>
#include <Device/ClientReporter.h>

#define MAX_DPB_LENGTH 128  // decoded parameter block length (plain text)

class DeviceTable {

    friend class DDMeta;        // in order to read deviceCount and devices

public:
    DeviceTable(DeviceDriver *deviceArray[], ClientReporter *reporter);
    ~DeviceTable();

    int open(int opts, int flags, const char *name);
    int read(int handle, int flags, int reg, int count, byte *buf);
    int write(int handle, int flags, int reg, int count, byte *buf);
    int close(int handle, int flags);

    int dispatchTimers();
    void reset();

    bool claimPin(int p);
    bool releasePin(int p);

private:

    uint8_t pinLocks[(TOTAL_PINS+7)/8] {0};

    int deviceCount;
    DeviceDriver **devices;

    ClientReporter *cr;             // for communication to the client

};

#endif

