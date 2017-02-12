#ifndef CONFIG_H
#define CONFIG_H

#include "../Input/Key_Binds.h"
#include "ConfigParser.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <istream>

class Config {
public:
	Config();
	// Overwrite the current config with the contents of the stream.
	// The filename is used for error reporting.
	void loadFromStream(std::string const& filename, std::istream&);

	sf::Keyboard::Key getKey(Key_Binds::Control) const;
	sf::VideoMode getVideoMode() const;


private:
	void setDefaultVideoMode();
	void setDefaultKeybindings();

	void loadScreenSettingsFromStream(ConfigParser&);
	void loadKeybindingsFromStream(ConfigParser&);

	sf::VideoMode m_video_mode;
	std::map<Key_Binds::Control, sf::Keyboard::Key> m_keybindings;
};

#endif
