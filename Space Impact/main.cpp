#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <Windows.h>
#include "Player.h"
#include "Enemy.h"
#include "Laser.h"
#include "Menu.h"
#include "Upgrade.h"
#include "Pause.h"
#include "Over.h"
using namespace std;
using namespace sf;

class Game {
	Player* player;
	RenderWindow* window;
	map<string, Texture*> texture2;
	vector<Laser*> laser;
	vector<Enemy*> enemy;
	Enemy* temp;
	Pause* pmenu;
	Over* gameover;

	Upgrade* upgrade[6];

	Vector2f position;
	SoundBuffer buffer, bgs, buy_sfx, shield_sfx, poof_sfx, cant_buy_sfx, bover;
	Sound sound, bg, buy, shield, poof, cant_buy, sover;
	Sprite money, worldBG, overbg, shtp;
	Texture moneyTexture, worldBGTex, overtex, htp;
	Image icon;

	Font font;
	Text text, line, coin, ship_upgrade, laser_upgrade, fireRate_upgrade, repairText, playerLevelText, laserLevelText, fireRateLevelText, bossHP;
	string waveFont;
	Color grey, yellow;
	int playerLevel, laserLevel, fireRateLevel, coinCount;
	int before, after, seconds, random;
	int clickTime, count, fontCount;
	int totalEnemyKilled, bossLevel, hit, nEnemy, wave, maxEnemy;
	int shipPrice, laserPrice, fireRatePrice, repairPrice;
	bool boss, once, active, onceFont;
public:
	Game() {
		initWindow();
	}
	void Initialize() {
		basicInit();
		initBGmusic();
		initBGTex();
		initPause(window);
		initOver(window);
		initOverMusic();

		boss = false;   once = false;   active = false;   onceFont = false;
						
		count = 0;			fontCount = 0;		clickTime = 0;	
		coinCount = 20000;		
				
		hit = 0;
		wave = 1;		nEnemy = 1;
		maxEnemy = 5;	totalEnemyKilled = 0;
		bossLevel = 1;		

		playerLevel = 1;		shipPrice = 200;
		laserLevel = 1;			laserPrice = 300;
		fireRateLevel = 1;		fireRatePrice = 300;
		repairPrice = 30;

		before = GetTickCount64();
		waveFont = to_string(wave);

		grey.r = 128;	grey.g = 128;   grey.b = 128;
		yellow.r = 255; yellow.g = 255; yellow.b = 0;

		moneyTexture.loadFromFile("Texture/coin.png");
		money.setTexture(moneyTexture);
		money.scale(0.075f, 0.075f);
		font.loadFromFile("Fonts/Dosis-Light.ttf");

		text.setFont(font);							line.setFont(font);					coin.setFont(font);
		text.setCharacterSize(72);					line.setCharacterSize(72);			coin.setCharacterSize(48);
		text.setFillColor(Color::Blue);				line.setFillColor(grey);			coin.setFillColor(grey);
		text.setStyle(Text::Bold);					line.setString("-");				coin.setString(to_string(coinCount));
		text.setString("Wave " + waveFont);

		ship_upgrade.setFont(font);									laser_upgrade.setFont(font);									fireRate_upgrade.setFont(font);
		ship_upgrade.setCharacterSize(30);							laser_upgrade.setCharacterSize(30);								fireRate_upgrade.setCharacterSize(30);
		ship_upgrade.setFillColor(yellow);							laser_upgrade.setFillColor(yellow);								fireRate_upgrade.setFillColor(yellow);
		ship_upgrade.setString("Cost : " + to_string(shipPrice));	laser_upgrade.setString("Cost : " + to_string(laserPrice));		fireRate_upgrade.setString("Cost : " + to_string(fireRatePrice));

		playerLevelText.setFont(font);									laserLevelText.setFont(font);									fireRateLevelText.setFont(font);
		playerLevelText.setCharacterSize(30);							laserLevelText.setCharacterSize(30);							fireRateLevelText.setCharacterSize(30);
		playerLevelText.setFillColor(yellow);							laserLevelText.setFillColor(yellow);							fireRateLevelText.setFillColor(yellow);
		playerLevelText.setString("Lvl : " + to_string(playerLevel));	laserLevelText.setString("Lvl : " + to_string(laserLevel));		fireRateLevelText.setString("Lvl : " + to_string(fireRateLevel));

		bossHP.setFont(font);										repairText.setFont(font);
		bossHP.setCharacterSize(48);								repairText.setCharacterSize(30);
		bossHP.setFillColor(Color::Red);							repairText.setFillColor(yellow);
		bossHP.setStyle(Text::Bold);								repairText.setString("Cost : " + to_string(repairPrice));
		bossHP.setString("BOSS HP");
	}
	void basicInit() {
		//init player
		this->player = new Player;

		//init enemy
		temp = new Asteroid;
		temp->setPosition();
		enemy.push_back(temp);

		//init laser texture
		this->texture2["LASER"] = new Texture();
		this->texture2["LASER"]->loadFromFile("Texture/shot6_12.png");

		//init money sfx
		if (!buy_sfx.loadFromFile("SFX/buy2_sfx.ogg")) { cout << "cant open buy2_sfx"; }

		buy.setBuffer(buy_sfx);

		if (!cant_buy_sfx.loadFromFile("SFX/clickclick.ogg")) { cout << "cant open click click"; }

		cant_buy.setBuffer(cant_buy_sfx);

		//init upgrade
		this->upgrade[0] = new Upship;
		this->upgrade[1] = new Updamage;
		this->upgrade[2] = new FireRate;
		this->upgrade[3] = new HealthBar;
		this->upgrade[4] = new EnemyHealthBar;
		this->upgrade[5] = new Repair;

	}
	void initIcon() {
		if (!this->icon.loadFromFile("Texture/icon.png")) {
			cout << "ERROR::GAME::COULD NOT lOAD ICON TEXTURE" << endl;
		}
		this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}
	void initBGMusicMenu() {
		bgs.loadFromFile("SFX/Menu.ogg");
		bg.setBuffer(bgs);
		bg.play();
		bg.setLoop(true);
	}
	void initBGTexMenu() {
		if (!this->worldBGTex.loadFromFile("Texture/menu.jpg")) {
			cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << endl;
		}
		this->worldBG.setTexture(this->worldBGTex);
	}
	void initHTPTex() {
		if (!this->htp.loadFromFile("Texture/howtoplay.png")) {
			cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << endl;
		}		
		this->shtp.setTexture(this->htp);		
	}
	void initOverTex() {
		if (!this->overtex.loadFromFile("Texture/overbg.jpg")) {
			cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << endl;
		}
		this->overbg.setTexture(this->overtex);
	}
	void initBGTex() {
		if (!this->worldBGTex.loadFromFile("Texture/rsz_battlespace.jpg")) {
			cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << endl;
		}
		this->worldBG.setTexture(this->worldBGTex);
	}
	void initOverMusic() {
		bover.loadFromFile("SFX/gameover.ogg");
		sover.setBuffer(bover);
	}
	void initBGmusic() {
		bgs.loadFromFile("SFX/Spacewar.ogg");
		bg.setBuffer(bgs);
		bg.play();
		bg.setLoop(true);
	}	
	void initPause(RenderWindow* window) {
		pmenu = new Pause(window);
	}
	void initOver(RenderWindow* window) {
		gameover = new Over(window);
	}	
	void initWindow() {
		this->window = new RenderWindow(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Space Keeper", Style::Close | Style::Titlebar);
		this->window->setFramerateLimit(60);
		this->window->setVerticalSyncEnabled(false);
	}
		
	void Save() {
		fstream file;
		file.open("SaveGame.txt", ios::out);
		if (!file.is_open()) {
			cout << "File cannot be opened / doesn't exist!" << endl;
		}
		else {
			file << wave << endl;
			file << coinCount << endl;
			file << playerLevel << endl;
			file << laserLevel << endl;
			file << fireRateLevel << endl;
			file << this->player->getHealth() << endl;
			file << bossLevel << endl;
			file.close();
			cout << "Data Saved" << endl;
		}
	}
	void Load() {
		fstream file;
		file.open("SaveGame.txt", ios::in);
		if (!file.is_open()) {
			cout << "File cannot be opened / doesn't exist!" << endl;
		}
		else {
			int health;
			file >> wave;
			file >> coinCount;
			file >> playerLevel;
			file >> laserLevel;
			file >> fireRateLevel;
			file >> health;
			file >> bossLevel;
			this->player->setHealth(health);
			file.close();
			cout << "Data Loaded" << endl;		
		}
	}

	void HTP() {		
		initHTPTex();
		while (window->isOpen()) {			
			Event e;
			while (window->pollEvent(e)) {
				switch (e.key.code) {
					case Keyboard::Escape:
						this->window->clear();
						Play();
				}
				if (e.Event::type == Event::Closed) {
					window->close();
				}				
			}
			this->window->clear();
			renderHTP();
			this->window->display();
		}
	}
	void Play() {
		initBGTexMenu();
		initBGMusicMenu();
		initIcon();
		Menu menu(window->getSize().x, window->getSize().y);
		while (window->isOpen()) {
			Event e;
			while (window->pollEvent(e)) {			
				switch (e.type) {
				case Event::KeyReleased:
					switch (e.key.code) {
					case Keyboard::Up:
						menu.MoveUp();
						break;
					case Keyboard::Down:
						menu.MoveDown();
						break;
					case Keyboard::Return:
						switch (menu.GetPressedItem()) {
						case 0: {
							vector<Laser*> laser;
							vector<Enemy*> enemy;
							Enemy* temp;
							Upgrade* upgrade[6];
						}
							window->clear();
							Initialize();
							run();
							break;
						case 1:						
							HTP();
							break;																				
						case 2: {
							vector<Laser*> laser;
							vector<Enemy*> enemy;
							Enemy* temp;
						}
							Initialize();
							Load();
							
							this->player->changeTexture(playerLevel);
							this->upgrade[0]->changetexture(playerLevel);
							this->texture2["LASER"]->loadFromFile("Texture/shot6_" + std::to_string(laserLevel) + ".png");
							this->upgrade[1]->changetexture(laserLevel);
							this->upgrade[2]->changetexture(fireRateLevel);
							upgrade[3]->changetexture(player->getHealth());
							for (int i = 0; i < fireRateLevel; i++) {
								this->player->increaseFireRate();
							}

							waveFont = to_string(wave);

							playerLevel == 1 ? shipPrice = 200 : playerLevel == 2 ? shipPrice = 500 : shipPrice = 1000;
							laserLevel == 1 ? laserPrice = 300 :laserLevel == 2 ? laserPrice = 500 : laserLevel == 3 ? laserPrice = 800 : laserLevel == 4 ? laserPrice = 1200 : laserPrice = 1700;

							if (!(playerLevel > 3)) {
								ship_upgrade.setString("Cost : " + to_string(shipPrice));
								playerLevelText.setString("Lvl : " + to_string(playerLevel));
							}
							else {
								ship_upgrade.setString("");
								playerLevelText.setString("");
							}
							
							if (!(laserLevel > 5)) {
								laser_upgrade.setString("Cost : " + to_string(laserPrice));
								laserLevelText.setString("Lvl : " + to_string(laserLevel));
								cout << "AA";
							}
							else {
								laser_upgrade.setString("");
								laserLevelText.setString("");
							}
							
							if (!(fireRateLevel > 24)) {
								fireRate_upgrade.setString("Cost : " + to_string(fireRatePrice));
								fireRateLevelText.setString("Lvl : " + to_string(fireRateLevel));
							}
							else {
								fireRate_upgrade.setString("");
								fireRateLevelText.setString("");
							}							
							run();
							break;
						case 3:
							window->close();
							exit(0);
							break;
						}
					}
					break;
				}
				if (e.Event::type == Event::Closed) {
					window->close();
				}
			}
			this->window->clear();
			renderBG();
			menu.draw(window);		
			this->window->display();
		}
	}
	void updatePollEvents() {
		Event e;
		while (window->pollEvent(e)) {
			if (e.Event::type == Event::Closed) {
				window->close();
			}
			if (e.Event::KeyPressed && e.Event::key.code == Keyboard::Escape && !gameover->over()) {
				pmenu->pauseState();
			}
			if (pmenu->paused() && !gameover->over()) {
				switch (e.type) {
				case Event::KeyReleased:
					switch (e.key.code) {
					case Keyboard::Up:
						pmenu->MoveUp();
						break;
					case Keyboard::Down:
						pmenu->MoveDown();
						break;
					case Keyboard::Return:
						switch (pmenu->GetPressedItem()) {
						case 0:
							pmenu->unpauseState();
							break;
						case 1: {
							this->laser.erase(this->laser.begin(), this->laser.end());
							this->enemy.erase(this->enemy.begin(), this->enemy.end());
						}
							Play();
							break;
						case 2:
							Save();
							break;
						case 3:
							window->close();
							exit(0);
							break;
						}
					}
					break;
				}
			}
			if (gameover->over()) {
				switch (e.type) {
				case Event::KeyReleased:
					switch (e.key.code) {
					case Keyboard::Up:
						gameover->MoveUp();
						break;
					case Keyboard::Down:
						gameover->MoveDown();
						break;
					case Keyboard::Return:
						switch (gameover->GetPressedItem()) {
						case 0: {
							this->laser.erase(this->laser.begin(), this->laser.end());
							this->enemy.erase(this->enemy.begin(), this->enemy.end());
							vector<Laser*> laser;
							vector<Enemy*> enemy;
							Enemy* temp;
							Upgrade* upgrade[6];
						}
							gameover->UnoverState();
							window->clear();
							Initialize();
							run();
							break;
						case 1: {
							this->laser.erase(this->laser.begin(), this->laser.end());
							this->enemy.erase(this->enemy.begin(), this->enemy.end());
						}
							 gameover->UnoverState();
							 Play();
							 break;
						case 2:
							window->close();
							exit(0);
							break;
						}
					}
					break;
				}
			}
		}
	}
	void processInput() {
		//Move player
		if (!pmenu->paused() && !gameover->over()) {

			if (Keyboard::isKeyPressed(Keyboard::A)) {
				this->player->move(-1.f, 0.f);
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				this->player->move(1.f, 0.f);
			}
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				this->player->move(0.f, -1.f);
			}
			if (Keyboard::isKeyPressed(Keyboard::S) ) {
				this->player->move(0.f, 1.f);
			}
			if (Mouse::isButtonPressed(Mouse::Left) && this->player->canAttack()) {
				if (!(Mouse::getPosition().y >= this->window->getSize().y / 4 * 3 + 90)) {//--> tidak bisa nembak di wilayah upgrade
					buffer.loadFromFile("SFX/bullet.ogg");
					sound.setBuffer(buffer);
					sound.play();
					this->laser.push_back(new Laser(this->texture2["LASER"], this->player->getPos().x, this->player->getPos().y, 1.f, 0.f, 10.f));
				}
			}
		}	
	}
	void whatHappensWhenBossDead() {		
			boss = false;
			wave++;
			cout << "wave : " << wave;
			if (!once) {
				fontCount = seconds;
				once = true;
			}
			updateFont();
			totalEnemyKilled--;	
	}
	void updateLaser() { // cek semua yang berhubungan dengan laser. Musuh kena laser atau laser di delete setelah lewat dari layar
		int counter = 0;
		for (auto* i : this->laser) {
			i->update();
			if (i->getPos().x >= 1835) {
				delete this->laser.at(counter);
				this->laser.erase(this->laser.begin() + counter);
				--counter;
			}
			int length = 0;

			for (auto j : this->enemy) {
				if (i->getBounds().intersects(j->getBounds())) {//-->cek collision laser dengan enemy

					delete this->laser.at(counter);
					this->laser.erase(this->laser.begin() + counter);
					--counter;

					if (j->getShield() == true && (dynamic_cast<Boss2*>(j) || dynamic_cast<Boss3*>(j))) {
						poof_sfx.loadFromFile("SFX/VOLUME_poof.ogg");
						poof.setBuffer(poof_sfx);
						poof.play();
					}
					else {
						hit = laserLevel;
						j->setHit(hit);

						if (boss && j->getHealth() != 0) {
							this->upgrade[4]->changetexture(j->getHealth() * 3);
						}
						
						buffer.loadFromFile("SFX/hit_sfx1.ogg"); //--> sound effect kalo kena musuh lasernya 
						sound.setBuffer(buffer);
						sound.play();
					}
					
					if (j->getHealth() <= 0) {

						if (wave % 5 == 0 && j->getType() >= 3) {
							whatHappensWhenBossDead();
							coinCount += 10;
						}
							
						delete this->enemy.at(length);
						this->enemy.erase(this->enemy.begin() + length);
						totalEnemyKilled++;
						coinCount += 15;
						--length;			
					}
					hit = 0;										
				}
				++length;
			}
			++counter;
		}
	}
	void updateEnemy() { // semua yang berhubungan sama enemy tp tanpa laser. Spt musuh kebobolan , atau musuh nabrak player
		int length = 0; int hit = 0; 
		for (auto i : enemy) {
			i->updates();
			if (seconds % 5 == 0 && seconds != 0 && count != seconds && i->getShield() == false && (dynamic_cast<Boss2*>(i) || dynamic_cast<Boss3*>(i))) {
				i->changeTexture(bossLevel);// untuk ganti texture shield sesuai level boss
				i->setShield(true);
				shield_sfx.loadFromFile("SFX/shield.ogg");
				shield.setBuffer(shield_sfx);
				shield.play();
				count = seconds;
			}
			if ((dynamic_cast<Boss2*>(i) || dynamic_cast<Boss3*>(i)) && i->getShield() == true && seconds % 3 == 0 && seconds != 0 && count != seconds) {
				/*i->initTexture();*/
				i->changeBossTexture(bossLevel);
				i->setShield(false);
				count = seconds;
			}
			if (i->getBounds().intersects(player->getBounds())) { // kalo enemy nabrak player

				playerLevel == 1 ? hit = 5 : playerLevel == 2 ? hit = 3 : playerLevel == 3 ? hit = 2 : hit = 1;
				// kalo player level 1 dan nabrak player maka hit nya kerasa 5 dan seiring bertambahnya level hit nya berkurang karena makin tebel 

				player->setHit(hit);
				this->upgrade[3]->changetexture(this->player->getHealth());

				if (wave % 5 == 0 && i->getType() >= 3)
					whatHappensWhenBossDead();
				
					delete this->enemy.at(length);
					this->enemy.erase(this->enemy.begin() + length);
					totalEnemyKilled++;
					--length;
							
			}
			else if (i->getPos().x < 20) {
			
				if (wave % 5 == 0 && i->getType() >= 3)
					whatHappensWhenBossDead();
				
				playerLevel == 1 ? hit = 5 : playerLevel == 2 ? hit = 3 : playerLevel == 3 ? hit = 2 : hit = 1;
				// kalo player level 1 dan nabrak player maka hit nya kerasa 5 dan seiring bertambahnya level hit nya berkurang karena makin tebel 

				player->setHit(hit);
				this->upgrade[3]->changetexture(this->player->getHealth());

				delete this->enemy.at(length);
				this->enemy.erase(this->enemy.begin() + length);
				totalEnemyKilled++;
				--length;
				cout << "Total Enemy Killed Boss: " << totalEnemyKilled;
			}
			++length;
			hit = 0;
		}	
	}	
	void updateFont() {
		if (((seconds - fontCount <= 5)) && (once == true)) {
			active = true;
		}
		else {
			once = false;
			active = false;
			onceFont = false;
		}
	}
	void drawFont() {
		text.setPosition(this->window->getSize().x / 2 - 120, this->window->getSize().y / 2);
		int temp; 
		
		
		if (!onceFont) {
			temp = stoi(waveFont) + 1;
			waveFont = to_string(temp);
			onceFont = true;
		}
		text.setString("Wave " + waveFont);
		this->window->draw(text);
	}
	void drawUpgradeables() {//--->untuk layar 1920 x 1080 pas untuk 1366 x 768 pas
		float panjangLayar = VideoMode::getDesktopMode().width;
		float tinggiLayar = VideoMode::getDesktopMode().height;
		for (int i = 0; i < panjangLayar; i++)
		{
			line.setPosition(i, tinggiLayar / 4 * 3);
			this->window->draw(line);
		}
		money.setPosition(panjangLayar / 30 - 30, tinggiLayar / 5 * 4 + 30);
		this->window->draw(money);

		coin.setString(to_string(coinCount));
		coin.setPosition(panjangLayar / 30 + 40, tinggiLayar / 5 * 4 + 35);
		this->window->draw(coin);

		this->upgrade[0]->setPosition(panjangLayar / 30 + 200, tinggiLayar / 5 * 4 + 27.664); // tombol upgrade kapal
		this->upgrade[0]->render(*this->window);

		ship_upgrade.setPosition(panjangLayar / 30 + 285, tinggiLayar / 5 * 4 + 25);//Text harga nya berapa
		this->window->draw(ship_upgrade);
		playerLevelText.setPosition(panjangLayar / 30 + 285, tinggiLayar / 5 * 4 + 55);//Text Level Kapal
		this->window->draw(playerLevelText);

		this->upgrade[1]->setPosition(panjangLayar / 30 + 430, tinggiLayar / 5 * 4 + 30);//tombol upgrade laser
		this->upgrade[1]->render(*this->window);

		laser_upgrade.setPosition(panjangLayar / 30 + 520, tinggiLayar / 5 * 4 + 25);//Text harga nya berapa
		this->window->draw(laser_upgrade);
		laserLevelText.setPosition(panjangLayar / 30 + 520, tinggiLayar / 5 * 4 + 55);//Text Level laser
		this->window->draw(laserLevelText);

		this->upgrade[2]->setPosition(panjangLayar / 30 + 660, tinggiLayar / 5 * 4 + 30);//tombol upgrade fire rate laser
		this->upgrade[2]->render(*this->window);

		fireRate_upgrade.setPosition(panjangLayar / 30 + 750, tinggiLayar / 5 * 4 + 25);//Text harga nya berapa
		this->window->draw(fireRate_upgrade);
		fireRateLevelText.setPosition(panjangLayar / 30 + 750, tinggiLayar / 5 * 4 + 55);//Text Level fire rate
		this->window->draw(fireRateLevelText);

		this->upgrade[5]->setPosition(panjangLayar / 30 + 890, tinggiLayar / 5 * 4 + 30);//Tombol Repair
		this->upgrade[5]->render(*this->window);

		repairText.setPosition(panjangLayar / 30 + 1000, tinggiLayar / 5 * 4 + 40);//Harga repair
		this->window->draw(repairText);

		this->upgrade[3]->setPosition(panjangLayar / 30 + 162.064, tinggiLayar / 5 * 4 + 125);//healthbar player
		this->upgrade[3]->render(*this->window);

		if (boss) { //enemy HP untuk boss saja
			bossHP.setPosition(panjangLayar / 2 + 420, tinggiLayar / 5 * 4 + 60);//tulisan BOSS HP
			this->window->draw(bossHP);

			this->upgrade[4]->setPosition(panjangLayar / 2 + 700.064, tinggiLayar / 5 * 4 + 125);//enemy healthbar
			this->upgrade[4]->render(*this->window);
		}		
	}
	void updateUpgradeables() {

		if (Mouse::isButtonPressed(Mouse::Left) && clickTime != seconds) {

			if (upgrade[0]->getBounds().contains(Mouse::getPosition().x, Mouse::getPosition().y - 25)) {
				if (playerLevel < 4) {

					if (coinCount < shipPrice) cant_buy.play();

					else {
						coinCount -= shipPrice;
						playerLevel++;
						
						playerLevel == 2 ? shipPrice = 500 : shipPrice = 1000; // kalo 2 harga 500 kalo 3 1000

						if (playerLevel > 3) {
							ship_upgrade.setString("");
							playerLevelText.setString("");
						}
						else {
							ship_upgrade.setString("Cost : " + to_string(shipPrice));
							playerLevelText.setString("Lvl : " + to_string(playerLevel));
						}

						buy.play();
						this->player->changeTexture(playerLevel);
						this->upgrade[0]->changetexture(playerLevel);
					}
				}
				else {
					cant_buy.play();
				}
			}
			else if (upgrade[1]->getBounds().contains(Mouse::getPosition().x, Mouse::getPosition().y - 25) && this->laser.size() == 0) {
				if (laserLevel < 6) {

					if (coinCount < laserPrice) cant_buy.play();

					else {
						coinCount -= laserPrice;
						laserLevel++;
						
						laserLevel == 2 ? laserPrice = 500 : laserLevel == 3 ? laserPrice = 800 : laserLevel == 4 ? laserPrice = 1200 : laserPrice = 1700;

						if (laserLevel > 5) {
							laser_upgrade.setString("");
							laserLevelText.setString("");
						}
						else {
							laser_upgrade.setString("Cost : " + to_string(laserPrice));
							laserLevelText.setString("Lvl : " + to_string(laserLevel));
						}

						buy.play();
						this->texture2["LASER"]->loadFromFile("Texture/shot6_" + std::to_string(laserLevel) + ".png");
						this->upgrade[1]->changetexture(laserLevel);
					}

				}
				else {
					cant_buy.play();
				}
			}
			else if (upgrade[2]->getBounds().contains(Mouse::getPosition().x, Mouse::getPosition().y - 25) && this->laser.size() == 0) {
				if (fireRateLevel < 25) {

					if (coinCount < fireRatePrice) cant_buy.play();
											
					else {
						fireRateLevel++;
						
						coinCount -= fireRatePrice;
						if (fireRateLevel > 24) {
							fireRate_upgrade.setString("");
							fireRateLevelText.setString("");
						}
						else {
							fireRate_upgrade.setString("Cost : " + to_string(fireRatePrice));
							fireRateLevelText.setString("Lvl : " + to_string(fireRateLevel));
						}

						buy.play();
						this->player->increaseFireRate();
						this->upgrade[2]->changetexture(fireRateLevel);
					}
				}
				else {					
					cant_buy.play();
				}
			}
			else if (upgrade[5]->getBounds().contains(Mouse::getPosition().x, Mouse::getPosition().y - 25)) {
				if (coinCount < repairPrice) cant_buy.play();

				else {
					coinCount -= repairPrice;
					buy.play();
					player->addHealth(10);
					upgrade[3]->changetexture(player->getHealth());
				}
			}
			clickTime = seconds;
		}
	}
	int Randomizer() { return rand() % 2; }//--> ini buat random enemy yg akan di spawn utk sekarang 1 = asteroid 2 = meteor 
	
