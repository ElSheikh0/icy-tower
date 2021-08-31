#include <SFML\Graphics.hpp>
#include<iostream>
#include<SFML\Audio.hpp>
#include <fstream>
#include <sstream>
#include <windows.h>
 
#define Max_main_menu 7


using namespace std;
using namespace sf;
int page_number;


sf::Vector2f pos(320, 750);//posetion to player
sf::Vector2f vel(0, 0);   // player velocity (per frame)
sf::Vector2f gravity(0, 0.5f);   // gravity (per frame)

Vector2i bodysize(65, 55);
Vector2f Posetion(190, 500);

const float maxfall = 3;   // max fall velocity
const float runacc = .25f;  // run acceleratio
const float maxrun = 2.5f;   // max run velocity
const float jumpacc = -2.5;   // jump acceleration
const unsigned int jumpframes = 10;   // number of frames to accelerate in
unsigned int jumpcounter = 0;    // counts the number of frames where you can still accelerate
int sel_player = 0;
int scoree = 0;
int score = 0;
bool hid_menu = false;
bool hid = true;
bool hid_play = true;
bool end1 = true;
bool level2 = true;
bool level3 = true;
bool level4 = true;
int bonus = 0;
Clock last;

int compo;
Vector2f sd(1080, 800);       //for window

 
string num_step;
String score_string;
int highscoree;

struct location //structu for steps
{
	int x, y, w, h;
}floorlocation[1000];

class Main_menu //menuu
{
public:
	Main_menu(float width, float hight);


	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();


	int mainMenuPressed()
	{
		return mainMenuSelected;
	}

	~Main_menu();

private:
	int mainMenuSelected;
	sf::Font font;
	sf::Text mainMenu[Max_main_menu];
};



Main_menu::Main_menu(float width, float height)
{
	if (!font.loadFromFile("font/DSSnowfall.ttf")) {}
	
	//play
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(sf::Color::Blue);
	mainMenu[0].setString("PLAY GAME");
	mainMenu[0].setCharacterSize(35);
	mainMenu[0].setPosition(sf::Vector2f(600, 470));
	mainMenu[0].setScale(.9, 1);
	//INSTRUCTIONS
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color::White);
	mainMenu[1].setString("INSTRUCTIONS");
	mainMenu[1].setCharacterSize(35);
	mainMenu[1].setPosition(sf::Vector2f(600, 510));
	mainMenu[1].setScale(.9, 1);
	mainMenu[1].setOutlineThickness(.1);
	mainMenu[1].setOutlineColor(Color::White);

	//PROFILE
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color::White);
	mainMenu[2].setString("CREDITS");
	mainMenu[2].setCharacterSize(35);
	mainMenu[2].setPosition(sf::Vector2f(600, 550));
	mainMenu[2].setScale(.9, 1);
	mainMenu[2].setOutlineThickness(.1);
	mainMenu[2].setOutlineColor(Color::White);

	//HIGH SCORES
	mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(sf::Color::White);
	mainMenu[3].setString("ABOUT THE GAME");
	mainMenu[3].setCharacterSize(30);
	mainMenu[3].setPosition(sf::Vector2f(600, 590));
	mainMenu[3].setScale(.9, 1);
	mainMenu[3].setOutlineThickness(.1);
	mainMenu[3].setOutlineColor(Color::White);


	//options sound
	mainMenu[4].setFont(font);
	mainMenu[4].setFillColor(sf::Color::White);
	mainMenu[4].setString("OPTIONS SOUND");
	mainMenu[4].setCharacterSize(35);
	mainMenu[4].setPosition(sf::Vector2f(600, 630));
	mainMenu[4].setScale(.9, 1);
	mainMenu[4].setOutlineThickness(.1);
	mainMenu[4].setOutlineColor(Color::White);

	//exit
	mainMenu[5].setFont(font);
	mainMenu[5].setFillColor(sf::Color::White);
	mainMenu[5].setString("CHARACTERS");
	mainMenu[5].setCharacterSize(35);
	mainMenu[5].setPosition(sf::Vector2f(600, 670));
	mainMenu[5].setScale(.9, 1);
	mainMenu[5].setOutlineThickness(.1);
	mainMenu[5].setOutlineColor(Color::White);
	mainMenuSelected = 0;  //start from zero index (play)
	mainMenu[6].setFont(font);
	mainMenu[6].setFillColor(sf::Color::White);
	mainMenu[6].setString("EXIT");
	mainMenu[6].setCharacterSize(40);
	mainMenu[6].setPosition(sf::Vector2f(600, 710));
	mainMenu[6].setScale(.9, 1);
}


Main_menu::~Main_menu()
{
}


//***********Function of drawing main menu***************//
void Main_menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 7; i++)
	{
		window.draw(mainMenu[i]);
	}
}

//***********Function of moving up******************/
void Main_menu::moveUp()
{
	if (mainMenuSelected - 1 >= -1) // check if not on the first item (play)

	{
		mainMenu[mainMenuSelected].setScale(.9, 1);

		mainMenu[mainMenuSelected].setFillColor(sf::Color::White);  //change the pervious item's color

		mainMenuSelected--;  //move to the upper item       
		if (mainMenuSelected == -1)
		{
			mainMenuSelected = 6;
		}
		mainMenu[mainMenuSelected].setFillColor(sf::Color::Blue); //change the new item's color
		mainMenu[mainMenuSelected].setScale(1.2, 1);
	}
}

//***********Function of moving down******************/
void Main_menu::moveDown()
{
	if (mainMenuSelected + 1 <= Max_main_menu) //check if not on the last item (exit)

	{
		mainMenu[mainMenuSelected].setScale(.9, 1);
		mainMenu[mainMenuSelected].setFillColor(sf::Color::White);  //change the pervious item's color

		mainMenuSelected++;  //move to the lower item
		if (mainMenuSelected == 7)
		{
			mainMenuSelected = 0;
		}
		mainMenu[mainMenuSelected].setFillColor(sf::Color::Blue);           //change the new item's color
		mainMenu[mainMenuSelected].setScale(1.2, 1);
	}
}


//***********Function of moving up******************/

//***********start ******************/


