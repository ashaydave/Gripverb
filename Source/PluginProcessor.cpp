/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <cassert>

//==============================================================================
GottaGetAGripverbAudioProcessor::GottaGetAGripverbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), parameters(*this, nullptr, juce::Identifier("GetAGripVerb"), {
         std::make_unique<juce::AudioParameterFloat>("roomSizeParameter", "Room Size", 0, 1, 0.5),
         std::make_unique<juce::AudioParameterFloat>("dampParameter", "Damp", 0, 1, 0.5),
         std::make_unique<juce::AudioParameterFloat>("widthParameter", "Width", 0, 1, 0.5),
         std::make_unique<juce::AudioParameterFloat>("dryParameter", "Dry", 0, 1, 0.5),
         std::make_unique<juce::AudioParameterFloat>("wetParameter", "Wet", 0, 1, 0)
                       })
#endif
{
    roomSizeParameter = parameters.getRawParameterValue("roomSizeParameter");
	dampParameter = parameters.getRawParameterValue("dampParameter");
	widthParameter = parameters.getRawParameterValue("widthParameter");
	dryParameter = parameters.getRawParameterValue("dryParameter");
	wetParameter = parameters.getRawParameterValue("wetParameter");
}

GottaGetAGripverbAudioProcessor::~GottaGetAGripverbAudioProcessor()
{
}

//==============================================================================
const juce::String GottaGetAGripverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GottaGetAGripverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GottaGetAGripverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GottaGetAGripverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GottaGetAGripverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GottaGetAGripverbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GottaGetAGripverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GottaGetAGripverbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String GottaGetAGripverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void GottaGetAGripverbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void GottaGetAGripverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void GottaGetAGripverbAudioProcessor::releaseResources()
{
    // Buffer will be full of rubbish - so we MUST mute them
    verb.mute();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GottaGetAGripverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void GottaGetAGripverbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    verb.setDamp(*dampParameter);
    verb.setDry(*dryParameter);
    verb.setRoomSize(*roomSizeParameter);
    verb.setWet(*wetParameter);
    verb.setWidth(*widthParameter);

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    assert(totalNumInputChannels == 2);
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    float* input_output_L = buffer.getWritePointer(0);
    float* input_output_R = buffer.getWritePointer(1);
    verb.processStereo(input_output_L, input_output_R, input_output_L, input_output_R, buffer.getNumSamples(), 1);
    
    //for (int channel = 0; channel < totalNumInputChannels; ++channel)
    //{
    //    auto* channelData = buffer.getWritePointer (channel);
    //    float* channelData = buffer.getWritePointer(channel);
    //    float * stereoProc = block.buffer.getWriterPointer(channel);
    //    std::copy_n(stereoProc, buffer.getNumSamples(), channelData);

    //    
    //}
}

//==============================================================================
bool GottaGetAGripverbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* GottaGetAGripverbAudioProcessor::createEditor()
{
    return new GottaGetAGripverbAudioProcessorEditor (*this);
}

//==============================================================================
void GottaGetAGripverbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GottaGetAGripverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GottaGetAGripverbAudioProcessor();
}
