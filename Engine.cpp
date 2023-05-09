#include "Engine.h"

int PARTICLE_COUNT = 5;

Engine::Engine() {
	// Call create on m_window to populate the RenderWindow member m_window
	sf::RenderWindow m_Window(sf::VideoMode::getDesktopMode(), "Particle Launcher");
	// You can assign a custom resolution or you can call VideoMode::getDesktopMode() to get the screen resolution
}

void Engine::run() {
	Clock timePerFrame;
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { m_Window.getSize().x / 2,m_Window.getSize().y / 2});
	p.unitTests();
	cout << "Unit tests complete. Starting engine..." << endl;
	while (m_Window.isOpen()) {
		timePerFrame.restart();
		input();
		update(timePerFrame.getElapsedTime().asSeconds());
		draw();
	}
}

void Engine::input() {
	// Test for some sort of window input
		// Test if that input was trying to close out of the window
			// If so, close the window
		// Otherwise, check for a left click
	Event event;
	if (event.type == Event::Closed) {
		m_Window.close();
	}
	else if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			sf::Vector2i pixelPos = sf::Mouse::getPosition(m_Window);
			sf::Vector2f mouseClickPosition = m_Window.mapPixelToCoords(pixelPos, m_Window.getView());
			for (int i = 0; i < PARTICLE_COUNT; ++i)
			{
				Particle new_item(m_Window, (rand() % 26) + 25, mouseClickPosition);
				m_particles.push_back(new_item);
			}
		}
	}

}

void Engine::update(float dtAsSeconds) {
	for (int i = 0; i < m_particles.size(); ++i) {
		if (m_particles.at(i).getTTL() <= 0) {
			m_particles.erase(m_particles.begin() + i);
			--i;
		}
		else {
			m_particles.at(i).update(dtAsSeconds);
		}
	}

}

void Engine::draw() {
	m_Window.clear();
	for (int i = 0; i < m_particles.size(); ++i) {
		m_Window.draw(m_particles.at(i));
	}
	m_Window.display();

}