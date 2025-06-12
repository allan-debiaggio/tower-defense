#include "HUDView.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h> // for getcwd

// Custom EllipseShape for glossy heart
class EllipseShape : public sf::Shape
{
public:
  EllipseShape(float radiusX, float radiusY) : m_radiusX(radiusX), m_radiusY(radiusY)
  {
    update();
  }
  void setRadii(float radiusX, float radiusY)
  {
    m_radiusX = radiusX;
    m_radiusY = radiusY;
    update();
  }
  std::size_t getPointCount() const override { return 40; }
  sf::Vector2f getPoint(std::size_t index) const override
  {
    static const float pi = 3.141592654f;
    float angle = index * 2 * pi / getPointCount() - pi / 2;
    float x = std::cos(angle) * m_radiusX;
    float y = std::sin(angle) * m_radiusY;
    return sf::Vector2f(m_radiusX + x, m_radiusY + y);
  }

private:
  float m_radiusX, m_radiusY;
};

HUDView::HUDView(unsigned int width, unsigned int tileSize)
    : m_width(width), m_tileSize(tileSize)
{
  // Print current working directory for debugging
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != nullptr)
  {
    std::cout << "[HUDView] Current working directory: " << cwd << std::endl;
  }
  else
  {
    std::cerr << "[HUDView] Error getting current working directory." << std::endl;
  }
  // Try to load coin texture (PNG version of SVG)
  if (m_coinTexture.loadFromFile("assets/level_1/v2/ui_coin_display.png"))
  {
    m_coinTextureLoaded = true;
  }
  else
  {
    std::cerr << "[HUDView] Warning: Could not load coin image. Using fallback." << std::endl;
  }
  // Load heart texture
  if (m_heartTexture.loadFromFile("/Users/anatoliychubais/Desktop/Low_Level_Programming/tower_defense/presentation/assets/images/heart.png"))
  {
    m_heartTextureLoaded = true;
    std::cout << "[HUDView] Heart texture loaded successfully." << std::endl;
  }
  else
  {
    std::cerr << "[HUDView] Warning: Could not load heart image. Using fallback." << std::endl;
  }
}

// Helper: Draw a Mario-style coin icon
void HUDView::drawCoin(sf::RenderWindow &window, float x, float y) const
{
  // Main coin body
  sf::CircleShape coin(14);
  coin.setFillColor(sf::Color(255, 220, 40));   // Mario gold
  coin.setOutlineColor(sf::Color(255, 140, 0)); // Orange border
  coin.setOutlineThickness(4);
  coin.setPosition(sf::Vector2f(x, y));
  window.draw(coin);
  // Highlight
  sf::CircleShape highlight(6);
  highlight.setFillColor(sf::Color(255, 255, 255, 180));
  highlight.setPosition(sf::Vector2f(x + 7, y + 4));
  window.draw(highlight);
  // Inner ellipse for shine
  sf::RectangleShape shine(sf::Vector2f(4, 10));
  shine.setFillColor(sf::Color(255, 255, 255, 120));
  shine.setPosition(sf::Vector2f(x + 10, y + 6));
  shine.setRotation(sf::degrees(-20));
  window.draw(shine);
}

// Helper: Draw a Mario-style heart (rounded, outlined, glossy)
void HUDView::drawHeart(sf::RenderWindow &window, float x, float y) const
{
  if (m_heartTextureLoaded)
  {
    sf::Sprite heartSprite(m_heartTexture);
    heartSprite.setScale(sf::Vector2f(32.0f / m_heartTexture.getSize().x, 32.0f / m_heartTexture.getSize().y));
    heartSprite.setPosition(sf::Vector2f(x, y));
    window.draw(heartSprite);
    return;
  }
  sf::Color heartColor(255, 60, 90);
  sf::Color outlineColor(128, 0, 0);
  // Outline (drawn first, slightly larger)
  float outlineThickness = 3.0f;
  float ox = x - outlineThickness;
  float oy = y - outlineThickness;
  // Top lobes outline
  sf::CircleShape leftOutline(10 + outlineThickness);
  leftOutline.setScale(sf::Vector2f(1.15f, 1.0f));
  leftOutline.setFillColor(outlineColor);
  leftOutline.setPosition(sf::Vector2f(ox, oy));
  sf::CircleShape rightOutline(10 + outlineThickness);
  rightOutline.setScale(sf::Vector2f(1.15f, 1.0f));
  rightOutline.setFillColor(outlineColor);
  rightOutline.setPosition(sf::Vector2f(ox + 12, oy));
  // Bottom outline (5-point convex for roundness)
  sf::ConvexShape bottomOutline;
  bottomOutline.setPointCount(5);
  bottomOutline.setPoint(0, sf::Vector2f(ox + 2, oy + 12));
  bottomOutline.setPoint(1, sf::Vector2f(ox + 30, oy + 12));
  bottomOutline.setPoint(2, sf::Vector2f(ox + 26, oy + 28));
  bottomOutline.setPoint(3, sf::Vector2f(ox + 16, oy + 36));
  bottomOutline.setPoint(4, sf::Vector2f(ox + 6, oy + 28));
  bottomOutline.setFillColor(outlineColor);
  window.draw(leftOutline);
  window.draw(rightOutline);
  window.draw(bottomOutline);
  // Main heart
  sf::CircleShape leftCircle(10);
  leftCircle.setScale(sf::Vector2f(1.0f, 1.0f));
  leftCircle.setFillColor(heartColor);
  leftCircle.setPosition(sf::Vector2f(x, y));
  sf::CircleShape rightCircle(10);
  rightCircle.setScale(sf::Vector2f(1.0f, 1.0f));
  rightCircle.setFillColor(heartColor);
  rightCircle.setPosition(sf::Vector2f(x + 12, y));
  sf::ConvexShape bottom;
  bottom.setPointCount(5);
  bottom.setPoint(0, sf::Vector2f(x + 2, y + 12));
  bottom.setPoint(1, sf::Vector2f(x + 30, y + 12));
  bottom.setPoint(2, sf::Vector2f(x + 26, y + 28));
  bottom.setPoint(3, sf::Vector2f(x + 16, y + 36));
  bottom.setPoint(4, sf::Vector2f(x + 6, y + 28));
  bottom.setFillColor(heartColor);
  // Glossy highlight
  EllipseShape gloss(6, 3);
  gloss.setFillColor(sf::Color(255, 255, 255, 180));
  gloss.setPosition(sf::Vector2f(x + 10, y + 6));
  gloss.setRotation(sf::degrees(-18));
  // Draw main heart
  window.draw(leftCircle);
  window.draw(rightCircle);
  window.draw(bottom);
  window.draw(gloss);
}

