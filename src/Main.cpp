#include "MainComponent.h"

class UILaboratoryApplication final : public juce::JUCEApplication
{
public:
    const juce::String getApplicationName() override { return "JUCE UI Laboratory"; }
    const juce::String getApplicationVersion() override { return "0.1.0"; }
    bool moreThanOneInstanceAllowed() override { return true; }
    void initialise(const juce::String&) override
    {
        mainWindow = std::make_unique<Window>(getApplicationName());
    }
    void shutdown() override { mainWindow.reset(); }
    void systemRequestedQuit() override { quit(); }

private:
    class Window final : public juce::DocumentWindow
    {
    public:
        explicit Window(const juce::String& name)
          : DocumentWindow(name, juce::Colours::darkgrey, allButtons)
        {
            setUsingNativeTitleBar(true);
            setContentOwned(new MainComponent(), true);
            setResizable(true, true);
            centreWithSize(1120, 740);
            setVisible(true);
        }
        void closeButtonPressed() override { juce::JUCEApplication::getInstance()->systemRequestedQuit(); }
    };
    std::unique_ptr<Window> mainWindow;
};
START_JUCE_APPLICATION(UILaboratoryApplication)
