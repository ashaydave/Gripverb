#ifndef TUNING_H
#define TUNING_H

/*
  ==============================================================================

    Tuning.h
    Created: 29 Nov 2023 3:23:03pm
    Author:  ashay

  ==============================================================================
*/


const int	numCombs = 8;
const int	numAllPasses = 4;
const float	muted = 0;
const float	fixedGain = 0.015f;
const float scaleWet = 3;
const float scaleDry = 2;
const float scaleDamp = 0.4f;
const float scaleRoom = 0.28f;
const float offsetRoom = 0.7f;
const float initialRoom = 0.5f;
const float initialDamp = 0.5f;
const float initialWet = 1 / scaleWet;
const float initialDry = 0;
const float initialWidth = 1;
const float initialMode = 0;
const int	stereoSpread = 23;

const int combTuningL1 = 1116;
const int combTuningR1 = 1116 + stereoSpread;
const int combTuningL2 = 1188;
const int combTuningR2 = 1188 + stereoSpread;
const int combTuningL3 = 1277;
const int combTuningR3 = 1277 + stereoSpread;
const int combTuningL4 = 1356;
const int combTuningR4 = 1356 + stereoSpread;
const int combTuningL5 = 1422;
const int combTuningR5 = 1422 + stereoSpread;
const int combTuningL6 = 1491;
const int combTuningR6 = 1491 + stereoSpread;
const int combTuningL7 = 1557;
const int combTuningR7 = 1557 + stereoSpread;
const int combTuningL8 = 1617;
const int combTuningR8 = 1617 + stereoSpread;
const int allPassTuningL1 = 556;
const int allPassTuningR1 = 556 + stereoSpread;
const int allPassTuningL2 = 441;
const int allPassTuningR2 = 441 + stereoSpread;
const int allPassTuningL3 = 341;
const int allPassTuningR3 = 341 + stereoSpread;
const int allPassTuningL4 = 225;
const int allPassTuningR4 = 225 + stereoSpread;

#endif
