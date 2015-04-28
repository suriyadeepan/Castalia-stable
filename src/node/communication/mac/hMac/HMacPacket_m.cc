//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/mac/hMac/HMacPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "HMacPacket_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(HMacPacket);

HMacPacket::HMacPacket(const char *name, int kind) : ::MacPacket(name,kind)
{
    this->ptype_var = 0;
    this->slots_var = 0;
    for (unsigned int i=0; i<10; i++)
        this->slot_info_var[i] = 0;
    for (unsigned int i=0; i<10; i++)
        this->node_id_var[i] = 0;
    this->sleep_time_var = 0;
}

HMacPacket::HMacPacket(const HMacPacket& other) : ::MacPacket(other)
{
    copy(other);
}

HMacPacket::~HMacPacket()
{
}

HMacPacket& HMacPacket::operator=(const HMacPacket& other)
{
    if (this==&other) return *this;
    ::MacPacket::operator=(other);
    copy(other);
    return *this;
}

void HMacPacket::copy(const HMacPacket& other)
{
    this->ptype_var = other.ptype_var;
    this->slots_var = other.slots_var;
    for (unsigned int i=0; i<10; i++)
        this->slot_info_var[i] = other.slot_info_var[i];
    for (unsigned int i=0; i<10; i++)
        this->node_id_var[i] = other.node_id_var[i];
    this->sleep_time_var = other.sleep_time_var;
}

void HMacPacket::parsimPack(cCommBuffer *b)
{
    ::MacPacket::parsimPack(b);
    doPacking(b,this->ptype_var);
    doPacking(b,this->slots_var);
    doPacking(b,this->slot_info_var,10);
    doPacking(b,this->node_id_var,10);
    doPacking(b,this->sleep_time_var);
}

void HMacPacket::parsimUnpack(cCommBuffer *b)
{
    ::MacPacket::parsimUnpack(b);
    doUnpacking(b,this->ptype_var);
    doUnpacking(b,this->slots_var);
    doUnpacking(b,this->slot_info_var,10);
    doUnpacking(b,this->node_id_var,10);
    doUnpacking(b,this->sleep_time_var);
}

int HMacPacket::getPtype() const
{
    return ptype_var;
}

void HMacPacket::setPtype(int ptype)
{
    this->ptype_var = ptype;
}

int HMacPacket::getSlots() const
{
    return slots_var;
}

void HMacPacket::setSlots(int slots)
{
    this->slots_var = slots;
}

unsigned int HMacPacket::getSlot_infoArraySize() const
{
    return 10;
}

int HMacPacket::getSlot_info(unsigned int k) const
{
    if (k>=10) throw cRuntimeError("Array of size 10 indexed by %lu", (unsigned long)k);
    return slot_info_var[k];
}

void HMacPacket::setSlot_info(unsigned int k, int slot_info)
{
    if (k>=10) throw cRuntimeError("Array of size 10 indexed by %lu", (unsigned long)k);
    this->slot_info_var[k] = slot_info;
}

unsigned int HMacPacket::getNode_idArraySize() const
{
    return 10;
}

int HMacPacket::getNode_id(unsigned int k) const
{
    if (k>=10) throw cRuntimeError("Array of size 10 indexed by %lu", (unsigned long)k);
    return node_id_var[k];
}

void HMacPacket::setNode_id(unsigned int k, int node_id)
{
    if (k>=10) throw cRuntimeError("Array of size 10 indexed by %lu", (unsigned long)k);
    this->node_id_var[k] = node_id;
}

double HMacPacket::getSleep_time() const
{
    return sleep_time_var;
}

void HMacPacket::setSleep_time(double sleep_time)
{
    this->sleep_time_var = sleep_time;
}

class HMacPacketDescriptor : public cClassDescriptor
{
  public:
    HMacPacketDescriptor();
    virtual ~HMacPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(HMacPacketDescriptor);

HMacPacketDescriptor::HMacPacketDescriptor() : cClassDescriptor("HMacPacket", "MacPacket")
{
}

HMacPacketDescriptor::~HMacPacketDescriptor()
{
}

bool HMacPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<HMacPacket *>(obj)!=NULL;
}

const char *HMacPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HMacPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int HMacPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *HMacPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "ptype",
        "slots",
        "slot_info",
        "node_id",
        "sleep_time",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int HMacPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "ptype")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "slots")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "slot_info")==0) return base+2;
    if (fieldName[0]=='n' && strcmp(fieldName, "node_id")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "sleep_time")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *HMacPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "double",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *HMacPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HMacPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HMacPacket *pp = (HMacPacket *)object; (void)pp;
    switch (field) {
        case 2: return 10;
        case 3: return 10;
        default: return 0;
    }
}

std::string HMacPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    HMacPacket *pp = (HMacPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getPtype());
        case 1: return long2string(pp->getSlots());
        case 2: return long2string(pp->getSlot_info(i));
        case 3: return long2string(pp->getNode_id(i));
        case 4: return double2string(pp->getSleep_time());
        default: return "";
    }
}

bool HMacPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HMacPacket *pp = (HMacPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setPtype(string2long(value)); return true;
        case 1: pp->setSlots(string2long(value)); return true;
        case 2: pp->setSlot_info(i,string2long(value)); return true;
        case 3: pp->setNode_id(i,string2long(value)); return true;
        case 4: pp->setSleep_time(string2double(value)); return true;
        default: return false;
    }
}

const char *HMacPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *HMacPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HMacPacket *pp = (HMacPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


