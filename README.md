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

## Habillages (mise à jour expérimentale)

Les profils ne changent plus seulement les couleurs : les boutons (reliefs, ombres, formes), cases à cocher/interrupteurs, listes déroulantes, onglets, barres de menus et menus contextuels possèdent des modes de dessin distincts. La hauteur des menus, les espacements, les séparateurs, les coches et les états survolés varient également selon le style. **Ces adaptations restent des rendus JUCE et non des widgets natifs Win32, Cocoa ou GTK/Qt.** Cette évolution doit encore être compilée et contrôlée visuellement sur Windows, macOS et Linux.

### Contrôles et mises en page (correctifs de novembre 2026)

- Les libellés Unicode C++ (accents et typographie française) utilisent désormais des séquences universelles `\\uXXXX` dans les chaînes sources pour éviter toute dépendance au codepage MSVC ; le compilateur reste configuré avec `/utf-8`.
- Le champ numérique du curseur définit explicitement sa couleur de texte et son arrière-plan pour chaque palette, y compris les thèmes clairs.
- **JUCE Studio et GNOME** utilisent une navigation latérale à la place des trois onglets horizontaux. Les autres thèmes conservent une navigation haute, avec des dimensions différentes.
- L'habillage reste JUCE (imitation visuelle) : le véritable menu système Win32/macOS/GTK ou Qt n'est pas encore intégré.

Ces changements doivent être compilés et contrôlés à l'écran sur chaque OS.
