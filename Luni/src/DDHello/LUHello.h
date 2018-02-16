#ifndef LUHello_h
#define LUHello_h

class LUHello: public LogicalUnitInfo {

public:

    LUHello() : LogicalUnitInfo() {
        what = strdup("Hello");
        who = strdup("Earthlings");
    }

    LUHello(const char *to) : LogicalUnitInfo() {
        what = strdup("Hello");
        who = strdup(to);
    }

    ~LUHello() {
        free(what);
        free(who);
    }

    void setWhat(const char *newWhat) {
        free(what);
        what = strdup(newWhat);
    }

    const char *getWhat() {
        return what;
    }

    void setWho(const char *newWho) {
        free(who);
        who = strdup(newWho);
    }

    const char *getWho() {
        return who;
    }

private:
    char *what;
    char *who;
};

#endif
