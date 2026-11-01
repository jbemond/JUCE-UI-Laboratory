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
    setColour(juce::ComboBox::outlineColourId, p.accent.withAlpha(0.4f));
    setColour(juce::TextEditor::backgroundColourId, p.surface);
    setColour(juce::TextEditor::textColourId, p.text);
    setColour(juce::TextEditor::outlineColourId, p.accent.withAlpha(0.5f));
    setColour(juce::PopupMenu::backgroundColourId, p.surface);
    setColour(juce::PopupMenu::textColourId, p.text);
    setColour(juce::PopupMenu::highlightedBackgroundColourId, p.accent);
    setColour(juce::Slider::thumbColourId, p.accent);
    setColour(juce::Slider::trackColourId, p.accent.withAlpha(0.5f));
    setColour(juce::ToggleButton::textColourId, p.text);
    setColour(juce::ToggleButton::tickColourId, p.accent);
}
void MainComponent::LaboratoryLookAndFeel::drawButtonBackground(juce::Graphics& g, juce::Button& b, const juce::Colour& colour, bool over, bool down)
{
    auto r = b.getLocalBounds().toFloat().reduced(1.0f);
    auto c = b.getToggleState() ? palette.accent : colour;
    if (down) c = c.darker(0.18f);
    else if (over) c = c.brighter(0.13f);
    g.setColour(c);
    g.fillRoundedRectangle(r, static_cast<float>(palette.corner));
    g.setColour(palette.accent.withAlpha(0.25f));
    g.drawRoundedRectangle(r, static_cast<float>(palette.corner), 1.0f);
}
void MainComponent::LaboratoryLookAndFeel::drawPopupMenuBackground(juce::Graphics& g, int w, int h)
{
    g.fillAll(palette.surface);
    g.setColour(palette.accent.withAlpha(0.5f));
    g.drawRect(0, 0, w, h);
}