//PlayerAnimation  class 
class Animation
{


public:
	IntRect uv_Rect; //we use uv_rect to crop one texture properly
	Animation(Texture* character, Vector2u ImageCount, float SwitchTime);
	void update(int row, float deltaTime, bool face_right); //It is the function used to update the PlayerAnimation  of the character in each frame
	~Animation();
private:
	Vector2u ImageCount; //number of rows and columns of image
	Vector2u CurrentImage; //the index of the accessed image
	float TotalTime, SwitchTime; //switch time:is the time taken to switch between two textures

};
Animation::Animation(Texture* character, Vector2u ImageCount, float SwitchTime)
{
	this->ImageCount = ImageCount; //we use keyword "this" to differentiate between the private variable and the parameter
	this->SwitchTime = SwitchTime; //we use keyword "this" to differentiate between the private variable and the parameter
	TotalTime = 0; //we initialize the total time of PlayerAnimation  to zero
	CurrentImage.x = 0; //we access to the start point of the texture
	uv_Rect.width = character->getSize().x / float(ImageCount.x); //calculate the width of a single texture
	uv_Rect.height = character->getSize().y / float(ImageCount.y); //calculate the height of a single texture
}
Animation::~Animation() {

}
void Animation::update(int row, float deltaTime, bool face_right) //It is the function used to update the PlayerAnimation  of the character in each frame
{
	CurrentImage.y = row; //we initialize the current image on the y-axis to the index of the row to get the suitable texture for each specific movement
	TotalTime += deltaTime; //we add the value of delta time to the current value of total time
	if (TotalTime >= SwitchTime)
	{
		TotalTime -= SwitchTime; //we subtract the value of switch time from the Total time  
		CurrentImage.x++; //we access to the next texture after the switch is done
		if (CurrentImage.x >= ImageCount.x) //when we reach the last point of the row , we return back to the start point 
		{
			CurrentImage.x = 0;
		}
	}
	if (face_right) //if the user presses left key,the image will be flipped
	{
		uv_Rect.left = CurrentImage.x * uv_Rect.width;
		uv_Rect.width = abs(uv_Rect.width);
	}
	else
	{
		uv_Rect.left = (CurrentImage.x + 1) * abs(uv_Rect.width);
		uv_Rect.width = -abs(uv_Rect.width);
	}
	uv_Rect.top = CurrentImage.y * uv_Rect.height;
}


//Player class
class Player
{

public:
 
	Player(Texture* character, Vector2u ImageCount, float SwitchTime, float speed);  //Note:we add the speed
		 //initializer list for object's PlayerAnimation 
	void update(float deltaTime, RenderWindow& window, int w, int x);
	~Player();

	Vector2f GetPosition()
	{
		return body.getPosition();
	}
	RectangleShape body;


private:
	Animation  PlayerAnimation; //Creating object
	unsigned int row; //there is no index in negative
	bool face_right;
	float speed;
	
};

Player::Player(Texture* character, Vector2u ImageCount, float SwitchTime, float speed) : //Note:we add the speed
	PlayerAnimation(character, ImageCount, SwitchTime) //initializer list for object's PlayerAnimation 
{
	this->speed = speed;
	face_right = true;
	body.setSize(Vector2f(bodysize.x, bodysize.y));

	body.setTexture(character);
}
Player::~Player() {

}

void Player::update(float deltaTime, RenderWindow& window, int w, int x) //We used a window here to handle events 
{
	// inputs
	bool left = false;
	bool right = false;
	bool jump = false;
	Event event;
	
	Vector2f movement(0, 0);
	//Moving
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		movement.x -= speed * deltaTime; //to let the speed increase every frame in the left direction
		left = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		
		movement.x += speed * deltaTime; //to let the speed increase every frame in the right direction
		right = true;
	}
	if ((Keyboard::isKeyPressed(Keyboard::Space))) //jumping without pressing any other key
	{
		jump = true;

	}
	
	
	if (movement.x == 0)  //we access to row 0 when the character isn't moving
	{
		row = 0; //ideal position of the character
	}
	else
	{
		row = 1; //we access to row 1 when the character is moving
		if (movement.x > 0)
			face_right = true; //the character is moving rightwards
		else
			face_right = false; //the character is moving leftwards
	}
	// now update the velocity by...
	pos += vel;
	
	
	// ...updating gravity
	vel += gravity;
	// ...capping gravity
	if (vel.y > maxfall)
		vel.y = maxfall;
	if (left) // running to the left
	{
		vel.x -= runacc;
	}
	else if (right)// running to the right
	{
		vel.x += runacc;
	}
	else // not running anymore; slowing down each frame
	{
		vel.x *= .0111;
	}
	// jumping left and rigth
	if (jump)
	{
		if (left)
		{
			face_right = false;
			row = 2;
		}
		if (right)
		{
			face_right = true;
			row = 2;
		}
		if (right == false && left == false)
		{
			row = 3;
		}
		
		else if (jumpcounter > 0) { // first few frames in the air
			vel.y += -.15;
			jumpcounter--;
		}
	}
	else // jump key released, stop acceleration
	{
		jumpcounter = 0;
	}
		// update the position
	body.setPosition(pos);

	
	

	PlayerAnimation.update(row, deltaTime, face_right);//calling update function from PlayerAnimation  object
	body.setTextureRect(PlayerAnimation.uv_Rect);
	//  for collision with steps
	if (vel.y >= 0)
	{
		for (int i = 0; i < 1000; i++)
		{
			if ((pos.x - 0.6 * bodysize.x > floorlocation[i].x)
				&& (pos.x - bodysize.x < floorlocation[i].x + floorlocation[i].w)
				&& (pos.y + 0.5 * bodysize.y > floorlocation[i].y)
				&& (pos.y + 0.5 * bodysize.y < floorlocation[i].y + floorlocation[i].h))
			{

				
				pos.x = pos.x;
				vel.y = 0;
				pos.y = floorlocation[i].y - 20;
				scoree = i * 10;
				

				

				if (Keyboard::isKeyPressed(Keyboard::Space))
				{
					vel.y += jumpacc * 4;
					jumpcounter = jumpframes;

					if (jumpcounter > 0)  // first few frames in the air
					{
						vel.y += jumpacc;
						jumpcounter--;
					}
					

					
				}
			}
		}
	}
}
Sound sound_sot, sound_jump, sound_hello, sound_pose, sound_play, sound_coll;



