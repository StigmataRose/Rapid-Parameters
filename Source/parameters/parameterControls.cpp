#include "parameterControls.h"

namespace Params {
//============= [ Slider ] ========================
parameterSlider::parameterSlider(juce::AudioProcessorValueTreeState& state,
                                 const juce::String& parameterID,
                                 const juce::String& parameterLabel)
:   juce::Slider(parameterLabel)
{
    mAttachment = std::make_unique<SliderAttachment>(state,parameterID,*this);
}

parameterSlider::~parameterSlider() {
    mAttachment = nullptr;
}

//============= [ Button ] ========================

parameterButton::parameterButton(juce::AudioProcessorValueTreeState& state,
                                 const juce::String& parameterID,
                                 const juce::String& parameterLabel)
:   juce::TextButton(parameterLabel)
{
    mAttachment = std::make_unique<ButtonAttachment>(state,parameterID,*this);
}

parameterButton::~parameterButton() {
    mAttachment = nullptr;
}

//============= [ Toggle Button ] ========================

parameterToggleButton::parameterToggleButton(juce::AudioProcessorValueTreeState& state,
                                             const juce::String& parameterID,
                                             const juce::String& parameterLabel)
:   juce::ToggleButton(parameterLabel)
{
    mAttachment = std::make_unique<ToggleButtonAttachment>(state,parameterID,*this);
}

parameterToggleButton::~parameterToggleButton() {
    mAttachment = nullptr;
}

}
