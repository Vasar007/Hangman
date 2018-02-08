#pragma once
///файл, отвечающий за главное меню

bool multiplayer = false, isGame = true, isPashalka = false;
std::vector<char> alphabet(26);
std::string word = "";

void menu(sf::RenderWindow &window)
{
	window.setView(window.getDefaultView());
	sf::Texture menuTexture1, menuTexture2, menuTexture3, menuTexture4, menuTexture5, aboutTexture, menuBackground;
	if (!menuTexture1.loadFromFile("Images/Menu/111.png"))
		std::cout << "Error 010: Couldn't load image pack." << std::endl;
	if (!menuTexture2.loadFromFile("Images/Menu/222.png"))
		std::cout << "Error 011: Couldn't load image pack." << std::endl;
	if (!menuTexture3.loadFromFile("Images/Menu/333.png"))
		std::cout << "Error 012: Couldn't load image pack." << std::endl;
	if (!menuTexture4.loadFromFile("Images/Menu/444.png"))
		std::cout << "Error 013: Couldn't load image pack." << std::endl;
	if (!menuTexture5.loadFromFile("Images/Menu/555.png"))
		std::cout << "Error 013: Couldn't load image pack." << std::endl;
	if (!aboutTexture.loadFromFile("Images/Menu/epidemic-3.png"))
		std::cout << "Error 014: Couldn't load image pack." << std::endl;
	if (!menuBackground.loadFromFile("Images/Menu/hangman_menu.jpg"))
		std::cout << "Error 0145: Couldn't load image pack." << std::endl;

	sf::Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menu4(menuTexture4), menu5(menuTexture5), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = true;
	int menuNum = 0;
	menu1.setPosition(290, 350);
	menu2.setPosition(285, 410);
	menu3.setPosition(285, 460);
	menu4.setPosition(305, 515);
	menu5.setPosition(125, 400);
	menu5.setColor(sf::Color::Red);
	about.setPosition(-75, -75);
	about.setScale(0.725f, 0.725f);
	menuBg.setPosition(0, 0);

	sf::Music aboutS;			//создаем объект музыки
	if (!aboutS.openFromFile("Sounds/about.ogg"))			//загружаем файл
		std::cout << "Error 036: Couldn't load sound pack." << std::endl;

	///блок инициализации таймеров
	sf::Clock clock;			//вспомогательный таймер
	float currentFrame = 0;			//счётчик для анимации
	int posX = -75;
	bool isRight = true;

	//само меню
	while (isMenu) {
		float time = clock.getElapsedTime().asMicroseconds();	//дать прошедшее время в микросекундах
		clock.restart();	//перезагружает время
		time = time / 800;	//скорость игры
		currentFrame += 0.0025 * time;

		menu1.setColor(sf::Color::Red);
		menu2.setColor(sf::Color::Red);
		menu3.setColor(sf::Color::Red);
		menu4.setColor(sf::Color::Red);
		menuNum = 0;

		window.clear(sf::Color::White);

		if (sf::IntRect(305, 355, 215, 35).contains(sf::Mouse::getPosition(window))) {
			menu1.setColor(sf::Color::Black);
			menuNum = 1;
		}
		if (sf::IntRect(300, 415, 215, 35).contains(sf::Mouse::getPosition(window))) {
			menu2.setColor(sf::Color::Black);
			menuNum = 2;
		}
		if (sf::IntRect(300, 465, 200, 35).contains(sf::Mouse::getPosition(window))) {
			menu3.setColor(sf::Color::Black);
			menuNum = 3;
		}
		if (sf::IntRect(340, 515, 115, 35).contains(sf::Mouse::getPosition(window))) {
			menu4.setColor(sf::Color::Black);
			menuNum = 4;
		}
		if (sf::IntRect(475, 0, 185, 320).contains(sf::Mouse::getPosition(window))) {
			menuNum = 5;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (menuNum == 1)
				isMenu = false;			//если нажали первую кнопку, то выходим из меню 
			
			if (menuNum == 2) {
				sf::Event event;
				sf::Font font;			//шрифт
				if (!font.loadFromFile("Other/ARLRDBD.ttf"))
					std::cout << "Error 051: Couldn't load font." << std::endl;

				sf::Text textField("", font, 32);			//текст с выбранным шрифтом и строкой
				textField.setPosition(200, 450);
				textField.setFillColor(sf::Color::Red);
				std::string field = "";

				window.clear(sf::Color::White);
				window.draw(menuBg);
				window.draw(menu5);
				window.draw(textField);
				window.display();

				bool flag = true;
				while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && flag) {
					window.pollEvent(event);

					window.setKeyRepeatEnabled(false);			//убираем повторное срабатывание события, если клавиша удерживается

					if (event.type == sf::Event::KeyPressed) {
						if (event.key.code >= 0 && event.key.code <= 25) {
							char var = alphabet[event.key.code];
							if (field.length() < 30)
								field = field + var;
						}

						if (event.key.code == sf::Keyboard::BackSpace) {			//если backspace, то перезагружаем игру
							if (field.length() > 0)
								field = field.substr(0, field.length() - 1);
						}

						if (event.key.code == sf::Keyboard::Tab) {			//если таб, то space
							field += " ";
						}


						if (event.key.code == sf::Keyboard::Space) {			//если таб, то перезагружаем игру
							if (field.length() > 2 && checkChars(field)) {
								isMenu = false;			//если нажали первую кнопку, то выходим из меню
								multiplayer = true;
								word = field;
								flag = false;
							}
						}
					}
					window.clear(sf::Color::White);
					window.draw(menuBg);
					window.draw(menu5);
					textField.setString(field);
					window.draw(textField);
					window.display();
				}
			}

			if (menuNum == 3) {
				aboutS.play();
				window.clear();
				window.draw(about);
				window.display();
				while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					time = clock.getElapsedTime().asMicroseconds();	//дать прошедшее время в микросекундах
					clock.restart();	//перезагружает время
					time = time / 800;	//скорость игры
					currentFrame += 0.05 * time;
					
					window.clear();

					if (currentFrame > 0.05) {
						currentFrame -= 0.05;
						if (isRight) {
							posX++;
							about.setPosition(posX, -75);
							if (posX == 225)
								isRight = false;
						}
						else {
							posX--;
							about.setPosition(posX, -75);
							if (posX == -75)
								isRight = true;
						}
					}

					window.draw(about);
					
					window.display();
				}
				aboutS.stop();
			}

			if (menuNum == 4) {
				window.close();
				isMenu = false;
				isGame = false;
			}

			if (menuNum == 5) {
				isPashalka = true;
				isMenu = false;
				isGame = false;
			}
		}


		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.draw(menu4);

		window.display();
	}
}