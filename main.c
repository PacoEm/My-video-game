#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <fmodex/fmod.h>

#define HAUTEUR_FENETRE 1080
#define LARGEUR_FENETRE 1920
#define LARGEUR_MUR 40
#define NBR_ABS 41
#define NBR_ORD 25
#define DELAI 1
#define TEST_RIGHT 1
#define TEST_LEFT 2
#define TEST_UP 3
#define TEST_DOWN 4
#define FEMME_GAUCHE 560
#define FEMME_DROITE 1200
#define RAT_GAUCHE 560
#define RAT_DROITE 1160

int main ( int argc, char** argv )
{
FMOD_SYSTEM *system;
FMOD_System_Create(&system);
FMOD_System_Init(system, 2, FMOD_INIT_NORMAL, NULL);
FMOD_SOUND *bruit_clef = NULL;
FMOD_System_CreateSound(system, "sons/vibraslap.wav", FMOD_CREATESAMPLE, 0, &bruit_clef);

FMOD_SYSTEM *system1;
FMOD_System_Create(&system1);
FMOD_System_Init(system1, 2, FMOD_INIT_NORMAL, NULL);
FMOD_SOUND *perte = NULL;
FMOD_System_CreateSound(system1, "sons/coup.wav", FMOD_CREATESAMPLE, 0, &perte);

FMOD_SYSTEM *system2;
FMOD_System_Create(&system2);
FMOD_System_Init(system2, 2, FMOD_INIT_NORMAL, NULL);
FMOD_SOUND *porte_ouverte = NULL;
FMOD_System_CreateSound(system2, "sons/grincement.wav", FMOD_CREATESAMPLE, 0, &porte_ouverte);

FMOD_SYSTEM *system3;
FMOD_System_Create(&system3);
FMOD_System_Init(system3, 2, FMOD_INIT_NORMAL, NULL);
FMOD_SOUND *victoire = NULL;
FMOD_System_CreateSound(system3, "sons/victoire.wav", FMOD_CREATESAMPLE, 0, &victoire);

    SDL_Surface *ecran = NULL, *fond = NULL, *mur = NULL, *echelle = NULL, *compteur = NULL, *clef = NULL, *porte = NULL, *menu = NULL;
    SDL_Surface *clefRose = NULL, *clefBleue = NULL, *clefVerte = NULL, *clefJaune = NULL, *clefRouge = NULL;

    // perso vers la gauche xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    SDL_Surface *pL0 = SDL_LoadBMP("sprites/persoL0.bmp");
    SDL_Surface *pL1 = SDL_LoadBMP("sprites/persoL1.bmp");
    SDL_Surface *pL2 = SDL_LoadBMP("sprites/persoL2.bmp");
    SDL_Surface *pL3 = SDL_LoadBMP("sprites/persoL3.bmp");
    SDL_Surface *pL4 = SDL_LoadBMP("sprites/persoL4.bmp");
    SDL_Surface *pL5 = SDL_LoadBMP("sprites/persoL5.bmp");
    SDL_Surface *pL6 = SDL_LoadBMP("sprites/persoL6.bmp");
    SDL_Surface *pL7 = SDL_LoadBMP("sprites/persoL7.bmp");
    SDL_Surface *pL8 = SDL_LoadBMP("sprites/persoL8.bmp");
    // perso vers la droite xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    SDL_Surface *pR0 = SDL_LoadBMP("sprites/persoR0.bmp");
    SDL_Surface *pR1 = SDL_LoadBMP("sprites/persoR1.bmp");
    SDL_Surface *pR2 = SDL_LoadBMP("sprites/persoR2.bmp");
    SDL_Surface *pR3 = SDL_LoadBMP("sprites/persoR3.bmp");
    SDL_Surface *pR4 = SDL_LoadBMP("sprites/persoR4.bmp");
    SDL_Surface *pR5 = SDL_LoadBMP("sprites/persoR5.bmp");
    SDL_Surface *pR6 = SDL_LoadBMP("sprites/persoR6.bmp");
    SDL_Surface *pR7 = SDL_LoadBMP("sprites/persoR7.bmp");
    SDL_Surface *pR8 = SDL_LoadBMP("sprites/persoR8.bmp");

    // cube rouge vers la droite xxxxxxxxxxxxxxxxxxxxxxxx
    SDL_Surface *rR0 = SDL_LoadBMP("sprites/rR0.bmp");
    SDL_Surface *rR1 = SDL_LoadBMP("sprites/rR1.bmp");
    // cube rouge vers la gauche xxxxxxxxxxxxxxxxxxxxxxxx
    SDL_Surface *rL0 = SDL_LoadBMP("sprites/rL0.bmp");
    SDL_Surface *rL1 = SDL_LoadBMP("sprites/rL1.bmp");

    // cube vert vers la droite xxxxxxxxxxxxxxxxxxxxxxxxx
    SDL_Surface *vR0 = SDL_LoadBMP("sprites/vR0.bmp");
    SDL_Surface *vR1 = SDL_LoadBMP("sprites/vR1.bmp");
    // cube vert vers la gauche xxxxxxxxxxxxxxxxxxxxxxxxx
    SDL_Surface *vL0 = SDL_LoadBMP("sprites/vL0.bmp");
    SDL_Surface *vL1 = SDL_LoadBMP("sprites/vL1.bmp");

    // les clefs xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    clefRose = SDL_LoadBMP("sprites/clef_rose.bmp");
    clefBleue = SDL_LoadBMP("sprites/clef_bleue.bmp");
    clefVerte = SDL_LoadBMP("sprites/clef_verte.bmp");
    clefJaune = SDL_LoadBMP("sprites/clef_jaune.bmp");
    clefRouge = SDL_LoadBMP("sprites/clef_rouge.bmp");

    porte = SDL_LoadBMP("sprites/porte.bmp");

    // tableau pour les sprites du perso principal xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    SDL_Surface *tabPerso[2][18] =
    {{pR0, pR1, pR2, pR3, pR4, pR5, pR6, pR7, pR8},
     {pL0, pL1, pL2, pL3, pL4, pL5, pL6, pL7, pL8}};

    // tableau pour les sprites du cube vert xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    SDL_Surface *tabFemme[2][4] =
    {{vR0, vR1},
     {vL0, vL1}};

    // tableau pour les sprites du rat xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    SDL_Surface *tabRat[2][4] =
    {{rR0, rR1},
     {rL0, rL1}};

    // tableau pour les deux positions du levier xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    SDL_Surface *tabLevier[2] ={SDL_LoadBMP("sprites/levier_haut.bmp"), SDL_LoadBMP("sprites/levier_bas.bmp")};

    // tableau pour les deux positions du compteur xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    SDL_Surface *tabCompteur[2] ={SDL_LoadBMP("sprites/compteur_off.bmp"), SDL_LoadBMP("sprites/compteur_on.bmp")};

    fond = SDL_LoadBMP("sprites/fond.bmp");
    clef = SDL_LoadBMP("sprites/clef.bmp");
    menu = SDL_LoadBMP("sprites/menu.bmp");

    SDL_Rect positionFond, positionPerso, positionFemme, positionRat, positionMur, positionEchelle, positionPorte;
    SDL_Rect posClefRose, posClefBleue, posClefVerte, posClefJaune, posClefRouge;
    SDL_Rect positionClef, positionCompteur, positionLevier;
    SDL_Rect positionMenu;
    SDL_Event event;

    positionMenu.x = 0;
    positionMenu.y = 0;

    int i = 0, j = 0; // j: les ordonnées pour la position des murs / i = les absices
    int m = 0, l = 0; // l; les ordonnées pour tabPerso / m: les absices
    int oF = 0, aF = 0; // oF: ordonnées pour tabFemme / aF: les absices
    int oR = 0, aR = 0; // oR: ordonnées pour tabRat / aR: les absices
    int pC = 0; // pC pour position Compteur: 0 s'il est éteint, 1 s'il est allumé
    int pL = 0; // pL pour position Levier: 0 s'il est éteint, 1 s'il est allumé
    int actionClefRose = 0, actionClefBleue = 0, actionClefVerte = 0, actionClefJaune = 0, actionClefRouge = 0;
    int collision = 0, effetsCollision = 0, partieGagnee = 0;

    int boucle = 1, afficherMenu = 1, retourMenu = 1, jouer = 1;
    int testCollision = 0;
    int plusQuarante = 0; // pour l'initialisation de tableauPositions

    int moveLeft = 0, moveRight = 0, moveUp = 0, moveDown = 0, action = 0;

    int niveau[NBR_ORD][NBR_ABS] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 2, 0, 0, 0, 4, 0, 0, 0, 0, 1, 0, 4, 0, 0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 1, 0, 4, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3, 0, 1, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 2, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0}};

    int tableauPositions[NBR_ABS] = {0};

    // initialisation de tableauPositions à +40 pour chaque item
    for(i = 0; i < NBR_ABS; i++)
    {
        tableauPositions[i] = plusQuarante;
        plusQuarante += 40;
    }

    // ----------------------------------------------------

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_NOFRAME | SDL_FULLSCREEN | SDL_DOUBLEBUF);

    SDL_SetColorKey(clefRose, SDL_SRCCOLORKEY, SDL_MapRGB(clefRose -> format, 0, 0, 0));
    SDL_SetColorKey(clefBleue, SDL_SRCCOLORKEY, SDL_MapRGB(clefBleue -> format, 0, 0, 0));
    SDL_SetColorKey(clefVerte, SDL_SRCCOLORKEY, SDL_MapRGB(clefVerte -> format, 0, 0, 0));
    SDL_SetColorKey(clefJaune, SDL_SRCCOLORKEY, SDL_MapRGB(clefJaune -> format, 0, 0, 0));
    SDL_SetColorKey(clefRouge, SDL_SRCCOLORKEY, SDL_MapRGB(clefRouge -> format, 0, 0, 0));

    // positions sprites xxxxxxxxxxxxx

    positionFond.x = 0;
    positionFond.y = 0;

    positionPerso.x = 840;
    positionPerso.y = 320;

    positionFemme.x = 1000;
    positionFemme.y = 920;

    positionRat.x = 840;
    positionRat.y = 520;


    posClefRose.x = 560;
    posClefRose.y = 710;

    posClefBleue.x = 1400;
    posClefBleue.y = 710;

    posClefVerte.x = 1400;
    posClefVerte.y = 310;

    posClefJaune.x = 560;
    posClefJaune.y = 510;

    posClefRouge.x = 560;
    posClefRouge.y = 910;

    positionPorte.x = 2000;
    positionPorte.y = 2000;

    niveau[23][36] = 1;


    SDL_EnableKeyRepeat(10,10);

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    while(boucle)
    {
        FMOD_SYSTEM *system4;
        FMOD_System_Create(&system4);
        FMOD_System_Init(system4, 2, FMOD_INIT_NORMAL, NULL);
        FMOD_SOUND *musique = NULL;
        FMOD_System_CreateSound(system4, "sons/musique_intro.wav", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);

        FMOD_CHANNELGROUP *channel;
        FMOD_System_GetMasterChannelGroup(system4, &channel);

        FMOD_Sound_SetLoopCount(musique, -1);

            positionPerso.x = 840;
            positionPerso.y = 320;

            positionFemme.x = 1000;
            positionFemme.y = 920;

            positionRat.x = 840;
            positionRat.y = 520;

            posClefRose.x = 560;
            posClefRose.y = 710;

            posClefBleue.x = 1400;
            posClefBleue.y = 710;

            posClefVerte.x = 1400;
            posClefVerte.y = 310;

            posClefJaune.x = 600;
            posClefJaune.y = 510;

            posClefRouge.x = 560;
            posClefRouge.y = 910;

            actionClefRose = 0;
            actionClefBleue = 0;
            actionClefVerte = 0;
            actionClefJaune = 0;
            actionClefRouge = 0;

            positionPorte.x = 2000;
            positionPorte.y = 2000;

        while(afficherMenu)
        {
            SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
            SDL_Flip(ecran);


            SDL_PollEvent(&event);

            switch(event.type)
                {
                    case SDL_KEYDOWN:

                        switch(event.key.keysym.sym)
                        {
                        case SDLK_SPACE:
                            afficherMenu = 0;
                            jouer = 1;
                            break;

                        case SDLK_ESCAPE:
                            afficherMenu = 0;
                            jouer = 0;
                            boucle = 0;
                            break;
                        }
                        break;
                }

        }

        if(jouer)
        {

            FMOD_System_PlaySound(system4, FMOD_CHANNEL_FREE, musique, 0, NULL);
        }


        while(jouer)
        {
            SDL_PollEvent(&event);

            switch(event.type)
                {
                    case SDL_KEYDOWN:

                        switch(event.key.keysym.sym)
                        {

                        case SDLK_r:
                            jouer = 0;
                            afficherMenu = 1;
                            FMOD_Sound_Release(musique);
                            break;

                        case SDLK_RIGHT:
                            testCollision = TEST_RIGHT;
                            break;

                        case SDLK_LEFT:
                            testCollision = TEST_LEFT;
                            break;

                        case SDLK_UP:
                            testCollision = TEST_UP;
                            break;

                        case SDLK_DOWN:
                            testCollision = TEST_DOWN;
                            break;
                        }
                        break;
                }



            if(testCollision == TEST_RIGHT)
            {
                for(j = 0; j < NBR_ORD; j++)
                {
                    for(i = 0; i < NBR_ABS; i++)
                    {
                        positionMur.x = tableauPositions[i];
                        positionMur.y = tableauPositions[j];

                        if((positionPerso.x + LARGEUR_MUR == positionMur.x) && (positionPerso.y + LARGEUR_MUR > positionMur.y) &&
                           (positionPerso.y < positionMur.y + LARGEUR_MUR) && niveau[j][i] == 1)
                        {
                            positionPerso.x--;
                        }
                        else if((positionPerso.x == positionMur.x) && (positionPerso.y + LARGEUR_MUR > positionMur.y) &&
                           (positionPerso.y < positionMur.y + LARGEUR_MUR) && niveau[j][i] == 2)
                        {
                            positionPerso.x --;
                        }
                        else
                        {
                            moveRight = 1;
                        }
                    }
                }
            }

            else if(testCollision == TEST_LEFT)
            {
                for(j = 0; j < NBR_ORD; j++)
                {
                    for(i = 0; i < NBR_ABS; i++)
                    {
                        positionMur.x = tableauPositions[i];
                        positionMur.y = tableauPositions[j];

                        if((positionPerso.x == positionMur.x + LARGEUR_MUR) && (positionPerso.y + LARGEUR_MUR > positionMur.y) &&
                           (positionPerso.y < positionMur.y + LARGEUR_MUR) && niveau[j][i] == 1)
                        {
                            positionPerso.x ++;
                        }
                        else if((positionPerso.x == positionMur.x) && (positionPerso.y + LARGEUR_MUR > positionMur.y) &&
                           (positionPerso.y < positionMur.y + LARGEUR_MUR) && niveau[j][i] == 2)
                        {
                            positionPerso.x ++;
                        }
                        else
                        {
                            moveLeft = 1;
                        }
                    }
                }
            }

            else if(testCollision == TEST_UP)
            {
                for(j = 0; j < NBR_ORD; j++)
                {
                    for(i = 0; i < NBR_ABS; i++)
                    {
                        positionMur.x = tableauPositions[i];
                        positionMur.y = tableauPositions[j];

                        if((positionPerso.x + LARGEUR_MUR > positionMur.x) && (positionPerso.x < positionMur.x + LARGEUR_MUR)
                           && (positionPerso.y == positionMur.y + LARGEUR_MUR) && niveau[j][i] == 4)
                        {
                            positionPerso.y++;
                        }
                        else if(niveau[j][i] == 2  && (positionPerso.x + LARGEUR_MUR > positionMur.x) && (positionPerso.x < positionMur.x + LARGEUR_MUR)) // descendre echelle
                        {
                            positionPerso.x = tableauPositions[i];
                            moveUp = 1;
                        }
                    }
                }
            }

            else if(testCollision == TEST_DOWN)
            {
                for(j = 0; j < NBR_ORD; j++)
                {
                    for(i = 0; i < NBR_ABS; i++)
                    {
                        positionMur.x = tableauPositions[i];
                        positionMur.y = tableauPositions[j];

                        if(niveau[j][i] == 1 && (positionPerso.x + LARGEUR_MUR > positionMur.x) && (positionPerso.x < positionMur.x + LARGEUR_MUR) && (positionPerso.y == positionMur.y - LARGEUR_MUR))
                        {
                            positionPerso.y--;
                        }
                        else if(niveau[j][i] == 2 &&(positionPerso.x + LARGEUR_MUR > positionMur.x) && (positionPerso.x < positionMur.x + LARGEUR_MUR)) // descendre echelle
                        {
                            positionPerso.x = tableauPositions[i];
                        }
                        else
                        {
                            moveDown = 1;
                        }
                    }
                }
            }


            if(moveLeft == 1)
            {
                positionPerso.x --;
                l = 1;
                m++;


                // collision avec rat en marchant vers la droite xxxxxxxxxxxxxxxxxxxx
                if(positionPerso.y == 520 && positionPerso.x == positionRat.x + 40)
                {
                    collision = 1;
                }//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

                // collision avec femme en marchant vers la gauche xxxxxxxxxxxxxxxxxx
                if(positionPerso.y == 920 && positionPerso.x == positionFemme.x + 40)
                {
                    collision = 1;
                }//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

                if(m > 8)
                {
                    m = 0;
                }

            }

            if(moveRight == 1)
            {

                positionPerso.x ++;
                l = 0;
                m++;

                if(m > 8)
                {
                    m = 0;
                }
            }
            else if(moveRight == 0 && moveLeft == 0)
            {
                m = 0;
            }

            if(moveUp == 1)
            {
                positionPerso.y --;
            }
            if(moveDown == 1)
            {
                positionPerso.y++;
            }

            // déplacement femme en boucle xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
            if(positionFemme.x > FEMME_GAUCHE && positionFemme.x < FEMME_DROITE)
            {
                if(oF == 0)
                {
                    positionFemme.x ++;
                    aF++;

                    if(aF > 1)
                    {
                        aF = 0;
                    }
                }
                if(positionFemme.x == FEMME_DROITE)
                {
                    oF = 1;
                }
                if(oF == 1)
                {
                    if(positionFemme.x > FEMME_GAUCHE)
                    {
                        positionFemme.x --;
                        aF ++;

                        if(aF > 1)
                        {
                            aF = 0;
                        }
                        if(positionFemme.x == FEMME_GAUCHE)
                        {
                            oF = 0;
                            positionFemme.x ++;
                        }
                    }
                }
            }//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

            // déplacement Rat en boucle xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
            if(positionRat.x > RAT_GAUCHE && positionRat.x < RAT_DROITE)
            {
                if(oR == 0)
                {
                    positionRat.x ++;
                    aR++;

                    if(aR > 1)
                    {
                        aR = 0;
                    }
                }
                if(positionRat.x == RAT_DROITE)
                {
                    oR = 1;
                }
                if(oR == 1)
                {
                    if(positionRat.x > RAT_GAUCHE)
                    {
                        positionRat.x --;
                        aR ++;

                        if(aR > 1)
                        {
                            aR = 0;
                        }
                        if(positionRat.x == RAT_GAUCHE)
                        {
                            oR = 0;
                            positionRat.x ++;
                        }
                    }
                }
            }

            // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
            // gestion des collisions xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
            // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

            // collision avec cube rouge xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
            if((positionPerso.y > 480 && positionPerso.y < 560) && (positionPerso.x == positionRat.x + 40) || // collision perso statique + cube rouge droite ou gauche
                (positionPerso.y > 480 && positionPerso.y < 560) && (positionPerso.x == positionRat.x - 40))
            {
                collision = 1;
            }
            if((moveRight == 1 && positionPerso.y == 520) && // collision perso en mouvement vers la droite + cube rouge
               (positionPerso.x + 40 == positionRat.x || positionPerso.x + 39 == positionRat.x))
            {
               collision = 1;
            }
            if((moveLeft == 1 && positionPerso.y == 520) && // collision perso en mouvement vers la gauche + cube rouge
               (positionPerso.x  == positionRat.x + 40 || positionPerso.x == positionRat.x + 39))
            {
               collision = 1;
            }
            if(moveDown == 1 && positionPerso.y == positionRat.y - 40 &&  // collision perso vers le bas + cube rouge
               (positionPerso.x + 40 > positionRat.x && positionPerso.x < positionRat.x + 40))
            {
                collision = 1;
            }
            if(moveUp == 1 && positionPerso.y == positionRat.y + 40 &&  // collision perso vers le haut + cube rouge
               (positionPerso.x + 40 > positionRat.x && positionPerso.x < positionRat.x + 40))
            {
                collision = 1;
            }

            // collision avec cube vert xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
            if((positionPerso.y > 880 && positionPerso.y < 960) && (positionPerso.x == positionFemme.x + 40) || // collision perso statique + cube vert droite ou gauche
                (positionPerso.y > 880 && positionPerso.y < 960) && (positionPerso.x == positionFemme.x - 40))
            {
                collision = 1;
            }
            if((moveRight == 1 && positionPerso.y == 920) && // collision perso en mouvement vers la droite + cube vert
               (positionPerso.x + 40 == positionFemme.x || positionPerso.x + 39 == positionFemme.x))
            {
               collision = 1;
            }
            if((moveLeft == 1 && positionPerso.y == 920) && // collision perso en mouvement vers la gauche + cube vert
               (positionPerso.x  == positionFemme.x + 40 || positionPerso.x == positionFemme.x + 39))
            {
               collision = 1;
            }
            if(moveDown == 1 && positionPerso.y == positionFemme.y - 40 &&  // collision perso vers le bas + cube vert
               (positionPerso.x + 40 > positionFemme.x && positionPerso.x < positionFemme.x + 40))
            {
                collision = 1;
            }
            // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
            // xxxxxxxxxxxxxxxxxxxxxxx actions diverses xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
            // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

            // prendre la clef Rose xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

            if(positionPerso.x == posClefRose.x + 30 && positionPerso.y == 720)
            {
                    posClefRose.x = 165;
                    posClefRose.y = 74;
                    actionClefRose = 1;

                    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, bruit_clef, 0, NULL);
                             }
            if(positionPerso.x == posClefBleue.x - 30 && positionPerso.y == 720 && (actionClefRose == 1))
            {
                    posClefBleue.x = 245;
                    posClefBleue.y = 74;
                    actionClefBleue = 1;

                    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, bruit_clef, 0, NULL);

            }
            if(positionPerso.x == posClefVerte.x - 30 && positionPerso.y == 320 && (actionClefRose == 1 && actionClefBleue == 1))
            {
                    posClefVerte.x = 325;
                    posClefVerte.y = 74;
                    actionClefVerte = 1;

                    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, bruit_clef, 0, NULL);
            }
            if(positionPerso.x == posClefJaune.x + 30 && positionPerso.y == 520 && (actionClefRose == 1 && actionClefBleue == 1 && actionClefVerte == 1))
            {
                    posClefJaune.x = 405;
                    posClefJaune.y = 74;
                    actionClefJaune = 1;

                    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, bruit_clef, 0, NULL);
            }
            if(positionPerso.x == posClefRouge.x + 30 && positionPerso.y == 920 && (actionClefRose == 1 && actionClefBleue == 1 && actionClefVerte == 1 && actionClefJaune == 1))
            {
                    posClefRouge.x = 485;
                    posClefRouge.y = 74;
                    actionClefRouge = 1;


                    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, porte_ouverte, 0, NULL);
            }

            if(actionClefRose == 1 && actionClefBleue == 1 && actionClefVerte == 1 && actionClefJaune == 1 && actionClefRouge == 1)
            {
                positionPorte.x = 1440;
                positionPorte.y = 850;

                niveau[23][36] = 0;
            }
            if(positionPerso.y == 920 && positionPerso.x == 1520)
            {
                    jouer = 0;
                            FMOD_Sound_Release(musique);

                    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, victoire, 0, NULL);
                    SDL_Delay(2500);
                    afficherMenu = 1;
                    partieGagnee = 0;

            }

            moveLeft = 0;
            moveRight = 0;
            moveUp = 0;
            moveDown = 0;
            action = 0;
            testCollision = 0;

            // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
            // xxxxxxxxxxxxxxxxxxxxxxxxxxx BLITAGES xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
            // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran -> format, 0, 0, 0));

            // affichage des murs xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
            for(j = 0; j < NBR_ORD; j++)
            {
                for(i = 0; i < NBR_ABS; i++)
                {
                    positionMur.x = tableauPositions[i];
                    positionMur.y = tableauPositions[j];

                    if(niveau[j][i] == 1)
                    {
                        SDL_BlitSurface(mur, NULL, ecran, &positionMur);
                    }
                    else if(niveau[j][i] == 2)
                    {
                        SDL_BlitSurface(echelle, NULL, ecran, &positionMur);
                    }
                }

            }//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
            if(collision == 1)
            {
            FMOD_System_PlaySound(system1, FMOD_CHANNEL_FREE, perte, 0, NULL);

            positionPerso.x = 840;
            positionPerso.y = 320;

            positionFemme.x = 1000;
            positionFemme.y = 920;

            positionRat.x = 840;
            positionRat.y = 520;

            posClefRose.x = 560;
            posClefRose.y = 710;

            posClefBleue.x = 1400;
            posClefBleue.y = 710;

            posClefVerte.x = 1400;
            posClefVerte.y = 310;

            posClefJaune.x = 600;
            posClefJaune.y = 510;

            posClefRouge.x = 560;
            posClefRouge.y = 910;

            actionClefRose = 0;
            actionClefBleue = 0;
            actionClefVerte = 0;
            actionClefJaune = 0;
            actionClefRouge = 0;

            positionPorte.x = 2000;
            positionPorte.y = 2000;

            niveau[23][36] = 1;

            SDL_Delay(2500);

            }
            collision = 0;
            effetsCollision = 0;

            SDL_Delay(5);

            SDL_BlitSurface(fond, NULL, ecran, &positionFond);
            SDL_BlitSurface(porte, NULL, ecran, &positionPorte);
            SDL_BlitSurface(clefRose, NULL, ecran, &posClefRose);
            SDL_BlitSurface(clefBleue, NULL, ecran, &posClefBleue);
            SDL_BlitSurface(clefVerte, NULL, ecran, &posClefVerte);
            SDL_BlitSurface(clefJaune, NULL, ecran, &posClefJaune);
            SDL_BlitSurface(clefRouge, NULL, ecran, &posClefRouge);
            SDL_BlitSurface(tabPerso[l][m], NULL, ecran, &positionPerso);
            SDL_BlitSurface(tabFemme[oF][aF], NULL, ecran, &positionFemme);
            SDL_BlitSurface(tabRat[oR][aR], NULL, ecran, &positionRat);
            SDL_Flip(ecran);
        }
    }

    FMOD_Sound_Release(bruit_clef);
    FMOD_Sound_Release(perte);
    FMOD_Sound_Release(porte_ouverte);
    FMOD_Sound_Release(victoire);

    FMOD_System_Close(system);
    FMOD_System_Release(system);

    SDL_FreeSurface(pL0);
    SDL_FreeSurface(pL1);
    SDL_FreeSurface(pL2);
    SDL_FreeSurface(pL3);
    SDL_FreeSurface(pL4);
    SDL_FreeSurface(pL5);
    SDL_FreeSurface(pL6);
    SDL_FreeSurface(pL7);
    SDL_FreeSurface(pL8);

    SDL_FreeSurface(pR0);
    SDL_FreeSurface(pR1);
    SDL_FreeSurface(pR2);
    SDL_FreeSurface(pR3);
    SDL_FreeSurface(pR4);
    SDL_FreeSurface(pR5);
    SDL_FreeSurface(pR6);
    SDL_FreeSurface(pR7);
    SDL_FreeSurface(pR8);

    SDL_FreeSurface(rR0);
    SDL_FreeSurface(rR1);
    SDL_FreeSurface(rL0);
    SDL_FreeSurface(rL1);
    SDL_FreeSurface(vR0);
    SDL_FreeSurface(vR1);
    SDL_FreeSurface(vL0);
    SDL_FreeSurface(vL1);

    SDL_FreeSurface(fond);
    SDL_FreeSurface(clef);
    SDL_FreeSurface(menu);

    SDL_Quit();

    return EXIT_SUCCESS;

}


