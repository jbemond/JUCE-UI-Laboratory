# JUCE UI Laboratory

Laboratoire JUCE multithème pour Windows, macOS et Linux.

## Compilation

CMake 3.22+, C++17 et Git requis ; JUCE 8.0.9 est téléchargé automatiquement lors de la configuration.

```sh
cmake -S . -B build
cmake --build build --config Release
```

Dix thèmes : JUCE Classic, Compact, Modern, Studio, Windows Classic, Windows 11, macOS, GNOME, KDE et Custom Lab. Les styles système sont des **imitations JUCE**, pas des widgets Win32/Cocoa/GTK/Qt réels. Le choix du dialogue natif est disponible via `FileChooser` lorsque supporté. Le bouton Enregistrer ne modifie pas de fichier.

Version initiale non encore compilée sur les trois OS ; validation nécessaire.
