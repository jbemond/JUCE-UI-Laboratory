#pragma once
#include <JuceHeader.h>

class MainComponent final : public juce::Component, private juce::MenuBarModel,
                            private juce::Button::Listener, private juce::ComboBox::Listener
{
public:
    MainComponent();
    ~MainComponent() override;
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    struct Palette
    {
        juce::String name;
        juce::Colour background, surface, text, accent;
        int corner = 6;
        float fontSize = 15.0f;
    };
    class LaboratoryLookAndFeel final : public juce::LookAndFeel_V4
    {
    public:
        void setPalette(const Palette&);
        void drawButtonBackground(juce::Graphics&, juce::Button&, const juce::Colour&, bool, bool) override;
        void drawPopupMenuBackground(juce::Graphics&, int, int) override;
    private:
        Palette palette;
    } lookAndFeel;

    juce::StringArray getMenuBarNames() override;
    juce::PopupMenu getMenuForIndex(int, const juce::String&) override;
    void menuItemSelected(int, int) override;
    void buttonClicked(juce::Button*) override;
    void comboBoxChanged(juce::ComboBox*) override;
    void selectTheme(int);
    void chooseFile(bool save);
    void updateLayout();

    juce::MenuBarComponent menuBar { this };
    juce::Label title, description, themeLabel, densityLabel, choiceLabel, sliderLabel, status, detail;
    juce::ComboBox themeBox, densityBox, choiceBox;
    juce::TextButton openButton { "Ouvrir…" }, saveButton { "Enregistrer…" }, contextButton { "Menu contextuel" }, actionButton { "Bouton d'action" };
    juce::ToggleButton nativeChooser { "Dialogue de fichiers natif" }, enabledToggle { "Activer l'option" };
    juce::Slider slider;
    juce::TextEditor editor;
    juce::TextButton tabs[3] { { "Composants" }, { "Menus" }, { "Fichiers" } };
    std::unique_ptr<juce::FileChooser> chooser;
    juce::Array<Palette> palettes;
    Palette current;
    int density = 0, selectedTab = 0;
};
