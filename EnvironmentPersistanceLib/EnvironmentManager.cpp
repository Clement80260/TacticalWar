#include "pch.h"
#include "EnvironmentManager.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
//#include <fstream>
#pragma warning(disable : 4996)
#define TAILLE_MAX 1000 // Tableau de taille 1000


using namespace std;



tw::EnvironmentManager * tw::EnvironmentManager::instance = NULL;

tw::EnvironmentManager * tw::EnvironmentManager::getInstance()
{
	if (instance == NULL)
		instance = new tw::EnvironmentManager();

	return instance;
}

tw::Environment * tw::EnvironmentManager::testEnvironment = NULL;
void tw::EnvironmentManager::createTestEnvironmentIfNotExists()
{
	if (testEnvironment == NULL)
	{
		testEnvironment = new tw::Environment(15, 15, 1);
		testEnvironment->getMapData(1, 1)->setIsWalkable(false);
		testEnvironment->getMapData(2, 2)->setIsObstacle(true);

		testEnvironment->getMapData(13, 13)->setIsWalkable(false);
		testEnvironment->getMapData(12, 12)->setIsObstacle(true);

		testEnvironment->getMapData(0, 0)->setTeamStartPoint(1);
		testEnvironment->getMapData(0, 1)->setTeamStartPoint(1);

		testEnvironment->getMapData(14, 14)->setTeamStartPoint(2);
		testEnvironment->getMapData(13, 14)->setTeamStartPoint(2);
	}
}


tw::Environment * tw::EnvironmentManager::loadEnvironment(int environmentId)
{
	// Equipe éditeur de map : Il faudra charger les données depuis le fichier environmentId.txt
	// situé dans le dossier /assets/map/ et construire une variable de type Environment que vous retournerez.
	
	createTestEnvironmentIfNotExists();
	return testEnvironment;
}

void tw::EnvironmentManager::saveEnvironment(Environment * environment)
{
	// Equipe éditeur de map : Il faudra enregistrer dans un fichier la map
	// passée en paramètre dans le dossier /assets/map/.
	// L'extension du fichier sera .txt
	FILE* fichier = NULL;
	fichier = fopen("C:\\assets\\map\\map.txt", "w+");

	if (fichier != NULL)
	{
		fputc('A', fichier); // Écriture du caractère A
		fclose(fichier);
	}
	

}