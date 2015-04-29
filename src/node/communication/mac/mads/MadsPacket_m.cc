//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/mac/mads/MadsPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "MadsPacket_m.h"

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

Register_Class(MadsPacket);

MadsPacket::MadsPacket(const char *name, int kind) : ::MacPacket(name,kind)
{
    this->ptype_var = 0;
    this->slots_var = 0;
    for (unsigned int i=0; i<10; i++)
        this->node_id_var[i] = 0;
    this->nextSlot_var = 0;
    this->clusterSize_var = 0;
    this->sleep_time_var = 0;
}

MadsPacket::MadsPacket(const MadsPacket& other) : ::MacPacket(other)
{
    copy(other);
}

MadsPacket::~MadsPacket()
{
}

MadsPacket& MadsPacket::operator=(const MadsPacket& other)
{
    if (this==&other) return *this;
    ::MacPacket::operator=(other);
    copy(other);
    return *this;
}

void MadsPacket::copy(const MadsPacket& other)
{
    this->ptype_var = other.ptype_var;
    this->slots_var = other.slots_var;
    for (unsigned int i=0; i<10; i++)
        this->node_id_var[i] = other.node_id_var[i];
    this->nextSlot_var = other.nextSlot_var;
    this->clusterSize_var = other.clusterSize_var;
    this->sleep_time_var = other.sleep_time_var;
}

void MadsPacket::parsimPack(cCommBuffer *b)
{
    ::MacPacket::parsimPack(b);
    doPacking(b,this->ptype_var);
    doPacking(b,this->slots_var);
    doPacking(b,this->node_id_var,10);
    doPacking(b,this->nextSlot_var);
    doPacking(b,this->clusterSize_var);
    doPacking(b,this->sleep_time_var);
}

void MadsPacket::parsimUnpack(cCommBuffer *b)
{
    ::MacPacket::parsimUnpack(b);
    doUnpacking(b,this->ptype_var);
    doUnpacking(b,this->slots_var);
    doUnpacking(b,this->node_id_var,10);
    doUnpacking(b,this->nextSlot_var);
    doUnpacking(b,this->clusterSize_var);
    doUnpacking(b,this->sleep_time_var);
}

int MadsPacket::getPtype() const
{
    return ptype_var;
}

void MadsPacket::setPtype(int ptype)
{
    this->ptype_var = ptype;
}

int MadsPacket::getSlots() const
{
    return slots_var;
}

void MadsPacket::setSlots(int slots)
{
    this->slots_var = slots;
}

unsigned int MadsPacket::getNode_idArraySize() const
{
    return 10;
}

int MadsPacket::getNode_id(unsigned int k) const
{
    if (k>=10) throw cRuntimeError("Array of size 10 indexed by %lu", (unsigned long)k);
    return node_id_var[k];
}

void MadsPacket::setNode_id(unsigned int k, int node_id)
{
    if (k>=10) throw cRuntimeError("Array of size 10 indexed by %lu", (unsigned long)k);
    this->node_id_var[k] = node_id;
}

int MadsPacket::getNextSlot() const
{
    return nextSlot_var;
}

void MadsPacket::setNextSlot(int nextSlot)
{
    this->nextSlot_var = nextSlot;
}

int MadsPacket::getClusterSize() const
{
    return clusterSize_var;
}

void MadsPacket::setClusterSize(int clusterSize)
{
    this->clusterSize_var = clusterSize;
}

double MadsPacket::getSleep_time() const
{
    return sleep_time_var;
}

void MadsPacket::setSleep_time(double sleep_time)
{
    this->sleep_time_var = sleep_time;
}

class MadsPacketDescriptor : public cClassDescriptor
{
  public:
    MadsPacketDescriptor();
    virtual ~MadsPacketDescriptor();

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

Register_ClassDescriptor(MadsPacketDescriptor);

MadsPacketDescriptor::MadsPacketDescriptor() : cClassDescriptor("MadsPacket", "MacPacket")
{
}

MadsPacketDescriptor::~MadsPacketDescriptor()
{
}

bool MadsPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<MadsPacket *>(obj)!=NULL;
}

const char *MadsPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int MadsPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount(object) : 6;
}

unsigned int MadsPacketDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *MadsPacketDescriptor::getFieldName(void *object, int field) const
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
        "node_id",
        "nextSlot",
        "clusterSize",
        "sleep_time",
    };
    return (field>=0 && field<6) ? fieldNames[field] : NULL;
}

int MadsPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "ptype")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "slots")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "node_id")==0) return base+2;
    if (fieldName[0]=='n' && strcmp(fieldName, "nextSlot")==0) return base+3;
    if (fieldName[0]=='c' && strcmp(fieldName, "clusterSize")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "sleep_time")==0) return base+5;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *MadsPacketDescriptor::getFieldTypeString(void *object, int field) const
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
        "int",
        "double",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : NULL;
}

const char *MadsPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int MadsPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    MadsPacket *pp = (MadsPacket *)object; (void)pp;
    switch (field) {
        case 2: return 10;
        default: return 0;
    }
}

std::string MadsPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    MadsPacket *pp = (MadsPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getPtype());
        case 1: return long2string(pp->getSlots());
        case 2: return long2string(pp->getNode_id(i));
        case 3: return long2string(pp->getNextSlot());
        case 4: return long2string(pp->getClusterSize());
        case 5: return double2string(pp->getSleep_time());
        default: return "";
    }
}

bool MadsPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    MadsPacket *pp = (MadsPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setPtype(string2long(value)); return true;
        case 1: pp->setSlots(string2long(value)); return true;
        case 2: pp->setNode_id(i,string2long(value)); return true;
        case 3: pp->setNextSlot(string2long(value)); return true;
        case 4: pp->setClusterSize(string2long(value)); return true;
        case 5: pp->setSleep_time(string2double(value)); return true;
        default: return false;
    }
}

const char *MadsPacketDescriptor::getFieldStructName(void *object, int field) const
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

void *MadsPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    MadsPacket *pp = (MadsPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


