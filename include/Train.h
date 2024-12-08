#ifndef TRAIN_H
#define TRAIN_H

#include <string>
#include <vector>
#include <iostream>

class Train {
private:
    int numeroTrain;
    std::string villeDepart;
    std::string villeArrivee;
    std::string horaireDepart;
    std::string horaireArrivee;
    int capacite;
    int placesLibres;

public:
    Train(int numero, const std::string& depart, const std::string& arrivee, const std::string& horaireDep, const std::string& horaireArr, int capaciteTotal);

    bool verifierDisponibilite() const;
    bool reserverPlace();
    bool annulerReservation();
    void afficherInfosTrain() const;

    // Getters
    int getNumeroTrain() const;
    const std::string& getVilleDepart() const;
    const std::string& getVilleArrivee() const;
    const std::string& getHoraireDepart() const;
    const std::string& getHoraireArrivee() const;
    int getPlacesLibres() const;
    int getCapacite() const;

    // Gestion des fichiers
    static std::vector<Train> chargerTrains(const std::string& fichier);
    static void sauvegarderTrains(const std::vector<Train>& trains, const std::string& fichier);
};

#endif
