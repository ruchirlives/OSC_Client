/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
OSC_ClientAudioProcessorEditor::OSC_ClientAudioProcessorEditor (OSC_ClientAudioProcessor& p)
	: AudioProcessorEditor(&p), audioProcessor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 250);

	// Set the label text
	addAndMakeVisible(label);
	label.setText("Tags", juce::dontSendNotification);
	label.setColour(juce::Label::textColourId, juce::Colours::white); // Set the text colour explicitly
	label.setFont(juce::Font(15.0f, juce::Font::bold)); // Set the font and size

	// Add the text editor to the editor
	addAndMakeVisible(textEditor);
	textEditor.setMultiLine(true);
	textEditor.setReturnKeyStartsNewLine(true);
	textEditor.setReadOnly(false);
	textEditor.setScrollbarsShown(true);
	textEditor.addListener(this);

	// Allow to tab out of the text editor
	textEditor.setWantsKeyboardFocus(true);

	// Set the text in the text editor to the tags from the processor
	textEditor.setText(audioProcessor.getTags());

	// Set the port and IP address labels
	addAndMakeVisible(ipAddressLabel);
	ipAddressLabel.setText("IP Address", juce::dontSendNotification);
	ipAddressLabel.setColour(juce::Label::textColourId, juce::Colours::white);
	ipAddressLabel.setFont(juce::Font(15.0f, juce::Font::bold));

	addAndMakeVisible(ipAddressEditor);
	ipAddressEditor.setMultiLine(false);
	ipAddressEditor.setReturnKeyStartsNewLine(false);
	ipAddressEditor.setReadOnly(false);
	ipAddressEditor.setScrollbarsShown(false);
	ipAddressEditor.addListener(this);
	ipAddressEditor.setText(audioProcessor.getIpAddress());

	addAndMakeVisible(portLabel);
	portLabel.setText("Port", juce::dontSendNotification);
	portLabel.setColour(juce::Label::textColourId, juce::Colours::white);
	portLabel.setFont(juce::Font(15.0f, juce::Font::bold));

	addAndMakeVisible(portEditor);
	portEditor.setMultiLine(false);
	portEditor.setReturnKeyStartsNewLine(false);
	portEditor.setReadOnly(false);
	portEditor.setScrollbarsShown(false);
	portEditor.addListener(this);
	portEditor.setText(juce::String(audioProcessor.getPort()));

	addAndMakeVisible(reconnectButton);
	reconnectButton.setButtonText("Reconnect");
	reconnectButton.onClick = [this]() { audioProcessor.reConnect(); };

	addAndMakeVisible(getTagsButton);
	getTagsButton.setButtonText("Get Tags");
	getTagsButton.onClick = [this]() 
		{ 
			auto& tags = audioProcessor.receiver.getLatestTags();
			// convert StringArray to new line separated string list
			juce::String tagsAsString = tags.joinIntoString("\n");
			
			textEditor.setText(tagsAsString);
			audioProcessor.setTags(tagsAsString);
				
		};

}



void OSC_ClientAudioProcessorEditor::textEditorFocusLost(juce::TextEditor& textEditor)
{
	if (&textEditor == &ipAddressEditor)
	{
		// Get the text from the text editor
		auto text = ipAddressEditor.getText();
		// Send the text to the processor
		audioProcessor.setIpAddress(text);
	}
	else if (&textEditor == &portEditor)
	{
		// Get the text from the text editor
		auto text = portEditor.getText();
		// Send the text to the processor
		audioProcessor.setPort(text.getIntValue());
	}
	else if (&textEditor == &textEditor)
	{
		// Get the text from the text editor
		auto text = textEditor.getText();
		// Send the text to the processor
		audioProcessor.setTags(text);
	}
}

OSC_ClientAudioProcessorEditor::~OSC_ClientAudioProcessorEditor()
{
}

//==============================================================================
void OSC_ClientAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));

}

void OSC_ClientAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	label.setBounds(10, 10, 100, 20);
	// Layout texteditor relative
	textEditor.setBounds(10, 30, getWidth() - 20, 100);

	// Layout IP address and port labels
	ipAddressLabel.setBounds(10, getHeight() - 100, 100, 20);
	ipAddressEditor.setBounds(10, getHeight() - 80, 100, 20);
	portLabel.setBounds(120, getHeight() - 100, 100, 20);
	portEditor.setBounds(120, getHeight() - 80, 100, 20);

	// Layout reconnect button
	reconnectButton.setBounds(10, getHeight() - 50, 100, 20);

	// Layout get tags button
	getTagsButton.setBounds(120, getHeight() - 50, 100, 20);
	

}
