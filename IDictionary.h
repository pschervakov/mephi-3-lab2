#ifndef MEPHI_3_LAB2_IDICTIONARY_H
#define MEPHI_3_LAB2_IDICTIONARY_H

#include "string"

using std::string;

template<class K, class V>
class IDictionary {
public:
    virtual void add(K, V) = 0;

    virtual void remove(K) = 0;

    virtual V &get(K) = 0;

    virtual bool find(K) = 0;

    virtual int getCount() = 0;

    virtual int getCapacity() = 0;

    virtual string toString() = 0;


};


#endif //MEPHI_3_LAB2_IDICTIONARY_H

