#include "chifoumi.h"
#include <cstdlib>
#include <ctime>

        ///* ---- PARTIE MODèLE ---------------------------

    Chifoumi::Chifoumi()
    {
        //ctor
        // partie modèle
        (*this).coupJoueur=rien;
        (*this).coupMachine=rien;
        (*this).scoreJoueur=0;
        (*this).scoreMachine=0;
    }

    Chifoumi::~Chifoumi()
    {
        //dtor
    }

            /// Getters

    Chifoumi::UnCoup Chifoumi::getCoupJoueur()
    {
        return (*this).coupJoueur;
    }

    Chifoumi::UnCoup Chifoumi::getCoupMachine()
    {
        return (*this).coupMachine;
    }

    unsigned int Chifoumi::getScoreJoueur()
    {
        return (*this).scoreJoueur;
    }

    unsigned int Chifoumi::getScoreMachine()
    {
        return (*this).scoreMachine;
    }

    char Chifoumi::determinerGagnant()
    {
        char gagnantARetourner;

        // avant de commencer : match nul
        gagnantARetourner='N';

        // il sera modifié dans l'un des cas suivants
        if((*this).coupJoueur==pierre)
        {
            if ((*this).coupMachine==ciseau)
            {
                gagnantARetourner='J';
            }
            else if ((*this).coupMachine==papier)
            {
                gagnantARetourner='M';
            }
        }
        else if((*this).coupJoueur==ciseau)
        {
            if ((*this).coupMachine==pierre)
            {
                gagnantARetourner='M';
            }
            else if ((*this).coupMachine==papier)
            {
                gagnantARetourner='J';
            }
        }
        else if((*this).coupJoueur==papier)
        {
            if ((*this).coupMachine==ciseau)
            {
                gagnantARetourner='M';
            }
            else if ((*this).coupMachine==pierre)
            {
                gagnantARetourner='J';
            }
        }

        return gagnantARetourner;


    }


             ///* Méthodes utilitaires du Modèle

    int randMinMax(int min, int max){
        /* pré-condition : min<max ;
           Le nbre aléatoire est compris entre [min, max[ */
       return rand()%(max-min) + min;
    }

    Chifoumi::UnCoup Chifoumi::genererUnCoup()
    {
            UnCoup valeurGeneree;   // valeur à retourner
            int valeurAleatoire;

            valeurAleatoire=randMinMax(1,4);
            switch (valeurAleatoire)
            {
            case 1:
                valeurGeneree = pierre;
                break;

            case 2:
                valeurGeneree = papier;
                break;

            case 3:
                valeurGeneree = ciseau;
                break;
            }
            return valeurGeneree;

    }

            /// Setters

    void Chifoumi::setCoupJoueur(UnCoup p_coup)
    {
        (*this).coupJoueur=p_coup;
    }

    void Chifoumi::setCoupMachine(UnCoup p_coup)
    {
        (*this).coupMachine=p_coup;
    }

    void Chifoumi::setScoreJoueur(unsigned int p_score)
    {
        (*this).scoreJoueur=p_score;
    }

    void Chifoumi::setScoreMachine(unsigned int p_score)
    {
        (*this).scoreMachine=p_score;
    }

    void Chifoumi::majScores(char p_gagnant)
    {
        if (p_gagnant=='J')
        {
            (*this).scoreJoueur+=1;
        }
        if (p_gagnant=='M')
        {
            (*this).scoreMachine+=1;
        }

    }

    void Chifoumi::initScores()
    {
        (*this).scoreJoueur=0;
        (*this).scoreMachine=0;
    }

    void Chifoumi::initCoups()
    {
        (*this).coupJoueur=rien;
        (*this).coupMachine=rien;
    }
