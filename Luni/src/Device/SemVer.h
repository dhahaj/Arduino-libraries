#ifndef SemVer_h
#define SemVer_h

// There is ONE call to DECLARE_VERSION in DeviceDriver.h in the protected
// section of the class declaration.

#define DECLARE_VERSION \
uint8_t releaseVersion[4] {3,0,0,0};\
const char* scopeName {"ABCDEF"};\
char* preReleaseLabel {"p"};\
char* buildLabel {"b"};

// Put call to DEFINE_VERSION as a line in the device driver constructor.
// This call needs to be in the body of the constructor so that the class
// name is picked up correctly.
//
// A pre-release label and a build meta-data label can be added using
// alternate forms of the macro.  For example:
//
// DEFINE_VERSION(0,8,1)
// DEFINE_VERSION_PRE(0,5,0,beta)
// DEFINE_VERSION_PRE_BLD(0,5,0,beta,__DATE__)

#define DEFINE_VERSION(major, minor, patch) \
DEFINE_VERSION_ALL(major, minor, patch,,)

#define DEFINE_VERSION_PRE(major, minor, patch,prLabel) \
DEFINE_VERSION_ALL(major, minor, patch,prLabel,)

#define DEFINE_VERSION_BLD(major, minor, patch,bLabel) \
DEFINE_VERSION_ALL(major, minor, patch,,bLabel)

#define DEFINE_VERSION_PRE_BLD(major, minor, patch, prLabel, bLabel) \
DEFINE_VERSION_ALL(major, minor, patch, prLabel, bLabel)

#define DEFINE_VERSION_ALL(major, minor, patch,prLabel,bLabel) \
releaseVersion[0]= 3; \
releaseVersion[1]= (uint8_t)major; \
releaseVersion[2]= (uint8_t)minor; \
releaseVersion[3]= (uint8_t)patch; \
scopeName = (const char *)__func__; \
preReleaseLabel = #prLabel; \
buildLabel = #bLabel;


#endif
