#ifndef BILLET_H
#define BILLET_H

#include <string>
#include <vector>

class Billet {
private:
    int numeroBillet;
    std::string typeClasse;
    float prix;
    int numeroTrain;
    std::string dateVoyage;
    std::string villeDepart;
    std::string villeArrivee;

public:
    // Constructeur
    Billet(int numero, const std::string& classe, float prixBillet, int train, const std::string& date,
           const std::string& depart = "", const std::string& arrivee = "");

    // Méthodes principales
    void afficherDetailsBillet() const;

    // Getters
    int getNumeroBillet() const;
    const std::string& getTypeClasse() const;
    float getPrix() const;
    int getNumeroTrain() const;
    const std::string& getDateVoyage() const;
    const std::string& getVilleDepart() const;
    const std::string& getVilleArrivee() const;

    // Gestion des fichiers
    static std::vector<Billet> chargerBillets(const std::string& fichier);
    static void sauvegarderBillets(const std::vector<Billet>& billets, const std::string& fichier);
};

#endif
