
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Coloration test module");

	sf::Shader shader;
	shader.loadFromFile("./assets/shaders/vertex.vert", "./assets/shaders/fragment.frag");

	sf::Texture Source;
	sf::Texture Assets;
	if (!Source.loadFromFile("assets/Mage/bottomright-die-sheet.png")) { std::cout << "Impossible de charger Grass texture" << std::endl; }
	if (!Assets.loadFromFile("assets/Mage/mask/bottomright-die-sheet.png")) { std::cout << "Impossible de charger Grass texture" << std::endl; }
	sf::Sprite perso;
	sf::Sprite mask;
	sf::Uint8  *pixels = new sf::Uint8[800 * 600 * 4];

	// Passage en image pour acc�der aux pixels :
	sf::Image src = Source.copyToImage(); 
	sf::Image img = Assets.copyToImage();

	mask.setTexture(Assets);
	mask.setTextureRect(sf::IntRect(0, 0, 281, 268));
	perso.setTexture(Source);
	perso.setTextureRect(sf::IntRect(0, 0, 281, 268));
	Source.setSmooth(true);
	 
	// Couleur que l'on souhaite appliquer :
	sf::Color toApplyarmure = sf::Color(120, 17, 17);
	sf::Color toApplycheveux = sf::Color(108, 70, 35);
	sf::Color toApplypeau = sf::Color(202,165,150);

	/* Couleur d'armure qui definie une equipe

	
	Color(75, 101, 222) -> bleu 
	Color(120,17,17) -> rouge 
	*/
	/* Couleur aleatoire appliquer sur les cheveux 

	
	Color(108,70,35) -> chatain 

	*/
	/* Couleur de base de la peau

	Color(202,165,150) -> tein de peau*/
	
	
	/*
	for (int x = 0; x < img.getSize().x; x++)
	{
		for (int y = 0; y < img.getSize().y; y++)
		{
			sf::Color couleur = img.getPixel(x, y);

			if (couleur.r > couleur.b && couleur.r > couleur.g && couleur.r > 50)
			{
				sf::Color colorSrc = src.getPixel(x, y);
				colorSrc = colorSrc * toApplyarmure;
				src.setPixel(x, y, colorSrc);

			}else if (couleur.b > couleur.r && couleur.b > couleur.g && couleur.b > 50)
			{
				sf::Color colorSrc = src.getPixel(x, y);
				colorSrc = colorSrc * toApplycheveux;
				src.setPixel(x, y, colorSrc);

			}else if (couleur.g > couleur.r && couleur.g > couleur.b && couleur.g > 50)
			{
				sf::Color colorSrc = src.getPixel(x, y);
				colorSrc = colorSrc * toApplypeau;
				src.setPixel(x, y, colorSrc);
			}
			
			

			//sf::Color couleur = img.getPixel(x, y);
			//couleur = couleur * toApply;
			//img.setPixel(x, y, couleur);
			 
			//pixels[(y * x) * 4] = 255; // R?
			//pixels[(y * x) * 4 + 1] = 255; // G?
			//pixels[(y * x) * 4 + 2] = 255; // B?
			//pixels[(y * x) * 4 + 3] = 255; // A?
		}
	}  

	Source.update(src);
	*/

	while (window.isOpen())
	{
		

		sf::Event event;
		while (window.pollEvent(event))
		{
			

			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear();

		shader.setUniform("mask", mask.getTexture());
		shader.setUniform("color1", sf::Glsl::Vec4(toApplyarmure));
		shader.setUniform("color2", sf::Glsl::Vec4(toApplycheveux));
		shader.setUniform("color3", sf::Glsl::Vec4(toApplypeau));

		sf::Shader::bind(&shader);
		window.draw(perso);
		sf::Shader::bind(NULL);
		window.display();
	}

	delete[] pixels;
	return 0;
}