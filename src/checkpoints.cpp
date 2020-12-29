// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of 
(         0, uint256("0xb477d9bc0721a1b96547495404583d68123f471fdd1d4058a9adff2fa7452298"))
(         30000, uint256("0xe333edb2a6052a29a0c9f471ec4de5b82a2f8e398fc295db499d2adb1f72b750"))
(         62000, uint256("0xc12547453d2a3995893890e0d73cf4b1fe68f1b6b68e0b407547d6050ba0352f"))
(         81000, uint256("0x08afecfd7028b3448ce283e236f8a0535da611c6f6942d2062e364fe8ca5f95c"))
(        100000, uint256("0x056386351ce37a32a5e6cf3edd90a4a6e4f41a6f1c58d3d4044dfcb762ceb274"))
(        133000, uint256("0x2c9ce87324212f2cba4a63840439c173bf16ba1e6ecf9bbf3e8702b828a8d87b"))
(        222222, uint256("0x9c732c3be5225afda793fc6e515e4d7c8fc50c76fb376497fb9cd238b320b5d3"))
(        333333, uint256("0x2240e1ace3526e5d58e37fd08f12d407bc12887fbebda22b9ff87b39c79abab3"))
(        505000, uint256("0xc989c1ec8ef4dabfd10922831826d27a0d2cc95947b2066e385e280b3bc512cb"))
(       1000000, uint256("0xdf496e3d3d525d330683d700649116a9b3b97868a35111203c662fff5107f4fe"))
        ;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
