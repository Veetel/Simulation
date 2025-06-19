## 📁 Contenu du dépôt

### 1. **Simulation Physique (Java)**
> 📂 Fichiers principaux : `Map.java`, `Rabbit.java`, `Time.java`, `Coordonates.java`, `MTRandom.java`, `Cezeaux.java`

Ce projet simule des entités (notamment des lapins 🐇) évoluant dans un environnement à l’aide de coordonnées et de règles temporelles. Il comprend :

- Une carte dynamique (`Map`) avec entités mobiles.
- Une gestion du temps (`Time`) pour piloter les événements.
- Des entités autonomes (`Rabbit`) avec position et comportement.
- Un générateur pseudo-aléatoire pour l’environnement (`MTRandom`).

📌 Objectif : Simuler un comportement animal ou naturel dans un environnement discret.

---

### 2. **TP Monte Carlo – Volume de sphère (C)**
> 📂 Fichier principal : `tp3-1.c`

Simulation statistique par la méthode de Monte Carlo pour approximer le volume d’une sphère unité.

Fonctionnalités :
- Génération de points dans un cube [0,1]^3
- Évaluation du volume par probabilité d’inclusion
- Estimation de l'erreur relative et de l’intervalle de confiance (Student)

🧪 Méthodes statistiques employées :
- Loi uniforme
- Erreur relative
- Estimateur sans biais
- Méthode de Monte Carlo

📌 Objectif : Évaluer la convergence statistique de l’estimation du volume.

---

### 3. **TP Distribution & Génération aléatoire (C)**
> 📂 Fichier principal : `mt19937ar.c`

Ce projet exploite le générateur Mersenne Twister pour simuler diverses lois de probabilité et leurs effets.

Fonctionnalités :
- Génération de :
  - Lois uniformes
  - Lois exponentielles négatives
  - Lois normales (via méthode de Box-Muller)
- Création de distributions tabulées
- Moyenne de jets de dés, histogrammes

📌 Objectif : Visualiser le comportement des lois aléatoires simulées avec Mersenne Twister.

---
