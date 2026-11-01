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
        int style = 0; // 0 classique, 1 compact, 2 moderne, 3 studio, 4 Win32, 5 Win11, 6 macOS, 7 GNOME, 8 KDE, 9 laboratoire
        float fontSize = 15.0f;
    };
    class LaboratoryLookAndFeel final : public juce::LookAndFeel_V4
    {
    public:
        void setPalette(const Palette&);
        void drawButtonBackground(juce::Graphics&, juce::Button&, const juce::Colour&, bool, bool) override;
        void drawPopupMenuBackground(juce::Graphics&, int, int) override;
        juce::Font getPopupMenuFont() override;
        void drawMenuBarBackground(juce::Graphics&, int, int, bool, juce::MenuBarComponent&) override;
        void drawMenuBarItem(juce::Graphics&, int, int, int, const juce::String&, bool, bool, bool, juce::MenuBarComponent&) override;
        void drawPopupMenuItem(juce::Graphics&, const juce::Rectangle<int>&, bool, bool, bool, bool, bool, const juce::String&, const juce::String&, const juce::Drawable*, const juce::Colour*) override;
        void getIdealPopupMenuItemSize(const juce::String&, bool, int, int&, int&) override;
        int getMenuBarItemWidth(juce::MenuBarComponent&, int, const juce::String&) override;
        juce::Font getMenuBarFont(juce::MenuBarComponent&, int, const juce::String&) override;
        void drawComboBox(juce::Graphics&, int, int, bool, int, int, int, int, juce::ComboBox&) override;
        void drawToggleButton(juce::Graphics&, juce::ToggleButton&, bool, bool) override;
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
    juce::TooltipWindow tooltipWindow { this, 1000 };
    juce::Label title, description, themeLabel, densityLabel, choiceLabel, sliderLabel, status, detail;
    juce::ComboBox themeBox, densityBox, choiceBox;
    juce::TextButton openButton { "Ouvrir…" }, saveButton { "Enregistrer…" }, contextButton { "Menu contextuel" }, actionButton { "Bouton d'action" };
    juce::ToggleButton nativeChooser { "Dialogue de fichiers natif" }, enabledToggle { "Activer l'option" };
    juce::Slider slider;
    juce::TextEditor editor;
    juce::TextButton tabs[3];
    std::unique_ptr<juce::FileChooser> chooser;
    juce::Array<Palette> palettes;
    Palette current;
    int density = 0, selectedTab = 0;
};
