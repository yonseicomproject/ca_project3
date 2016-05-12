
/**
 * @file
 * Declaration of a SRRIP tag store.
 * The LRU tags guarantee that the true least-recently-used way in
 * a set will always be evicted.
 */

#ifndef __MEM_CACHE_TAGS_MYREPL_HH__
#define __MEM_CACHE_TAGS_MYREPL_HH__

#include "mem/cache/tags/base_set_assoc.hh"
#include "params/MyRepl.hh"

class MyRepl : public BaseSetAssoc
{
  public:
    /** Convenience typedef. */
    typedef MyReplParams Params;

    /**
     * Construct and initialize this tag store.
     */
    MyRepl(const Params *p);

    /**
     * Destructor
     */
    ~MyRepl();

    //light
    /*
    void updateSomething();
    void setWarmUp()
    {
        warmedUp =true;
        updateSomething();
    }
    */
    //end


    CacheBlk* accessBlock(Addr addr, bool is_secure, Cycles &lat,
                         int context_src);
    CacheBlk* findVictim(Addr addr);
    void insertBlock(PacketPtr pkt, BlkType *blk);
    void invalidate(CacheBlk *blk);
    int* rrip_bits;
};

#endif // __MEM_CACHE_TAGS_MYREPL_HH__
