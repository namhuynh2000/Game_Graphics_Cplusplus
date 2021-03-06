#include "Common_Fuction.h"
#include "MainObject.h"
#include "ThreatObject.h"
#include "ExplosionObject.h"
using namespace SDLCommonFunc;

SDL_Surface *g_object;
SDL_Surface *g_car; 
MainObject human_object;
#define HEART 3
Mix_Music* g_sound_ingame[6];


bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if (g_screen == NULL)
	{
		return false;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		return false;
	return true;
}


int main()
{
	int speech_;
	int menu = 0; //menu=0=>bật menu; menu=1=>vào game; menu=2=>vào about
	int music=0; //cái này t định viết ra để kiểm tra mà chưa dùng tới
	int heart = HEART; //set máu =3
	int level = 1; //set level=1
	int NUM_Threat = 2;//số lượng chướng ngại vật của mỗi làn
	int speech = 1; // tốc độ cho map1
	int speech2 = 1; //tốc độ cho map2
	int speech3 = 1; //tốc độ cho map3
	bool is_quit = false;
	if (Init() == false)
		return 0;
	g_sound_ingame[0] = Mix_LoadMUS("ingame2.wav"); //nhạc nền game*
	g_sound_ingame[1] = Mix_LoadMUS("death.wav"); //lúc mất mạng *
	g_sound_ingame[2] = Mix_LoadMUS("roundgame.wav"); //lúc qua map mới *
	g_sound_ingame[3] = Mix_LoadMUS("win.wav"); // nhạc lúc thắng game*
	g_sound_ingame[4] = Mix_LoadMUS("lose.wav"); //nhạc lúc thua *
	

	Mix_PlayMusic(g_sound_ingame[0], -1); //load nhạc
	
	g_bkground = LoadImage("background1.png");
	g_bkground2 = LoadImage("background5.png");

	//make quit, continue, about, play, save
	BaseObject quit, Continue,play,about,save;
	quit.LoadImg("quit.png");
	Continue.LoadImg("continue.png");
	play.LoadImg("play.png");
	about.LoadImg("about.png");
	save.LoadImg("save.png");

	//make level
	BaseObject level_;

	//make heart
	BaseObject heart_;
	heart_.SetRect(675,0);

	// make human
	MainObject human_object;
	human_object.SetRect(0, 0);
	human_object.LoadImg("nguoi.png");

	//Init explosion object
	ExplosionObject exp_main;
	exp_main.LoadImg("exp_main.png");
	exp_main.set_clip();

	// make car
	ThreatObject* p_threats1 = new ThreatObject[NUM_Threat];
	for (int t = 0; t < NUM_Threat; t++)
	{
		int recty;
		ThreatObject* p_threat = (p_threats1 + t);
		p_threat->LoadImg("car2.png");
		srand(time(NULL));
		int random = 1;
		if (random == 1)
		{
			recty = SCREEN_HEIGHT * 0.145;
		}
		else if (random == 2)
		{
			recty = SCREEN_HEIGHT * 0.28;
		}
		else  if (random == 3)

		{
			recty = SCREEN_HEIGHT * 0.545;
		}
		else  if (random == 4)
		{
			recty = SCREEN_HEIGHT * 0.678;
		}
		p_threat->SetRect(SCREEN_WIDTH -300+ 300 * t,recty);
		p_threat->set_x_val(level);
	}

	ThreatObject* p_threats2 = new ThreatObject[NUM_Threat];
	for (int t = 0; t < NUM_Threat; t++)
	{
		int recty;
		ThreatObject* p_threat = (p_threats2 + t);
		p_threat->LoadImg("car2.png");
		srand(time(NULL));
		int random = 2;
		if (random == 1)
		{
			recty = SCREEN_HEIGHT * 0.145;
		}
		else if (random == 2)
		{
			recty = SCREEN_HEIGHT * 0.28;
		}
		else  if (random == 3)
		{
			recty = SCREEN_HEIGHT * 0.545;
		}
		else  if (random == 4)
		{
			recty = SCREEN_HEIGHT * 0.678;
		}
		p_threat->SetRect(SCREEN_WIDTH - 600 + 500 * t, recty);
		p_threat->set_x_val(level);
	}

	ThreatObject* p_threats3 = new ThreatObject[NUM_Threat];
	for (int t = 0; t < NUM_Threat; t++)
	{
		int recty;
		ThreatObject* p_threat = (p_threats3 + t);
		p_threat->LoadImg("car2.png");
		srand(time(NULL));
		int random = 3;
		if (random == 1)
		{
			recty = SCREEN_HEIGHT * 0.145;
		}
		else if (random == 2)
		{
			recty = SCREEN_HEIGHT * 0.28;
		}
		else  if (random == 3)
		{
			recty = SCREEN_HEIGHT * 0.545;
		}
		else  if (random == 4)
		{
			recty = SCREEN_HEIGHT * 0.678;
		}
		p_threat->SetRect(SCREEN_WIDTH - 900 + 400 * t, recty);
		p_threat->set_x_val(level);
	}

	ThreatObject* p_threats4 = new ThreatObject[NUM_Threat];
	for (int t = 0; t < NUM_Threat; t++)
	{
		int recty;
		ThreatObject* p_threat = (p_threats4 + t);
		p_threat->LoadImg("car2.png");
		srand(time(NULL));
		int random = 4;
		if (random == 1)
		{
			recty = SCREEN_HEIGHT * 0.145;
		}
		else if (random == 2)
		{
			recty = SCREEN_HEIGHT * 0.28;
		}
		else  if (random == 3)
		{
			recty = SCREEN_HEIGHT * 0.545;
		}
		else  if (random == 4)
		{
			recty = SCREEN_HEIGHT * 0.678;
		}
		p_threat->SetRect(SCREEN_WIDTH + 300 * t, recty);
		p_threat->set_x_val(level);
	}

	ThreatObject* p_threats5 = new ThreatObject[NUM_Threat];
	for (int t = 0; t < NUM_Threat; t++)
	{
		int recty;
		ThreatObject* p_threat = (p_threats5 + t);
		p_threat->LoadImg("car1.png");
		srand(time(NULL));
		int random = 2;
		if (random == 1)
		{
			recty = SCREEN_HEIGHT * 0.145;
		}
		else if (random == 2)
		{
			recty = SCREEN_HEIGHT * 0.28;
		}
		else  if (random == 3)
		{
			recty = SCREEN_HEIGHT * 0.545;
		}
		else  if (random == 4)
		{
			recty = SCREEN_HEIGHT * 0.678;
		}
		p_threat->SetRect(SCREEN_WIDTH - 600 + 500 * t, recty);
		p_threat->set_x_val(level);
	}

	ThreatObject* p_threats6 = new ThreatObject[NUM_Threat];
	for (int t = 0; t < NUM_Threat; t++)
	{
		int recty;
		ThreatObject* p_threat = (p_threats6 + t);
		p_threat->LoadImg("car1.png");
		srand(time(NULL));
		int random = 4;
		if (random == 1)
		{
			recty = SCREEN_HEIGHT * 0.145;
		}
		else if (random == 2)
		{
			recty = SCREEN_HEIGHT * 0.28;
		}
		else  if (random == 3)
		{
			recty = SCREEN_HEIGHT * 0.545;
		}
		else  if (random == 4)
		{
			recty = SCREEN_HEIGHT * 0.678;
		}
		p_threat->SetRect(SCREEN_WIDTH - 400 + 400 * t, recty);
		p_threat->set_x_val(level);
	}

	ThreatObject* p_threats7 = new ThreatObject[NUM_Threat];
		for (int t = 0; t < NUM_Threat; t++)
		{
			int recty;
			ThreatObject* p_threat = (p_threats7 + t);
			p_threat->LoadImg("ship2.png");
			srand(time(NULL));
			int random = 2;
			if (random == 1)
			{
				recty = SCREEN_HEIGHT * 0.145;
			}
			else if (random == 2)
			{
				recty = SCREEN_HEIGHT * 0.28;
			}
			else  if (random == 3)
			{
				recty = SCREEN_HEIGHT * 0.545;
			}
			else  if (random == 4)
			{
				recty = SCREEN_HEIGHT * 0.678;
			}
			p_threat->SetRect(SCREEN_WIDTH - 550 + 300 * t, recty);
			p_threat->set_x_val(level);
		}

	ThreatObject* p_threats8 = new ThreatObject[NUM_Threat];
	for (int t = 0; t < NUM_Threat; t++)
	{
			int recty;
			ThreatObject* p_threat = (p_threats8 + t);
			p_threat->LoadImg("ship1.png");
			srand(time(NULL));
			int random = 3;
			if (random == 1)
			{
				recty = SCREEN_HEIGHT * 0.145;
			}
			else if (random == 2)
			{
				recty = SCREEN_HEIGHT * 0.28;
			}
			else  if (random == 3)
			{
				recty = SCREEN_HEIGHT * 0.545;
			}
			else  if (random == 4)
			{
				recty = SCREEN_HEIGHT * 0.678;
			}
			p_threat->SetRect(SCREEN_WIDTH - 350 + 600 * t, recty);
			p_threat->set_x_val(level);
	}
	


	while (!is_quit)
	{
		/*while (SDL_PollEvent(&g_even))
		{
			if (g_even.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			human_object.HandleInputAction(g_even); //hàm cho người di chuyển
		}*/
		if (menu == 0)//menu
		{   //load menu
			Menu = LoadImage("menu2.png");
			ApplySurface(Menu, g_screen, 0, 0);
			play.SetRect(350, 260);
			play.Show(g_screen);
			Continue.SetRect(310,340);
			Continue.Show(g_screen);
			about.SetRect(330, 420);
			about.Show(g_screen);
			quit.SetRect(350, 500);
			quit.Show(g_screen);
			while (SDL_PollEvent(&geven))
			{
				if (geven.type == SDL_MOUSEMOTION)//hàm kiểm tra di chuyển chuột
				{
					if (geven.motion.x >= 350 && geven.motion.x <= 440 && geven.motion.y >= 260 && geven.motion.y <=305)
					{
						play.LoadImg("play2.png");
						play.Show(g_screen);
					}
					else if (geven.motion.x >= 310 && geven.motion.x <= 485 && geven.motion.y >= 340 && geven.motion.y <= 385)
					{
						Continue.LoadImg("continue2.png");
						Continue.Show(g_screen);
					}
					else if (geven.motion.x >= 330 && geven.motion.x <= 456 && geven.motion.y >= 420 && geven.motion.y <= 470)
					{
						about.LoadImg("about2.png");
						about.Show(g_screen);
					}
					else if (geven.motion.x >= 350 && geven.motion.x <= 440 && geven.motion.y >= 500 && geven.motion.y <= 545)
					{
						quit.LoadImg("quit2.png");
						quit.Show(g_screen);
					}
					else {
						play.LoadImg("play.png");
						play.Show(g_screen);
						Continue.LoadImg("continue.png");
						Continue.Show(g_screen);
						about.LoadImg("about.png");
						about.Show(g_screen);
						quit.LoadImg("quit.png");
						quit.Show(g_screen);
					}
				}
				else if (geven.type == SDL_MOUSEBUTTONDOWN) //hàm kiểm tra bấm chuột
				{
					if (geven.motion.x >= 350 && geven.motion.x <= 440 && geven.motion.y >= 260 && geven.motion.y <= 305)
					{
						menu = 1;
					}
					else if (geven.motion.x >= 310 && geven.motion.x <= 485 && geven.motion.y >= 340 && geven.motion.y <= 385)
					{
						menu = 3;
					}
					else if (geven.motion.x >= 330 && geven.motion.x <= 456 && geven.motion.y >= 420 && geven.motion.y <= 470)
					{
						menu = 2;
					}
					else if (geven.motion.x >= 350 && geven.motion.x <= 440 && geven.motion.y >= 500 && geven.motion.y <= 545)
					{
						is_quit = true;
						break;
					}
				}
			}
			
		}
		else if (menu == 1)// vào game
		{
			ApplySurface(g_bkground, g_screen, 0, 0); //load background
			//load level
			if (level == 1)
			{
				level_.LoadImg("level1.png");
				level_.SetRect(680, 50);
				level_.Show(g_screen);
			}
			else if (level == 2)
			{
				level_.LoadImg("level2.png");
				level_.SetRect(680, 50);
				level_.Show(g_screen);
			}
			else if (level == 3)
			{
				level_.LoadImg("level3.png");
				level_.SetRect(680, 50);
				level_.Show(g_screen);
			}
			else if (level == 4)
			{
				level_.LoadImg("level4.png");
				level_.SetRect(680, 50);
				level_.Show(g_screen);
			}
			else if (level == 5)
			{
				level_.LoadImg("level5.png");
				level_.SetRect(680, 50);
				level_.Show(g_screen);
			}
			else if (level == 6)
			{
				level_.LoadImg("level6.png");
				level_.SetRect(680, 50);
				level_.Show(g_screen);
			}
			else if (level == 7)
			{
				level_.LoadImg("level7.png");
				level_.SetRect(680, 50);
				level_.Show(g_screen);
			}
			else if (level == 8)
			{
				level_.LoadImg("level8.png");
				level_.SetRect(680, 50);
				level_.Show(g_screen);
			}
			else if (level == 9)
			{
				level_.LoadImg("level9.png");
				level_.SetRect(680, 50);
				level_.Show(g_screen);
			}
			else if (level == 10)
			{
				level_.LoadImg("level10.png");
				level_.SetRect(680, 50);
				level_.Show(g_screen);
			}
			human_object.Show(g_screen);
			
			//run threat
			if (heart != 0 && level <= 4)
			{
				if (heart == 3)
				{
					heart_.LoadImg("heart3.png");
					heart_.SetRect(675, 0);
					heart_.Show(g_screen);
				}
				else if (heart == 2)
				{
					heart_.LoadImg("heart2.png");
					heart_.SetRect(675, 0);
					heart_.Show(g_screen);
				}
				else if (heart == 1)
				{
					heart_.LoadImg("heart1.png");
					heart_.SetRect(675, 0);
					heart_.Show(g_screen);
				}
				save.SetRect(350, 500);
				save.Show(g_screen);
				while (SDL_PollEvent(&geven))
				{
					human_object.HandleInputAction(geven);
					if (geven.type == SDL_MOUSEMOTION)//hàm kiểm tra di chuyển chuột
					{
						if (geven.motion.x >= 350 && geven.motion.x <= 440 && geven.motion.y >= 500 && geven.motion.y <= 545)
						{
							save.LoadImg("save2.png");
							save.Show(g_screen);
						}
						else {

							save.LoadImg("save.png");
							save.Show(g_screen);
						}
					}
					else if (geven.type == SDL_MOUSEBUTTONDOWN) //hàm kiểm tra bấm chuột
					{
						if (geven.motion.x >= 350 && geven.motion.x <= 440 && geven.motion.y >= 500 && geven.motion.y <= 545)
						{
							save_(heart, level);
							menu = 0;
						}
					}
				}
				for (int i = 0; i < NUM_Threat; i++)
				{
					ThreatObject* p_threat = (p_threats1 + i);
					p_threat->Show(g_screen);
					p_threat->HandleMove2(SCREEN_WIDTH, SCREEN_HEIGHT); //hàm di chuyển xe
					p_threat->set_x_val(speech); //hàm tăng tốc sau mỗi lần thắng
					int is_col = CheckCollision(human_object.GetRect(), p_threat->GetRect());//hàm kiểm tra va chạm
					if (is_col == 0)
					{
						Mix_PlayMusic(g_sound_ingame[1], 0);
						for (int ex = 0; ex < 4; ex++)
						{
							int x_pos = (human_object.GetRect().x + human_object.GetRect().w * 0.5) - EXP_WIDTH * 0.5;
							int y_pos = (human_object.GetRect().y + human_object.GetRect().h * 0.5) - EXP_HEIGHT * 0.5;
							exp_main.set_frame(ex);
							exp_main.SetRect(x_pos, y_pos);
							exp_main.ShowEx(g_screen);
							SDL_Delay(100);

							//update screen
							if (SDL_Flip(g_screen) == -1)
								return 0;
						}
						heart -= 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
						Mix_PlayMusic(g_sound_ingame[0], -1);
					}
					else if (is_col == 1)
					{
						level += 1;
						speech += 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
					}
				}
				for (int i = 0; i < NUM_Threat; i++)
				{
					ThreatObject* p_threat = (p_threats2 + i);
					p_threat->Show(g_screen);
					p_threat->HandleMove2(SCREEN_WIDTH, SCREEN_HEIGHT);
					p_threat->set_x_val(speech);
					int is_col = CheckCollision(human_object.GetRect(), p_threat->GetRect());
					if (is_col == 0)
					{
						Mix_PlayMusic(g_sound_ingame[1], 0);
						for (int ex = 0; ex < 4; ex++)
						{
							int x_pos = (human_object.GetRect().x + human_object.GetRect().w * 0.5) - EXP_WIDTH * 0.5;
							int y_pos = (human_object.GetRect().y + human_object.GetRect().h * 0.5) - EXP_HEIGHT * 0.5;
							exp_main.set_frame(ex);
							exp_main.SetRect(x_pos, y_pos);
							exp_main.ShowEx(g_screen);
							SDL_Delay(100);

							//update screen
							if (SDL_Flip(g_screen) == -1)
								return 0;
						}
						heart -= 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
						Mix_PlayMusic(g_sound_ingame[0], -1);
					}
					else if (is_col == 1)
					{
						level += 1;
						speech += 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
					}
				}
				for (int i = 0; i < NUM_Threat; i++)
				{

					ThreatObject* p_threat = (p_threats3 + i);
					p_threat->Show(g_screen);
					p_threat->HandleMove2(SCREEN_WIDTH, SCREEN_HEIGHT);
					p_threat->set_x_val(speech);
					int is_col = CheckCollision(human_object.GetRect(), p_threat->GetRect());
					if (is_col == 0)
					{
						Mix_PlayMusic(g_sound_ingame[1], 0);
						for (int ex = 0; ex < 4; ex++)
						{
							int x_pos = (human_object.GetRect().x + human_object.GetRect().w * 0.5) - EXP_WIDTH * 0.5;
							int y_pos = (human_object.GetRect().y + human_object.GetRect().h * 0.5) - EXP_HEIGHT * 0.5;
							exp_main.set_frame(ex);
							exp_main.SetRect(x_pos, y_pos);
							exp_main.ShowEx(g_screen);
							SDL_Delay(100);

							//update screen
							if (SDL_Flip(g_screen) == -1)
								return 0;
						}
						heart -= 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
						Mix_PlayMusic(g_sound_ingame[0], -1);
					}
					else if (is_col == 1)
					{
						level += 1;
						speech += 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
					}
				}
				for (int i = 0; i < NUM_Threat; i++)
				{

					ThreatObject* p_threat = (p_threats4 + i);
					p_threat->Show(g_screen);
					p_threat->HandleMove2(SCREEN_WIDTH, SCREEN_HEIGHT);
					p_threat->set_x_val(speech);
					int is_col = CheckCollision(human_object.GetRect(), p_threat->GetRect());
					if (is_col == 0)
					{
						Mix_PlayMusic(g_sound_ingame[1], 0);
						for (int ex = 0; ex < 4; ex++)
						{
							int x_pos = (human_object.GetRect().x + human_object.GetRect().w * 0.5) - EXP_WIDTH * 0.5;
							int y_pos = (human_object.GetRect().y + human_object.GetRect().h * 0.5) - EXP_HEIGHT * 0.5;
							exp_main.set_frame(ex);
							exp_main.SetRect(x_pos, y_pos);
							exp_main.ShowEx(g_screen);
							SDL_Delay(100);

							//update screen
							if (SDL_Flip(g_screen) == -1)
								return 0;
						}
						heart -= 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
						Mix_PlayMusic(g_sound_ingame[0], -1);
					}
					else if (is_col == 1)
					{
						level += 1;
						speech += 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
					}
				}
			}
			else if (heart != 0 && level >= 5 && level <=7 )
			{
			save.SetRect(350, 500);
			save.Show(g_screen);
			while (SDL_PollEvent(&geven))
			{
				human_object.HandleInputAction(geven);
				if (geven.type == SDL_MOUSEMOTION)//hàm kiểm tra di chuyển chuột
				{
					if (geven.motion.x >= 350 && geven.motion.x <= 440 && geven.motion.y >= 500 && geven.motion.y <= 545)
					{
						save.LoadImg("save2.png");
						save.Show(g_screen);
					}
					else {

						save.LoadImg("save.png");
						save.Show(g_screen);
					}
				}
				else if (geven.type == SDL_MOUSEBUTTONDOWN) //hàm kiểm tra bấm chuột
				{
					if (geven.motion.x >= 350 && geven.motion.x <= 440 && geven.motion.y >= 500 && geven.motion.y <= 545)
					{
						save_(heart, level);
						menu = 0;
					}
				}
			}
				if (heart == 3)
				{
					heart_.LoadImg("heart3.png");
					heart_.SetRect(675, 0);
					heart_.Show(g_screen);
				}
				else if (heart == 2)
				{
					heart_.LoadImg("heart2.png");
					heart_.SetRect(675, 0);
					heart_.Show(g_screen);
				}
				else if (heart == 1)
				{
					heart_.LoadImg("heart1.png");
					heart_.SetRect(675, 0);
					heart_.Show(g_screen);
				}
				for (int i = 0; i < NUM_Threat; i++)
				{
					ThreatObject* p_threat = (p_threats1 + i);
					p_threat->Show(g_screen);
					p_threat->HandleMove2(SCREEN_WIDTH, SCREEN_HEIGHT);
					p_threat->set_x_val(speech2);
					int is_col = CheckCollision(human_object.GetRect(), p_threat->GetRect());
					if (is_col == 0)
					{
			
						Mix_PlayMusic(g_sound_ingame[1], 0);
						for (int ex = 0; ex < 4; ex++)
						{
							int x_pos = (human_object.GetRect().x + human_object.GetRect().w * 0.5) - EXP_WIDTH * 0.5;
							int y_pos = (human_object.GetRect().y + human_object.GetRect().h * 0.5) - EXP_HEIGHT * 0.5;
							exp_main.set_frame(ex);
							exp_main.SetRect(x_pos, y_pos);
							exp_main.ShowEx(g_screen);
							SDL_Delay(100);

							//update screen
							if (SDL_Flip(g_screen) == -1)
								return 0;
						}
						heart -= 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
						Mix_PlayMusic(g_sound_ingame[0], -1);
					}
					else if (is_col == 1)
					{
						level += 1;
						speech2 += 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
					}
				}
				for (int i = 0; i < NUM_Threat; i++)
				{
					ThreatObject* p_threat = (p_threats5 + i);
					p_threat->Show(g_screen);
					p_threat->HandleMove1(SCREEN_WIDTH, SCREEN_HEIGHT);
					p_threat->set_x_val(speech2);
					int is_col = CheckCollision(human_object.GetRect(), p_threat->GetRect());
					if (is_col == 0)
					{
						Mix_PlayMusic(g_sound_ingame[1], 0);
						for (int ex = 0; ex < 4; ex++)
						{
							int x_pos = (human_object.GetRect().x + human_object.GetRect().w * 0.5) - EXP_WIDTH * 0.5;
							int y_pos = (human_object.GetRect().y + human_object.GetRect().h * 0.5) - EXP_HEIGHT * 0.5;
							exp_main.set_frame(ex);
							exp_main.SetRect(x_pos, y_pos);
							exp_main.ShowEx(g_screen);
							SDL_Delay(100);

							//update screen
							if (SDL_Flip(g_screen) == -1)
								return 0;
						}
						heart -= 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
						Mix_PlayMusic(g_sound_ingame[0], -1);
					}
					else if (is_col == 1)
					{
						level += 1;
						speech2 = level;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
					}
				}
				for (int i = 0; i < NUM_Threat; i++)
				{

					ThreatObject* p_threat = (p_threats3 + i);
					p_threat->Show(g_screen);
					p_threat->HandleMove2(SCREEN_WIDTH, SCREEN_HEIGHT);
					p_threat->set_x_val(speech2);
					int is_col = CheckCollision(human_object.GetRect(), p_threat->GetRect());
					if (is_col == 0)
					{
						Mix_PlayMusic(g_sound_ingame[1], 0);
						for (int ex = 0; ex < 4; ex++)
						{
							int x_pos = (human_object.GetRect().x + human_object.GetRect().w * 0.5) - EXP_WIDTH * 0.5;
							int y_pos = (human_object.GetRect().y + human_object.GetRect().h * 0.5) - EXP_HEIGHT * 0.5;
							exp_main.set_frame(ex);
							exp_main.SetRect(x_pos, y_pos);
							exp_main.ShowEx(g_screen);
							SDL_Delay(100);

							//update screen
							if (SDL_Flip(g_screen) == -1)
								return 0;
						}
						heart -= 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
						Mix_PlayMusic(g_sound_ingame[0], -1);
					}
					else if (is_col == 1)
					{
						level += 1;
						speech2 += 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
					}
				}
				for (int i = 0; i < NUM_Threat; i++)
				{

					ThreatObject* p_threat = (p_threats6 + i);
					p_threat->Show(g_screen);
					p_threat->HandleMove1(SCREEN_WIDTH, SCREEN_HEIGHT);
					p_threat->set_x_val(speech2);
					int is_col = CheckCollision(human_object.GetRect(), p_threat->GetRect());
					if (is_col == 0)
					{
						Mix_PlayMusic(g_sound_ingame[1], 0);
						for (int ex = 0; ex < 4; ex++)
						{
							int x_pos = (human_object.GetRect().x + human_object.GetRect().w * 0.5) - EXP_WIDTH * 0.5;
							int y_pos = (human_object.GetRect().y + human_object.GetRect().h * 0.5) - EXP_HEIGHT * 0.5;
							exp_main.set_frame(ex);
							exp_main.SetRect(x_pos, y_pos);
							exp_main.ShowEx(g_screen);
							SDL_Delay(100);

							//update screen
							if (SDL_Flip(g_screen) == -1)
								return 0;
						}
						heart -= 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
						Mix_PlayMusic(g_sound_ingame[0], -1);
					}
					else if (is_col == 1)
					{
						level += 1;
						speech2 += 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
					}
				}
			}
			else if (heart != 0 && level>=8 && level<=10)
			{
				 
				ApplySurface(g_bkground2, g_screen, 0, 0);
				human_object.Show(g_screen);
				if (heart == 3)
				{
					heart_.LoadImg("heart3.png");
					heart_.SetRect(675, 0);
					heart_.Show(g_screen);
				}
				else if (heart == 2)
				{
					heart_.LoadImg("heart2.png");
					heart_.SetRect(675, 0);
					heart_.Show(g_screen);
				}
				else if (heart == 1)
				{
					heart_.LoadImg("heart1.png");
					heart_.SetRect(675, 0);
					heart_.Show(g_screen);
				}
				if (level == 8)
				{
					level_.LoadImg("level8.png");
					level_.SetRect(680, 50);
					level_.Show(g_screen);
				}
				else if (level == 9)
				{
					level_.LoadImg("level9.png");
					level_.SetRect(680, 50);
					level_.Show(g_screen);
				}
				else if (level == 10)
				{
					level_.LoadImg("level10.png");
					level_.SetRect(680, 50);
					level_.Show(g_screen);
				}
				save.SetRect(350, 500);
				save.Show(g_screen);
				while (SDL_PollEvent(&geven))
				{
					human_object.HandleInputAction(geven);
					if (geven.type == SDL_MOUSEMOTION)//hàm kiểm tra di chuyển chuột
					{
						if (geven.motion.x >= 350 && geven.motion.x <= 440 && geven.motion.y >= 500 && geven.motion.y <= 545)
						{
							save.LoadImg("save2.png");
							save.Show(g_screen);
						}
						else {

							save.LoadImg("save.png");
							save.Show(g_screen);
						}
					}
					else if (geven.type == SDL_MOUSEBUTTONDOWN) //hàm kiểm tra bấm chuột
					{
						if (geven.motion.x >= 350 && geven.motion.x <= 440 && geven.motion.y >= 500 && geven.motion.y <= 545)
						{
							save_(heart, level);
							menu = 0;
						}
					}
				}
				for (int i = 0; i < NUM_Threat; i++)
				{
					ThreatObject* p_threat = (p_threats1 + i);
					p_threat->Show(g_screen);

					p_threat->HandleMove2(SCREEN_WIDTH, SCREEN_HEIGHT);
					p_threat->set_x_val(speech3);
					int is_col = CheckCollision(human_object.GetRect(), p_threat->GetRect());
					if (is_col == 0)
					{
						Mix_PlayMusic(g_sound_ingame[1], 0);
						for (int ex = 0; ex < 4; ex++)
						{
							int x_pos = (human_object.GetRect().x + human_object.GetRect().w * 0.5) - EXP_WIDTH * 0.5;
							int y_pos = (human_object.GetRect().y + human_object.GetRect().h * 0.5) - EXP_HEIGHT * 0.5;
							exp_main.set_frame(ex);
							exp_main.SetRect(x_pos, y_pos);
							exp_main.ShowEx(g_screen);
							SDL_Delay(100);

							//update screen
							if (SDL_Flip(g_screen) == -1)
								return 0;
						}
						heart -= 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
						Mix_PlayMusic(g_sound_ingame[0], -1);
					}
					else if (is_col == 1)
					{
						level += 1;
						speech3 += 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
					}
				}
				for (int i = 0; i < NUM_Threat; i++)
				{
					ThreatObject* p_threat = (p_threats7 + i);
					p_threat->Show(g_screen);

					p_threat->HandleMove1(SCREEN_WIDTH, SCREEN_HEIGHT);
					p_threat->set_x_val(speech3);
					int is_col = CheckCollision2(human_object.GetRect(), p_threat->GetRect());
					if (is_col == 0)
					{
						Mix_PlayMusic(g_sound_ingame[1], 0);
						for (int ex = 0; ex < 4; ex++)
						{
							int x_pos = (human_object.GetRect().x + human_object.GetRect().w * 0.5) - EXP_WIDTH * 0.5;
							int y_pos = (human_object.GetRect().y + human_object.GetRect().h * 0.5) - EXP_HEIGHT * 0.5;
							exp_main.set_frame(ex);
							exp_main.SetRect(x_pos, y_pos);
							exp_main.ShowEx(g_screen);
							SDL_Delay(100);

							//update screen
							if (SDL_Flip(g_screen) == -1)
								return 0;
						}
						heart -= 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
						Mix_PlayMusic(g_sound_ingame[0], -1);
					}
					else if (is_col == 1)
					{
						level += 1;
						speech3 += 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
					}
				}
				for (int i = 0; i < NUM_Threat; i++)
				{
					ThreatObject* p_threat = (p_threats8 + i);
					p_threat->Show(g_screen);

					p_threat->HandleMove2(SCREEN_WIDTH, SCREEN_HEIGHT);
					p_threat->set_x_val(speech3);
					int is_col = CheckCollision2(human_object.GetRect(), p_threat->GetRect());
					if (is_col == 0)
					{
						Mix_PlayMusic(g_sound_ingame[1], 0);
						for (int ex = 0; ex < 4; ex++)
						{
							int x_pos = (human_object.GetRect().x + human_object.GetRect().w * 0.5) - EXP_WIDTH * 0.5;
							int y_pos = (human_object.GetRect().y + human_object.GetRect().h * 0.5) - EXP_HEIGHT * 0.5;
							exp_main.set_frame(ex);
							exp_main.SetRect(x_pos, y_pos);
							exp_main.ShowEx(g_screen);
							SDL_Delay(100);

							//update screen
							if (SDL_Flip(g_screen) == -1)
								return 0;
						}
						heart -= 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
						Mix_PlayMusic(g_sound_ingame[0], -1);
					}
					else if (is_col == 1)
					{
						level += 1;
						speech3 += 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
					}
				}
				for (int i = 0; i < NUM_Threat; i++)
				{

					ThreatObject* p_threat = (p_threats6 + i);
					p_threat->Show(g_screen);
					p_threat->HandleMove1(SCREEN_WIDTH, SCREEN_HEIGHT);
					p_threat->set_x_val(speech3);
					int is_col = CheckCollision(human_object.GetRect(), p_threat->GetRect());
					if (is_col == 0)
					{
						Mix_PlayMusic(g_sound_ingame[1], 0);
						for (int ex = 0; ex < 4; ex++)
						{
							int x_pos = (human_object.GetRect().x + human_object.GetRect().w * 0.5) - EXP_WIDTH * 0.5;
							int y_pos = (human_object.GetRect().y + human_object.GetRect().h * 0.5) - EXP_HEIGHT * 0.5;
							exp_main.set_frame(ex);
							exp_main.SetRect(x_pos, y_pos);
							exp_main.ShowEx(g_screen);
							SDL_Delay(100);

							//update screen
							if (SDL_Flip(g_screen) == -1)
								return 0;
						}
						heart -= 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
						Mix_PlayMusic(g_sound_ingame[0], -1);
					}
					else if (is_col == 1)
					{
						level += 1;
						speech3 += 1;
						human_object.SetRect(0, 0);
						human_object.Show(g_screen);
					}
				}
			}
			else if (heart != 0 && level>10)
			{
			
			//reset lại tốc độ
			speech = 1; 
			speech2 = 1;
			speech3 = 1;
				g_bkground3 = LoadImage("youwin.png");
				ApplySurface(g_bkground3, g_screen, 0, 0);
				quit.SetRect(10, 550);
				quit.Show(g_screen);
				Continue.SetRect(615, 550);
				Continue.Show(g_screen);
				while (SDL_PollEvent(&geven))
				{
					human_object.HandleInputAction(geven);
					if (geven.type == SDL_MOUSEMOTION)
					{
						if (geven.motion.x >= 615 && geven.motion.x <= 790 && geven.motion.y >= 550 && geven.motion.y <= 595)
						{
							Continue.LoadImg("continue2.png");
							Continue.Show(g_screen);
						}
						else if (geven.motion.x >= 10 && geven.motion.x <= 100 && geven.motion.y >= 550 && geven.motion.y <= 595)
						{
							quit.LoadImg("quit2.png");
							quit.Show(g_screen);
						}
						else {
							Continue.LoadImg("continue.png");
							Continue.Show(g_screen);
							quit.LoadImg("quit.png");
							quit.Show(g_screen);
						}
					}
					else if (geven.type == SDL_MOUSEBUTTONDOWN)
					{
						if (geven.motion.x >= 615 && geven.motion.x <= 790 && geven.motion.y >= 550 && geven.motion.y <= 595)
						{
							heart = 3;
							level = 1;
						}
						else if (geven.motion.x >= 10 && geven.motion.x <= 100 && geven.motion.y >= 550 && geven.motion.y <= 595)
						{
							menu = 0;
							heart = 3;
							level = 1;
						}

					}
				}
			}
			else if (heart == 0) //khi thua
			{

			speech = 1;
			speech2 = 1;
			speech3 = 1;
				g_bkground3 = LoadImage("youlose.png");
				ApplySurface(g_bkground3, g_screen, 0, 0);
				if (level == 1)
				{
					level_.LoadImg("level_1.png");
					level_.SetRect(300, 200);
					level_.Show(g_screen);
				}
				else if (level == 2)
				{
					level_.LoadImg("level_2.png");
					level_.SetRect(300, 200);
					level_.Show(g_screen);
				}
				else if (level == 3)
				{
					level_.LoadImg("level_3.png");
					level_.SetRect(300, 200);
					level_.Show(g_screen);
				}
				else if (level == 4)
				{
					level_.LoadImg("level_4.png");
					level_.SetRect(300, 200);
					level_.Show(g_screen);
				}
				else if (level == 5)
				{
					level_.LoadImg("level_5.png");
					level_.SetRect(300, 200);
					level_.Show(g_screen);
				}
				else if (level == 6)
				{
					level_.LoadImg("level_6.png");
					level_.SetRect(300, 200);
					level_.Show(g_screen);
				}
				else if (level == 7)
				{
					level_.LoadImg("level_7.png");
					level_.SetRect(300, 200);
					level_.Show(g_screen);
				}
				else if (level == 8)
				{
					level_.LoadImg("level_8.png");
					level_.SetRect(300, 200);
					level_.Show(g_screen);
				}
				else if (level == 9)
				{
					level_.LoadImg("level_9.png");
					level_.SetRect(300, 200);
					level_.Show(g_screen);
				}
				else if (level == 10)
				{
					level_.LoadImg("level_10.png");
					level_.SetRect(300, 200);
					level_.Show(g_screen);
				}
				quit.SetRect(10, 550);
				quit.Show(g_screen);
				Continue.SetRect(615, 550);
				Continue.Show(g_screen);
			
				while (SDL_PollEvent(&geven))
				{
					human_object.HandleInputAction(geven);
					if (geven.type == SDL_MOUSEMOTION)
					{
						if (geven.motion.x >= 615 && geven.motion.x <= 790 && geven.motion.y >= 550 && geven.motion.y <= 595)
						{
							Continue.LoadImg("continue2.png");
							Continue.Show(g_screen);
						}
						else if (geven.motion.x >= 10 && geven.motion.x <= 100 && geven.motion.y >= 550 && geven.motion.y <= 595)
						{
							quit.LoadImg("quit2.png");
							quit.Show(g_screen);
						}
						else {
							Continue.LoadImg("continue.png");
							Continue.Show(g_screen);
							quit.LoadImg("quit.png");
							quit.Show(g_screen);
						}
					}
					else if (geven.type == SDL_MOUSEBUTTONDOWN)
					{
						if (geven.motion.x >= 615 && geven.motion.x <= 790 && geven.motion.y >= 550 && geven.motion.y <= 595)
						{
							heart = 3;
							level = 1;
						}
						else if (geven.motion.x >= 10 && geven.motion.x <= 100 && geven.motion.y >= 550 && geven.motion.y <= 595)
						{
							menu = 0;
							heart = 3;
							level = 1;
	
						}

					}
				}
			}

		}
		else if (menu == 2)//about
		{
		g_bkground3 = LoadImage("menuabout.png");
		ApplySurface(g_bkground3, g_screen, 0, 0);
		quit.SetRect(10, 550);
		quit.Show(g_screen);
		while (SDL_PollEvent(&geven))
		{
			if (geven.type == SDL_MOUSEMOTION)
			{
				
				if (geven.motion.x >= 10 && geven.motion.x <= 100 && geven.motion.y >= 550 && geven.motion.y <= 595)
				{
					quit.LoadImg("quit2.png");
					quit.Show(g_screen);
				}
				else {
					quit.LoadImg("quit.png");
					quit.Show(g_screen);
				}
			}
			else if (geven.type == SDL_MOUSEBUTTONDOWN)
			{
				if (geven.motion.x >= 10 && geven.motion.x <= 100 && geven.motion.y >= 550 && geven.motion.y <= 595)
				{
					menu = 0;
				}

			}
		}
		 }
		else if(menu==3)//continue
		{
		Continue_(heart, level);
		if (level == 1)
		{
			speech = 1;
		}
		else if (level == 2)
		{
			speech = 2;
		}
		else if (level == 3)
		{
			speech = 3;
		}
		else if (level == 4)
		{
			speech = 4;
		}
		else if (level == 5)
		{
			speech2 = 1;
		}
		else if (level == 6)
		{
			speech2 = 2;
		}
		else if (level == 7)
		{
			speech2 = 3;
		}
		else if (level == 8)
		{
			speech3 = 1;
		}
		else if (level == 9)
		{
			speech3 = 2;
		}
		else if (level == 10)
		{
			speech3 = 3;
		}
		menu = 1;
		}	
	
		 //update screen
		 if (SDL_Flip(g_screen) == -1)
			 return 0;
	}
	delete[] p_threats1;//xe;làn 1;di chuyển từ phải sang trái 
	delete[] p_threats2;//xe;làn 2;di chuyển từ phải sang trái
	delete[] p_threats3;//xe;làn 3;di chuyển từ phải sang trái
	delete[] p_threats4;//xe;làn 4;di chuyển từ phải sang trái
	delete[] p_threats5;//xe;làn 2;di chuyển từ trái  sang phải
	delete[] p_threats6;//xe;làn 4;di chuyển từ trái  sang phải
	delete[] p_threats7;//thuyền;làn 2;di chuyển từ trái sang phải
	delete[] p_threats8;//thuyền;làn 3;di chuyển từ phải sang trái

	SDL_Quit();
	return 1;
}

