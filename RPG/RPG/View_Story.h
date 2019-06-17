#pragma once
#include "View.h"
#include "Sprite.h"
#include "Text.h"

struct Conversation {
	int player;
	int length;
	bool firstPlayer;
};

class View_Story : public View {
public:
	View_Story(ViewManager*);
	~View_Story();

	void Activate();
	void Deactivate();

	void Update();
	void Draw();
	void Position();
	void Load(int);

	void Interact(sf::Event::KeyEvent);
	void Escape(sf::Event::KeyEvent);
private:
	int conversation = 0;
	int player;
	bool activeSpeaker;
	int conversationLength;
	sf::Sprite sprite[2];
	Text text[2];
	std::vector<std::string> texts;
	std::vector<Conversation> conversations;

	void LoadConversation();
};