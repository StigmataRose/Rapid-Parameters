/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RapidParametersAudioProcessorEditor::RapidParametersAudioProcessorEditor (RapidParametersAudioProcessor& p)
: AudioProcessorEditor (&p), editorTree(p), audioProcessor (p)
{

    setSize (400, 100);
    
    // Slider for button control
      addAndMakeVisible(controls[kParam_ModeID]);
      controls[kParam_ModeID]->setBounds(0,0,100,100);
      controls[kParam_ModeID]->setSliderStyle(juce::Slider::RotaryVerticalDrag);
      controls[kParam_ModeID]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
      controls[kParam_ModeID]->addListener(this);
      controls[kParam_ModeID]->setVisible(false);
      // Connected Button
    
    addAndMakeVisible(&onOff);
    onOff.setBounds(0, 0, 100, 100);
    onOff.onClick = [this]{
        if(controls[kParam_ModeID]->getValue() < 0.5f){
            controls[kParam_ModeID]->setValue(1.0f, juce::sendNotification);
        }else{
            controls[kParam_ModeID]->setValue(0.0f, juce::sendNotification);
        }
    };
    //when the ui is constructed set the button
    if(controls[kParam_ModeID]->getValue() < 0.5f){
        onOff.setButtonText("OFF");
    }else{
        onOff.setButtonText("ON");
    }
    // Slider array for quick access
      addAndMakeVisible(controls[kParam_InputID]);
      controls[kParam_InputID]->setBounds(100,0,100,100);
      controls[kParam_InputID]->setSliderStyle(juce::Slider::RotaryVerticalDrag);
      controls[kParam_InputID]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
     // controls[k_input]->setLookAndFeel(&draw);
      
      
      addAndMakeVisible(controls[kParam_MixID]);
      controls[kParam_MixID]->setBounds(200,0,100,100);
      controls[kParam_MixID]->setSliderStyle(juce::Slider::RotaryVerticalDrag);
      controls[kParam_MixID]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
     // controls[k_mix]->setLookAndFeel(&draw);
      
      
      addAndMakeVisible(controls[kParam_OutputID]);
      controls[kParam_OutputID]->setBounds(300,0,100,100);
      controls[kParam_OutputID]->setSliderStyle(juce::Slider::RotaryVerticalDrag);
      controls[kParam_OutputID]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    //  controls[k_output]->setLookAndFeel(&draw);
}

RapidParametersAudioProcessorEditor::~RapidParametersAudioProcessorEditor()
{
}

//==============================================================================
void RapidParametersAudioProcessorEditor::paint (juce::Graphics& g)
{

g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void RapidParametersAudioProcessorEditor::resized()
{
  
}

// for now this is how to connect a button
void RapidParametersAudioProcessorEditor::sliderValueChanged (juce::Slider* slider){
    // This is for when the plugin is loaded from the state, or automated
    // the display will always match up with the actual value of the slider.,
    if(slider == controls[kParam_ModeID]){
        if(controls[kParam_ModeID]->getValue() < 0.5f){
            onOff.setButtonText("OFF");
        }else{
            onOff.setButtonText("ON");
        }
    }
}
