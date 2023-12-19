/*
  ==============================================================================

    processorTree.cpp
    Created: 24 Jul 2023 3:39:44pm
    Author:  Skyler Crank

  ==============================================================================
*/

#include <JuceHeader.h>
#include "treeProcessor.h"

namespace Params {
//==============================================================================
treeProcessor::treeProcessor(const BusesProperties& ioLayouts) : juce::AudioProcessor(ioLayouts),treeState(*this, nullptr, "PARAMETER", createParameterLayout())
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
#ifdef SMOOTHING_ENABLED
    for(int i = 0; i <kParam_NumParameters; ++i){
        std::unique_ptr smooth = std::make_unique<juce::SmoothedValue<float>>();
        (*smooth).setCurrentAndTargetValue(userParameterValue[i].defaultValue);
        //  smoothers.add(smooth.release());
        smoothers.add(std::move(smooth.release()));
    }
#endif
    }
    
treeProcessor::~treeProcessor()
    {
        smoothers.clear();
    }
    
    juce::AudioProcessorValueTreeState::ParameterLayout treeProcessor::createParameterLayout()
    {
        std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
        
        
        for(int i = 0; i <kParam_NumParameters; ++i){
            // local range created
            juce::NormalisableRange<float> loopRange {userParameterValue[i].minValue, userParameterValue[i].maxValue,userParameterValue[i].increment};
            
            // determine skew
            if(userParameterValue[i].skew){
                loopRange.setSkewForCentre(userParameterValue[i].skewCenter);
            }
            // push back param to vector
            params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {userParameterID[i],  1 }, userParameterName[i], loopRange, userParameterValue[i].defaultValue));
            //Smoother
        }
        
        return { params.begin(), params.end() };
    }
    
}
