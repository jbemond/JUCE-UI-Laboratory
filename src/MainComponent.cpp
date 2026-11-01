#include "MainComponent.h"

void MainComponent::LaboratoryLookAndFeel::setPalette(const Palette& p)
{
    palette = p;
    setColour(juce::ResizableWindow::backgroundColourId, p.background);
    setColour(juce::Label::textColourId, p.text);
    setColour(juce::TextButton::buttonColourId, p.surface);
    setColour(juce::TextButton::buttonOnColourId, p.accent);
    setColour(juce::TextButton::textColourOffId, p.text);
    setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    setColour(juce::ComboBox::backgroundColourId, p.surface);
    setColour(juce::ComboBox::textColourId, p.text);
    setColour(juce::ComboBox::arrowColourId, p.text);
    setColour(juce::ComboBox::outlineColourId, p.accent.withAlpha(0.4f));
    setColour(juce::TextEditor::backgroundColourId, p.surface);
    setColour(juce::TextEditor::textColourId, p.text);
    setColour(juce::TextEditor::outlineColourId, p.accent.withAlpha(0.5f));
    setColour(juce::TextEditor::highlightColourId, p.accent.withAlpha(0.45f));
    setColour(juce::PopupMenu::backgroundColourId, p.surface);
    setColour(juce::PopupMenu::textColourId, p.text);
    setColour(juce::PopupMenu::highlightedBackgroundColourId, p.accent);
    setColour(juce::Slider::textBoxTextColourId, p.text);
    setColour(juce::Slider::textBoxBackgroundColourId, p.surface);
    setColour(juce::Slider::textBoxOutlineColourId, p.text.withAlpha(0.35f));
    setColour(juce::Slider::thumbColourId, p.accent);
    setColour(juce::Slider::trackColourId, p.accent.withAlpha(0.5f));
    setColour(juce::ToggleButton::textColourId, p.text);
    setColour(juce::ToggleButton::tickColourId, p.accent);
}
void MainComponent::LaboratoryLookAndFeel::drawButtonBackground(juce::Graphics& g, juce::Button& b, const juce::Colour& base, bool over, bool down)
{
    auto r = b.getLocalBounds().toFloat().reduced(1.0f);
    const int style = palette.style;
    const bool classic = style == 0 || style == 4;
    const bool flat = style == 1 || style == 3;
    const bool pill = style == 6 || style == 7;
    const bool tab = b.getComponentID() == "lab-tab";
    auto colour = b.getToggleState() ? palette.accent : base;
    if (flat && ! b.getToggleState()) colour = palette.surface.interpolatedWith(palette.text, 0.08f);
    if (tab && ! b.getToggleState())
        colour = palette.background;
    if (over) colour = colour.brighter(0.10f);
    if (down) colour = colour.darker(0.20f);
    const float radius = classic ? 0.0f : (pill ? r.getHeight() * 0.48f : (float) palette.corner);
    if (classic)
    {
        g.setColour(colour);
        g.fillRect(r);
        g.setColour(down ? juce::Colours::darkgrey : juce::Colours::white);
        g.drawLine(r.getX(), r.getBottom(), r.getX(), r.getY(), 2.0f);
        g.drawLine(r.getX(), r.getY(), r.getRight(), r.getY(), 2.0f);
        g.setColour(down ? juce::Colours::white : juce::Colours::darkgrey);
        g.drawLine(r.getRight(), r.getY(), r.getRight(), r.getBottom(), 2.0f);
        g.drawLine(r.getX(), r.getBottom(), r.getRight(), r.getBottom(), 2.0f);
    }
    else
    {
        if (style == 5 || style == 8)
        {
            g.setColour(juce::Colours::black.withAlpha(0.10f));
            g.fillRoundedRectangle(r.translated(0.0f, 2.0f), radius);
        }
        g.setColour(colour);
        g.fillRoundedRectangle(r, radius);
        if (! flat || (style == 3 && ! tab))
        {
            g.setColour(palette.accent.withAlpha(style == 6 ? 0.10f : 0.34f));
            g.drawRoundedRectangle(r, radius, 1.0f);
        }
        if (tab && b.getToggleState())
        {
            g.setColour(palette.accent);
            if (style == 6 || style == 5 || style == 8)
                g.fillRoundedRectangle(r.removeFromBottom(3.0f), 1.5f);
            else
                g.fillRect(r.removeFromBottom(3.0f));
        }
    }
}
juce::Font MainComponent::LaboratoryLookAndFeel::getPopupMenuFont()
{
    return juce::Font(juce::FontOptions(palette.fontSize));
}
void MainComponent::LaboratoryLookAndFeel::drawPopupMenuBackground(juce::Graphics& g, int w, int h)
{
    g.fillAll(palette.surface);
    if (palette.style == 4 || palette.style == 0)
    {
        g.setColour(juce::Colours::white);
        g.drawLine(0, 0, (float) w, 0, 2.0f);
        g.drawLine(0, 0, 0, (float) h, 2.0f);
        g.setColour(juce::Colours::grey);
        g.drawLine((float) w - 1, 0, (float) w - 1, (float) h, 2.0f);
        g.drawLine(0, (float) h - 1, (float) w, (float) h - 1, 2.0f);
    }
    else
    {
        g.setColour(palette.accent.withAlpha(palette.style == 3 ? 0.6f : 0.22f));
        g.drawRect(0, 0, w, h, 1);
    }
}
void MainComponent::LaboratoryLookAndFeel::drawMenuBarBackground(juce::Graphics& g, int w, int h, bool, juce::MenuBarComponent&)
{
    const int s = palette.style;
    g.fillAll((s == 1 || s == 3 || s == 4) ? palette.surface : palette.background);
    if (s == 0 || s == 4)
    {
        g.setColour(juce::Colours::white.withAlpha(0.75f));
        g.drawHorizontalLine(0, 0.0f, (float) w);
        g.setColour(palette.text.withAlpha(0.40f));
        g.drawHorizontalLine(h - 1, 0.0f, (float) w);
    }
    else if (s == 3)
    {
        g.setColour(palette.accent);
        g.fillRect(0, h - 2, w, 2);
    }
    else if (s == 5 || s == 6 || s == 8)
    {
        g.setColour(palette.text.withAlpha(0.09f));
        g.drawHorizontalLine(h - 1, 0.0f, (float) w);
    }
}
juce::Font MainComponent::LaboratoryLookAndFeel::getMenuBarFont(juce::MenuBarComponent&, int, const juce::String&)
{
    return juce::Font(juce::FontOptions(palette.fontSize + (palette.style == 6 ? 0.5f : 0.0f)));
}
int MainComponent::LaboratoryLookAndFeel::getMenuBarItemWidth(juce::MenuBarComponent& bar, int item, const juce::String& text)
{
    const auto font = getMenuBarFont(bar, item, text);
    const int padding = palette.style == 1 ? 12 : (palette.style == 6 || palette.style == 7 ? 32 : 23);
    return juce::GlyphArrangement::getStringWidthInt(font, text) + padding;
}
void MainComponent::LaboratoryLookAndFeel::drawMenuBarItem(juce::Graphics& g, int w, int h, int index, const juce::String& text,
                                                              bool over, bool open, bool, juce::MenuBarComponent& bar)
{
    const int s = palette.style;
    auto r = juce::Rectangle<float>(1.0f, 2.0f, (float) w - 2.0f, (float) h - 4.0f);
    if (open || over)
    {
        g.setColour(open ? palette.accent : palette.accent.withAlpha(s == 4 ? 0.40f : 0.18f));
        if (s == 0 || s == 4) g.fillRect(r);
        else if (s == 3) g.fillRect(r.removeFromBottom(3.0f));
        else g.fillRoundedRectangle(r, s == 6 || s == 7 ? 9.0f : 5.0f);
    }
    g.setColour(open && s != 3 ? juce::Colours::white : palette.text.withMultipliedAlpha(bar.isEnabled() ? 1.0f : 0.4f));
    g.setFont(getMenuBarFont(bar, index, text));
    g.drawFittedText(text, 0, 0, w, h, juce::Justification::centred, 1);
}
void MainComponent::LaboratoryLookAndFeel::getIdealPopupMenuItemSize(const juce::String& text, bool separator,
                                                                       int, int& idealWidth, int& idealHeight)
{
    if (separator)
    {
        idealWidth = 2;
        idealHeight = 5;
        return;
    }

    // The menu uses exactly the same font as the main application menu bar.
    // Reserve the checkmark gutter only for menus that can contain selections
    // (JUCE normally positions menu items using a shared width).
    idealWidth = juce::GlyphArrangement::getStringWidthInt(getPopupMenuFont(), text) + 26;
    idealHeight = juce::roundToInt(palette.fontSize) + 10;
}
void MainComponent::LaboratoryLookAndFeel::drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area,
                                                               bool separator, bool active, bool highlighted, bool ticked,
                                                               bool hasSubMenu, const juce::String& text, const juce::String& shortcut,
                                                               const juce::Drawable* icon, const juce::Colour* textColour)
{
    if (separator)
    {
        g.setColour(palette.text.withAlpha(0.20f));
        g.fillRect(area.reduced(5, 0).withHeight(1).withY(area.getCentreY()));
        return;
    }
    const bool selected = active && highlighted;
    if (selected)
    {
        g.setColour(palette.accent);
        if (palette.style == 0 || palette.style == 4)
            g.fillRect(area);
        else
            g.fillRoundedRectangle(area.toFloat().reduced(2.0f, 1.0f), (float) juce::jmin(palette.corner, 5));
    }

    g.setColour(textColour != nullptr ? *textColour
                                      : selected ? juce::Colours::white
                                                 : palette.text.withMultipliedAlpha(active ? 1.0f : 0.45f));
    g.setFont(getPopupMenuFont());
    const int left = ticked || icon != nullptr ? 24 : 8;
    const int right = hasSubMenu ? 18 : (shortcut.isNotEmpty() ? 45 : 7);
    g.drawFittedText(text, area.withTrimmedLeft(left).withTrimmedRight(right),
                     juce::Justification::centredLeft, 1);
    if (shortcut.isNotEmpty())
        g.drawFittedText(shortcut, area.withTrimmedRight(17),
                         juce::Justification::centredRight, 1);

    if (ticked)
    {
        const float x = (float) area.getX() + 6, y = (float) area.getCentreY();
        g.drawLine(x, y, x + 4.0f, y + 4.0f, 1.5f);
        g.drawLine(x + 4.0f, y + 4.0f, x + 11.0f, y - 4.0f, 1.5f);
    }
    if (hasSubMenu)
    {
        const float x = (float) area.getRight() - 12, y = (float) area.getCentreY();
        juce::Path arrow;
        arrow.startNewSubPath(x - 2, y - 4);
        arrow.lineTo(x + 2, y);
        arrow.lineTo(x - 2, y + 4);
        g.strokePath(arrow, juce::PathStrokeType(1.5f));
    }
}
void MainComponent::LaboratoryLookAndFeel::drawComboBox(juce::Graphics& g, int w, int h, bool,
                                                          int, int, int, int, juce::ComboBox& box)
{
    auto r = juce::Rectangle<float>(0.5f, 0.5f, (float) w - 1.0f, (float) h - 1.0f);
    const bool classic = palette.style == 0 || palette.style == 4;
    const float radius = classic ? 0.0f : (palette.style == 6 ? 10.0f : (float) palette.corner);
    g.setColour(palette.surface);
    g.fillRoundedRectangle(r, radius);
    g.setColour(classic ? palette.text.withAlpha(0.65f) : palette.accent.withAlpha(0.35f));
    g.drawRoundedRectangle(r, radius, 1.0f);
    juce::Path arrow;
    const float x = (float) w - 16.0f, y = (float) h * 0.5f;
    arrow.startNewSubPath(x - 4.0f, y - 2.0f);
    arrow.lineTo(x, y + 2.0f);
    arrow.lineTo(x + 4.0f, y - 2.0f);
    g.setColour(palette.text);
    g.strokePath(arrow, juce::PathStrokeType(1.6f));
    juce::ignoreUnused(box);
}
void MainComponent::LaboratoryLookAndFeel::drawToggleButton(juce::Graphics& g, juce::ToggleButton& button, bool over, bool)
{
    const auto bounds = button.getLocalBounds().toFloat();
    const bool on = button.getToggleState();
    const bool switchStyle = palette.style == 5 || palette.style == 6 || palette.style == 7;
    if (switchStyle)
    {
        const juce::Rectangle<float> track(2.0f, bounds.getCentreY() - 10.0f, 38.0f, 20.0f);
        g.setColour(on ? palette.accent : palette.text.withAlpha(0.30f));
        g.fillRoundedRectangle(track, 10.0f);
        g.setColour(juce::Colours::white);
        g.fillEllipse(on ? 22.0f : 4.0f, track.getY() + 2.0f, 16.0f, 16.0f);
    }
    else
    {
        juce::Rectangle<float> square(3.0f, bounds.getCentreY() - 8.0f, 16.0f, 16.0f);
        g.setColour(on ? palette.accent : palette.surface);
        g.fillRoundedRectangle(square, palette.style == 4 ? 0.0f : 3.0f);
        g.setColour(palette.text.withAlpha(0.6f));
        g.drawRoundedRectangle(square, palette.style == 4 ? 0.0f : 3.0f, 1.0f);
        if (on)
        {
            g.setColour(juce::Colours::white);
            g.drawLine(6.0f, bounds.getCentreY(), 10.0f, bounds.getCentreY() + 4.0f, 2.0f);
            g.drawLine(10.0f, bounds.getCentreY() + 4.0f, 17.0f, bounds.getCentreY() - 5.0f, 2.0f);
        }
    }
    g.setColour(palette.text.brighter(over ? 0.1f : 0.0f));
    g.setFont(juce::Font(juce::FontOptions(palette.fontSize)));
    g.drawFittedText(button.getButtonText(), juce::Rectangle<int>(switchStyle ? 48 : 26, 0, button.getWidth() - (switchStyle ? 48 : 26), button.getHeight()),
                     juce::Justification::centredLeft, 1);
}

