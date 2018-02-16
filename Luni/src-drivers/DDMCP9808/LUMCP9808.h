#ifndef LUMCP9808_h
#define LUMCP9808_h

class LUMCP9808: public LogicalUnitInfo {

friend class DDMCP9808;

public:

  LUMCP9808(int addr) : LogicalUnitInfo(), i2cAddress(addr) {}
  ~LUMCP9808() {}

private:
  int i2cAddress;

};

#endif
