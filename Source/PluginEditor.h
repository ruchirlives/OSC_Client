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
class OSC_ClientAudioProcessorEditor : public juce::AudioProcessorEditor, public juce::TextEditor::Listener
{
public:
	// Add the listener to the class
	void textEditorFocusLost(juce::TextEditor& textEditor) override;

    OSC_ClientAudioProcessorEditor (OSC_ClientAudioProcessor&);
    ~OSC_ClientAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    OSC_ClientAudioProcessor& audioProcessor;

	// Create a TextEditor component
	juce::TextEditor textEditor;

    // Create a label
	juce::Label label;

	// Create labels and text boxes for the IP address and port
	juce::Label ipAddressLabel;
	juce::TextEditor ipAddressEditor;
	juce::Label portLabel;
	juce::TextEditor portEditor;

	// Create a button for IP and port reconnection
	juce::TextButton reconnectButton;

	// Create a button to get the latest tags
	juce::TextButton getTagsButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSC_ClientAudioProcessorEditor)
};
