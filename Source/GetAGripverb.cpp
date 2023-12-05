/*
  ==============================================================================

    Reverb.cpp
    Created: 28 Nov 2023 5:04:03pm
    Author:  ashay

  ==============================================================================
*/

#include "GetAGripverb.h"

GetAGripverb::GetAGripverb()
{
	combL[0].setBuffer(bufferCombL1, combTuningL1);
	combR[0].setBuffer(bufferCombR1, combTuningR1);
	combL[1].setBuffer(bufferCombL2, combTuningL2);
	combR[1].setBuffer(bufferCombR2, combTuningR2);
	combL[2].setBuffer(bufferCombL3, combTuningL3);
	combR[2].setBuffer(bufferCombR3, combTuningR3);
	combL[3].setBuffer(bufferCombL4, combTuningL4);
	combR[3].setBuffer(bufferCombR4, combTuningR4);
	combL[4].setBuffer(bufferCombL5, combTuningL5);
	combR[4].setBuffer(bufferCombR5, combTuningR5);
	combL[5].setBuffer(bufferCombL6, combTuningL6);
	combR[5].setBuffer(bufferCombR6, combTuningR6);
	combL[6].setBuffer(bufferCombL7, combTuningL7);
	combR[6].setBuffer(bufferCombR7, combTuningR7);
	combL[7].setBuffer(bufferCombL8, combTuningL8);
	combR[7].setBuffer(bufferCombR8, combTuningR8);
	allPassL[0].setBuffer(bufferAllPassL1, allPassTuningL1);
	allPassR[0].setBuffer(bufferAllPassR1, allPassTuningR1);
	allPassL[1].setBuffer(bufferAllPassL2, allPassTuningL2);
	allPassR[1].setBuffer(bufferAllPassR2, allPassTuningR2);
	allPassL[2].setBuffer(bufferAllPassL3, allPassTuningL3);
	allPassR[2].setBuffer(bufferAllPassR3, allPassTuningR3);
	allPassL[3].setBuffer(bufferAllPassL4, allPassTuningL4);
	allPassR[3].setBuffer(bufferAllPassR4, allPassTuningR4);

	allPassL[0].setFeedback(0.5f);
	allPassR[0].setFeedback(0.5f);
	allPassL[1].setFeedback(0.5f);
	allPassR[1].setFeedback(0.5f);
	allPassL[2].setFeedback(0.5f);
	allPassR[2].setFeedback(0.5f);
	allPassL[3].setFeedback(0.5f);
	allPassR[3].setFeedback(0.5f);
	setWet(initialWet);
	setRoomSize(initialRoom);
	setDry(initialDry);
	setDamp(initialDamp);
	setWidth(initialWidth);
	//setmode(initialmode);


}

GetAGripverb::~GetAGripverb()
{
}

void GetAGripverb::mute()
{
	for (int i = 0; i < numCombs; i++)
	{
		combL[i].mute();
		combR[i].mute();
	}
	for (int i = 0; i < numAllPasses; i++)
	{
		allPassL[i].mute();
		allPassR[i].mute();
	}
}

void GetAGripverb::processStereo(float* inputL, float* inputR, float* outputL, float* outputR, int numSamples, int skip)
{
	float outL, outR, input;

	while (numSamples-- > 0)
	{
		outL = outR = 0;
		input = (*inputL + *inputR) * gain;

		for (int i = 0; i < numCombs; i++)
		{
			outL += combL[i].process(input);
			outR += combR[i].process(input);
		}

		for (int i = 0; i < numAllPasses; i++)
		{
			outL = allPassL[i].process(outL);
			outR = allPassR[i].process(outR);
		}

		*outputL = outL * wet1 + outR * wet2 + *inputL * dry;
		*outputR = outR * wet1 + outL * wet2 + *inputR * dry;

		outputL += skip;
		outputR += skip;
		inputL += skip;
		inputR += skip;
	}
}

void GetAGripverb::process(float* inputL, float* inputR, float* outputL, float* outputR, int numSamples, int skip)
{
	float outL, outR, input;

	while (numSamples-- > 0)
	{
		outL = outR = 0;
		input = (*inputL + *inputR) * gain;

		for (int i = 0; i < numCombs; i++)
		{
			outL += combL[i].process(input);
			outR += combR[i].process(input);
		}

		for (int i = 0; i < numAllPasses; i++)
		{
			outL = allPassL[i].process(outL);
			outR = allPassR[i].process(outR);
		}

		*outputL = outL * wet1 + outR * wet2 + *inputL * dry;
		*outputR = outR * wet1 + outL * wet2 + *inputR * dry;

		outputL += skip;
		outputR += skip;
		inputL += skip;
		inputR += skip;
	}
}

void GetAGripverb::update()
{
	int i;

	wet1 = wet * (width / 2 + 0.5f);
	wet2 = wet * ((1 - width) / 2);

	roomSize = roomSize;
	damp1 = damp;
	gain = fixedGain;

	for (i = 0; i < numCombs; i++)
	{
		combL[i].setDamp(damp1);
		combR[i].setDamp(damp1);
	}

	for (i = 0; i < numCombs; i++)
	{
		combL[i].setFeedback(roomSize);
		combR[i].setFeedback(roomSize);
	}
}


void GetAGripverb::setRoomSize(float value)
{
	roomSize = (value * scaleRoom) + offsetRoom;
	update();
}

float GetAGripverb::getRoomSize()
{
	return (roomSize-offsetRoom) / scaleRoom;
}

void GetAGripverb::setDamp(float value)
{
	damp = value * scaleDamp;
	update();
}

float GetAGripverb::getDamp()
{
	return damp / scaleDamp;
}

void GetAGripverb::setWet(float value)
{
	wet = value * scaleWet;
	update();
}

float GetAGripverb::getWet()
{
	return wet / scaleWet;
}

void GetAGripverb::setDry(float value)
{
	dry = value * scaleDry;
}

float GetAGripverb::getDry()
{
	return dry / scaleDry;
}

void GetAGripverb::setWidth(float value)
{
	width = value;
	update();
}

float GetAGripverb::getWidth()
{
	return width;
}
