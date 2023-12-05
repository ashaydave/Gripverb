#ifndef GETAGRIPVERB_H
#define GETAGRIPVERB_H

/*
  ==============================================================================

    Reverb.h
    Created: 28 Nov 2023 5:04:03pm
    Author:  ashay

  ==============================================================================
*/

#include "CombFilter.h"
#include "AllPassFilter.h"
#include "Tuning.h"

class GetAGripverb
{
public:
    GetAGripverb();
    ~GetAGripverb();
    void mute();
    void process(float* inputL, float* inputR, float* outputL, float* outputR, int numSamples, int skip);
    void processStereo(float* inputL, float* inputR, float* outputL, float* outputR, int numSamples, int skip);
    void setRoomSize(float value);
    float getRoomSize();
    void setDamp(float value);
    float getDamp();
    void setWet(float value);
    float getWet();
    void setDry(float value);
    float getDry();
    void setWidth(float value);
    float getWidth();
   /* void setmode(float value);
    float getmode();*/

    void update();
    
private:
    float gain;
    float roomSize;
    float damp, damp1;
    float wet, wet1, wet2;
    float dry;
    float width;
    //float mode;

    CombFilter combL[numCombs];
    CombFilter combR[numCombs];
    AllPassFilter allPassL[numAllPasses];
    AllPassFilter allPassR[numAllPasses];

    // Comb Filter buffers
    float	bufferCombL1[combTuningL1];
    float	bufferCombR1[combTuningR1];
    float	bufferCombL2[combTuningL2];
    float	bufferCombR2[combTuningR2];
    float	bufferCombL3[combTuningL3];
    float	bufferCombR3[combTuningR3];
    float	bufferCombL4[combTuningL4];
    float	bufferCombR4[combTuningR4];
    float	bufferCombL5[combTuningL5];
    float	bufferCombR5[combTuningR5];
    float	bufferCombL6[combTuningL6];
    float	bufferCombR6[combTuningR6];
    float	bufferCombL7[combTuningL7];
    float	bufferCombR7[combTuningR7];
    float	bufferCombL8[combTuningL8];
    float	bufferCombR8[combTuningR8];

    // All Pass Buffers
    float	bufferAllPassL1[allPassTuningL1];
    float	bufferAllPassR1[allPassTuningR1];
    float	bufferAllPassL2[allPassTuningL2];
    float	bufferAllPassR2[allPassTuningR2];
    float	bufferAllPassL3[allPassTuningL3];
    float	bufferAllPassR3[allPassTuningR3];
    float	bufferAllPassL4[allPassTuningL4];
    float	bufferAllPassR4[allPassTuningR4];

};

#endif
