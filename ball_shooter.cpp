#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>

using namespace sf;
using namespace std;

void update(RenderWindow &window, CircleShape &player, vector<CircleShape> &projectiles, CircleShape &projectile, vector<RectangleShape> &enemies, RectangleShape &enemy, int &enemySpawnTimer, int &projectileSpawnTimer);
void draw(RenderWindow &window, CircleShape &player, vector<CircleShape> &projectiles, vector<RectangleShape> &enemies);
void updateProjectiles(CircleShape &player, vector<CircleShape> &projectiles, CircleShape &projectile, int &projectileSpawnTimer);
void updateEnemies(RenderWindow &window, vector<RectangleShape> &enemies, RectangleShape &enemy, int &enemySpawnTimer);
void updateOnCollision(vector<CircleShape> &projectiles, vector<RectangleShape> &enemies);

int main() {

    srand(time(NULL));

    RenderWindow window(VideoMode(800, 520), "Ball Shooter");
    window.setFramerateLimit(60);

    CircleShape player(55.f);
    player.setFillColor(Color::Blue), player.setPosition(window.getSize().x/2.f - player.getRadius(), window.getSize().y - player.getRadius()*2.f - 15.f);

    CircleShape projectile(10.f);
    projectile.setFillColor(Color::Red);

    vector<CircleShape> projectiles;

    RectangleShape enemy(Vector2f(60.f, 60.f));
    enemy.setFillColor(Color::Green);

    vector<RectangleShape> enemies;

    int projectileSpawnTimer = 0, enemySpawnTimer = 0; //delaying times

    while (window.isOpen()) {

        Event event;
        while(window.pollEvent(event)) if (event.type == Event::Closed) window.close();

        update(window, player, projectiles, projectile, enemies, enemy, enemySpawnTimer, projectileSpawnTimer);

        draw(window, player, projectiles, enemies);
    }
    return 0;
}

void update(RenderWindow &window, CircleShape &player, vector<CircleShape> &projectiles, CircleShape &projectile, vector<RectangleShape> &enemies, RectangleShape &enemy, int &enemySpawnTimer, int &projectileSpawnTimer) {
    updateProjectiles(player, projectiles, projectile, projectileSpawnTimer);

    player.setPosition(Mouse::getPosition(window).x - player.getRadius(), player.getPosition().y); //update player

    updateEnemies(window, enemies, enemy, enemySpawnTimer);

    updateOnCollision(projectiles, enemies);
}

void draw(RenderWindow &window, CircleShape &player, vector<CircleShape> &projectiles, vector<RectangleShape> &enemies) {
    window.clear();

    window.draw(player);

    for(CircleShape &projectile :  projectiles) window.draw(projectile);

    for(RectangleShape &enemy :  enemies) window.draw(enemy);

    window.display();
}

void updateProjectiles(CircleShape &player, vector<CircleShape> &projectiles, CircleShape &projectile, int &projectileSpawnTimer) {
    projectileSpawnTimer++;

    projectile.setPosition(player.getPosition().x + player.getRadius() - projectile.getRadius(), player.getPosition().y - projectile.getRadius()*2);

    if(projectileSpawnTimer >= 7 && Mouse::isButtonPressed(Mouse::Left)) {
        projectileSpawnTimer = 0;
        projectiles.push_back(projectile);
    }

    for(size_t i = 0; i < projectiles.size(); i++) {
        projectiles[i].move(0.f, -12.f);

        if(projectiles[i].getPosition().y <= 0.f) projectiles.erase(projectiles.begin() + i);
    }
}

void updateEnemies(RenderWindow &window, vector<RectangleShape> &enemies, RectangleShape &enemy, int &enemySpawnTimer) {
    enemySpawnTimer++;

    if(enemySpawnTimer == 20) {
        enemySpawnTimer = 0;

        enemy.setPosition(rand() % int(window.getSize().x - enemy.getSize().x), 0.f);
        enemies.push_back(enemy);
    }

    for(size_t i = 0; i < enemies.size(); i++) {
        enemies[i].move(0.f, 7.f);

        if(enemies[i].getPosition().y >= window.getSize().y) enemies.erase(enemies.begin() + i);
    }
}

void updateOnCollision(vector<CircleShape> &projectiles, vector<RectangleShape> &enemies) {
    for(size_t i = 0; i < projectiles.size(); i++) {
        for(size_t j = 0; j < enemies.size(); j++) {
            if(projectiles[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds())) {
                projectiles.erase(projectiles.begin() + i), enemies.erase(enemies.begin() + j);
                break;
            }
        }
    }
}
