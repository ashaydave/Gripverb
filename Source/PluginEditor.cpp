/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GottaGetAGripverbAudioProcessorEditor::GottaGetAGripverbAudioProcessorEditor (GottaGetAGripverbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 500);

    auto parameterTree = audioProcessor.getParameters();

    addAndMakeVisible(roomSizeLabel);
    roomSizeLabel.setText("", juce::dontSendNotification);
    roomSizeLabel.setColour(juce::Label::textColourId, juce::Colours::hotpink);
    roomSizeLabel.setJustificationType(juce::Justification::centred);
    roomSizeLabel.setFont(juce::Font(14.0f, juce::Font::bold));

    addAndMakeVisible(roomSizeSlider);
    roomSizeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    roomSizeSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::hotpink);
    roomSizeSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::floralwhite);
    roomSizeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 30);

    roomSizeSliderParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(0);
    roomSizeSlider.setRange(roomSizeSliderParameter->range.start, roomSizeSliderParameter->range.end, 0.01);

    roomSizeSlider.setValue(*roomSizeSliderParameter, juce::NotificationType::dontSendNotification);

    roomSizeSlider.onValueChange = [this]
        {
            *audioProcessor.roomSizeParameter = roomSizeSlider.getValue();

        };

    /*------------*/

    addAndMakeVisible(dampLabel);
    dampLabel.setText("", juce::dontSendNotification);
    dampLabel.setColour(juce::Label::textColourId, juce::Colours::lightgoldenrodyellow);
    dampLabel.setJustificationType(juce::Justification::centred);
    dampLabel.setFont(juce::Font(14.0f, juce::Font::bold));

    addAndMakeVisible(dampSlider);
    dampSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    dampSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::hotpink);
    dampSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::floralwhite);
    dampSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);

    dampSliderParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(1);
    dampSlider.setRange(dampSliderParameter->range.start, dampSliderParameter->range.end, 0.01);

    dampSlider.setValue(*dampSliderParameter, juce::NotificationType::dontSendNotification);

    dampSlider.onValueChange = [this]
        {
            *audioProcessor.dampParameter = dampSlider.getValue();
        };

    /*-------------*/

    addAndMakeVisible(widthLabel);
    widthLabel.setText("", juce::dontSendNotification);
    widthLabel.setColour(juce::Label::textColourId, juce::Colours::lightgoldenrodyellow);
    widthLabel.setJustificationType(juce::Justification::centred);
    widthLabel.setFont(juce::Font(14.0f, juce::Font::bold));

    addAndMakeVisible(widthSlider);
    widthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    widthSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::hotpink);
    widthSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::floralwhite);
    widthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 30, 30);

    widthSliderParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(2);
    widthSlider.setRange(widthSliderParameter->range.start, widthSliderParameter->range.end, 0.01);

    widthSlider.setValue(*widthSliderParameter, juce::NotificationType::dontSendNotification);

    widthSlider.onValueChange = [this]
        {
            *audioProcessor.widthParameter = widthSlider.getValue();

        };

    /*------------*/

    addAndMakeVisible(dryLabel);
    dryLabel.setText("", juce::dontSendNotification);
    dryLabel.setColour(juce::Label::textColourId, juce::Colours::lightgoldenrodyellow);
    dryLabel.setJustificationType(juce::Justification::centred);
    dryLabel.setFont(juce::Font(14.0f, juce::Font::bold));

    addAndMakeVisible(drySlider);
    drySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    drySlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::hotpink);
    drySlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::floralwhite);
    drySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 30, 30);

    drySliderParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(3);
    drySlider.setRange(drySliderParameter->range.start, drySliderParameter->range.end, 0.01);

    drySlider.setValue(*drySliderParameter, juce::NotificationType::dontSendNotification);

    drySlider.onValueChange = [this]
        {
            *audioProcessor.dryParameter = drySlider.getValue();
        };

    /*------------*/

    addAndMakeVisible(wetLabel);
    wetLabel.setText("", juce::dontSendNotification);
    wetLabel.setColour(juce::Label::textColourId, juce::Colours::lightgoldenrodyellow);
    wetLabel.setJustificationType(juce::Justification::centred);
    wetLabel.setFont(juce::Font(14.0f, juce::Font::bold));

    addAndMakeVisible(wetSlider);
    addAndMakeVisible(nasha);
    wetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    wetSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::hotpink);
    wetSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::floralwhite);
    wetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 30, 30);

    wetSliderParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(4);
    wetSlider.setRange(wetSliderParameter->range.start, wetSliderParameter->range.end, 0.01);

    wetSlider.setValue(*wetSliderParameter, juce::NotificationType::dontSendNotification);

    wetSlider.onValueChange = [this]
        {
            *audioProcessor.wetParameter = wetSlider.getValue();
            nasha.setImage(wetSlider.getValue() / wetSlider.getRange().getEnd());
        };


    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::skyblue);
}

GottaGetAGripverbAudioProcessorEditor::~GottaGetAGripverbAudioProcessorEditor()
{
}

//==============================================================================
void GottaGetAGripverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    auto backgroundImage = juce::ImageCache::getFromMemory(BinaryData::GripverbNew_png, BinaryData::GripverbNew_pngSize);
    g.drawImage(backgroundImage, 0, 0, getWidth(), getHeight(), 0, 0, 400, 500);
}

void GottaGetAGripverbAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    auto width = bounds.getWidth();
    auto height = bounds.getHeight();

    float labelWidth = 150.0f;
    float labelHeight = 20.0f;
    float sliderWidth = 100.0f;
    float sliderHeight = 150.0f;
    float xMargin = 20.0f;  // Increased margin for more space
    float yMargin = 20.0f;  // Increased margin for more space

    float totalWidth = (5 * sliderWidth) + (4 * xMargin);

    float startX = (width - totalWidth) / 2 + 200;

    // First row
    roomSizeLabel.setBounds(startX - 150, height / 3.25 - labelHeight - 15, labelWidth, labelHeight);
    roomSizeSlider.setBounds(startX - 35, height / 7 + yMargin - 10, sliderWidth, sliderHeight);

    startX += sliderWidth + xMargin;
    dampLabel.setBounds(startX + 50, height / 3.25 - labelHeight - 15, labelWidth, labelHeight);
    dampSlider.setBounds(startX - 20, height / 7 + yMargin - 10, sliderWidth, sliderHeight);

    // Second row
    startX = (width - totalWidth) / 2 + 200; // Reset the horizontal position
    widthLabel.setBounds(startX - 75, height * 3 / 5 - labelHeight - 15, labelWidth, labelHeight);
    widthSlider.setBounds(startX + 30, height * 3 / 7 + yMargin - 10, sliderWidth, sliderHeight);

    // Third row
    startX = (width - totalWidth) / 2 + 200; // Reset the horizontal position
    dryLabel.setBounds(startX - 150, height * 5.75 / 7 - labelHeight - 15, labelWidth, labelHeight);
    drySlider.setBounds(startX - 35, height * 4.5 / 7 + yMargin - 10, sliderWidth, sliderHeight);

    startX += sliderWidth + xMargin;
    wetLabel.setBounds(startX + 50, height * 5.75 / 7 - labelHeight - 15, labelWidth, labelHeight);
    wetSlider.setBounds(startX - 20, height * 4.5 / 7 + yMargin - 10, sliderWidth, sliderHeight);



   // nasha.setBounds(width / 2, yMargin, width / 2 - xMargin, height - 2 * yMargin);
}