void GameOver()
{
	sf::RenderWindow window0(sf::VideoMode(600, 600), "SFML WORK!", Style::None);

	sf::SoundBuffer tryAgain;

	if (tryAgain.loadFromFile("falling.wav") == false)
	{
		//code here
	}
	sf::Sound t_again;
	t_again.setBuffer(tryAgain);
	t_again.play();



	Texture T_GameOver;
	T_GameOver.loadFromFile("images/Gover.png");
	Sprite s_GameOver(T_GameOver);
	std::fstream file;
	std::string highS;
	Text text9, text10, text11, text12;
	Font font1;
	font1.loadFromFile("font/actionj.ttf");
	text9.setFont(font1);  // to draw word "score : "
	text9.setCharacterSize(60); 
	text9.setFillColor(sf::Color::White); 
	text9.setPosition(50, 420);

	text10.setFont(font1);  // to draw word "high score :"
	text10.setCharacterSize(50); 
	text10.setFillColor(sf::Color::White); 
	text10.setPosition(50, 500);

	text11.setFont(font1);  // to draw word "player score number"
	text11.setCharacterSize(60); 
	text11.setFillColor(sf::Color::White); 
	text11.setPosition(400, 420);

	text12.setFont(font1);  // to draw word "high score number"
	text12.setCharacterSize(60); 
	text12.setFillColor(sf::Color::White); 
	text12.setPosition(450, 500);
	while (window0.isOpen())
	{
		sf::Event event;

		while (window0.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					window0.close();
					hid_menu = false;
					hid = false;
					end1 = false;
					break;


				}
				break;

			}
			file.open("hadi.txt", ios::in);
			getline(file, highS);

			file.close();
			highscoree = stoi(highS);

			if ((scoree ) > highscoree)
			{

				highscoree = (scoree );
				file.open("hadi.txt", std::ios::out);
				file << highscoree << endl;

				file.close();
			}

			text9.setString("score : ");

			text10.setString("high score : ");

			text11.setString(score_string);

			text12.setString(highS);

		}

		window0.clear();
		window0.draw(s_GameOver);
		window0.draw(text11);
		window0.draw(text12);
		window0.draw(text10);
		window0.draw(text9);



		window0.display();
	}
}


void how_to_play(RenderWindow& window)
{
	Texture t_how_play;
	t_how_play.loadFromFile("images/instructions.png");
	Sprite s_how_play;
	s_how_play.setTexture(t_how_play);
	
	
	window.clear(Color(0, 0, 0));
	
	window.draw(s_how_play);
	window.display();
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		hid_menu = false;
	}
}

void profiel(RenderWindow& window)
{
	Texture por;
	
	por.loadFromFile("final.jpg");
	Sprite s_por;
	s_por.setTexture(por);
	s_por.setScale(Vector2f(.562, .739));
	window.clear(Color(0, 0, 0));

	window.draw(s_por);
	window.display();
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		hid_menu = false;
	}
}
void profiel_game(RenderWindow& window) {
	Texture  por_game;
	por_game.loadFromFile("images/IMG_20210529_212726.jpg");
	
	Sprite  s_por_game;
	
	s_por_game.setTexture(por_game);
	window.clear();
	window.draw(s_por_game);
	

	window.display();
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		hid_menu = false;
	}
}


