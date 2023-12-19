#pragma once

#include <JuceHeader.h>
#include "userParams.h"
#include "parameterControls.h"
#include "treeProcessor.h"
//==============================================================================
/*
*/
namespace Params {
class editorTree : public parameterINFO
{
public:
    editorTree(treeProcessor& state);
    ~editorTree();
    juce::OwnedArray<juce::Slider> controls;
private:
    
};

}
