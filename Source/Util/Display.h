#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <SFML/Graphics.hpp>

namespace Display
{
	constexpr static float HEIGHT = 720;
	constexpr static float WIDTH = 1280;

	void create	(const std::string& name = "My Window");

	void update ();
	void clear  ();

	bool isOpen	();

	void prepareSfDraw  ();
	void sfDraw         (const sf::Drawable& drawable);
	void endSfDraw      ();

	const sf::RenderWindow& get();

	float getAspect();

	void checkForClose();
	void close	();
}

#endif
