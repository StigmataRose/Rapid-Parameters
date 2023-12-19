/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RapidParametersAudioProcessor::RapidParametersAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : treeProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif

{
 
}

RapidParametersAudioProcessor::~RapidParametersAudioProcessor()
{
}

//==============================================================================
const juce::String RapidParametersAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool RapidParametersAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool RapidParametersAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool RapidParametersAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double RapidParametersAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int RapidParametersAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int RapidParametersAudioProcessor::getCurrentProgram()
{
    return 0;
}

void RapidParametersAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String RapidParametersAudioProcessor::getProgramName (int index)
{
    return {};
}

void RapidParametersAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void RapidParametersAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    setCurrentAndTargetValues();
}

void RapidParametersAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool RapidParametersAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void RapidParametersAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    // for segmented buffers
    int startSample = 0;
    int endSample = buffer.getNumSamples();
    int numChannels = buffer.getNumChannels();
    // channel pointers mono to stereo
    // intended for dual channel processing

    const float* inputL = buffer.getReadPointer(0);
    const float* inputR = nullptr;
    
    float* outputL = buffer.getWritePointer(0);
    float* outputR = buffer.getWritePointer(0);
    
    if(totalNumInputChannels > 1){
        inputR = buffer.getReadPointer(1);
    }
    if(totalNumOutputChannels > 1){
        outputR = buffer.getWritePointer(1);
    }
    setTargetValue(kParam_InputID);
    setTargetValue(kParam_MixID);
    setTargetValue(kParam_OutputID);
    
    // with atomics for buttons
    int On = getTreeStateValue(kParam_ModeID);
    
    for(int sample = startSample; sample < endSample; ++sample){
        float inL = inputL[sample];
        float inR = inL;
        if(totalNumInputChannels){
            inR = inputR[sample];
        }
        // Update Params
        auto input = juce::Decibels::decibelsToGain(getNextValue(kParam_InputID));
        auto mix = getNextValue(kParam_MixID) * 0.01f;
        auto output = juce::Decibels::decibelsToGain(getNextValue(kParam_OutputID));
        // Do processing here
        float outL = inL * input;
        float outR = inR * input;
       
        // direct access
        switch(On){
            case 0:
                inL = 0.0f;
                inR = 0.0f;
                outL = 0.0f;
                outR = 0.0f;
                break;
            case 1:
            
                break;
            default:
                break;
        }
        // output
        outputL[sample] = MIX(inL,(outL * output),mix);
        if(totalNumOutputChannels > 1){
        outputR[sample] = MIX(inR,(outR * output),mix);
        }
    }
}

//==============================================================================
bool RapidParametersAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* RapidParametersAudioProcessor::createEditor()
{
    return new RapidParametersAudioProcessorEditor (*this);
}

//==============================================================================
void RapidParametersAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = treeState.copyState();
     std::unique_ptr<juce::XmlElement> xml(state.createXml());

     copyXmlToBinary(*xml, destData);
}

void RapidParametersAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
      if (xmlState.get() != nullptr)
          if (xmlState->hasTagName(treeState.state.getType()))
              treeState.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RapidParametersAudioProcessor();
}
