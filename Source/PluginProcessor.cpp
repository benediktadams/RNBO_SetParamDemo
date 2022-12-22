/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#define RNBO_JUCE_NO_CREATE_PLUGIN_FILTER


#include "PluginProcessor.h"
#include "PluginEditor.h"



#include "rnbo/RNBO.cpp"
#include "rnbo/adapters/juce/RNBO_JuceAudioProcessorUtils.cpp"
#include "rnbo/adapters/juce/RNBO_JuceAudioProcessor.cpp"
#include "rnbo/adapters/juce/RNBO_JuceAudioProcessorEditor.cpp"

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DerivedAudioProcessor ();
}

DerivedAudioProcessor::DerivedAudioProcessor ()
{
    
}

AudioProcessorEditor* DerivedAudioProcessor::createEditor()
{
    return new PluginEditor (*this);
}


void DerivedAudioProcessor::handleParameterEvent(const RNBO::ParameterEvent& event)
{
    DBG("Processor: handleParameterEvent() " << event.getIndex () << ": " << event.getValue ());
    RNBO::JuceAudioProcessor::handleParameterEvent (event);
}
