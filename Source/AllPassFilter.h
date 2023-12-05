#ifndef ALLPASSFILTER_H
#define ALLPASSFILTER_H
/*
  ==============================================================================

    AllPassFilter.h
    Created: 28 Nov 2023 5:03:41pm
    Author:  ashay

  ==============================================================================
*/

class AllPassFilter
{
public:
    AllPassFilter();
    ~AllPassFilter();
    void setBuffer(float* buffer, int size);
    float process(float input);
    void mute();
    void setFeedback(float value);
    float getFeedback();

    private:
        float* buffer;
        int bufferSize;
        int bufferIndex;
        float feedback;
};


#endif