int main()
{
	//logo
	{
		Texture logo;

		 logo.loadFromFile("images/GEN_172.jpg");

		Sprite sp;
		sp.setTexture(logo);
		//sp.scale(0.4, 0.5); // My logo is quite big in fact (1st google result btw)

		int logoWidth = sp.getGlobalBounds().width;
		int logoHeight = sp.getGlobalBounds().height;

		// With the logo loaded, I know its size, so i create the window accordingly
		RenderWindow window(sf::VideoMode(logoWidth, logoHeight), "SFML", Style::None); // <- Important!! Style=None removes title

		// To close splash window by timeout, I just suppose you want something like this, don't you?
		Clock timer00;
		Time time5 = timer00.restart();

		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				// event loop is always needed
			}
			// Window closed by time
			time5 += timer00.restart();
			if (time5 >= sf::seconds(1.5f)) {
				window.close();
			}

			window.clear();
			window.draw(sp);
			window.display();
		}
	}


	/*****menue*******/
	Texture t20, esc, b2, b3;
	esc.loadFromFile("grey.png");
	b2.loadFromFile("blue-sky-clouds_1417-1850.jpg");
	Sprite escS(esc), b_2;
	b_2.setTexture(b2);
	b_2.setScale(Vector2f(2.5, 2.5));
	t20.loadFromFile("back.jpg");
	b3.loadFromFile("Screenshot (11).png");
	Sprite  back(t20), b30(b3);
	back.setScale(Vector2f(.6, .8));


	/* headddddddd */
	RectangleShape player_head(Vector2f(355.0f, 500)), player_head_2(Vector2f(355.0f, 500)), player_head_3(Vector2f(355.0f, 500));
	player_head.setPosition(350, -20);
	Texture playertex_head, playertex_head_2, playertex_head_3;
	playertex_head.loadFromFile("ju.png");
	playertex_head_2.loadFromFile("ju.png");
	playertex_head_3.loadFromFile("ju.png");

	player_head.setTexture(&playertex_head);
	player_head.setScale(Vector2f(.9, .9));
	player_head_2.setTexture(&playertex_head);
	player_head_2.setScale(Vector2f(.1, .1));
	player_head_2.setPosition(560, 460);
	player_head_3.setPosition(70, 0);
	player_head_3.setScale(Vector2f(.9, .9));
	player_head_3.setTexture(&playertex_head_3);
	Animation ani_head(&playertex_head, Vector2u(8, 1), 0.1f);
	Animation ani_head_2(&playertex_head_2, Vector2u(8, 1), 0.1f);
	Animation ani_head_3(&playertex_head_3, Vector2u(8, 1), 0.1f);

	int c0 = 460;
	Clock clock02;

	
	Texture por, por_game;
	por_game.loadFromFile("images/IMG_20210529_212726.jpg");
	por.loadFromFile("final.jpg");
	Sprite s_por, s_por_game;
	s_por.setTexture(por);
	s_por.setScale(Vector2f(.562, .739));
	s_por_game.setTexture(por_game);

		/*photo sounddddddddd */
	Texture music[7];
	Texture sound[7];
	for (int i = 0; i < 7; i++)
	{
		sound[i].loadFromFile(to_string(i) + ".png");
		music[i].loadFromFile(to_string(i) + ".png");
	}
	int counter = 3;
	Sprite musicsprite;
	musicsprite.setTexture(music[counter]);
	musicsprite.setPosition(680, 400);
	musicsprite.setScale(Vector2f(.9, .8));



	int counter2 = 3;
	Sprite soundsprite;
	soundsprite.setTexture(sound[counter2]);
	soundsprite.setPosition(680, 500);
	soundsprite.setScale(Vector2f(.9, .8));
	Font font_sound;
	font_sound.loadFromFile("font/Double_Bubble_shadow_italic.otf");

	Text soundtext[3];
	soundtext[0].setFont(font_sound);
	soundtext[0].setString("MUSIC");
	soundtext[0].setPosition(580, 415);
	soundtext[0].setCharacterSize(30);
	soundtext[0].setFillColor(sf::Color::Blue);
	soundtext[0].setScale(1.2, 1);
	soundtext[1].setFont(font_sound);
	soundtext[1].setString("SOUND");
	soundtext[1].setPosition(580, 515);
	soundtext[1].setCharacterSize(30);
	soundtext[2].setFont(font_sound);
	soundtext[2].setString("BACK");
	soundtext[2].setPosition(580, 600);
	soundtext[2].setCharacterSize(30);
	int sel = 0;

	/* sounddddddddddd */
		//////////////////////

	SoundBuffer menu, play_game, jump, jump2, hello, pose, alarm;
	menu.loadFromFile("menu.wav");
	play_game.loadFromFile("Elevator Music - Gaming Background Music (HD).wav");
	alarm.loadFromFile("19.wav");
	jump2.loadFromFile("jump_mid.wav");
	jump.loadFromFile("jump_lo.wav");
	hello.loadFromFile("hello.wav");
	pose.loadFromFile("pause.wav");
	Sound sound_sot, sound_jump, sound_hello, sound_pose, sound_play, sound_coll, sound_alarm;
	sound_alarm.setBuffer(alarm);

	sound_coll.setBuffer(jump2);
	sound_sot.setBuffer(menu);
	sound_hello.setBuffer(hello);
	sound_jump.setBuffer(jump);
	sound_pose.setBuffer(pose);
	sound_play.setBuffer(play_game);
	sound_sot.setLoop(true);
	sound_play.setLoop(true);
	sound_sot.play();
	sound_coll.setVolume(counter2 * 20);
	sound_jump.setVolume(counter2 * 20);
	sound_hello.setVolume(counter2 * 20);
	sound_pose.setVolume(counter2 * 20);
	sound_play.setVolume(counter2 * 5);
	sound_sot.setVolume(counter * 20);
	sound_alarm.setVolume(counter2 * 20);
	/////////////////


	/*select charecter*/
	Text player_ch[4];
	player_ch[0].setFont(font_sound);
	player_ch[0].setString("player1");
	player_ch[0].setPosition(580, 415);
	player_ch[0].setCharacterSize(30);
	player_ch[0].setFillColor(sf::Color::Blue);
	player_ch[0].setScale(1.2, 1);
	player_ch[1].setFont(font_sound);
	player_ch[1].setString("player2");
	player_ch[1].setPosition(580, 515);
	player_ch[1].setCharacterSize(30);
	player_ch[2].setFont(font_sound);
	player_ch[2].setString("player3");
	player_ch[2].setPosition(580, 600);
	player_ch[2].setCharacterSize(30);
	
	player_ch[3].setFont(font_sound);
	player_ch[3].setString("back");
	player_ch[3].setPosition(580,680);
	player_ch[3].setCharacterSize(30);
	player_ch[3].setFillColor(sf::Color::White);
	player_ch[3].setScale(1.2, 1);
	Texture player10, player20, player30;
	player10.loadFromFile("images/ore3.png");
	player20.loadFromFile("images/bayz3.png");
	player30.loadFromFile("images/2smr3.png");
	Sprite s_player10(player10), s_player20(player20), s_player30(player30);
	s_player10.setPosition(700, 415);
	s_player20.setPosition(700, 515);
	s_player30.setPosition(700, 620);
	s_player10.setScale(.5, .7);
	s_player20.setScale(.5, .7);
	s_player30.setScale(.5, .7);








	/******exitttttt********/
	/**/
	
	sf::Texture icy;
	icy.loadFromFile("eximmmm2 (1).png");
	sf::Sprite icyshape;
	icyshape.setTexture(icy);
	icyshape.setScale(Vector2f(.7, .7));
	icyshape.setPosition(190, 180);
	
	
	Font font20;
	font20.loadFromFile("font/Chocolate Bar Demo.otf");
	sf::Text text0;
	text0.setFont(font20);
	text0.setString("Are you sure to exit?");
	text0.setFillColor(sf::Color(0, 0, 200));
	text0.setPosition(365.0f, 350.0f);
	text0.setScale(Vector2f(1.2, 1));
	sf::Text yes_no[2];
	yes_no[0].setFont(font20);
	yes_no[0].setString("Yes");
	yes_no[0].setPosition(400, 480);
	yes_no[0].setFillColor(sf::Color::Blue);
	yes_no[0].setScale(1.2, 1);
	yes_no[1].setFont(font20);
	yes_no[1].setString("NO");
	yes_no[1].setPosition(655, 485);
	yes_no[1].setFillColor(sf::Color::White);
	yes_no[1].setScale(.9, 1);
	int sel_yes_no = 0;
	sf::Text yes_no2[3];
	yes_no2[0].setFont(font20);
	yes_no2[0].setString("Yes");
	yes_no2[0].setPosition(400, 480);
	yes_no2[1].setFont(font20);
	yes_no2[1].setString("No");
	yes_no2[1].setPosition(655, 485);
	yes_no2[1].setFillColor(sf::Color::White);
	yes_no2[1].setScale(.9, 1);
	int sel_yes_no2 = 2;
	/*****end exit******/




	/**********play gamee********************/
	
	
	Texture tbackground, tleftborder, trightborder;
	Texture  tstep2, tstep3, tstep4, tstep5;
	Sprite sbackground, sleftborder, srightborder;     //for background , charcter ,left border& right border
	Texture icy_man;  //for charcter

	icy_man.loadFromFile("images/oregenal.png"); //load the charcter
	tbackground.loadFromFile("images/545.png");   //load background
	trightborder.loadFromFile("R1.png");// load right border
	tleftborder.loadFromFile("L1.png");//load left border

	tstep2.loadFromFile("1 (1).png");     //load the second steps
	tstep3.loadFromFile("1 (9).png");     //load the second steps
	tstep4.loadFromFile("1 (8).png");     //load the second steps
	tstep5.loadFromFile("1 (talg).png");     //load the second steps



	View view(FloatRect(0, 0, sd.x, sd.y)); //to move screen
	View view2(FloatRect(0, 0, sd.x, sd.y)); //to fixed things

	// all the texture
	Texture tstep0, ColckTextuer, tbackground2, thurryup, tmountanes, tgameover;    //for the first four steps

	ColckTextuer.loadFromFile("Clock.png");   //load the cclock texter 
	tbackground.setRepeated(true);   //for repeating background
	tbackground2.setRepeated(true);   //for repeating background
	trightborder.setRepeated(true); //for repeated right border
	tleftborder.setRepeated(true);//for repeated left border
	//texture for charcter
	Vector2u T_size = icy_man.getSize();
	Player player1(&icy_man, Vector2u(4, 6), 0.4, 100); //creating an object from player class 

	//all the sprites and rectangel shape
	RectangleShape  step2, ColckRectangl, step3, step4, step5;

	step2.setTexture(&tstep2);
	step3.setTexture(&tstep3);
	step4.setTexture(&tstep4);
	step5.setTexture(&tstep5);
	
	//clock PlayerAnimation 
	Animation  ColckAnimationOpject(&ColckTextuer, Vector2u(15, 1), 1.05f);
	ColckRectangl.setTexture(&ColckTextuer);
	ColckRectangl.setSize(Vector2f(90, 90));
	ColckRectangl.setPosition(0, 0);

	RectangleShape  vie, vie2, vie3;
	vie.setSize(Vector2f(1640, .000001));
	vie2.setSize(Vector2f(1000, 0.5));
	vie3.setSize(Vector2f(1640, 0.000001));
	
	vie.setPosition(0, 300);
	vie2.setPosition(0, 880);
	vie3.setPosition(0, 940);
	
	//sprites
	Sprite sbackground2;

	sbackground2.setTexture(tbackground2);   //to load background in sprite
	sbackground.setTexture(tbackground);   //to load background in sprite
	srightborder.setTexture(trightborder); //load right border in sprite
	sleftborder.setTexture(tleftborder); //load left border in sprite
	sleftborder.setPosition(1000, 0); //Make its starting point at the bottom left of the screen
	srightborder.setPosition(0, 0);//Make its starting point at the bottom right of the screen

	//all fonts
	Font font1,font2 ,font3;
	font2.loadFromFile("font/BEYONDCONTROL.ttf");
	font3.loadFromFile("font/Cartoon Blocks Christmas.otf");

	font1.loadFromFile("MATURASC.ttf");
	//all texts
	Text text1, text2, text3, text4, text5, text6, text7;
	//text1
	text1.setFont(font2);  // to draw word "hurry up"
	text1.setString("hurry up");  //to load the word hurry up
	text1.setCharacterSize(100); // in pixels, not points!
	text1.setFillColor(sf::Color::Yellow);

	//text2
	text2.setFont(font2);
	text2.setCharacterSize(30); // in pixels, not points!
	text2.setFillColor(sf::Color::Black); //to set the color of the word hurry up
	//text3
	text3.setFont(font3);
	text3.setCharacterSize(50); // in pixels, not points!
	text3.setFillColor(sf::Color::Color(0, 0, 0)); //to set the color of the word hurry up
	text3.setPosition(10, 730);
	text3.setString("Score : ");
	//text4
	text4.setFont(font3);
	text4.setCharacterSize(50); // in pixels, not points!
	text4.setFillColor(sf::Color::Color(0,0,0)); //to set the color of the word hurry up
	text4.setPosition(200, 730);
	text5.setFont(font1);  // to draw word "hurry up"
	text5.setString("cool ");  //to load the word hurry up
	text5.setCharacterSize(100); // in pixels, not points!
	text5.setFillColor(sf::Color::Yellow);

	//all times and clocks
	Clock clock/*for clock*/, clock3/*for text1*/;
	Clock c,  z; //Clock2
	int vy = -2.5;   //velocity of view of y axis
	int y = 1000;   //for repeating background
	int h = 100000;   //variable for repeating backgrond upward
	FloatRect fBounds(0.f, 0.f, sd.x, sd.y); // arbitrary > view height
	IntRect iBounds(fBounds);
	int num = 0;
	int a = 0;
	float deltaTime_clock = 0.0f;


	while (true)
	{

		ShowWindow(GetConsoleWindow(), SW_HIDE);
		sf::RenderWindow window(VideoMode(1080, 800), "SF1MMake_Menu");
		Main_menu menu(500, 500);
		//Setting the framerate limit to 60 FPS
		window.setFramerateLimit(85);
		while (window.isOpen())
		{

			sf::Event event;

			while (window.pollEvent(event))
			{


				if (event.type == sf::Event::Closed)
					window.close();
				/*****start move menu******/
				if (hid_menu == false)
				{
					if (event.type == sf::Event::KeyPressed)
					{
						if (event.key.code == sf::Keyboard::Up)
						{

							menu.moveUp(
							);
							if (c0 >= 460)
							{

								if (c0 == 460)
									c0 = 740;
								c0 = c0 - 40;
							}
							player_head_2.setPosition(560, c0);
							break;
						}
						if (event.key.code == sf::Keyboard::Down)
						{

							menu.moveDown();
							if (c0 <= 740)
							{
								c0 = c0 + 40;
								if (c0 == 740) {
									c0 = 460;
								}
							}


							cout << c0;
							player_head_2.setPosition(560, c0);

							break;

						}
					}

					


				}
				/***end move menu*****/

				/*******start back******/
				if (event.type == sf::Event::KeyReleased)
				{
					if (event.key.code == sf::Keyboard::Escape)
					{

						hid_menu = false;

						break;
					}
				}
				/*****end back********/

				/**** rest the gameee ******/
				if (hid_menu == false && end1 == false)
				{
					level2 = true;
					level3 = true;
					level4 = true;
					hid = true;
					sound_play.pause();
					
					tbackground.loadFromFile("images/545.png");   //load background
					trightborder.loadFromFile("R1.png");// load right border
					tleftborder.loadFromFile("L1.png");//load left border
					tstep2.loadFromFile("1 (1).png");     //load the second steps

					sound_sot.play();
					y = 0;
					vy = -2.5;   //velocity of view of y axis
				  
					

					pos.x = 320;
					pos.y = 750;
					
					
					vie.setPosition(0, 300);
					vie2.setPosition(0, 990);
					vie3.setPosition(0, 940);
					
					// player velocity (per frame)
					FloatRect fBounds(0.f, 0.f, sd.x, sd.y); // arbitrary > view height
					IntRect iBounds(fBounds);
					  

					    //load the first step
					    //load the second steps
					deltaTime_clock = c.restart().asSeconds(); //clock restarts time at each frame
					clock.restart().asSeconds();
					clock3.restart().asSeconds();

					
					score = 0;
					hid = true;
					num = 0;
					end1 = true;
					view.setCenter(540, 400);

					Animation  ColckAnimationOpject(&ColckTextuer, Vector2u(15, 1), 2.5f);
					
					deltaTime_clock = c.restart().asSeconds(); //clock restarts time at each frame


				}
				/****end rest the gameee *******/

				/******choose page from menu*****/
				if (event.key.code == sf::Keyboard::Return) //enter
				{

					if (menu.mainMenuPressed() == 0)
					{
						page_number = 0;
						hid_menu = true;

					}
					if (menu.mainMenuPressed() == 1)
					{
						page_number = 1;
						hid_menu = true;
					}
					if (menu.mainMenuPressed() == 2)
					{
						page_number = 2;
						hid_menu = true;
					}
					if (menu.mainMenuPressed() == 3)
					{
						hid_menu = true;
						page_number = 3;
					}
					if (menu.mainMenuPressed() == 4)
					{
						hid_menu = true;
						page_number = 4;
					}
					if (menu.mainMenuPressed() == 5)
					{
						hid_menu = true;
						page_number = 5;
					}
					if (menu.mainMenuPressed() == 6)
					{
						hid_menu = true;
						page_number = 6;
					}
				}
				/******end choose page from menu*****/

				/******start pose the game************/
				if (hid_play != true && page_number == 0)
				{

					if (event.type == sf::Event::KeyReleased)
					{
						if (event.key.code == sf::Keyboard::Left)
						{

							if (sel_yes_no - 1 >= -1) // check if not on the first item (play)

							{
								yes_no[sel_yes_no].setScale(.9, 1);
								yes_no[sel_yes_no].setFillColor(sf::Color::White);  //change the pervious item's color

								sel_yes_no--;  //move to the upper item       
								if (sel_yes_no == -1)
								{
									sel_yes_no = 1;
								}
								yes_no[sel_yes_no].setFillColor(sf::Color::Blue); //change the new item's color
								yes_no[sel_yes_no].setScale(1.2, 1);

							}
							break;
						}
						if (event.key.code == sf::Keyboard::Right)
						{
							if (sel_yes_no + 1 <= 2) // check if not on the first item (play)

							{
								yes_no[sel_yes_no].setScale(.9, 1);
								yes_no[sel_yes_no].setFillColor(sf::Color::White);  //change the pervious item's color

								sel_yes_no++;  //move to the upper item       
								if (sel_yes_no == 2)
								{
									sel_yes_no = 0;
								}
								yes_no[sel_yes_no].setFillColor(sf::Color::Blue); //change the new item's color
								yes_no[sel_yes_no].setScale(1.2, 1);

							}
							break;
						}

					}

					if (sel_yes_no == 1)
					{
						if (event.type == sf::Event::KeyReleased) {
							if (event.key.code == sf::Keyboard::Return)
							{
								hid_play = true;
								end1 = true;

							}

						}
					}
					if (sel_yes_no == 0)
					{
						if (event.type == sf::Event::KeyReleased) {
							if (event.key.code == sf::Keyboard::Return)
							{
								hid_menu = false;
								hid = false;
								sel_yes_no2 = 2;


							}

						}
					}
				}

				/******end pose the game************/
				/***** start display how to playyy*****/
				if (page_number == 1 && hid_menu == true) {
					how_to_play(window);
					
				}
				/****end displlay how to play*******/
				/********start dispalay profail******/
				if (page_number == 2 && hid_menu == true)
				{
					profiel(window);
				}
				/*****start display profail game*******/
				if (page_number == 3 && hid_menu == true)
				{
					profiel_game(window);

				}
				/******start sound move the game************/
				if (page_number == 4 && hid_menu == true)

				{

					if (event.type == sf::Event::KeyPressed)
					{
						if (event.key.code == sf::Keyboard::Up)
						{

							if (sel - 1 >= -1) // check if not on the first item (play)

							{
								soundtext[sel].setScale(.9, 1);

								soundtext[sel].setFillColor(sf::Color::White);  //change the pervious item's color

								sel--;  //move to the upper item       
								if (sel == -1)
								{
									sel = 2;
								}
								soundtext[sel].setFillColor(sf::Color::Blue); //change the new item's color
								soundtext[sel].setScale(1.2, 1);
							}
							break;
						}
						if (event.key.code == sf::Keyboard::Down)
						{
							if (sel + 1 <= 3) // check if not on the first item (play)

							{
								soundtext[sel].setScale(.9, 1);

								soundtext[sel].setFillColor(sf::Color::White);  //change the pervious item's color

								sel++;  //move to the upper item       
								if (sel == 3)
								{
									sel = 0;
								}
								soundtext[sel].setFillColor(sf::Color::Blue); //change the new item's color
								soundtext[sel].setScale(1.2, 1);
							}
							break;
						}

					}
					if (sel == 0)
					{

						if (Keyboard::isKeyPressed(Keyboard::Right))
						{

							if (counter < 6)
								counter++;

							musicsprite.setTexture(music[counter]);
							
							sound_sot.setVolume(counter * 20);
							

						}
						if (Keyboard::isKeyPressed(Keyboard::Left))
						{
							if (counter > 0)
								counter--;


							musicsprite.setTexture(music[counter]);
							sound_sot.setVolume(counter * 20);

						}
					}
					if (sel == 1)
					{
						if (Keyboard::isKeyPressed(Keyboard::Right))
						{
							if (counter2 < 6)
								counter2++;

							soundsprite.setTexture(sound[counter2]);
							sound_coll.setVolume(counter2 * 20);
							sound_jump.setVolume(counter2 * 20);
							sound_hello.setVolume(counter2 * 20);
							sound_pose.setVolume(counter2 * 20);
							sound_play.setVolume(counter2 * 5);
							
							sound_alarm.setVolume(counter2 * 20);


						}
						if (Keyboard::isKeyPressed(Keyboard::Left))
						{
							if (counter2 > 0)
								counter2--;


							soundsprite.setTexture(sound[counter2]);
							sound_coll.setVolume(counter2 * 20);
							sound_jump.setVolume(counter2 * 20);
							sound_hello.setVolume(counter2 * 20);
							sound_pose.setVolume(counter2 * 20);
							sound_play.setVolume(counter2 * 5);
							
							sound_alarm.setVolume(counter2 * 20);

						}
					}
					if (sel == 2)
					{
						if (event.type == sf::Event::KeyReleased) {
							if (event.key.code == sf::Keyboard::Return)
							{
								sel = 0;
								soundtext[sel].setScale(1.2, 1);
								soundtext[sel].setFillColor(sf::Color::Blue);
								hid_menu = false;
								soundtext[2].setFillColor(sf::Color::White);


							}

						}
					}
					if (Keyboard::isKeyPressed(Keyboard::Escape))
					{
						hid_menu = false;
					}
					
					
					
				}
				/******end sound move the game************/
				if (page_number == 5 && hid_menu == true) {

					if (event.type == sf::Event::KeyPressed)
					{
						if (event.key.code == sf::Keyboard::Up)
						{

							if (sel_player - 1 >= -1) // check if not on the first item (play)

							{
								player_ch[sel_player].setScale(.9, 1);

								player_ch[sel_player].setFillColor(sf::Color::White);  //change the pervious item's color

								sel_player--;  //move to the upper item       
								if (sel_player == -1)
								{
									sel_player = 3;
								}
								player_ch[sel_player].setFillColor(sf::Color::Blue); //change the new item's color
								player_ch[sel_player].setScale(1.2, 1);
							}
							break;
						}
						if (event.key.code == sf::Keyboard::Down)
						{
							if (sel_player + 1 <= 4) // check if not on the first item (play)

							{
								player_ch[sel_player].setScale(.9, 1);

								player_ch[sel_player].setFillColor(sf::Color::White);  //change the pervious item's color

								sel_player++;  //move to the upper item       
								if (sel_player == 4)
								{
									sel_player = 0;
								}
								player_ch[sel_player].setFillColor(sf::Color::Blue); //change the new item's color
								player_ch[sel_player].setScale(1.2, 1);
							}
							break;
						}

					}
					if (sel_player == 0)
					{

						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							icy_man.loadFromFile("images/oregenal.png"); //load the charcter
						}

					}
					if (sel_player == 1)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							icy_man.loadFromFile("images/cape character.png"); //load the charcter
						}
					}
					if (sel_player == 2)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							icy_man.loadFromFile("images/black boy.png"); //load the charcter
						}
					}
					if (sel_player == 3)
					{
						if (event.type == sf::Event::KeyReleased) {
							if (event.key.code == sf::Keyboard::Return)
							{
								sel_player = 0;
								player_ch[sel_player].setScale(1.2, 1);
								player_ch[sel_player].setFillColor(sf::Color::Blue);
								hid_menu = false;
								player_ch[3].setFillColor(sf::Color::White);


							}

						}
					}
					window.clear(Color(0, 0, 0));
					window.draw(back);
					window.draw(escS);

					window.draw(s_player10);
					window.draw(s_player20);
					window.draw(s_player30);

					for (int i = 0; i <= 3; i++)
					{
						window.draw(player_ch[i]);
					}
					window.display();
				}
				/******start exit move the game************/
				if (page_number == 6 && hid_menu == true)

				{

					if (event.type == sf::Event::KeyReleased)
					{
						if (event.key.code == sf::Keyboard::Left)
						{

							if (sel_yes_no2 - 1 >= -1) // check if not on the first item (play)

							{
								yes_no2[sel_yes_no2].setScale(.9, 1);
								yes_no2[sel_yes_no2].setFillColor(sf::Color::White);  //change the pervious item's color


								sel_yes_no2--;  //move to the upper item       
								if (sel_yes_no2 == -1)
								{
									sel_yes_no2 = 2;
								}
								yes_no2[sel_yes_no2].setFillColor(sf::Color::Blue); //change the new item's color
								yes_no2[sel_yes_no2].setScale(1.2, 1);

							}
							break;
						}
						if (event.key.code == sf::Keyboard::Right)
						{
							if (sel_yes_no2 + 1 <= 3) // check if not on the first item (play)

							{
								yes_no2[sel_yes_no2].setScale(.9, 1);
								yes_no2[sel_yes_no2].setFillColor(sf::Color::White);  //change the pervious item's color

								sel_yes_no2++;  //move to the upper item       
								if (sel_yes_no2 == 3)
								{
									sel_yes_no2 = 0;
								}
								yes_no2[sel_yes_no2].setFillColor(sf::Color::Blue); //change the new item's color
								yes_no2[sel_yes_no2].setScale(1.2, 1);

							}
							break;
						}

					}

					if (sel_yes_no2 == 1)
					{
						if (event.type == sf::Event::KeyReleased) {
							if (event.key.code == sf::Keyboard::Return)
							{
								
								hid_menu = false;
								hid = false;
								sel_yes_no2 = 2;
								yes_no2[1].setFillColor(sf::Color::White);
							}
						
						}
					}
					if (sel_yes_no2 == 0)
					{
						if (event.type == sf::Event::KeyReleased) {
							if (event.key.code == sf::Keyboard::Return)
							{
								return 0;


							}

						}
					}
					
				}
				/*****end exit move the game************/
				
			}//end window event


			/*display sound*/
			if (page_number == 4 && hid_menu == true) {
				window.clear(Color(0, 0, 0));
				window.draw(back);
				window.draw(escS);
				window.draw(musicsprite);
				window.draw(soundsprite);


				for (int i = 0; i <= 2; i++)
				{
					window.draw(soundtext[i]);
				}
				ani_head_3.update(0, .012, true);
				player_head_3.setTextureRect(ani_head_3.uv_Rect);
				window.draw(player_head_3);
				window.display();
			}
			if (page_number == 6 && hid_menu == true)

			{
				if (hid == true)
				{

					window.draw(b30);
					window.draw(icyshape);
					window.draw(text0);

					for (int i = 0; i < 2; i++)
					{
						window.draw(yes_no2[i]);
					}


					window.display();
				}
			}
			
			/*******start dispalt menu*********/
			if (hid_menu == false) {
				window.clear();
				window.draw(back);
				ani_head.update(0, .012, true);
				player_head.setTextureRect(ani_head.uv_Rect);
				window.draw(player_head);
				ani_head_2.update(0, .012, false);
				player_head_2.setTextureRect(ani_head_2.uv_Rect);
				window.draw(player_head_2);
				menu.draw(window);

				window.display();
				hid = true;
			}
			/******end display menu*************/
			/******* start pageeeee playyyyyy******/
			if (page_number == 0 && hid_menu == true) //display pose game
			{

				if (hid_play == false)
				{
					for (int i = 0; i < 2; i++)
					{
						window.draw(yes_no[i]);
					}

					window.draw(icyshape);
					window.draw(text0);
					window.display();

				}



			}
			if (end1 == true) {
				if (page_number == 0 && hid_menu == true)
				{
					sound_play.play(); 
					sound_sot.pause();
					sound_hello.play();
					//setting positions of each step randomly
					for (int i = 0; i < 1000; i++)
					{

						floorlocation[i].h = 50;
						if (i < 100)
						{
							floorlocation[i].w = rand() % 550;
							if (floorlocation[i].w <= 225)
								floorlocation[i].w = 200;
							else if (floorlocation[i].w > 230 && floorlocation[i].w <= 270)
								floorlocation[i].w = 250;
							else if (floorlocation[i].w > 250 && floorlocation[i].w <= 300)
								floorlocation[i].w = 300;
							else if (floorlocation[i].w > 300 && floorlocation[i].w <= 320)
								floorlocation[i].w = 330;
							else
								floorlocation[i].w = 258;
						}
						if (i > 100 && i < 300)
						{
							if (floorlocation[i].w <= 200)
								floorlocation[i].w = 170;
							else if (floorlocation[i].w > 200 && floorlocation[i].w <= 230)
								floorlocation[i].w = 165;
							else
								floorlocation[i].w = 160;
						}
						if (i > 300)
							floorlocation[i].w = 100;
						if (i == 0 || (i % 50 == 0))
							floorlocation[i].w = 1080;
						floorlocation[i].x = rand() % 1000;
						if (i == 0)
						{
							floorlocation[i].x = 0;
							floorlocation[i].y = 735;
						}
						else
							floorlocation[i].y = floorlocation[i - 1].y - 120;
					}


					// handil the position of steps
					for (int i = 1; i < 1000; i++)
					{
						if (floorlocation[i].x < 140)
							floorlocation[i].x = 140;
						if ((floorlocation[i].x + floorlocation[i].w) > 1000)
							floorlocation[i].x = (1000 - floorlocation[i].w);
						if (i % 50 == 0)
							floorlocation[i].x = 0;
					}
					



					while (end1)
					{




						player1.body.setOrigin(bodysize.x , bodysize.y / 3.5);

						if (player1.body.getGlobalBounds().intersects(srightborder.getGlobalBounds()))
						{
							vel.x = -.5 * vel.x;
							pos.x = 1012;
							sound_coll.play();
						}

						if (player1.body.getGlobalBounds().intersects(sleftborder.getGlobalBounds()))
						{
							sound_coll.play();
							vel.x = -.5 * vel.x;
							pos.x = 128;



						}


						Event Pose;
						while (window.pollEvent(Pose))
						{
							if (Pose.type == Event::Closed)
							{
								window.close();

							}
							if (Pose.type == Event::KeyReleased)
							{
								if (Pose.key.code == Keyboard::Escape)
								{
									end1 = false;

									hid_play = false;
									sound_pose.play();
								}
								if (Pose.key.code == Keyboard::Space)

									sound_jump.play();



							}


						}



						if (pos.y < floorlocation[20].y && level2 == true)
						{


							tbackground.loadFromFile("bg2.png");   //load background
							trightborder.loadFromFile("R3.png");// load right border
							tleftborder.loadFromFile("L3.png");//load left border



							level2 = false;
						}
						if (pos.y < floorlocation[40].y && level3 == true && level2 == false)
						{

							tbackground.loadFromFile("images/BG3.png");   //load background
							trightborder.loadFromFile("R5.png");// load right border
							tleftborder.loadFromFile("L5.png");//load left border

							level3 = false;
						}
						if (pos.y < floorlocation[60].y && level4 == true && level2 == false && level3 == false)
						{

							tbackground.loadFromFile("op2.png");   //load background
							trightborder.loadFromFile("R2.png");// load right border
							tleftborder.loadFromFile("L2.png");//load left border

							level4 = false;
						}

						y += 10 * sd.y;
						deltaTime_clock = c.restart().asSeconds(); //clock restarts time at each frame
						sbackground.setPosition(fBounds.left, fBounds.top - 1000.f - h); //for repeating background upward
						sbackground2.setPosition(fBounds.left, fBounds.top - 1000.f - h); //for repeating background upward
						sleftborder.setPosition(fBounds.left, fBounds.top - 1000.f - h); //for repeating left border upward
						srightborder.setPosition(fBounds.left + (1080 - 65), fBounds.top - 1000.f - h); //for repeating right border upward
						sbackground.setTextureRect(IntRect(0, 0, sd.x, y));  //repeat background
						sbackground2.setTextureRect(IntRect(0, 0, sd.x, y));  //repeat background
						sleftborder.setTextureRect(IntRect(0, 0, 58, y));    //repeat left border
						srightborder.setTextureRect(IntRect(0, 0, 74, y));   //repeat right border
						  //the event
						// increase the value of repeating
						// check all the window's events that were triggered since the last iteration of the loop
						if (player1.body.getPosition().y < 10)
						{
							ColckAnimationOpject.update(0, deltaTime_clock, true);   // updat the clock PlayerAnimation  by calling update function from clock PlayerAnimation  object
							ColckRectangl.setTextureRect(ColckAnimationOpject.uv_Rect);    //to crup the tectuer of the clock
						}
						player1.update(.011, window, floorlocation[a].w, floorlocation[a].x); // updat the character PlayerAnimation  by calling update function from player1 object

						score_string = to_string(scoree);
						text4.setString(score_string);

						window.setView(view);
						window.draw(sbackground);

						for (int i = 0; i < 1000; i++)
						{


							if (i < 20) {
								step2.setSize(Vector2f(floorlocation[i].w, floorlocation[i].h));

								step2.setPosition(floorlocation[i].x, floorlocation[i].y);
								window.draw(step2);

							}
							else if (i >= 20 && i < 40) {

								step3.setSize(Vector2f(floorlocation[i].w, floorlocation[i].h));

								step3.setPosition(floorlocation[i].x, floorlocation[i].y);

								window.draw(step3);
							}
							else if (i >= 40 && i < 60) {
								step4.setSize(Vector2f(floorlocation[i].w, floorlocation[i].h));

								step4.setPosition(floorlocation[i].x, floorlocation[i].y);
								window.draw(step4);
							}
							else if (i >= 60) {
								step5.setSize(Vector2f(floorlocation[i].w, floorlocation[i].h));

								step5.setPosition(floorlocation[i].x, floorlocation[i].y);
								window.draw(step5);
							}

						}


						window.draw(vie);
						window.draw(vie2);
						window.draw(vie3);
						window.draw(player1.body); //draw charcter
						window.draw(sleftborder);  //draw the left border
						window.draw(srightborder);  //draw the right border
					//	cout << vie2.getPosition().y << "    vie2" << endl;
							//cout << player1.body.getPosition().y<<"::::::::::::::"<<endl;
							//cout << view.getCenter().y<<endl;
						for (int i = 0; i < 1000; i++)
						{
							if (i % 10 == 0)
							{
								num = i;
								num_step = to_string(num);
								text2.setString(num_step);
								text2.setPosition(floorlocation[i].x + 0.5 * floorlocation[i].w - 20, floorlocation[i].y + 10);
								window.draw(text2);
							}
						}
						
							if (player1.body.getPosition().y < 300)
						{
								if (clock.getElapsedTime().asSeconds() >= 16)  //increasse velocity of view every 30 seconds
								{
									vy=vy-.7;
									clock.restart();

								}
							view.move(0, vy);
							vie.move(0, vy);
							vie2.move(0, vy);
							vie3.move(0, vy);

							
						}

						if (clock3.getElapsedTime().asSeconds() >= 20)
							clock3.restart();

						if (pos.y > 10)
						{
							clock.restart();
							clock3.restart();
						}


						window.setView(view2);

						window.draw(vie3);
						if (clock.getElapsedTime().asSeconds() >= 15)
						{
							text1.setPosition(100, 400);
							window.draw(text1);
							sound_alarm.play();

						}

						for (int i = 1; i < 1000; i++)
						{
							if (i == 50)
							{

								if (pos.y <= floorlocation[i].y && pos.y >= floorlocation[i + 10].y)
								{
									clock3.restart().asSeconds();
									if (clock3.getElapsedTime().asSeconds() <= 2) {
										text5.setPosition(100, 300);
										window.draw(text5);
									}

								}
							}

						}


						if (player1.body.getGlobalBounds().intersects(vie2.getGlobalBounds()))
						{
							cout << "game over" << endl;

							GameOver();
							break;
							//window.clear();

							//	window.close();

						}
						window.draw(text4);
						window.draw(text3);

						window.draw(ColckRectangl);   //drowing the clock texter

						if (player1.body.getGlobalBounds().intersects(vie.getGlobalBounds()))
						{
							view.move(0, vel.y);
							vie.move(0, vel.y);
							vie2.move(0, vel.y-.5);
							vie3.move(0, vel.y);
						}

						window.display();
					}



				}
			}
			

		}//end window is open 

		
				break;
		

	}

	return 0;
}
//