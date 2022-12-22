/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class PluginEditor  : public juce::AudioProcessorEditor,
                    public AsyncUpdater,
                    public RNBO::EventHandler,
                    public Slider::Listener
{
public:
    PluginEditor (DerivedAudioProcessor&);
    ~PluginEditor() override;
    
    void eventsAvailable() override;
    void handleAsyncUpdate () override;
    void handleParameterEvent(const RNBO::ParameterEvent& event) override;
    
    void sliderValueChanged (Slider* s) override;
    
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    DerivedAudioProcessor& audioProcessor;
    
    RNBO::ParameterEventInterfaceUniquePtr parameterInterface;
    
    Slider knob;
   
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