	void update() {

		updatePollEvents();
		if (!pmenu->paused() && !gameover->over()) {
			updateEnemy();
			if (nEnemy != maxEnemy) {
				if (wave % 5 == 0 && boss == false && !active) {
					bool boss2 = false, boss3 = false;
					
					if (wave <= 15) {
						wave % 15 == 0 ? boss3 = true : wave % 10 == 0 ? boss2 = true : boss2 = false;
					}
					else {
						
						(wave - 15 * bossLevel) % 15 == 0 ? boss3 = true : (wave - 15 * bossLevel) % 10 == 0 ? boss2 = true : boss2 = false;
						if ((wave - 15 * bossLevel) % 15 == 5) {
							bossLevel++;
						}
					}
					
					if (boss3) {
						temp = new Boss3;
						temp->setPosition();
						temp->changeBossTexture(bossLevel);
						enemy.push_back(temp);
					}
					else if (boss2) {
						temp = new Boss2;
						temp->setPosition();
						temp->changeBossTexture(bossLevel);
						enemy.push_back(temp);
					}
					else {
						temp = new Boss1;
						temp->setPosition();
						temp->changeBossTexture(bossLevel);
						enemy.push_back(temp);
					}

					boss = true;

				}
				else if (!boss && !active) {//--> kalo boss tidak spawn apa2 selain itu spawn asteroid atau meteor
					if (seconds % 3 == 0 && seconds != 0 && count != seconds && nEnemy <= maxEnemy) {//---> tiap 3 detik spawn enemy
						int a = Randomizer();
						if (a == 0) {
							temp = new Asteroid;
							temp->setPosition();
							enemy.push_back(temp);
						}
						else if (a == 1) {
							temp = new Meteor;
							temp->setPosition();
							enemy.push_back(temp);
						}
						nEnemy++;
						count = seconds;//--> count buat bisa dapetin 3 detik
					}
				}

			}

			else if (totalEnemyKilled == maxEnemy) {
				if (!(wave % 5 == 0)) {//--> selain wave keliapatan 5 ditambah seperti biasa, wave kelipatan 5 spawn 1 enemy smpe enemy nya mati
					wave++;
					totalEnemyKilled = 0;
				}
				if (!once) {
					fontCount = seconds;
					once = true;
				}
				nEnemy = 0;
			}

			updateFont();
			updateUpgradeables();
			this->player->update();
			if (this->player->getStatus() == true) {
				window->clear();
				bg.stop();
				gameover->OverState();
				sover.play();
			}
			updateLaser();
			after = GetTickCount64();//-->get seconds (int)
			seconds = (after - before) / 1000;
		}
		else {
			this->pmenu->update();
		}
	}
	void renderBG() {
		this->window->draw(this->worldBG);
	}
	void renderOverBG() {
		this->window->draw(this->overbg);
	}
	void renderHTP() {
		this->window->draw(this->shtp);	
	}
	void renderPause(RenderTarget* target) {
		if (pmenu->paused()) {
			this->pmenu->render(target);
		}
	}
	void renderOver(RenderTarget* target) {
		if (gameover->over()) {
			this->gameover->render(target);
		}
	}
	void render() {
		if (!gameover->over()) {
			this->window->clear();
			this->renderBG();
			this->player->render(*this->window);
			for (auto* i : enemy)
				i->render(*this->window);

			for (auto* i : this->laser)
				i->render(this->window);

			if (active) {
				drawFont();
			}
			drawUpgradeables();
			if (pmenu->paused()) {
				this->pmenu->render(this->window);
			}
		}
		if (gameover->over()) {
			initOverTex();
			this->renderOverBG();
			this->gameover->render(this->window);
		}
		this->window->display();
	}
	void run() {
		while (1) {
			processInput();
			update();
			render();
		}
	}
	~Game() {
		delete this->window;
		delete this->player;
		
		//Delete textures
		for (auto& i : this->texture2) 
			delete i.second;
		
		//Delete laser
		for (auto* i : this->laser) 
			delete i;
		
		//delete enemy
		for (auto* i : this->enemy) 
			delete i;
		
		for (int i = 0; i < 6; i++)		
			delete upgrade[i];		
	}
};

int main() {
	srand(time(NULL));
	Game game;

	game.Play();
	return 0;
}