MainComponent::MainComponent()
{
    palettes.add({ "JUCE Classic", juce::Colour(0xffe3e3e3), juce::Colour(0xfff7f7f7), juce::Colour(0xff202020), juce::Colour(0xff507caf), 4, 0, 15 });
    palettes.add({ "JUCE Compact", juce::Colour(0xff24272b), juce::Colour(0xff34383e), juce::Colour(0xfff4f4f4), juce::Colour(0xff6facd5), 2, 1, 13 });
    palettes.add({ "JUCE Modern", juce::Colour(0xff1d222b), juce::Colour(0xff303948), juce::Colour(0xfff4f6fa), juce::Colour(0xff57b0ed), 12, 2, 16 });
    palettes.add({ "JUCE Studio", juce::Colour(0xff171b20), juce::Colour(0xff282c34), juce::Colour(0xffe4e7ed), juce::Colour(0xffe39b53), 6, 3, 15 });
    palettes.add({ "Windows Classic (inspir\u00e9)", juce::Colour(0xffd4d0c8), juce::Colour(0xffefede7), juce::Colour(0xff1d1d1d), juce::Colour(0xff2753b5), 0, 4, 14 });
    palettes.add({ "Windows 11 (inspir\u00e9)", juce::Colour(0xffebedf2), juce::Colour(0xffffffff), juce::Colour(0xff20252c), juce::Colour(0xff0067c0), 8, 5, 15 });
    palettes.add({ "macOS (inspir\u00e9)", juce::Colour(0xffeeeeef), juce::Colour(0xffffffff), juce::Colour(0xff25262a), juce::Colour(0xff007aff), 10, 6, 15 });
    palettes.add({ "GNOME Adwaita (inspir\u00e9)", juce::Colour(0xfff6f5f4), juce::Colour(0xffffffff), juce::Colour(0xff242424), juce::Colour(0xff3584e4), 9, 7, 15 });
    palettes.add({ "KDE Breeze (inspir\u00e9)", juce::Colour(0xffeff2f5), juce::Colour(0xffffffff), juce::Colour(0xff232629), juce::Colour(0xff3daee9), 5, 8, 15 });
    palettes.add({ "Custom Lab", juce::Colour(0xff262433), juce::Colour(0xff39364b), juce::Colour(0xfff2eefa), juce::Colour(0xffbb86fc), 10, 9, 16 });

    setLookAndFeel(&lookAndFeel);
    addAndMakeVisible(menuBar);
    auto label = [this](juce::Label& l, const juce::String& text)
    {
        l.setText(text, juce::dontSendNotification);
        addAndMakeVisible(l);
    };
    label(title, "JUCE UI Laboratory");
    label(description, "M\u00eame programme, plusieurs apparences et dialogues syst\u00e8me");
    label(themeLabel, "Th\u00e8me");
    label(densityLabel, "Densit\u00e9");
    label(choiceLabel, "Liste d\u00e9roulante");
    label(sliderLabel, "Curseur");
    label(status, "Pr\u00eat \u2014 aucun fichier ouvert");
    label(detail, "Comparaison des composants graphiques (UTF-8 : \u00e9 \u00e8 \u00ea \u00e7 \u0153 \u00e0)");
    for (int i = 0; i < palettes.size(); ++i) themeBox.addItem(palettes[i].name, i + 1);
    densityBox.addItemList({ "Normale", "Compacte", "Large" }, 1);
    choiceBox.addItemList({ "Option A", "Option B", "Option C" }, 1);
    for (auto* c : { &themeBox, &densityBox, &choiceBox }) { addAndMakeVisible(*c); c->addListener(this); }
    densityBox.setSelectedId(2); // Compacte par defaut (id 2)
    choiceBox.setSelectedId(1);
    for (auto* b : { &openButton, &saveButton, &contextButton, &actionButton }) { addAndMakeVisible(*b); b->addListener(this); }
    const juce::String tabNames[] = { "Composants", "Menus", "Fichiers" };
    for (int i = 0; i < 3; ++i) { tabs[i].setButtonText(tabNames[i]); tabs[i].setComponentID("lab-tab"); tabs[i].setClickingTogglesState(true); tabs[i].setRadioGroupId(1001); addAndMakeVisible(tabs[i]); tabs[i].addListener(this); }
    tabs[0].setToggleState(true, juce::dontSendNotification);
    nativeChooser.setToggleState(true, juce::dontSendNotification);
    enabledToggle.setToggleState(true, juce::dontSendNotification);
    addAndMakeVisible(nativeChooser);
    addAndMakeVisible(enabledToggle);
    slider.setRange(0, 100, 1);
    slider.setValue(50);
    slider.setSliderStyle(juce::Slider::LinearHorizontal);
    slider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 65, 24);
    addAndMakeVisible(slider);
    editor.setMultiLine(true);
    editor.setText("Texte \u00e9ditable \u2014 caract\u00e8res UTF-8 : \u00e9t\u00e9, cr\u00e9ation, fa\u00e7ade, c\u0153ur.\nEssayez de modifier le th\u00e8me puis de s\u00e9lectionner un fichier.");
    addAndMakeVisible(editor);
    setSize(1040, 680);
    openButton.setTooltip("Ouvrir un fichier - dialogue natif ou JUCE");
    saveButton.setTooltip("Choisir une destination sans ecrire de fichier");
    contextButton.setTooltip("Afficher un menu contextuel et ses sous-menus");
    actionButton.setTooltip("Declencher une action de demonstration");
    nativeChooser.setTooltip("Choisir un dialogue natif du systeme ou un dialogue JUCE");
    themeBox.setTooltip("Changer completement le style graphique du programme");
    densityBox.setTooltip("Compacte : economise l'espace ; Normale ; Large");
    slider.setTooltip("Reglage numerique avec souris ou clavier");
    themeBox.setSelectedId(3);
}
MainComponent::~MainComponent()
{
    chooser.reset();
    menuBar.setModel(nullptr);
    setLookAndFeel(nullptr);
}
juce::StringArray MainComponent::getMenuBarNames() { return { "Fichier", "\u00c9dition", "Affichage", "Outils", "Aide" }; }
juce::PopupMenu MainComponent::getMenuForIndex(int index, const juce::String&)
{
    juce::PopupMenu m;
    m.setLookAndFeel(&lookAndFeel);
    if (index == 0) { m.addItem(1, "Ouvrir\u2026"); m.addItem(2, "Enregistrer\u2026"); m.addSeparator(); m.addItem(3, "Quitter"); }
    if (index == 1) { m.addItem(4, "S\u00e9lectionner tout"); m.addItem(5, "Effacer le texte"); }
    if (index == 2)
        for (int i = 0; i < palettes.size(); ++i)
            m.addItem(100 + i, palettes[i].name, true, themeBox.getSelectedItemIndex() == i);
    if (index == 3) { m.addItem(6, "Menu contextuel"); m.addItem(7, "Choisir un dossier\u2026"); }
    if (index == 4) m.addItem(8, "\u00c0 propos du laboratoire");
    return m;
}
void MainComponent::menuItemSelected(int id, int)
{
    if (id >= 100 && id < 100 + palettes.size()) { themeBox.setSelectedId(id - 99); return; }
    if (id == 1) chooseFile(false);
    if (id == 2) chooseFile(true);
    if (id == 3) juce::JUCEApplication::getInstance()->systemRequestedQuit();
    if (id == 4) editor.selectAll();
    if (id == 5) editor.clear();
    if (id == 6) buttonClicked(&contextButton);
    if (id == 7)
    {
        chooser = std::make_unique<juce::FileChooser>("S\u00e9lectionner un dossier", juce::File{}, "*", nativeChooser.getToggleState());
        chooser->launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectDirectories,
            [safe = juce::Component::SafePointer<MainComponent>(this)](const juce::FileChooser& fc)
            {
                if (safe != nullptr && fc.getResult() != juce::File{}) safe->status.setText("Dossier : " + fc.getResult().getFullPathName(), juce::dontSendNotification);
            });
    }
    if (id == 8) juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::InfoIcon, "JUCE UI Laboratory", "D\u00e9monstrateur de th\u00e8mes JUCE multiplateforme \u2014 version 0.1.0");
}
void MainComponent::selectTheme(int index)
{
    if (! juce::isPositiveAndBelow(index, palettes.size())) return;
    current = palettes[index];
    current.fontSize = density == 1 ? 12.0f : (density == 2 ? 16.0f : 13.5f);
    lookAndFeel.setPalette(current);
    for (auto* child : { static_cast<juce::Component*>(&menuBar), static_cast<juce::Component*>(&themeBox), static_cast<juce::Component*>(&densityBox), static_cast<juce::Component*>(&choiceBox), static_cast<juce::Component*>(&editor) }) child->repaint();
    for (auto& tab : tabs) tab.repaint();
    for (auto* button : { &openButton, &saveButton, &contextButton, &actionButton })
    {
        button->setColour(juce::TextButton::textColourOffId, current.text);
        button->setColour(juce::TextButton::textColourOnId, juce::Colours::white);
        button->repaint();
    }
    for (auto& tab : tabs)
    {
        tab.setColour(juce::TextButton::textColourOffId, current.text);
        tab.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    }
    for (auto* combo : { &themeBox, &densityBox, &choiceBox })
    {
        combo->setColour(juce::ComboBox::textColourId, current.text);
        combo->setColour(juce::ComboBox::backgroundColourId, current.surface);
        combo->repaint();
    }
    slider.setColour(juce::Slider::textBoxTextColourId, current.text);
    slider.setColour(juce::Slider::textBoxBackgroundColourId, current.surface);
    slider.setColour(juce::Slider::textBoxOutlineColourId, current.text.withAlpha(0.35f));
    slider.repaint();
    editor.setColour(juce::TextEditor::textColourId, current.text);
    editor.setColour(juce::TextEditor::backgroundColourId, current.surface);
    editor.applyColourToAllText(current.text, true);
    editor.repaint();
    title.setFont(juce::Font(juce::FontOptions(current.fontSize + (density == 1 ? 6.0f : 9.0f), juce::Font::bold)));
    const float textSize = density == 1 ? 12.0f : (density == 2 ? 16.0f : 13.0f);
    description.setFont(juce::Font(juce::FontOptions(textSize)));
    for (auto* label : { &themeLabel, &densityLabel, &choiceLabel, &sliderLabel, &status, &detail })
        label->setFont(juce::Font(juce::FontOptions(textSize)));
    menuItemsChanged();
    repaint();
    updateLayout();
}
void MainComponent::comboBoxChanged(juce::ComboBox* c)
{
    if (c == &themeBox) selectTheme(themeBox.getSelectedItemIndex());
    if (c == &densityBox) { density = densityBox.getSelectedItemIndex(); selectTheme(themeBox.getSelectedItemIndex()); }
}
void MainComponent::buttonClicked(juce::Button* b)
{
    if (b == &openButton) chooseFile(false);
    else if (b == &saveButton) chooseFile(true);
    else if (b == &actionButton) status.setText("Action d\u00e9clench\u00e9e \u2014 " + current.name, juce::dontSendNotification);
    else if (b == &contextButton)
    {
        juce::PopupMenu menu;
        menu.setLookAndFeel(&lookAndFeel);
        menu.addItem(1, "Premi\u00e8re action");
        menu.addItem(2, "Deuxi\u00e8me action");
        juce::PopupMenu sub;
        sub.setLookAndFeel(&lookAndFeel);
        sub.addItem(3, "Sous-menu");
        menu.addSubMenu("Options suppl\u00e9mentaires", sub);
        menu.showMenuAsync(juce::PopupMenu::Options().withTargetComponent(contextButton).withPreferredPopupDirection(juce::PopupMenu::Options::PopupDirection::downwards),
            [safe = juce::Component::SafePointer<MainComponent>(this)](int result)
            {
                if (safe != nullptr && result > 0) safe->status.setText("Menu : action " + juce::String(result), juce::dontSendNotification);
            });
    }
    else for (int i = 0; i < 3; ++i)
        if (b == &tabs[i]) { selectedTab = i; detail.setText("Onglet : " + tabs[i].getButtonText(), juce::dontSendNotification); repaint(); }
}
void MainComponent::chooseFile(bool save)
{
    chooser = std::make_unique<juce::FileChooser>(save ? "Enregistrer un fichier" : "Ouvrir un fichier", juce::File{}, "*", nativeChooser.getToggleState());
    int chooserFlags = (save ? juce::FileBrowserComponent::saveMode : juce::FileBrowserComponent::openMode) | juce::FileBrowserComponent::canSelectFiles;
    chooser->launchAsync(chooserFlags, [safe = juce::Component::SafePointer<MainComponent>(this), save](const juce::FileChooser& fc)
    {
        if (safe != nullptr && fc.getResult() != juce::File{})
            safe->status.setText((save ? "Destination choisie (aucune \u00e9criture) : " : "Fichier choisi : ") + fc.getResult().getFullPathName(), juce::dontSendNotification);
    });
}
void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(current.background);
    const int margin = density == 1 ? 12 : density == 2 ? 24 : 16;
    auto r = getLocalBounds().reduced(margin);
    r.removeFromTop(density == 1 ? 116 : density == 2 ? 165 : 139);
    g.setColour(current.surface);
    if (current.style == 4 || current.style == 0) g.fillRect(r);
    else g.fillRoundedRectangle(r.toFloat(), static_cast<float>(current.corner));
    g.setColour(current.accent.withAlpha(0.25f));
    if (current.style == 4 || current.style == 0) g.drawRect(r, 1);
    else g.drawRoundedRectangle(r.toFloat(), static_cast<float>(current.corner), 1.0f);
}
void MainComponent::resized() { updateLayout(); }
void MainComponent::updateLayout()
{
    // All sizes are logical JUCE pixels; the underlying OS manages HiDPI scaling.
    const bool compact = density == 1;
    const bool large = density == 2;
    const int margin = compact ? 12 : (large ? 24 : 17);
    const int spacing = compact ? 5 : (large ? 15 : 9);
    const int height = compact ? 25 : (large ? 39 : 31);
    const int menuHeight = compact ? 24 : (large ? 38 : 30);
    auto area = getLocalBounds();
    menuBar.setBounds(area.removeFromTop(menuHeight));
    area.reduce(margin, compact ? 6 : 10);
    title.setBounds(area.removeFromTop(compact ? 30 : (large ? 48 : 39)));
    description.setBounds(area.removeFromTop(compact ? 21 : 27));
    auto controls = area.removeFromTop(compact ? 34 : (large ? 48 : 41));
    themeLabel.setBounds(controls.removeFromLeft(compact ? 47 : 54));
    themeBox.setBounds(controls.removeFromLeft(compact ? 225 : 268).reduced(1, compact ? 4 : 5));
    controls.removeFromLeft(spacing);
    densityLabel.setBounds(controls.removeFromLeft(compact ? 60 : 68));
    densityBox.setBounds(controls.removeFromLeft(compact ? 121 : 153).reduced(1, compact ? 4 : 5));
    controls.removeFromLeft(spacing);
    nativeChooser.setBounds(controls);
    area.removeFromTop(compact ? 10 : 22);

    if (current.style == 3 || current.style == 7)
    {
        auto sidebar = area.removeFromLeft(compact ? 130 : 167);
        for (auto& tab : tabs)
            tab.setBounds(sidebar.removeFromTop(height + spacing).reduced(2, 2));
        area.removeFromLeft(compact ? 6 : 12);
    }
    else
    {
        auto tabRow = area.removeFromTop(height + (compact ? 3 : 7));
        const int tabWidth = compact ? 112 : (current.style == 6 ? 120 : 145);
        for (auto& tab : tabs)
            tab.setBounds(tabRow.removeFromLeft(tabWidth).reduced(compact ? 1 : 3, 1));
        area.removeFromTop(compact ? 6 : spacing + 8);
    }

    auto buttons = area.removeFromTop(height);
    const int actionWidth = compact ? 131 : (current.style == 3 || current.style == 7 ? 150 : 168);
    for (auto* b : { &openButton, &saveButton, &contextButton, &actionButton })
    {
        b->setBounds(buttons.removeFromLeft(actionWidth).reduced(compact ? 2 : 4, 0));
        buttons.removeFromLeft(spacing);
    }
    area.removeFromTop(spacing + (compact ? 3 : 6));
    auto row = area.removeFromTop(height + (compact ? 3 : 9));
    choiceLabel.setBounds(row.removeFromLeft(compact ? 114 : 135));
    choiceBox.setBounds(row.removeFromLeft(compact ? 165 : 195).reduced(2, 2));
    row.removeFromLeft(spacing);
    enabledToggle.setBounds(row.removeFromLeft(190));
    area.removeFromTop(spacing);
    row = area.removeFromTop(height + (compact ? 5 : 12));
    sliderLabel.setBounds(row.removeFromLeft(compact ? 112 : 135));
    slider.setBounds(row.removeFromLeft(compact ? 375 : 430));
    area.removeFromTop(spacing);
    detail.setBounds(area.removeFromTop(compact ? 22 : 28));
    status.setBounds(area.removeFromBottom(compact ? 25 : 35));
    area.removeFromBottom(spacing);
    editor.setBounds(area.reduced(compact ? 1 : 2));
}
