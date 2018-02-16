#ifndef LUMeta_h
#define LUMeta_h

#define SAMPLE_COUNT 16

class LUMeta: public LogicalUnitInfo {

friend class DDMeta;

public:

    LUMeta() : LogicalUnitInfo() {}
    ~LUMeta() {}

private:

    int sampleIndex[2] = {0,0};
    unsigned long samples[2][SAMPLE_COUNT + 1];
    bool isSampleBufferFull[2] = {false, false};

};

#endif
