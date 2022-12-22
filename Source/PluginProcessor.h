/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


#include "rnbo/RNBO.h"
#include "rnbo/adapters/juce/RNBO_JuceAudioProcessorUtils.h"
#include "rnbo/adapters/juce/RNBO_JuceAudioProcessor.h"
#include "rnbo/adapters/juce/RNBO_JuceAudioProcessorEditor.h"


class DerivedAudioProcessor : public RNBO::JuceAudioProcessor
{
public:
    DerivedAudioProcessor ();
    AudioProcessorEditor* createEditor() override;
    
    void handleParameterEvent(const RNBO::ParameterEvent& event) override;
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DerivedAudioProcessor)
};



