#pragma once

#include <JuceHeader.h>
namespace Params {
// inherit from any class you want access to the list array
struct userParams{
public:
    enum userParameters
    {
        kParam_InputID = 0,
        kParam_MixID,
        kParam_OutputID,
        kParam_ModeID,
        kParam_NumParameters
    };
    
    enum userControllerTypes{
        kControl_Slider,
        kControl_Button,
        kControl_ToggleButton
    };
};

// stores the default values of user parameters
class parameterINFO : public userParams
{
public:
    parameterINFO(){};
    ~parameterINFO(){};
    
    // Range Struct =============================
    struct parameterRange{
        float minValue = 0.0f;
        float maxValue = 0.0f;
        float increment = 0.0f;
        float defaultValue = 0.0f;
        bool skew = false;
        float skewCenter = 0.0f;
        
    };
    
    
    // User Parameter Values =========================
    parameterRange userParameterValue[kParam_NumParameters] =
    {
        {-24.0f,24.0f,0.0f,0.0f},   // input
        {0.0f,100.0f,0.0f,50.0f}, // mix
        {-24.0f,24.0f,0.0f,0.0f},    // output
        {0.0f,1.0f,1.0f,1.0f}    // mode
        
    };
    
    /* User Controller Type for Attachement ====================
     0 == Slider
     1 == Button
     2 == Toggle Button
     
     *** see parameterControls ***
     */
    
    int userControlType [kParam_NumParameters] =
    {
        kControl_Slider, // Input
        kControl_Slider, // Mix
        kControl_Slider,  // Output
        kControl_Slider //Mode
    };
    
    // User Parameter Names for linking ==============
    juce::String userParameterID [kParam_NumParameters] =
    {
        "inputID",
        "mixID",
        "outputID",
        "modeID"
        
    };
    
    // User Parameter Names in DAW ======================
    juce::String userParameterName [kParam_NumParameters] =
    {
        "Input",
        "Mix",
        "Output",
        "Mode"
    };
    
    
    const int numParams = kParam_NumParameters;
private:
};


}
