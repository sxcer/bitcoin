// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c)      2014 The Sexcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "forkparams.h"
#include "main.h"

using namespace std;

static CForkParams forkParams;

#define FORK1_HEIGHT 155000

// Constructor
CForkParams::CForkParams() {
        // Timespan and Spacing values are moved here from definition as
        // global vars in main.cpp.
        nTargetTimespan = 8 * 60 * 60; // 8 hours
        nTargetSpacing = 60; // 60 Seconds
        // Interval 480 blocks

        // Fork1 - Tweak Difficulty Calc window etc
        nTargetTimespan_Fork1 = 30 * 60; // 30 minutes
        nTargetSpacing_Fork1 = 30; // 30 seconds
        // Interval 60 blocks

}

int64_t CForkParams::Timespan() const {
    //int64_t height=GetHeight();
    int64_t height=chainActive.Height();
    if ( height >= FORK1_HEIGHT ) { return nTargetTimespan_Fork1; }
    return nTargetTimespan;
}

int64_t CForkParams::Spacing() const {
    //int64_t height=GetHeight();
    int64_t height=chainActive.Height();
    if  ( height >= FORK1_HEIGHT ) { return nTargetSpacing_Fork1; }
    return nTargetSpacing;
}

int64_t CForkParams::Interval() const { return Timespan()/Spacing(); }

static CForkParams *pCurrentForkingParams = &forkParams;
const CForkParams &ForkingParams() { return *pCurrentForkingParams; }