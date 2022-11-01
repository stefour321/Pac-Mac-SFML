/*
Author: Stella Fournier
Class: ECE4122 A
Last Date Modified: 10/20/2022

Description:
This is the code file for the PacMan game. This file uses SFML.
*/

#include <SFML/Graphics.hpp>
using namespace sf;
#include <vector>
using namespace std;
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>

int gameScorePlus = 1000;

// This function sets the direction of the Ghosts.
void setDirection(int &dir, Sprite &spriteObj, float &speedNum, Time &time)
{
  switch (dir)
  {
  case (1):
    return spriteObj.setPosition(spriteObj.getPosition().x - (speedNum * time.asSeconds()), spriteObj.getPosition().y);
    break;
  case (2):
    return spriteObj.setPosition(spriteObj.getPosition().x + (speedNum * time.asSeconds()), spriteObj.getPosition().y);
    break;
  case (3):
    return spriteObj.setPosition(spriteObj.getPosition().x, spriteObj.getPosition().y - (speedNum * time.asSeconds()));
    break;
  case (4):
    return spriteObj.setPosition(spriteObj.getPosition().x, spriteObj.getPosition().y + (speedNum * time.asSeconds()));
    break;
  }
}
// Get the ghost out of collision from the walls by moving one pixel
void resetDirection(Sprite &spriteObj, int &startSpeed)
{
  switch (startSpeed)
  {
  case (1):
    return spriteObj.move(1, 0);
    break;
  case (2):
    return spriteObj.move(-1, 0);
    break;
  case (3):
    return spriteObj.move(0, 1);
    break;
  case (4):
    return spriteObj.move(0, -1);
    break;
  }
}

