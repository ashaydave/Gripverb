#ifndef COMBFILTER_H
#define COMBFILTER_H

/*
  ==============================================================================

    CombFilter.h
    Created: 28 Nov 2023 5:03:49pm
    Author:  ashay

  ==============================================================================
*/

class CombFilter
{
public:
    CombFilter();
    ~CombFilter();
    void setBuffer(float* buffer, int size);
    float process(float input);
    void mute();
    void setDamp(float value);
    float getDamp();
    void setFeedback(float value);
    float getFeedback();

private:
    float feedback;
    float filterStore;
    float damp1;
    float damp2;
    float* buffer;
    int bufferSize;
    int bufferIndex;
};


#endif
