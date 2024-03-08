#include <SFML/Graphics.hpp>
using namespace sf;

void update(CircleShape &target, CircleShape &ball, RenderWindow &window, bool &moveToRight, bool &isBallMovingUpward);
void draw(RenderWindow &Window, CircleShape &target, CircleShape &ball);
void updateTarget(CircleShape &target, RenderWindow &window, bool &moveToRight);
void updateBall(CircleShape &ball, CircleShape &target, RenderWindow &window, bool &isBallMovingUpward);

int main() {

    RenderWindow window(VideoMode(640, 400), "Simple shoot-the-target game");
    window.setFramerateLimit(60);

    CircleShape target(50);
    target.setFillColor(Color::Red), target.setPosition(0.f, 8.f);

    CircleShape ball(15.f);
    ball.setFillColor(Color::Blue), ball.setPosition(0.f, window.getSize().y - ball.getRadius() * 3.f);

    bool moveToRight = true, isBallMovingUpward = false;
    
    while(window.isOpen()) {

        Event event;
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) window.close();
        
            if(event.KeyPressed && event.key.code == Keyboard::Escape) window.close();
        }

        update(target, ball, window, moveToRight, isBallMovingUpward);
        draw(window, target, ball);
    }
    return 0;
}

void update(CircleShape &target, CircleShape &ball, RenderWindow &window, bool &moveToRight, bool &isBallMovingUpward) {
    updateTarget(target, window, moveToRight);

    updateBall(ball, target, window, isBallMovingUpward);
}

void draw(RenderWindow &window, CircleShape &target, CircleShape &ball) {
    window.clear();
    window.draw(target), window.draw(ball);
    window.display();
}

void updateTarget(CircleShape &target, RenderWindow &window, bool &moveToRight) {
    if(target.getPosition().x <= 0) moveToRight = true;
    else if(target.getPosition().x + target.getRadius() * 2.f >= window.getSize().x) moveToRight = false;

    moveToRight ? target.move(5.f, 0.f) : target.move(-5.f, 0.f);
}

void updateBall(CircleShape &ball, CircleShape &target, RenderWindow &window, bool &isBallMovingUpward) {
    if(Mouse::isButtonPressed(Mouse::Left)) isBallMovingUpward = true;

    isBallMovingUpward ? ball.move(0.f, -5.f) : ball.setPosition(Mouse::getPosition(window).x >= 0.f && Mouse::getPosition(window).x + ball.getRadius() * 2.f <= window.getSize().x ? Mouse::getPosition(window).x : ball.getPosition().x, ball.getPosition().y);

    if(ball.getPosition().y <= 0 || ball.getGlobalBounds().intersects(target.getGlobalBounds())) {
        isBallMovingUpward = false;
        ball.setPosition(ball.getPosition().x, window.getSize().y - ball.getRadius() * 3.f);
    }
}