MainComponent::MainComponent()
{
    palettes.add({ "JUCE Classic", juce::Colour(0xffe3e3e3), juce::Colour(0xfff7f7f7), juce::Colour(0xff202020), juce::Colour(0xff507caf), 4, 15 });
    palettes.add({ "JUCE Compact", juce::Colour(0xff24272b), juce::Colour(0xff34383e), juce::Colour(0xfff4f4f4), juce::Colour(0xff6facd5), 2, 13 });
    palettes.add({ "JUCE Modern", juce::Colour(0xff1d222b), juce::Colour(0xff303948), juce::Colour(0xfff4f6fa), juce::Colour(0xff57b0ed), 12, 16 });
    palettes.add({ "JUCE Studio", juce::Colour(0xff171b20), juce::Colour(0xff282c34), juce::Colour(0xffe4e7ed), juce::Colour(0xffe39b53), 6, 15 });
    palettes.add({ "Windows Classic (inspiré)", juce::Colour(0xffd4d0c8), juce::Colour(0xffefede7), juce::Colour(0xff1d1d1d), juce::Colour(0xff2753b5), 0, 14 });
    palettes.add({ "Windows 11 (inspiré)", juce::Colour(0xffebedf2), juce::Colour(0xffffffff), juce::Colour(0xff20252c), juce::Colour(0xff0067c0), 8, 15 });
    palettes.add({ "macOS (inspiré)", juce::Colour(0xffeeeeef), juce::Colour(0xffffffff), juce::Colour(0xff25262a), juce::Colour(0xff007aff), 10, 15 });
    palettes.add({ "GNOME Adwaita (inspiré)", juce::Colour(0xfff6f5f4), juce::Colour(0xffffffff), juce::Colour(0xff242424), juce::Colour(0xff3584e4), 9, 15 });
    palettes.add({ "KDE Breeze (inspiré)", juce::Colour(0xffeff2f5), juce::Colour(0xffffffff), juce::Colour(0xff232629), juce::Colour(0xff3daee9), 5, 15 });
    palettes.add({ "Custom Lab", juce::Colour(0xff262433), juce::Colour(0xff39364b), juce::Colour(0xfff2eefa), juce::Colour(0xffbb86fc), 10, 16 });

    setLookAndFeel(&lookAndFeel);
    addAndMakeVisible(menuBar);
    auto label = [this](juce::Label& l, const juce::String& text)
    {
        l.setText(text, juce::dontSendNotification);
        addAndMakeVisible(l);
    };
    label(title, "JUCE UI Laboratory");
    label(description, "Même programme, plusieurs apparences et dialogues système");
    label(themeLabel, "Thème");
    label(densityLabel, "Densité");
    label(choiceLabel, "Liste déroulante");
    label(sliderLabel, "Curseur");
    label(status, "Prêt — aucun fichier ouvert");
    label(detail, "Comparaison des composants graphiques (UTF-8 : é è ê ç œ à)");
    for (int i = 0; i < palettes.size(); ++i) themeBox.addItem(palettes[i].name, i + 1);
    densityBox.addItemList({ "Normale", "Compacte", "Large" }, 1);
    choiceBox.addItemList({ "Option A", "Option B", "Option C" }, 1);
    for (auto* c : { &themeBox, &densityBox, &choiceBox }) { addAndMakeVisible(*c); c->addListener(this); }
    densityBox.setSelectedId(1);
    choiceBox.setSelectedId(1);
    for (auto* b : { &openButton, &saveButton, &contextButton, &actionButton }) { addAndMakeVisible(*b); b->addListener(this); }
    const juce::String tabNames[] = { "Composants", "Menus", "Fichiers" };
    for (int i = 0; i < 3; ++i) { tabs[i].setButtonText(tabNames[i]); addAndMakeVisible(tabs[i]); tabs[i].addListener(this); }
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
    editor.setText("Texte éditable — caractères UTF-8 : été, création, façade, cœur.\nEssayez de modifier le thème puis de sélectionner un fichier.");
    addAndMakeVisible(editor);
    setSize(1120, 740);
    themeBox.setSelectedId(3);
}
MainComponent::~MainComponent()
{
    chooser.reset();
    menuBar.setModel(nullptr);
    setLookAndFeel(nullptr);
}
juce::StringArray MainComponent::getMenuBarNames() { return { "Fichier", "Édition", "Affichage", "Outils", "Aide" }; }
juce::PopupMenu MainComponent::getMenuForIndex(int index, const juce::String&)
{
    juce::PopupMenu m;
    if (index == 0) { m.addItem(1, "Ouvrir…"); m.addItem(2, "Enregistrer…"); m.addSeparator(); m.addItem(3, "Quitter"); }
    if (index == 1) { m.addItem(4, "Sélectionner tout"); m.addItem(5, "Effacer le texte"); }
    if (index == 2)
        for (int i = 0; i < palettes.size(); ++i) m.addItem(100 + i, palettes[i].name, true, themeBox.getSelectedItemIndex() == i);
    if (index == 3) { m.addItem(6, "Menu contextuel"); m.addItem(7, "Choisir un dossier…"); }
    if (index == 4) m.addItem(8, "À propos du laboratoire");
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
        chooser = std::make_unique<juce::FileChooser>("Sélectionner un dossier", juce::File{}, "*", nativeChooser.getToggleState());
        chooser->launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectDirectories,
            [safe = juce::Component::SafePointer<MainComponent>(this)](const juce::FileChooser& fc)
            {
                if (safe != nullptr && fc.getResult() != juce::File{}) safe->status.setText("Dossier : " + fc.getResult().getFullPathName(), juce::dontSendNotification);
            });
    }
    if (id == 8) juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::InfoIcon, "JUCE UI Laboratory", "Démonstrateur de thèmes JUCE multiplateforme — version 0.1.0");
}
void MainComponent::selectTheme(int index)
{
    if (! juce::isPositiveAndBelow(index, palettes.size())) return;
    current = palettes[index];
    lookAndFeel.setPalette(current);
    title.setFont(juce::Font(juce::FontOptions(current.fontSize + 12.0f, juce::Font::bold)));
    description.setFont(juce::Font(juce::FontOptions(current.fontSize)));
    menuItemsChanged();
    repaint();
    updateLayout();
}
void MainComponent::comboBoxChanged(juce::ComboBox* c)
{
    if (c == &themeBox) selectTheme(themeBox.getSelectedItemIndex());
    if (c == &densityBox) { density = densityBox.getSelectedItemIndex(); updateLayout(); }
}
void MainComponent::buttonClicked(juce::Button* b)
{
    if (b == &openButton) chooseFile(false);
    else if (b == &saveButton) chooseFile(true);
    else if (b == &actionButton) status.setText("Action déclenchée — " + current.name, juce::dontSendNotification);
    else if (b == &contextButton)
    {
        juce::PopupMenu menu;
        menu.addItem(1, "Première action");
        menu.addItem(2, "Deuxième action");
        juce::PopupMenu sub;
        sub.addItem(3, "Sous-menu");
        menu.addSubMenu("Options supplémentaires", sub);
        menu.showMenuAsync(juce::PopupMenu::Options().withTargetComponent(contextButton),
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
            safe->status.setText((save ? "Destination choisie (aucune écriture) : " : "Fichier choisi : ") + fc.getResult().getFullPathName(), juce::dontSendNotification);
    });
}
void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(current.background);
    auto r = getLocalBounds().reduced(20);
    r.removeFromTop(157);
    g.setColour(current.surface);
    g.fillRoundedRectangle(r.toFloat(), static_cast<float>(current.corner));
    g.setColour(current.accent.withAlpha(0.25f));
    g.drawRoundedRectangle(r.toFloat(), static_cast<float>(current.corner), 1.0f);
}
void MainComponent::resized() { updateLayout(); }
void MainComponent::updateLayout()
{
    const int spacing = density == 1 ? 6 : density == 2 ? 17 : 11;
    const int height = density == 1 ? 27 : density == 2 ? 39 : 33;
    auto area = getLocalBounds();
    menuBar.setBounds(area.removeFromTop(29));
    area.reduce(22, 12);
    title.setBounds(area.removeFromTop(46));
    description.setBounds(area.removeFromTop(31));
    auto controls = area.removeFromTop(48);
    themeLabel.setBounds(controls.removeFromLeft(52));
    themeBox.setBounds(controls.removeFromLeft(275).reduced(2, 5));
    controls.removeFromLeft(14);
    densityLabel.setBounds(controls.removeFromLeft(67));
    densityBox.setBounds(controls.removeFromLeft(150).reduced(2, 5));
    controls.removeFromLeft(18);
    nativeChooser.setBounds(controls);
    area.removeFromTop(24);
    auto tabRow = area.removeFromTop(height + 7);
    for (auto& tab : tabs) { tab.setBounds(tabRow.removeFromLeft(145).reduced(3, 2)); }
    area.removeFromTop(spacing + 8);
    auto buttons = area.removeFromTop(height);
    for (auto* b : { &openButton, &saveButton, &contextButton, &actionButton })
    {
        b->setBounds(buttons.removeFromLeft(168).reduced(4, 0));
        buttons.removeFromLeft(spacing);
    }
    area.removeFromTop(spacing + 6);
    auto row = area.removeFromTop(height + 9);
    choiceLabel.setBounds(row.removeFromLeft(135));
    choiceBox.setBounds(row.removeFromLeft(195).reduced(3, 3));
    row.removeFromLeft(15);
    enabledToggle.setBounds(row.removeFromLeft(190));
    area.removeFromTop(spacing);
    row = area.removeFromTop(height + 12);
    sliderLabel.setBounds(row.removeFromLeft(135));
    slider.setBounds(row.removeFromLeft(430));
    area.removeFromTop(spacing);
    detail.setBounds(area.removeFromTop(28));
    status.setBounds(area.removeFromBottom(35));
    area.removeFromBottom(spacing);
    editor.setBounds(area.reduced(2));
}
