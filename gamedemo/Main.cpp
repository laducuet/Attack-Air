#include "Common_Function.h"
#include "MainObject.h"
#include <vector>
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "playerpower.h"
#include "TextObject.h"
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

#undef main


TTF_Font* g_font_text = NULL;


//hàm Init để khởi tạo các thuộc tính ban đầu.
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

	//khoi tao am thanh
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		return false;
	}

	//neu dung thi doc am thanh
	g_sound_bullet[0] = Mix_LoadWAV("lazer.wav");
	g_sound_bullet[1] = Mix_LoadWAV("danthuong.wav");

	g_sound_exp[0] = Mix_LoadWAV("beep-10.wav");


	if (g_sound_bullet[0]==NULL || g_sound_bullet[1]==NULL || g_sound_exp[0] == NULL)
	{
		
	}

	if (TTF_Init() < 0)
	{
		//std::string tmp = TTF_GetError();
		//printf("Error %s", TTF_GetError());
		return false;
	}



	g_font_text = TTF_OpenFont("Veramobd.ttf", 20);
	
	
	if (g_font_text == NULL)
	{
		return false;
	}
	return true;
}



int main(int arc , char* argv[])
{
	bool is_run_screen = true;
	int bkgn_x = 0; 
	bool is_quit = false;// quan ly vong lap
	
	if (Init() == false)
	{
		return 0;
	}

	g_bkground = SDLCommonFunc::LoadImage("bg4800.png");
	if (g_bkground == NULL)
	{
		return 0;
	}

	// hien thi so mang 

	playerpower player_power;
	player_power.Init();

	TextObject time_game;
	time_game.SetColor(TextObject::BLACK_TEXT);

	TextObject mark_game;
	mark_game.SetColor(TextObject::WHITE_TEXT);



	//SDLCommonFunc::ApplySurface(g_bkground, g_screen, 0, 0);
	// 
	// 
	//Make MainObject
	MainObject plane_object;
	plane_object.SetRect(100, 200);
	bool res = plane_object.LoadImg("plane_fly.png");

	if (!res)
	{
		return 0;
	}

	// load hieu ung vu no
	ExplosionObject exp_main;
	bool ret = exp_main.LoadImg("exp_main.png");
	exp_main.set_clip();
	if (ret == false)
	{
		return 0;
	}





	// Make ThreatObject

	ThreatObject* p_threats = new ThreatObject[NUM_THREATS];

	for (int t = 0; t < NUM_THREATS; t++)
	{

		ThreatObject* p_threat = (p_threats+t);
		if (p_threat)
		{
			bool ret = p_threat->LoadImg("af1.png");
			if (!ret)
			{
				return 0;
			}

			int rand_y = rand() % 400;
			if (rand_y > SCREEN_HEIGHT - 200)
			{
				rand_y = SCREEN_HEIGHT * 0.3;
			}

			p_threat->SetRect(SCREEN_WIDTH + t * 400, rand_y);
			p_threat->set_x_val(3);

			AmoObject* p_amo = new AmoObject();
			p_threat->InitAmo(p_amo);
		}
		
	}

	unsigned int die_number = 0;
	unsigned int mark_value = 0;

	int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_text);
	if (ret_menu == 1)
	{
		is_quit = true;
	}

	while (!is_quit)
	{
		while (SDL_PollEvent(&g_even))
		{	
			if (g_even.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			plane_object.HandleInputAction(g_even,g_sound_bullet);
		}
		
		//SDLCommonFunc::ApplySurface(g_bkground, g_screen, 0, 0);// load lai man hinh

		if (is_run_screen==true)
		{
			bkgn_x -= 2;
			if (bkgn_x <= -(WIDTH_BACKGROUND - SCREEN_WIDTH))
			{
				is_run_screen = false;
			}
			else
			{
				SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
			}
			//SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
		}
		else
		{
			SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
			//NUM_THREATS++;
		}

		//show so mang cua nguoi choi
		player_power.Render(g_screen);

		
		plane_object.HandleMove();
		plane_object.Show(g_screen);
		//plane_object.HandleMove();
		plane_object.MakeAmo(g_screen);

		//chay threat

		
		for (int tt = 0; tt < NUM_THREATS; tt++)
		{
			ThreatObject* p_threat = (p_threats + tt);
			if (p_threat)
			{
				p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->Show(g_screen);
				//p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
				/*if (SDL_Flip(g_screen) == -1)
					return 0;*/

				bool is_col1 = false;
				std::vector<AmoObject*> amo_arr = p_threat->GetAmoList();
				for (int am = 0; am < amo_arr.size(); am++)
				{
					AmoObject* p_amo = amo_arr.at(am);
					if (p_amo)
					{
						is_col1 = SDLCommonFunc::CheckCollision(p_amo->GetRect(), plane_object.GetRect());
						if (is_col1 == true)
						{
							p_threat->ResetAmo(p_amo);
							break;
						}
					}
				}


				//ktra xem nhan vat va ke thu co cham nhau ko
				bool is_col = SDLCommonFunc::CheckCollision(plane_object.GetRect(), p_threat->GetRect());
				if (is_col||is_col1)
				{
					for (int ex = 0; ex <= 4; ex++) 
					{
						int x_pos = (plane_object.GetRect().x + plane_object.GetRect().w * 0.5) - EXP_WIDTH * 0.5;
						int y_pos = (plane_object.GetRect().y + plane_object.GetRect().h * 0.5) - EXP_HEIGHT * 0.5;

						exp_main.set_frame(ex);
						exp_main.SetRect(x_pos, y_pos);
						exp_main.ShowEx(g_screen);


						if (SDL_Flip(g_screen) == -1)
							return 0;
					}
					Mix_PlayChannel(-1, g_sound_exp[0], 0);

					die_number++;
					if (die_number <= 2)
					{
						SDL_Delay(1000);
						plane_object.SetRect(100, 200);
						player_power.Decrease();
						player_power.Render(g_screen);

						if (SDL_Flip(g_screen) == -1)
						{
							delete[] p_threats;
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 0;
						}
					}
					else
					{
						/*if (MessageBox(NULL, L"Game Over", L"Info", MB_OK) == IDOK)
						{*/
						std::string mark = std::to_string(mark_value);
						int game_over = SDLCommonFunc::ShowGameOver(g_screen, g_font_text,mark);

						if (game_over == 1)
						{

							delete[] p_threats;
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 1;
						}
						
							/*delete[] p_threats;
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 1;*/

						//}
					}
				}

				// kiem tra dan va ke thu co cham nhau khong

				std::vector<AmoObject*> amo_list = plane_object.GetAmoList();
				for (int im = 0; im < amo_list.size(); im++)
				{
					AmoObject* p_amo = amo_list.at(im);
					if (p_amo!=NULL)
					{
						bool ret_col = SDLCommonFunc::CheckCollision(p_amo->GetRect(), p_threat->GetRect());
						if (ret_col)
						{
							mark_value++;
							p_threat->Reset(SCREEN_WIDTH + tt * 400);
							plane_object.RemoveAmo(im);
							Mix_PlayChannel(-1, g_sound_exp[0], 0);
						}
					}
				}

			}
		}

		// show thoi gian cua game
		std::string str_time = "Time: ";
		Uint32 time_val = SDL_GetTicks() / 1000;
		std::string str_val = std::to_string(time_val);
		str_time += str_val;

		time_game.SetText(str_time);
		time_game.SetRect(SCREEN_WIDTH - 200, 10);
		time_game.CreateGameText(g_font_text, g_screen);

		//show diem len 
		std::string val_str_mark = std::to_string(mark_value);
		std::string strMark("Mark: ");
		strMark += val_str_mark;

		mark_game.SetText(strMark);
		mark_game.CreateGameText(g_font_text, g_screen);

		if (SDL_Flip(g_screen) == -1)
		{
			return 0;
		}
			
	}
	delete[] p_threats;

	SDLCommonFunc::CleanUp();
	SDL_Quit();
	
	return 0;
}