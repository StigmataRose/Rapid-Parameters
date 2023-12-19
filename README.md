# JUCE Rapid Prototyping Boilerplate

This is an example project for rapid prototyping boilerplate in JUCE for user parameter management with smoothing integrated with the processorTree.

## Setup

- Drag `Parameter` folder into your project, or include in Projucer.
- In `PluginEditor.h` and `PluginProcessor.h`, include `"../Source/parameters/include.h"`.
- Define in Projucer, Exporters under Extra Preprocessor Definitions `SMOOTHING_ENABLED=1` if you would like to use the smoothing array (256 samples by default) or change the amount of smoothing samples in `treeProcessor.h` under `SMOOTHING_SAMPLES`.

## User Parameter Setup

1. In `userParams.h`, list your sliders in `userParams::userParameters`.
   - Leave space for `kParam_NumParameters` at the end for array control.
2. In `ParameterINFO`, update values with optional skewing in `parameterRange`.
3. Define param type in `userControlType` (only supports slider).
4. Define `userParameterID` for tree state.
5. Define `userParameterName` for DAW display.

*<sub>**WARNING:** Steps 2-5 must have the same number of elements as \`userParameters\` (excluding \`kParam_NumParameters\`).</sub>*

## Processor

Replace `juce::AudioProcessor` with `Params::treeProcessor`.
- Reference the `prepareForPlay` and `processBlock` in `PluginProcessor.cpp` for parameter usage examples.
- `treeProcessor.h` for functions available, mirrored to `juce::SmoothedValue`.

## Editor

1. In `PluginEditor.h`, in your editor, inherit from `public Params::editorTree`.
2. In `PluginEditor.cpp`, pass in a reference to the processor `editorTree(p)`.

Refer to the constructor in `PluginEditor.cpp` for usage examples.

## To-Do

- Save and load encrypted presets.
- Support different types of buttons and displays.

// ========= \
