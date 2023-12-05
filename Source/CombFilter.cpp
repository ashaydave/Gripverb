/*
  ==============================================================================

    CombFilter.cpp
    Created: 28 Nov 2023 5:03:49pm
    Author:  ashay

  ==============================================================================
*/

#include "CombFilter.h"
#include "Denormalize.h"

CombFilter::CombFilter()
{
	filterStore = 0;
	bufferIndex = 0;
	bufferSize = 0;
	buffer = new float[bufferSize];
	feedback = 0;
	damp1 = 0;
	damp2 = 0;
}

CombFilter::~CombFilter()
{
}

float CombFilter::process(float input)
{
    float output;

    output = buffer[bufferIndex];
	//undenormalise(output);
    filterStore = (output * damp2) + (filterStore * damp1);
	//undenormalise(filterStore);
    buffer[bufferIndex] = input + (filterStore * feedback);
    if (++bufferIndex >= bufferSize)
    {
        bufferIndex = 0;
    }

	return output;
}


void CombFilter::setBuffer(float* buf, int size)
{
	buffer = buf;
	bufferSize = size;
}

void CombFilter::mute()
{
	for (int i = 0; i < bufferSize; i++)
		buffer[i] = 0;
}

void CombFilter::setDamp(float value)
{
	damp1 = value;
	damp2 = 1 - value;
}

float CombFilter::getDamp()
{
	return damp1;
}

void CombFilter::setFeedback(float value)
{
	feedback = value;
}

float CombFilter::getFeedback()
{
	return feedback;
}
