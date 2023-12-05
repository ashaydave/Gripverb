/*
  ==============================================================================

    DrugEngine.h
    Created: 29 Nov 2023 7:49:15pm
    Author:  ashay

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DrugEngine  : public juce::Component
{
public:
    DrugEngine();
    ~DrugEngine() override;
    void paint (juce::Graphics&) override;
    void resized() override;
    void setImage(const float& normalizedValue);
private:
    std::vector<juce::Image> images;
    std::mutex mutex;
    uint32_t currentImage = 0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DrugEngine)
};