// Helper: Draw a Mario-style wave/progress bar (top right)
void HUDView::drawWaveBar(sf::RenderWindow &window, float x, float y, int currentWave, int totalWaves) const
{
  float barWidth = 260.0f;
  float barHeight = 22.0f;
  float progress = (totalWaves > 0) ? float(currentWave) / float(totalWaves) : 0.f;
  sf::RectangleShape bg(sf::Vector2f(barWidth, barHeight));
  bg.setFillColor(sf::Color(30, 144, 255));
  bg.setOutlineColor(sf::Color(0, 0, 128));
  bg.setOutlineThickness(3);
  bg.setPosition(sf::Vector2f(x, y));
  window.draw(bg);
  sf::RectangleShape fg(sf::Vector2f(barWidth * progress, barHeight));
  fg.setFillColor(sf::Color(255, 220, 40));
  fg.setPosition(sf::Vector2f(x, y));
  window.draw(fg);
  sf::Font font;
  if (font.openFromFile("/System/Library/Fonts/Supplemental/Arial Bold.ttf"))
  {
    std::string labelStr = "Wave " + std::to_string(currentWave) + "/" + std::to_string(totalWaves);
    sf::Text label(font, labelStr, 22);
    label.setFillColor(sf::Color(255, 255, 255));
    label.setOutlineColor(sf::Color(0, 0, 128));
    label.setOutlineThickness(2);
    label.setStyle(sf::Text::Bold);
    auto bounds = label.getLocalBounds();
    label.setPosition(sf::Vector2f(x + barWidth / 2 - bounds.size.x / 2, y + barHeight / 2 - bounds.size.y / 2 - 2));
    window.draw(label);
  }
}

void HUDView::render(sf::RenderWindow &window, const Player &player, const LevelManager &level) const
{
  // Font
  sf::Font font;
  if (!font.openFromFile("/System/Library/Fonts/Supplemental/Arial Bold.ttf"))
  {
    std::cerr << "[HUDView] Warning: Could not load font." << std::endl;
  }
  float margin = 24.0f;
  float y = 24.0f;
  float x = margin;
  // Coins (top left)
  drawCoin(window, x, y);
  x += 44.0f;
  sf::Text coinsLabel(font, "Coins:", 22);
  coinsLabel.setFillColor(sf::Color(255, 220, 40));
  coinsLabel.setOutlineColor(sf::Color(128, 64, 0));
  coinsLabel.setOutlineThickness(2);
  coinsLabel.setStyle(sf::Text::Bold);
  coinsLabel.setPosition(sf::Vector2f(x, y - 2));
  window.draw(coinsLabel);
  x += coinsLabel.getLocalBounds().size.x + 12.0f;
  sf::Text coinsValue(font, std::to_string(player.getCoins()), 22);
  coinsValue.setFillColor(sf::Color(255, 255, 255));
  coinsValue.setOutlineColor(sf::Color(128, 64, 0));
  coinsValue.setOutlineThickness(2);
  coinsValue.setStyle(sf::Text::Bold);
  coinsValue.setPosition(sf::Vector2f(x, y - 2));
  window.draw(coinsValue);
  x += coinsValue.getLocalBounds().size.x + 32.0f;
  // Hearts (one per life)
  int lives = player.getLives();
  for (int i = 0; i < lives; ++i)
  {
    drawHeart(window, x, y - 4);
    x += 36.0f; // heart width + spacing (wider hearts)
  }
  // Wave Progress Bar (top right)
  int currentWave = level.getWaveManager().getCurrentWave();
  int totalWaves = level.getWaveManager().hasNextWave() ? level.getWaveManager().getCurrentWave() + 1 : level.getWaveManager().getCurrentWave();
  totalWaves = std::max(totalWaves, 1); // avoid div by zero
  float barWidth = 260.0f;
  float barX = m_width - barWidth - margin;
  float barY = margin;
  drawWaveBar(window, barX, barY, currentWave, totalWaves);
}