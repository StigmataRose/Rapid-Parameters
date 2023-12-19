/*
  ==============================================================================

    processorTree.h
    Created: 24 Jul 2023 3:39:44pm
    Author:  Skyler Crank

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "userParams.h"

 // Comment or uncomment this line to enable/
// Need to have define SMOOTHING_ENABLED=1 in projucer, for smoothing
#define SMOOTHING_SAMPLES 256
//==============================================================================
/*
*/
namespace Params {
class treeProcessor : public parameterINFO, public juce::AudioProcessor
{
public:
    treeProcessor(const BusesProperties& ioLayouts);
    ~treeProcessor();
    
    juce::AudioProcessorValueTreeState treeState;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    // Direct Access functions
    float getTreeStateValue(const int param){
        return (*treeState.getRawParameterValue(userParameterID[param])).load();
    }
    
    // Need to have #define SMOOTHING_ENABLED in projucer
    
    /*
     For concise memory management of smoothing, it would be better to use your own smoothing class in the processor, but this is here reguardless. Accessing the smoothing array may be too slow in some use case where 1 or 2 parameters need smoothing. However, the overall processing shouldn't be noticable in most use cases.
     
     It's basically an array wrapper for juce::SmoothedValue<float> & AudioProcessorValueTreeState's handshakes
     */
    
#ifdef SMOOTHING_ENABLED
    // de-referance the array so the computer doesn't "forget" where the memory is
    void setCurrentAndTargetValue(const int param){
        jassert (param > kParam_NumParameters);
        (*smoothers[param]).setCurrentAndTargetValue(*(treeState).getRawParameterValue(userParameterID[param]));
    }
    void specificSamplesToSmooth(const int param, const int numSamples){
        jassert (param > kParam_NumParameters);
        // defaults to SMOOTHING_SAMPLES on construction
        (*smoothers[param]).reset(numSamples);
    }
    void setTargetValue(const int param){
        //jassert (param > kParam_NumParameters);
        (*smoothers[param]).setTargetValue(*(treeState).getRawParameterValue(userParameterID[param]));
    }
    float getNextValue(const int param){
       // jassert (param > kParam_NumParameters);
        return (*smoothers[param]).getNextValue();
    }
    
    // for time based smoothing - not used in demo
    void reset (const double sampleRate, const double rampLengthInSeconds) noexcept
    {
        jassert (sampleRate > 0 && rampLengthInSeconds >= 0);
        for(int i = 0; i < kParam_NumParameters; ++i){
            (*smoothers[i]).reset((int) std::floor (rampLengthInSeconds * sampleRate));
        }
        
    }
    //==============[ entire array control ] ===================
    // just ad s to the functions above
    void setCurrentAndTargetValues(){
        for(int i = 0; i < kParam_NumParameters; ++i){
            (*smoothers[i]).setCurrentAndTargetValue((*(treeState).getRawParameterValue(userParameterID[i])).load());
        }
    }
    void setTargetValues(){
        for(int i = 0; i < kParam_NumParameters; ++i){
            (*smoothers[i]).setTargetValue(*(treeState).getRawParameterValue(userParameterID[i]));
        }
    }
    
#endif
private:
    // Need to have #define SMOOTHING_ENABLED in projucer
#ifdef SMOOTHING_ENABLED
    juce::OwnedArray<juce::SmoothedValue<float>> smoothers;
#endif
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (treeProcessor)
};
}