int main()
{
  srand((unsigned)time(NULL));
  VideoMode vm(641, 728);

  // Create and open a window for the game
  RenderWindow window(vm, "PacMan");

  // Create Start Page
  Texture tectureStartBackground;
  tectureStartBackground.loadFromFile("..\\graphics\\pac-man.bmp");
  Sprite spriteStartBackground;
  spriteStartBackground.setTexture(tectureStartBackground);
  spriteStartBackground.setPosition(0, 0);

  // Create a background
  Texture textureBackground;
  textureBackground.loadFromFile("..\\graphics\\maze.bmp");
  Sprite spriteBackground;
  spriteBackground.setTexture(textureBackground);
  spriteBackground.setPosition(0, 0);

  // Create Start Text
  Text startText;
  Font font;
  font.loadFromFile("..\\assets\\fonts\\slant_regular.ttf");
  startText.setFont(font);
  startText.setString("PRESS ENTER TO START");
  startText.setFillColor(Color::White);
  startText.setCharacterSize(45);

  // Position the text
  FloatRect textRect = startText.getLocalBounds();
  startText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
  startText.setPosition(641 / 2.0f, 728 / 2.0f);

  // Create End Text and Position End Text
  Text endTextWin;
  endTextWin.setFont(font);
  endTextWin.setString("YOU WIN!!!");
  endTextWin.setFillColor(Color::White);
  endTextWin.setCharacterSize(45);
  FloatRect textRect2 = endTextWin.getLocalBounds();
  endTextWin.setOrigin(textRect2.left + textRect2.width / 2.0f, textRect2.top + textRect2.height / 2.0f);
  endTextWin.setPosition(641 / 2.0f, 728 / 2.0f);

  // Create End Text and Position End Text
  Text endTextLose;
  endTextLose.setFont(font);
  endTextLose.setString("You Lose!!!");
  endTextLose.setFillColor(Color::White);
  endTextLose.setCharacterSize(45);
  FloatRect textRect3 = endTextLose.getLocalBounds();
  endTextLose.setOrigin(textRect3.left + textRect3.width / 2.0f, textRect3.top + textRect3.height / 2.0f);
  endTextLose.setPosition(641 / 2.0f, 728 / 2.0f);

  // Create Score Text
  Text scoreText;
  int gameScore = 0;
  scoreText.setFont(font);
  scoreText.setString(to_string(gameScore));
  scoreText.setFillColor(Color::White);
  scoreText.setCharacterSize(45);
  scoreText.setPosition(150, 660);

  // Create Wall Objects & push in a vector
  vector<RectangleShape> topWallVec;

  sf::RectangleShape midBoxTop1(sf::Vector2f(132, 10));
  midBoxTop1.setPosition(250, 283);
  topWallVec.push_back(midBoxTop1);
  sf::RectangleShape midBoxBottom(sf::Vector2f(137, 10));
  midBoxBottom.setPosition(250, 352);
  topWallVec.push_back(midBoxBottom);
  sf::RectangleShape midBoxLeft(sf::Vector2f(10, 72));
  midBoxLeft.setPosition(250, 283);
  topWallVec.push_back(midBoxLeft);
  sf::RectangleShape midBoxRight(sf::Vector2f(10, 72));
  midBoxRight.setPosition(376, 283);
  topWallVec.push_back(midBoxRight);

  sf::RectangleShape topLB1(sf::Vector2f(10, 200));
  topLB1.setPosition(32, 25);
  topWallVec.push_back(topLB1);
  sf::RectangleShape topLB2(sf::Vector2f(108, 10));
  topLB2.setPosition(32, 223);
  topWallVec.push_back(topLB2);
  sf::RectangleShape topLB3(sf::Vector2f(10, 75));
  topLB3.setPosition(132, 223);
  topWallVec.push_back(topLB3);
  sf::RectangleShape topLB4(sf::Vector2f(108, 10));
  topLB4.setPosition(32, 293);
  topWallVec.push_back(topLB4);
  sf::RectangleShape topLBox1(sf::Vector2f(55, 38));
  topLBox1.setPosition(87, 80);
  topWallVec.push_back(topLBox1);
  sf::RectangleShape topLBox2(sf::Vector2f(75, 38));
  topLBox2.setPosition(190, 80);
  topWallVec.push_back(topLBox2);
  sf::RectangleShape topLW1(sf::Vector2f(55, 15));
  topLW1.setPosition(87, 163);
  topWallVec.push_back(topLW1);
  sf::RectangleShape topLW2(sf::Vector2f(15, 138));
  topLW2.setPosition(187, 163);
  topWallVec.push_back(topLW2);
  sf::RectangleShape topLW3(sf::Vector2f(75, 15));
  topLW3.setPosition(190, 223);
  topWallVec.push_back(topLW3);

  // Top Mid
  sf::RectangleShape topB(sf::Vector2f(575, 10));
  topB.setPosition(32, 25);
  topWallVec.push_back(topB);
  sf::RectangleShape topMW1(sf::Vector2f(15, 90));
  topMW1.setPosition(312, 25);
  topWallVec.push_back(topMW1);
  sf::RectangleShape topMW2(sf::Vector2f(137, 15));
  topMW2.setPosition(250, 163);
  topWallVec.push_back(topMW2);
  sf::RectangleShape topMW3(sf::Vector2f(15, 75));
  topMW3.setPosition(312, 163);
  topWallVec.push_back(topMW3);

  // Top Right
  sf::RectangleShape topRB1(sf::Vector2f(10, 200));
  topRB1.setPosition(596, 25);
  topWallVec.push_back(topRB1);
  sf::RectangleShape topRB2(sf::Vector2f(108, 10));
  topRB2.setPosition(497, 223);
  topWallVec.push_back(topRB2);
  sf::RectangleShape topRB3(sf::Vector2f(10, 75));
  topRB3.setPosition(497, 223);
  topWallVec.push_back(topRB3);
  sf::RectangleShape topRB4(sf::Vector2f(108, 10));
  topRB4.setPosition(497, 293);
  topWallVec.push_back(topRB4);
  sf::RectangleShape topRBox1(sf::Vector2f(75, 38));
  topRBox1.setPosition(373, 80);
  topWallVec.push_back(topRBox1);
  sf::RectangleShape topRBox2(sf::Vector2f(55, 38));
  topRBox2.setPosition(497, 80);
  topWallVec.push_back(topRBox2);
  sf::RectangleShape topRW1(sf::Vector2f(75, 15));
  topRW1.setPosition(373, 223);
  topWallVec.push_back(topRW1);
  sf::RectangleShape topRW2(sf::Vector2f(15, 138));
  topRW2.setPosition(435, 163);
  topWallVec.push_back(topRW2);
  sf::RectangleShape topRW3(sf::Vector2f(55, 15));
  topRW3.setPosition(497, 163);
  topWallVec.push_back(topRW3);

  // Bottom Left
  sf::RectangleShape bottomLB1(sf::Vector2f(10, 237));
  bottomLB1.setPosition(32, 420);
  topWallVec.push_back(bottomLB1);
  sf::RectangleShape bottomLB2(sf::Vector2f(108, 10));
  bottomLB2.setPosition(32, 347);
  topWallVec.push_back(bottomLB2);
  sf::RectangleShape bottomLB3(sf::Vector2f(10, 75));
  bottomLB3.setPosition(132, 347);
  topWallVec.push_back(bottomLB3);
  sf::RectangleShape bottomLB4(sf::Vector2f(108, 10));
  bottomLB4.setPosition(32, 418);
  topWallVec.push_back(bottomLB4);
  sf::RectangleShape bottomLW1(sf::Vector2f(15, 75));
  bottomLW1.setPosition(187, 347);
  topWallVec.push_back(bottomLW1);
  sf::RectangleShape bottomLW2(sf::Vector2f(55, 15));
  bottomLW2.setPosition(87, 470);
  topWallVec.push_back(bottomLW2);
  sf::RectangleShape bottomLW3(sf::Vector2f(75, 15));
  bottomLW3.setPosition(190, 470);
  topWallVec.push_back(bottomLW3);
  sf::RectangleShape bottomLW4(sf::Vector2f(15, 75));
  bottomLW4.setPosition(128, 470);
  topWallVec.push_back(bottomLW4);
  sf::RectangleShape bottomLW5(sf::Vector2f(48, 15));
  bottomLW5.setPosition(32, 532);
  topWallVec.push_back(bottomLW5);
  sf::RectangleShape bottomLW6(sf::Vector2f(15, 75));
  bottomLW6.setPosition(190, 532);
  topWallVec.push_back(bottomLW6);
  sf::RectangleShape bottomLW7(sf::Vector2f(180, 15));
  bottomLW7.setPosition(87, 594);
  topWallVec.push_back(bottomLW7);

  // Bottom Right
  sf::RectangleShape bottomRB1(sf::Vector2f(10, 237));
  bottomRB1.setPosition(596, 420);
  topWallVec.push_back(bottomRB1);
  sf::RectangleShape bottomRB2(sf::Vector2f(108, 10));
  bottomRB2.setPosition(497, 347);
  topWallVec.push_back(bottomRB2);
  sf::RectangleShape bottomRB3(sf::Vector2f(10, 75));
  bottomRB3.setPosition(497, 347);
  topWallVec.push_back(bottomRB3);
  sf::RectangleShape bottomRB4(sf::Vector2f(108, 10));
  bottomRB4.setPosition(497, 418);
  topWallVec.push_back(bottomRB4);

  sf::RectangleShape bottomRW1(sf::Vector2f(15, 75));
  bottomRW1.setPosition(435, 347);
  topWallVec.push_back(bottomRW1);
  sf::RectangleShape bottomRW2(sf::Vector2f(75, 15));
  bottomRW2.setPosition(373, 470);
  topWallVec.push_back(bottomRW2);
  sf::RectangleShape bottomRW3(sf::Vector2f(55, 15));
  bottomRW3.setPosition(497, 470);
  topWallVec.push_back(bottomRW3);
  sf::RectangleShape bottomRW4(sf::Vector2f(15, 75));
  bottomRW4.setPosition(497, 470);
  topWallVec.push_back(bottomRW4);
  sf::RectangleShape bottomRW5(sf::Vector2f(48, 15));
  bottomRW5.setPosition(558, 532);
  topWallVec.push_back(bottomRW5);
  sf::RectangleShape bottomRW6(sf::Vector2f(15, 75));
  bottomRW6.setPosition(435, 532);
  topWallVec.push_back(bottomRW6);
  sf::RectangleShape bottomRW7(sf::Vector2f(180, 15));
  bottomRW7.setPosition(373, 594);
  topWallVec.push_back(bottomRW7);

  // Bottom Mid
  sf::RectangleShape bottomB(sf::Vector2f(575, 10));
  bottomB.setPosition(32, 652);
  topWallVec.push_back(bottomB);
  sf::RectangleShape bottomMW1(sf::Vector2f(137, 15));
  bottomMW1.setPosition(250, 410);
  topWallVec.push_back(bottomMW1);
  sf::RectangleShape bottomMW2(sf::Vector2f(15, 75));
  bottomMW2.setPosition(312, 410);
  topWallVec.push_back(bottomMW2);
  sf::RectangleShape bottomMW3(sf::Vector2f(137, 15));
  bottomMW3.setPosition(250, 532);
  topWallVec.push_back(bottomMW3);
  sf::RectangleShape bottomMW4(sf::Vector2f(15, 75));
  bottomMW4.setPosition(312, 532);
  topWallVec.push_back(bottomMW4);

  // Track whether the game is running
  bool paused = true;
  bool endGameLose = false;
  bool endGameWin = false;
  // Keep Track of Time
  // float timeRemaining = 6.0f;
  Clock clock;
  Clock timer;
  float dt;

  // Make a PAC sprite
  Texture texturePacMan;
  texturePacMan.loadFromFile("..\\graphics\\pacman.bmp");
  Sprite spritePacMan;
  spritePacMan.setTexture(texturePacMan);
  spritePacMan.setPosition(10, 10);
  // Position PAC
  FloatRect pacRect = spritePacMan.getLocalBounds();
  spritePacMan.setOrigin(pacRect.left + pacRect.width / 2.0f, pacRect.top + pacRect.height / 2.0f);
  spritePacMan.setPosition(641 / 2.0f, (728 / 2.0f) + 145);
  // PAC Movement
  float pacSpeed = 100.0f;
  Vector2f velocity;
  int directionPacMan = 0;

  // bool for ghost
  bool blueGhostActive = false;
  bool blueGhostCollision = false;
  bool power = false;

  // Make four Ghost sprite
  Texture textureBlueGhost;
  textureBlueGhost.loadFromFile("..\\graphics\\blue_ghost.bmp");
  Texture textureOrangeGhost;
  textureOrangeGhost.loadFromFile("..\\graphics\\orange_ghost.bmp");
  Texture texturePinkGhost;
  texturePinkGhost.loadFromFile("..\\graphics\\pink_ghost.bmp");
  Texture textureRedGhost;
  textureRedGhost.loadFromFile("..\\graphics\\red_ghost.bmp");
  // Make Sprites for each Ghost
  Sprite spriteBlueGhost;
  spriteBlueGhost.setTexture(textureBlueGhost);
  Sprite spriteOrangeGhost;
  spriteOrangeGhost.setTexture(textureOrangeGhost);
  Sprite spritePinkGhost;
  spritePinkGhost.setTexture(texturePinkGhost);
  Sprite spriteRedGhost;
  spriteRedGhost.setTexture(textureRedGhost);
  // Position each Ghost
  spriteBlueGhost.setPosition(304, 247);
  spriteOrangeGhost.setPosition(304, 247);
  spritePinkGhost.setPosition(304, 247);
  spriteRedGhost.setPosition(304, 247);
  // Ghost Speed
  float blueGhostSpeed = 100.0f;
  int randomStartSpeedBlue = 1 + rand() % 4;
  float orangeGhostSpeed = 100.0f;
  int randomStartSpeedOrange = 1 + rand() % 4;
  float pinkGhostSpeed = 100.0f;
  int randomStartSpeedPink = 1 + rand() % 4;
  float redGhostSpeed = 100.0f;
  int randomStartSpeedRed = 1 + rand() % 4;

  // Ghost Object Array
  vector<Sprite> ghostVec;
  ghostVec.push_back(spriteBlueGhost);
  ghostVec.push_back(spriteOrangeGhost);
  ghostVec.push_back(spritePinkGhost);
  ghostVec.push_back(spriteRedGhost);

  // Draw Power Boost Circles
  vector<CircleShape> powerBoostVector;
  CircleShape powerBoost1(7);
  powerBoost1.setPosition(55, 90);
  powerBoostVector.push_back(powerBoost1);
  CircleShape powerBoost2(7);
  powerBoost2.setPosition(568, 90);
  powerBoostVector.push_back(powerBoost2);
  CircleShape powerBoost3(7);
  powerBoost3.setPosition(55, 500);
  powerBoostVector.push_back(powerBoost3);
  CircleShape powerBoost4(7);
  powerBoost4.setPosition(568, 500);
  powerBoostVector.push_back(powerBoost4);

  // Draw Coins
  vector<CircleShape> circleVecTop;
  vector<CircleShape> circleVecBottom;

  vector<CircleShape> circleVectorGood;

  // draw coins in top area
  for (int i = 0; i < 26; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      CircleShape coin(10);
      coin.setPosition(58 + 20.5 * i, 53 + 20.5 * j);
      circleVecTop.push_back(coin);
    }
  }
  // draw coins in bottom area
  for (int i = 0; i < 26; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      CircleShape coin(9);
      coin.setPosition(58 + 20.5 * i, 442 + 20.5 * j);
      circleVecBottom.push_back(coin);
    }
  }
  // draw coins in the mid area (the two lines)
  for (int i = 0; i < 11; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      CircleShape coin(11);
      coin.setPosition(159 + 310 * j, 215 + 20.5 * i);
      circleVectorGood.push_back(coin);
    }
  }

  // Keep the coins that are not intersecting the walls in another vector
  bool coinIntersect = false;
  for (int i = 0; i < circleVecTop.size(); i++)
  {
    for (int j = 0; j < topWallVec.size(); j++)
    {
      if (circleVecTop[i].getGlobalBounds().intersects(topWallVec[j].getGlobalBounds()))
      {
        coinIntersect = true;
      }
    }
    if (coinIntersect == false)
    {
      circleVectorGood.push_back(circleVecTop[i]);
    }
    coinIntersect = false;
  }

  for (int i = 0; i < circleVecBottom.size(); i++)
  {
    for (int j = 0; j < topWallVec.size(); j++)
    {
      if (circleVecBottom[i].getGlobalBounds().intersects(topWallVec[j].getGlobalBounds()) || circleVecBottom[i].getGlobalBounds().intersects(spritePacMan.getGlobalBounds()))
      {
        coinIntersect = true;
      }
    }
    if (coinIntersect == false)
    {
      circleVectorGood.push_back(circleVecBottom[i]);
    }
    coinIntersect = false;
  }

  // Resize coin radius size to small
  for (int i = 0; i < circleVectorGood.size(); i++)
  {
    circleVectorGood[i].setRadius(2);
  }
  // while loop for the game
  while (window.isOpen())
  {
    Event event;
    // while loop for the pollevent
    while (window.pollEvent(event))
    {
      if (event.type == Event::Closed)
        // Quit the game when the window is closed
        window.close();
    }
    // if esp key is pressed, then close window
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
      window.close();
    }
    // if enter key is pressed, then start the game and set pac man position again.
    if (Keyboard::isKeyPressed(Keyboard::Return))
    {
      paused = false;
      spritePacMan.setPosition(641 / 2.0f, (728 / 2.0f) + 145);
    }
    // start clock.
    Time dt = clock.restart();
    // set ghost directions and change direction when collide with wall
    if (!paused)
    {
      setDirection(randomStartSpeedBlue, ghostVec[0], blueGhostSpeed, dt);
      setDirection(randomStartSpeedOrange, ghostVec[1], orangeGhostSpeed, dt);
      setDirection(randomStartSpeedPink, ghostVec[2], pinkGhostSpeed, dt);
      setDirection(randomStartSpeedRed, ghostVec[3], redGhostSpeed, dt);

      for (unsigned int i = 0; i < topWallVec.size(); i++)
      {

        if ((ghostVec[0].getGlobalBounds()).intersects(topWallVec[i].getGlobalBounds()))
        {
          resetDirection(ghostVec[0], randomStartSpeedBlue);
          randomStartSpeedBlue = 1 + rand() % 4;
        }
        else if ((ghostVec[1].getGlobalBounds()).intersects(topWallVec[i].getGlobalBounds()))
        {
          resetDirection(ghostVec[1], randomStartSpeedOrange);
          randomStartSpeedOrange = 1 + rand() % 4;
        }
        else if ((ghostVec[2].getGlobalBounds()).intersects(topWallVec[i].getGlobalBounds()))
        {
          resetDirection(ghostVec[2], randomStartSpeedPink);
          randomStartSpeedPink = 1 + rand() % 4;
        }
        else if ((ghostVec[3].getGlobalBounds()).intersects(topWallVec[i].getGlobalBounds()))
        {
          resetDirection(ghostVec[3], randomStartSpeedRed);
          randomStartSpeedRed = 1 + rand() % 4;
        }
      }
      // tunnel for pacman
      if (spritePacMan.getPosition().x < 0)
      {
        spritePacMan.setPosition(641, spritePacMan.getPosition().y);
      }
      else if (spritePacMan.getPosition().x > 641)
      {
        spritePacMan.setPosition(0, spritePacMan.getPosition().y);
      }
    }

    velocity.x = 0.f;
    velocity.y = 0.f;
    // update pacman direction
    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
      directionPacMan = 1;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
      directionPacMan = 2;
    }
    if (Keyboard::isKeyPressed(Keyboard::Up))
    {
      directionPacMan = 3;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down))
    {
      directionPacMan = 4;
    }
    // set pac man direction
    for (unsigned int i = 0; i < topWallVec.size(); i++)
    {
      if (spritePacMan.getGlobalBounds().intersects(topWallVec[i].getGlobalBounds()))
      {
        int oldDirection = directionPacMan;
        directionPacMan = 0;
        switch (oldDirection)
        {
        case (1):
          spritePacMan.move(1, 0);
          break;
        case (2):
          spritePacMan.move(-1, 0);
          break;
        case (3):
          spritePacMan.move(0, 1);
          break;
        case (4):
          spritePacMan.move(0, -1);
          break;
        }
      }
    }

    // Update pacman positoin

    switch (directionPacMan)
    {
    case (1):
      velocity.x += -pacSpeed * dt.asSeconds();
      break;
    case (2):
      velocity.x += pacSpeed * dt.asSeconds();
      break;
    case (3):
      velocity.y += -pacSpeed * dt.asSeconds();
      break;
    case (4):
      velocity.y += pacSpeed * dt.asSeconds();
      break;
    }

    spritePacMan.move(velocity);

    // Ghost & PacMan Contact
    for (int i = 0; i < ghostVec.size(); i++)
    {
      if (ghostVec[i].getGlobalBounds().intersects(spritePacMan.getGlobalBounds()))
      {
        endGameLose = true;
      }
    }
    // if pac man touches powerBoost, then start new timer
    for (int i = 0; i < powerBoostVector.size(); i++)
    {
      if (spritePacMan.getGlobalBounds().intersects(powerBoostVector[i].getGlobalBounds()))
      {
        powerBoostVector.erase(powerBoostVector.begin() + i);
        timer.restart();
      }
    }
    Time powerTimer = timer.getElapsedTime();
    // if timer smaller than 5 seconds, pac man can eat ghosts and erase ghost
    if (powerTimer.asSeconds() <= 5)
    {
      power = true;
      endGameLose = false;
      for (int j = 0; j < ghostVec.size(); j++)
      {
        if (spritePacMan.getGlobalBounds().intersects(ghostVec[j].getGlobalBounds()))
        {
          ghostVec.erase(ghostVec.begin() + j);
        }
      }
    }
    else
    {
      power = false;
    }

    // Get Score
    for (int i = 0; i < circleVectorGood.size(); i++)
    {
      if (spritePacMan.getGlobalBounds().intersects(circleVectorGood[i].getGlobalBounds()))
      {
        circleVectorGood.erase(circleVectorGood.begin() + i);

        gameScore += 1;

        scoreText.setString(to_string(gameScore));
      }
    }

    if (gameScore == 244)
    {
      endGameWin = true;
    }

    // Clear everything from the last frame
    window.clear();
    window.draw(spriteBackground);
    window.draw(spritePacMan);
    // draw ghosts from ghost vector
    for (int i = 0; i < ghostVec.size(); i++)
    {
      window.draw(ghostVec[i]);
    }
    // draw all power boost
    for (int i = 0; i < powerBoostVector.size(); i++)
    {
      window.draw(powerBoostVector[i]);
    }
    // draw score
    window.draw(scoreText);
    // draw all coins in circleVectorGood
    for (int i = 0; i < circleVectorGood.size(); i++)
    {
      window.draw(circleVectorGood[i]);
    }
    if (paused)
    {
      window.draw(spriteStartBackground);
      window.draw(startText);
    }
    // if you lose, end game
    if (endGameLose == true && power == false)
    {
      window.clear();
      window.draw(spriteStartBackground);
      window.draw(endTextLose);
    }
    // if you win, end game
    if (endGameWin == true)
    {
      window.clear();
      window.draw(spriteStartBackground);
      window.draw(endTextWin);
    }

    window.display();
  }
}