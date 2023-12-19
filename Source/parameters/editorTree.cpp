#include <JuceHeader.h>
#include "editorTree.h"

//==============================================================================
namespace Params {
editorTree::editorTree(treeProcessor& state)
{
    // I put this here for more control in the future, with button automation
    // however right now buttons are just glorified sliders
    // everything is a glorified slider at this point... ha

    for(int i = 0; i <kParam_NumParameters; ++i){
        switch(userControlType[i]){
            case kControl_Slider:
                controls.add(std::move(dynamic_cast<juce::Slider*>(new parameterSlider(state.treeState, userParameterID[i],userParameterName[i]))));
                break;
            case kControl_Button:
                break;
            case kControl_ToggleButton:
                break;
            default:
                // slider
                break;
                
        }
    }
}

editorTree::~editorTree()
{
    for(int i = 0; i < kParam_NumParameters; ++i){
        controls[i]->setLookAndFeel(nullptr);
    }
    controls.clear();
}

}
