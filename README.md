This is an example project for rapid prototyping boiler-plate in Juce for user parameter management with smoothing integrated with the processorTree.

#Setup
1. Drag Parameter Folder into your project, or include in projucer.

2. In the PluginEditor.h and PluginProcessor.h 
include "../Source/parameters/include.h"

3. define in Projucer,Exporters under Extra Preprocessor Definitions SMOOTHING_ENABLED=1
if you would like to use the smoothing array 256 samples by default or change the amount of smoothing samples in treeProcessor.h under SMOOTHING_SAMPLES

#User Parameter Setup
1. In the userParams.h list your sliders in userParams::userParameters
    a. leave for kParam_NumParameters at the end for array control
2. in ParameterINFO update values with optional skewing in parameterRange
3. Define param type in userControlType, only supports slider
4. Define userParameterID for tree state
5. Define userParameterName for daw display

/*WARNING*/
Steps 2-5 must have the same amount of elements that the userParameters has not counting kParam_NumParameters.

#Processor
1. replace juce::AudioProcessor with Params::treeProcessor
/* reference the prepareForPlay & processBlock in PluginProcessor.cpp for parameter usage examples.

treeProcessor.h for functions available, mirrored to
juce::SmoothedValue<float>
*/
 
#Editor
1. in PluginEditor.h in your EDITOR inherit from 
public Params::editorTree
2. in PluginEditor.cpp pass in a reference to the processor
editorTree(p)

/* reference the constructor in PluginEditor.cpp for usage example*/

#To-Do
1. save and load encrypted presets
2. support different types of buttons and displays
// ========= \\
