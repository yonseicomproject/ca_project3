

/**
 * @file
 * Definitions of a SRRIP tag store.
 */

#include "debug/CacheRepl.hh"
#include "mem/cache/tags/my_repl.hh"
#include "mm/cache/base.hh"
#define RRPV_SIZE 64 

MyRepl::MyRepl(const Params *p)
    : BaseSetAssoc(p)
{
}

CacheBlk*
MyRepl::accessBlock(Addr addr, bool is_secure, Cycles &lat, int master_id)
{
    CacheBlk *blk = BaseSetAssoc::accessBlock(addr, is_secure, lat, master_id);
    

    if (blk =! NULL) {
        // move this block to head of the MRU list
//       if(warmedUp)
//        {
            blk->rrpv = 0;
//        }
    } 
        DPRINTF(CacheRepl, "set %x: moving blk %x (%s) to MRU\n",
                blk->set, regenerateBlkAddr(blk->tag, blk->set),
                is_secure ? "s" : "ns");
    return blk;
}

CacheBlk*
MyRepl::findVictim(Addr addr)
{
    int set = extractSet(addr);
    // grab a replacement candidate
    bool found = false;
    int index =0;
    while(!found)
    {
        if((sets[set].blks[index])->rrpv == RRPV_SIZE-1)
        {
            found = true;
            break;
        }
        index++;
        if(index == assoc)
        {
            for(int i =0; i<assoc; i++)
                ((sets[set].blks[index])->rrpv)++;
            index = 0;
        }
    }
    assert(index < assoc);
    BlkType *blk = sets[set].blks[index];
    if(blk->isValid()){
        DPRINTF(CacheRepl, "set %x: selecting blk %x for replacement\n",
                set, regenerateBlkAddr(blk->tag,set));
    }
    return blk;
}
/*
void
MyRepl::updateSomething()
{
    for(unsigned int i = 0; numSets; i++)
    {
        unint8_t pcm_dirty,pcm_clean,dram_dirty,dram_clean;
        pcm_dirty = pcm_clean = dram_dirty = dram_clean = 0;
        for(unsigned int j =0; j<assoc; j++)
        {
            if(sets[i].blks[j]-> isDirty())
            {
                    if(sets[i].blks[j]->isPCM)
                        pcm_dirty++;
                    else
                        dram_dirty++;
            
            }
            else
            {
                    if(sets[i].blks[j]->isPcm)
                        pcm_clean++;
                    else
                        dram_clean++;
            }
        }
        DPRINTFR(CacheDirty, "%d %d %d %d\n",pcm_dirty,dram_Dirty, pcm_clean,dram_clean);

    }


}

*/
void
MyRepl::insertBlock(PacketPtr pkt, BlkType *blk)
{
    BaseSetAssoc::insertBlock(pkt, blk);
//    blk->rrpv = (RRPV_SIZE-1);
 //   if(warmedUp)
  //  {
                blk->rrpv = RRPV_SIZE/2;
  //  }
  //  else 
  //  {
    
    //    blk->rrpv = 0;
        
  //  }

}
   

void
MyRepl::invalidate(CacheBlk *blk)
{
    BaseSetAssoc::invalidate(blk);

    // should be evicted before valid blocks
   // blk->rrpv = RRPV_SIZE/2;
}

MyRepl*
MyReplParams::create()
{
    return new MyRepl(this);
}
