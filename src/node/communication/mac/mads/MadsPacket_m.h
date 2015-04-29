//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/mac/mads/MadsPacket.msg.
//

#ifndef _MADSPACKET_M_H_
#define _MADSPACKET_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
	#include "MacPacket_m.h"
// }}

/**
 * Class generated from <tt>src/node/communication/mac/mads/MadsPacket.msg:5</tt> by nedtool.
 * <pre>
 * packet MadsPacket extends MacPacket
 * {
 *     int ptype;
 * 
 *     int slots;
 *     int node_id[10];
 *     int nextSlot;
 * 
 *     int clusterSize;
 * 
 *     double sleep_time;
 * }
 * </pre>
 */
class MadsPacket : public ::MacPacket
{
  protected:
    int ptype_var;
    int slots_var;
    int node_id_var[10];
    int nextSlot_var;
    int clusterSize_var;
    double sleep_time_var;

  private:
    void copy(const MadsPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const MadsPacket&);

  public:
    MadsPacket(const char *name=NULL, int kind=0);
    MadsPacket(const MadsPacket& other);
    virtual ~MadsPacket();
    MadsPacket& operator=(const MadsPacket& other);
    virtual MadsPacket *dup() const {return new MadsPacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getPtype() const;
    virtual void setPtype(int ptype);
    virtual int getSlots() const;
    virtual void setSlots(int slots);
    virtual unsigned int getNode_idArraySize() const;
    virtual int getNode_id(unsigned int k) const;
    virtual void setNode_id(unsigned int k, int node_id);
    virtual int getNextSlot() const;
    virtual void setNextSlot(int nextSlot);
    virtual int getClusterSize() const;
    virtual void setClusterSize(int clusterSize);
    virtual double getSleep_time() const;
    virtual void setSleep_time(double sleep_time);
};

inline void doPacking(cCommBuffer *b, MadsPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, MadsPacket& obj) {obj.parsimUnpack(b);}


#endif // ifndef _MADSPACKET_M_H_
