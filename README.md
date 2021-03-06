# Le jeu de la vie

## Description
Le jeu de la vie est un automate cellulaire bidimensionnel où chaque cellule peut prendre deux valeurs (« 0 » ou « 1 », mais on parle plutôt de « vivante » ou « morte ») et où son état futur est déterminé par son état actuel et par le nombre de cellules vivantes parmi les huit qui l'entourent :

- Si la cellule est vivante et entourée par **2** ou **3** cellules vivantes, elle reste en vie à la génération suivante, sinon elle meurt.
- Si la cellule est morte et entourée par exactement **3** cellules vivantes, elle naît à la génération suivante.

## Fonctionnalités
- [x] Augmenter/Réduire le framerate (NumPad+/NumPad-)
- [x] Mettre en pause (Espace)
- [x] Placer/Supprimer une cellule, quand le jeu est en pause (Clic Droit)
- [x] Supprimer toutes les cellules, quand le jeu est en pause (F)

## Installation
Ce projet nécessite [SFML 2.5.1](https://www.sfml-dev.org/download/sfml/2.5.1/index-fr.php) pour pouvoir être compilé à nouveau.
