/*
  ==============================================================================

    AllPassFilter.cpp
    Created: 28 Nov 2023 5:03:41pm
    Author:  ashay

  ==============================================================================
*/

#include "AllPassFilter.h"
#include "Denormalize.h"

float AllPassFilter::process(float input)
{
    float output;
    float bufferOut;

    bufferOut = buffer[bufferIndex];
    //undenormalise(bufferOut);

    output = -input + bufferOut;
    buffer[bufferIndex] = input + (bufferOut * feedback);

    if (++bufferIndex >= bufferSize)
    {
		bufferIndex = 0;
	}

    return output;
}

AllPassFilter::AllPassFilter()
{
    bufferIndex = 0;
    bufferSize = 0;
    feedback = 0;
    buffer = new float[bufferSize];
}

AllPassFilter::~AllPassFilter()
{
    //delete[] buffer;
}

void AllPassFilter::setBuffer(float* buf, int size)
{
    buffer = buf;
    bufferSize = size;
}

void AllPassFilter::mute()
{
    for (int i = 0; i < bufferSize; i++)
        buffer[i] = 0;
}

void AllPassFilter::setFeedback(float value)
{
    feedback = value;
}

float AllPassFilter::getFeedback()
{
    return feedback;
}
