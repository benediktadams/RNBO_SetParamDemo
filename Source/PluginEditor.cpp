/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginEditor::PluginEditor (DerivedAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    parameterInterface = p.getRnboObject ().createParameterInterface (RNBO::ParameterEventInterface::SingleProducer, this);
    
    addAndMakeVisible (knob);
    knob.setRange ({0., 100.}, 1.0);
    knob.setValue (50.);
    knob.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    knob.addListener (this);
    
    setSize (400, 300);
}

PluginEditor::~PluginEditor ()
{
}

void PluginEditor::eventsAvailable ()
{
    triggerAsyncUpdate();
}

void PluginEditor::handleAsyncUpdate ()
{
    drainEvents();
}

void PluginEditor::handleParameterEvent (const RNBO::ParameterEvent& event)
{
    DBG("UI: handleParameterEvent ()" << event.getIndex () << ": " << event.getValue ());
    knob.setValue (event.getValue (), dontSendNotification);
}


void PluginEditor::sliderValueChanged (Slider* s)
{
    auto& rnbo = audioProcessor.getRnboObject ();
    DBG("UI: Setting knob value to " << s->getValue () );
    
    // @Cycling: When using scheduleEvent both PluginEditor::handleParameterEvent()
    // and DerivedAudioProcessor::handleParamterEvent() trigger
    rnbo.scheduleEvent (RNBO::ParameterEvent (0/*idx*/, 0/*time*/, s->getValue (), this));
    
    // @Cycling: When using setParameterValue no handleParameterEvent () callbacks receive any calls
    //rnbo.setParameterValue(0, s->getValue ());
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void PluginEditor::resized()
{
    const auto area = getLocalBounds ();
    Rectangle<int> knobArea (200, 200);
    knobArea.setCentre (area.getCentre ());
    knob.setBounds (knobArea);
}
