# Roadmap

- v0.1 : application JUCE, dix thèmes, densités, menus, onglets et sélecteurs de fichiers.
- v0.2 : éditeur de thèmes, palettes JSON, sauvegarde des préférences, comparateur côte à côte.
- v0.3 : menus réellement natifs lorsque possible, adaptateurs Win32/Cocoa et portails Linux, tests HiDPI et d'accessibilité.
- v0.4 : galerie complète de composants, aperçu waveform/spectrogramme et captures d'écran automatisées.

Les fonctionnalités postérieures à v0.1 ne sont pas implémentées.

## Contraintes de densité (référence : ruban compact de l'Explorateur Windows)

- **Compacte est le réglage par défaut**, sans imposer de grosses commandes.
- Polices : 12 pt logiques en compact, environ 13,5 en normal, 16 en agrandi ; titre proportionné.
- Hauteur des commandes : 25/31/39 pixels logiques ; barre de menus : 24/30/38 pixels.
- Marges extérieures : 12/17/24 pixels ; espacement inter-commandes : 5/9/15 pixels.
- Infobulles : délai d'une seconde sur les principales commandes.
- Architecture future du ruban : groupes densifiés, grand/petit bouton, boutons à flèche, textes facultatifs, ruban repliable, barre d'accès rapide et disposition utilisateur persistante.
- Les paramètres de densité sont indépendants du choix de la palette visuelle ; les valeurs sont des pixels JUCE logiques et non des pixels physiques.

**Validation à réaliser :** compilation Windows/macOS/Linux, contrôle à 100 %, 125 %, 150 % HiDPI ; vérification des libellés et de l'absence de chevauchement en tailles de fenêtres réduites.

## Charte de menus compacte (novembre 2026)

- Une seule police et une seule hauteur de référence pour barre de menus et menus déroulants ; popup calculée sur la largeur du texte + marges serrées.
- Même `LaboratoryLookAndFeel` appliqué explicitement aux menus de la barre principale, menus contextuels et sous-menus.
- Les menus déclenchés par les boutons préfèrent **descendre** sous leur contrôle. JUCE peut les repositionner si l'espace écran est insuffisant. Les sous-menus en cascade s'ouvrent latéralement selon l'espace disponible.
- Ne pas conserver une large réserve de gauche lorsqu'il n'y a ni coche ni icône, ni de réserve droite en l'absence de raccourci ou sous-menu.
- UTF-8 : les chaînes accentuées dans les sources C++ utilisent des échappements Unicode, y compris les libellés initialisés dans l'en-tête.
- Validation en attente sur Windows avec VS 2026/JUCE 8.0.9, puis macOS et Linux.
