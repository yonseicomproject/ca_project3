

/**
 * @file
 * Definitions of a SRRIP tag store.
 */

#include "debug/CacheRepl.hh"
#include "mem/cache/tags/my_repl.hh"
#include "mem/cache/base.hh"
#define RRPV_SIZE 4

MyRepl::MyRepl(const Params *p)
    : BaseSetAssoc(p)
{
    rrip_bits = new int[assoc];
    for (int i = 0; i<assoc; i++)
        rrip_bits[i] = RRPV_SIZE-1;
}

CacheBlk*
MyRepl::accessBlock(Addr addr, bool is_secure, Cycles &lat, int master_id)
{
    CacheBlk *blk = BaseSetAssoc::accessBlock(addr, is_secure, lat, master_id);

    if (blk != NULL) {
        // move this block to head of the MRU list
        blk->rrpv =0;
       // sets[blk->set].moveToHead(blk);
        DPRINTF(CacheRepl, "set %x: moving blk %x (%s) to MRU\n",
                blk->set, regenerateBlkAddr(blk->tag, blk->set),
                is_secure ? "s" : "ns");
    }

    return blk;
}

CacheBlk*
MyRepl::findVictim(Addr addr)
{
    CacheBlk *blk = BaseSetAssoc::findVictim(addr);
    //    blk = sets[set].blks[index];
    int set = extractSet(addr);
    // grab a replacement candidate

    for (int i = 0; i<assoc; i++)
    {


       //blk = sets[set].blks[index];
        if(!blk->isValid() || !blk)
        {
            rrip_bits[i] = RRPV_SIZE/2;
            return blk;
        
        }
    }
    int pointer = 0;
    for (int j = 0; j <= RRPV_SIZE-1; ++j)
    {
        for( int i = 0; i<assoc; i++)
        {
            //blk = sets[set].blks[index];
            if(rrip_bits[pointer] == RRPV_SIZE-1)
            {
                int index = pointer;
                //blk = sets[set].blks[index];
               // pointer = (pointer +1) % assoc;
                rrip_bits[index] = RRPV_SIZE/2;

                blk = sets[set].blks[index];
                return blk;
            }
            pointer = (pointer+1)%assoc;
        }
        for (int i = 0; i<assoc; i++)
        {
            rrip_bits[i]++;
        }
    }
    if (blk && blk->isValid()) {
        DPRINTF(CacheRepl, "set %x: selecting blk %x for replacement\n",
                set, regenerateBlkAddr(blk->tag, set));
    }
    return blk;
}

void
MyRepl::insertBlock(PacketPtr pkt, BlkType *blk)
{
    BaseSetAssoc::insertBlock(pkt, blk);
//    if(rrip_bits[
//    blk->rrpv = RRPV_SIZE/2;
//    int set = extractSet(pkt->getAddr());
//    sets[set].moveToHead(blk);
}

void
MyRepl::invalidate(CacheBlk *blk)
{
    BaseSetAssoc::invalidate(blk);

    // should be evicted before valid blocks
  //  int set = blk->set;
  //  sets[set].moveToTail(blk);
 //   blk->rrpv = RRPV_SIZE-1;
}

MyRepl*
MyReplParams::create()
{
    return new MyRepl(this);
}

MyRepl::~MyRepl(){
    delete [] rrip_bits;
}
