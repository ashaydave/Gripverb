/*
  ==============================================================================

    Denormalize.h
    Created: 29 Nov 2023 5:24:42pm
    Author:  ashay

  ==============================================================================
*/

#ifndef DENORMALIZE_H
#define DENORMALIZE_H

#define undenormalise(sample) if(((*(unsigned int*)&sample)&0x7f800000)==0) sample=0.0f

#endif
