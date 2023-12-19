#pragma once
#include "JuceHeader.h"
// All this class does is take JUCE’s default Slider and associate it with the AudioProcessorValueTreeState that exists in our processor.
// This easily allows us to ensure that the attachment class has the same lifetime as the Slider object.

//============= [ Slider ] ========================

namespace Params {

class parameterSlider
:   public juce::Slider
{
public:
    parameterSlider(juce::AudioProcessorValueTreeState& state,
                    const juce::String& parameterID,
                    const juce::String& parameterLabel);
    ~parameterSlider();
    
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    
private:
    std::unique_ptr<SliderAttachment> mAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(parameterSlider);
};

//============= [ Button ] ========================
class parameterButton
:   public juce::TextButton
{
public:
    parameterButton(juce::AudioProcessorValueTreeState& state,
                    const juce::String& parameterID,
                    const juce::String& parameterLabel);
    ~parameterButton();
    
    typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    
private:
    std::unique_ptr<ButtonAttachment> mAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(parameterButton);
};

//============= [ Toggle Button ] ========================

class parameterToggleButton
:   public juce::ToggleButton
{
public:
    parameterToggleButton(juce::AudioProcessorValueTreeState& state,
                          const juce::String& parameterID,
                          const juce::String& parameterLabel);
    ~parameterToggleButton();
    
    typedef juce::AudioProcessorValueTreeState::ButtonAttachment ToggleButtonAttachment;
    
private:
    std::unique_ptr<ToggleButtonAttachment> mAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(parameterToggleButton);
};
}
