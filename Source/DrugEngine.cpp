/*
  ==============================================================================

    DrugEngine.cpp
    Created: 29 Nov 2023 7:49:15pm
    Author:  ashay

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DrugEngine.h"

//==============================================================================
DrugEngine::DrugEngine()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    images.resize(BinaryData::namedResourceListSize);
    for (int i = 0; i < BinaryData::namedResourceListSize; i++)
    {
        auto size = 0;
        BinaryData::getNamedResource(BinaryData::namedResourceList[i], size);
        images[i] = juce::ImageCache::getFromMemory(BinaryData::getNamedResource(BinaryData::namedResourceList[i], size), size);

    }
}

DrugEngine::~DrugEngine()
{
}

void DrugEngine::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(juce::Colours::transparentBlack);

    auto bounds = this->getLocalBounds();
    juce::Rectangle<float> drawBounds = { static_cast<float>(bounds.getX()),static_cast<float>(bounds.getY()),static_cast<float>(bounds.getWidth()),static_cast<float>(bounds.getHeight()) };

    
    g.drawImage(images[currentImage], drawBounds, juce::RectanglePlacement::fillDestination, false);
}

void DrugEngine::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void DrugEngine::setImage(const float& normalizedValue)
{
    std::lock_guard lock_guard(mutex);
    currentImage = juce::jmap<uint32_t>(normalizedValue, 0, 1, 0, images.size() - 1);
    repaint();
    DBG("Images Loaded");
}
