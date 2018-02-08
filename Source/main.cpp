///Nain file.
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "game.h"
#include "menu.h"


#define COUNT 55
#define GAME_COUNT 7


/// Game function.
bool startGame(sf::RenderWindow &window, int &numberLevel, bool &showMainMenu)
{
	word.clear();

	/// Initialize main window.
	if (showMainMenu)
		menu(window);			// Display menu.

	/// Initializatioon of sound buffers.
	sf::SoundBuffer winBuffer;
	if (!winBuffer.loadFromFile("Sounds/win.ogg"))
		std::cout << "Error 031: Couldn't load sound pack." << std::endl;
	sf::Sound win(winBuffer);

	sf::SoundBuffer defeatBuffer;
	if (!defeatBuffer.loadFromFile("Sounds/defeat.ogg"))
		std::cout << "Error 032: Couldn't load sound pack." << std::endl;
	sf::Sound defeat(defeatBuffer);	

	sf::SoundBuffer hitBuffer;
	if (!hitBuffer.loadFromFile("Sounds/hit.ogg"))
		std::cout << "Error 033: Couldn't load sound pack." << std::endl;
	sf::Sound hit(hitBuffer);

	sf::SoundBuffer exitBuffer;
	if (!exitBuffer.loadFromFile("Sounds/exit.ogg"))
		std::cout << "Error 034: Couldn't load sound pack." << std::endl;
	sf::Sound exit(exitBuffer);

	sf::SoundBuffer startBuffer;
	if (!startBuffer.loadFromFile("Sounds/start.ogg"))
		std::cout << "Error 035: Couldn't load sound pack." << std::endl;
	sf::Sound start(startBuffer);

	sf::SoundBuffer stepsBuffer;
	if (!stepsBuffer.loadFromFile("Sounds/steps.ogg"))
		std::cout << "Error 037: Couldn't load sound pack." << std::endl;
	sf::Sound steps(stepsBuffer);

	sf::SoundBuffer mimoBuffer;
	if (!mimoBuffer.loadFromFile("Sounds/mimo.ogg"))
		std::cout << "Error 038: Couldn't load sound pack." << std::endl;
	sf::Sound mimo(mimoBuffer);

	sf::SoundBuffer uvedomBuffer;
	if (!uvedomBuffer.loadFromFile("Sounds/uvedom.ogg"))
		std::cout << "Error 038: Couldn't load sound pack." << std::endl;
	sf::Sound uvedom(uvedomBuffer);

	sf::SoundBuffer svistBuffer;
	if (!svistBuffer.loadFromFile("Sounds/svist.ogg"))
		std::cout << "Error 039: Couldn't load sound pack." << std::endl;
	sf::Sound svist(svistBuffer);

	sf::SoundBuffer deathBuffer;
	if (!deathBuffer.loadFromFile("Sounds/death.ogg"))
		std::cout << "Error 0310: Couldn't load sound pack." << std::endl;
	sf::Sound death(deathBuffer);

	///блок инициализации меню
	sf::Font font;			//шрифт
	if (!font.loadFromFile("Other/ARLRDBD.ttf"))
		std::cout << "Error 050: Couldn't load font." << std::endl;

	sf::Text text("text", font, 32);			// Text used to draw letters.
	sf::Text textLetters("", font, 32);

	sf::Text textMessage("", font, 32);
	textMessage.setFillColor(sf::Color::Black);
	textMessage.setPosition(400, 100);
	//textMessage.setString("Known letter!");

	sf::Text textWin("You WIN!", font, 72);
	textWin.setPosition(350, 250);
	textWin.setFillColor(sf::Color::Black);

	sf::Text textLose("You LOSE!", font, 72);
	textLose.setPosition(350, 250);
	textLose.setFillColor(sf::Color::Black);

	std::string tempWord;
	if (isGame) {
		start.play();
		if (!multiplayer)
			word = getWordPVE();
		else
			multiplayer = false;
		tempWord = word.substr(0, 1) + " ";
		for (unsigned int i = 0; i < word.length() - 1; i++) {
			if (word[i] != ' ')
				tempWord += "_ ";
			else
				tempWord += "  ";
		}
		tempWord += word.substr(word.length() - 1, 1);
		text.setString(tempWord);
		std::cout << word << std::endl;
	}
	else {
		if (isPashalka)
			svist.play();
		else
			exit.play();
	}

	/// Initialize timer.
	sf::Clock clock;
	float currentFrame = 0;			// Counter for animation.
	
	///Initializatioon block for textures.
	sf::Image hangmanImgGame[GAME_COUNT];
	for (int i = 0; i < GAME_COUNT; i++) {
		if (!hangmanImgGame[i].loadFromFile("Images/Textures/" + std::to_string(i) + ".jpg"))
			std::cout << "Error 015: Couldn't load image pack." << std::endl;
	}
	sf::Texture hangmanTextGame[GAME_COUNT];
	for (int i = 0; i < GAME_COUNT; i++) {
		if (!hangmanTextGame[i].loadFromImage(hangmanImgGame[i]))
			std::cout << "Error 020: Couldn't create texture pack." << std::endl;
	}
	sf::Sprite hangmanGame[GAME_COUNT];
	for (int i = 0; i < GAME_COUNT; i++) {
		hangmanGame[i].setTexture(hangmanTextGame[i]);
	}

	sf::Image hangmanImg[COUNT];
	for (int i = 0; i < COUNT; i++) {
		if (!hangmanImg[i].loadFromFile("Animation/" + std::to_string(i) + ".gif"))
			std::cout << "Error 016: Couldn't load image pack." << std::endl;
	}
	sf::Texture hangmanText[COUNT];
	for (int i = 0; i < COUNT; i++) {
		if (!hangmanText[i].loadFromImage(hangmanImg[i]))
			std::cout << "Error 021: Couldn't create texture pack." << std::endl;
	}
	sf::Sprite hangman[COUNT];
	for (int i = 0; i < COUNT; i++) {
		hangman[i].setTexture(hangmanText[i]);
	}

	int life = 6, slide = 0;
	bool isLife = true, isAnime = false, isDelay = false, isWin = false;
	std::vector<char> letters;
	std::vector<bool> enteredLetters(word.length());

	if (isGame) {
		for (unsigned int i = 0; i < enteredLetters.size(); i++)
			enteredLetters[i] = false;
		enteredLetters[0] = true;
		enteredLetters[enteredLetters.size() - 1] = true;

		char w0, w2;
		w0 = word[0];
		w2 = word[word.size() - 1];
		if ((word[0] >= 65) & (word[0] <= 90))
			w0 = word[0] + 32;
		if ((word[word.size() - 1] >= 65) & (word[word.size() - 1] <= 90))
			w2 = word[word.size() - 1] + 32;

		if (w0 == w2) {
			letters.push_back(word[0]);
			chWord(word[0], word, enteredLetters, letters);
		}
		else {
			letters.push_back(word[0]);
			letters.push_back(word[word.size() - 1]);
			chWord(word[0], word, enteredLetters, letters);
			chWord(word[word.size() - 1], word, enteredLetters, letters);
		}
		mon = true;
		outWord(word, enteredLetters, letters, tempWord);
	}
	else {
		isGame = true;
	}

	if (isPashalka) {
		isAnime = true;
		isLife = false;
		isDelay = true;
		isPashalka = false;
		window.clear();
		window.draw(hangman[0]);
		window.display();
	}


	/// Main game loop.
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();	// Get current time in milliseconds.
		clock.restart();	// Restart clock.
		time = time / 800;	// Set game frame rate.
		currentFrame += 0.0025 * time;

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			window.setKeyRepeatEnabled(false);			// Disable repeat key pressing.

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {			// If user pressed 'Tab' restart game.
				showMainMenu = true;
				return true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {			// If user pressed 'Esc' close program.
				showMainMenu = false;
				return false;
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code >= 0 && event.key.code <= 25) {
					char var = alphabet[event.key.code];
					if (chWord(var, word, enteredLetters, letters) == true) {
						uvedom.play();
						textMessage.setString("Right!");
						if (outWord(word, enteredLetters, letters, tempWord) == 1) {
							std::cout << "You won!\n";
							isDelay = true;
							isWin = true;
						}
					}
					else {
						if (retry == true) {
							std::cout << "You entered known letter!. Try again.\n";
							exit.play();
							textMessage.setString("Known letter!");
							outWord(word, enteredLetters, letters, tempWord);
						}
						else {
							mimo.play();
							life--;
							textMessage.setString("Wrong!");
							outWord(word, enteredLetters, letters, tempWord);
							if (life == 0) {
								std::cout << "You lost!\n";
								std::cout << "Answer: " << word << std::endl;
								isLife = false;
							}
						}
					}
				}
			}
		}

		if (currentFrame > 0.20) {
			currentFrame -= 0.20;
			if (isAnime)
				slide++;
		}

		window.clear();

		if (isLife) {
			window.draw(hangmanGame[GAME_COUNT - 1 - life]);
			text.setString("Word: " + tempWord);
			text.setPosition(100, 550);
			text.setFillColor(sf::Color::Black);
			window.draw(text);			// Draw the text.
			std::string temporary;
			for (unsigned int i = 0; i < letters.size() - 1; i++)
				temporary = temporary + letters[i] + ", ";
			temporary = temporary + letters[letters.size() - 1];
			textLetters.setString("Entered letters: " + temporary);			// Set text string.
			textLetters.setPosition(10, 0);
			textLetters.setFillColor(sf::Color::Black);
			window.draw(textLetters);
			window.draw(textMessage);
		}
		else if (!isAnime) {
			defeat.play();
			window.draw(hangmanGame[GAME_COUNT - 1]);
			window.draw(textLose);
			text.setString("Word: " + word);
			text.setPosition(100, 550);
			text.setFillColor(sf::Color::Black);
			window.draw(text);			// Draw the text.
			isAnime = true;
			isDelay = true;
		}
		else if (isAnime) {
			window.draw(hangman[slide]);
			if (slide == COUNT - 1) {
				isDelay = true;
				isWin = true;
			}
			else if (slide == 29) {
				hit.play();
				steps.stop();
			}
			else if (slide == 1) {
				steps.play();
			}
			else if (slide == 38) {
				death.play();
			}
		}
		
		if (isWin && !isAnime) {
			win.play();
			window.draw(textWin);
		}

		window.display();

		if (isDelay) {
			while (currentFrame < 3) {
				time = clock.getElapsedTime().asMicroseconds();
				clock.restart();
				time = time / 800;
				currentFrame += 0.0025 * time;
			}
			currentFrame -= 3;
			isDelay = false;
			if (isWin) {
				isWin = false;
				showMainMenu = true;
				return true;
			}
		}
	}
}

///Start/restart game fucntion.
void gameRunning(sf::RenderWindow &window, int &numberLevel, bool &showMainMenu) {
	if (startGame(window, numberLevel, showMainMenu)) {
		gameRunning(window, numberLevel, showMainMenu);
	}
}


/// Main function.
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Hangman", sf::Style::Default);			// Window initialization.
	//sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game", sf::Style::Fullscreen);
	window.setFramerateLimit(60);
	int numberLevel = 1;			// Number of level.
	bool showMainMenu = true;
	for (unsigned int i = 0; i < alphabet.size(); i++)
		alphabet[i] = 97 + i;

	sf::Music music;			//создаем объект музыки
	if (!music.openFromFile("Sounds/Petka_Vasilij_Ivanovich_-_You_are_in_the_army_now.ogg"))			// Load main music theme.
		std::cout << "Error 030: Couldn't load sound pack." << std::endl;
	music.play();
	music.setLoop(true);			// Endlessly play music.

	gameRunning(window, numberLevel, showMainMenu);			// Launch game.
	return EXIT_SUCCESS;
}