/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "DrugEngine.h"

//==============================================================================
/**
*/
class GottaGetAGripverbAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    GottaGetAGripverbAudioProcessorEditor (GottaGetAGripverbAudioProcessor&);
    ~GottaGetAGripverbAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GottaGetAGripverbAudioProcessor& audioProcessor;

    juce::Label roomSizeLabel, dampLabel, widthLabel, dryLabel, wetLabel;
    juce::Slider roomSizeSlider, dampSlider, widthSlider, drySlider, wetSlider;

    juce::AudioParameterFloat* roomSizeSliderParameter;
    juce::AudioParameterFloat* dampSliderParameter;
    juce::AudioParameterFloat* widthSliderParameter;
    juce::AudioParameterFloat* drySliderParameter;
    juce::AudioParameterFloat* wetSliderParameter;
    DrugEngine nasha;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GottaGetAGripverbAudioProcessorEditor)
};
