#include <iostream>
#include <vector>
#include <random>
#include <time.h>

using namespace std;


namespace ocean_life
{
	class Ocean_field
	{
		int width, height;
	public:
		char*** scene;
		Ocean_field(int width_inp, int height_inp)
		{
			width = width_inp;
			height = height_inp;
			scene = new char** [width];
			for (int i = 0; i < width; i++)
				scene[i] = new char* [height];

			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < height; j++)
				{
					scene[i][j] = new char[4];
					for (int k = 0; k < 4; k++)
					{
						scene[i][j][k] = ' ';
					}
				}
			}
		}

		void put_fish(int posX, int posY, int posI, char fish_type)
		{
			scene[posX][posY][posI] = fish_type;
		}

		void display_field();

		int get_width()
		{
			return width;
		}

		int get_height()
		{
			return height;
		}
	};


	class Organism
	{
	private:

	protected:
		char type;
		int age, id, hp, hp_max, food, food_max, moves;
		bool isMale;
		int location[3]; //3 coordinates - x, y, index

	public:
		
		Ocean_field* ocean_table;
		char get_type()
		{
			return type;
		}
		int get_age()
		{
			return age;
		}
		int get_id()
		{
			return id;
		}
		int get_hp()
		{
			return hp;
		}
		int get_hp_max()
		{
			return hp_max;
		}
		int get_food()
		{
			return food;
		}
		int get_food_max()
		{
			return food_max;
		}
		int get_moves()
		{
			return moves;
		}
		bool get_isMale()
		{
			return isMale;
		}
		int& get_location(int index)
		{
			return location[index];
		}
		void set_type(char inp_type)
		{
			this->type = inp_type;
		}
		void set_age(int inp_age)
		{
			this->age = inp_age;
		}
		void set_id(int inp_id)
		{
			this->id = inp_id;
		}
		void set_hp(int inp_hp)
		{
			this->hp = inp_hp;
		}
		void set_food(int inp_food)
		{
			this->food = inp_food;
		}
		void set_location(int coord, int count)
		{
			location[coord] = count;
		}
		virtual void aging(Organism* obj, int order)
		{
			obj->set_age(obj->get_age() + 1);
			obj->set_hp(obj->get_hp() - 1);
			if (obj->get_hp() <= 0)																					//
			{
				ocean_table->scene[obj->get_location(0)][obj->get_location(1)][obj->get_location(2)] = ' ';
			}
		}
	};

	class Plankton : public Organism
	{
	public:
		vector<Plankton> fish_plankton;
		void aging(Plankton* p_obj, int order) override
		{
			p_obj->set_age(p_obj->get_age() + 2);
			p_obj->set_hp(p_obj->get_hp() - 2);
			if (p_obj->get_hp() <= 0)
			{
				ocean_table->scene[p_obj->get_location(0)][p_obj->get_location(1)][p_obj->get_location(2)] = ' ';
				fish_plankton.erase(fish_plankton.begin() + order);
			}
		}
		Plankton()
		{
			hp_max = 3;
			hp = hp_max;
			moves = 1;
			age = 0;
			type = 'P';
		}
	};

	class Passive : public Organism
	{
		vector<Passive> fish_passive;
		void aging(Passive* pas_obj, int order)  override
		{
			pas_obj->set_age(pas_obj->get_age() + 2);
			pas_obj->set_hp(pas_obj->get_hp() - 2);
			if (pas_obj->get_hp() <= 0)
			{
				ocean_table->scene[pas_obj->get_location(0)][pas_obj->get_location(1)][pas_obj->get_location(2)] = ' ';
				fish_passive.erase(fish_passive.begin() + order);
			}
		}
	};

	class Clownfish : public Passive
	{
	public:
		Clownfish(string sex)
		{
			hp_max = 15; hp = hp_max;
			food_max = 10; food = food_max;
			moves = 3;
			age = 0;
			type = 'C';
			if (sex == "Male")
				isMale = true;
			if (sex == "Female")
				isMale = false;
			if (sex == "Random")
				isMale = rand() % 2;
		}
	};

	class Fugu : public Passive
	{
	public:
		Fugu(string sex)
		{
			hp_max = 20;
			hp = hp_max;
			food_max = 10;
			food = food_max;
			moves = 3;
			age = 0;
			type = 'F';
			if (sex == "Male")
				isMale = true;
			if (sex == "Female")
				isMale = false;
			if (sex == "Random")
				isMale = rand() % 2;
		}
	};

	class Aggressive : public Organism
	{
	protected:
		int damage;
	public:
		vector<Aggressive> fish_aggressive;
		void aging(Aggressive* agr_obj, int order)  override
		{
			agr_obj->set_age(agr_obj->get_age() + 2);
			agr_obj->set_hp(agr_obj->get_hp() - 2);
			if (agr_obj->get_hp() <= 0)
			{
				ocean_table->scene[agr_obj->get_location(0)][agr_obj->get_location(1)][agr_obj->get_location(2)] = ' ';
				fish_aggressive.erase(fish_aggressive.begin() + order);
			}
		}
		int get_damage()
		{
			return damage;
		}
	};

	class Killerwhale : public Aggressive
	{
	public:
		Killerwhale(string sex)
		{
			hp_max = 120;
			hp = hp_max;
			food_max = 30;
			food = food_max;
			moves = 4;
			damage = 15;
			age = 0;
			type = 'K';
			if (sex == "Male")
				isMale = true;
			if (sex == "Female")
				isMale = false;
			if (sex == "Random")
				isMale = rand() % 2;
		}
	};

	class Shark : public Aggressive
	{
	public:
		Shark(string sex)
		{
			hp_max = 150;
			hp = hp_max;
			food_max = 25;
			food = food_max;
			moves = 4;
			damage = 17;
			age = 0;
			type = 'S';
			if (sex == "Male")
				isMale = true;
			if (sex == "Female")
				isMale = false;
			if (sex == "Random")
				isMale = rand() % 2;
		}
	};

	class Neutral : public Organism
	{
	protected:
		int damage;
	public:
		vector<Neutral> fish_neutral;
		void aging(Neutral* neu_obj, int order)  override
		{
			neu_obj->set_age(neu_obj->get_age() + 2);
			neu_obj->set_hp(neu_obj->get_hp() - 2);
			if (neu_obj->get_hp() <= 0)
			{
				ocean_table->scene[neu_obj->get_location(0)][neu_obj->get_location(1)][neu_obj->get_location(2)] = ' ';
				fish_neutral.erase(fish_neutral.begin() + order);
			}
		}
		int get_damage()
		{
			return damage;
		}
	};

	class Whale : public Neutral
	{
	public:
		Whale(string sex)
		{
			hp_max = 300;
			hp = hp_max;
			food_max = 35;
			food = food_max;
			moves = 2;
			age = 0;
			type = 'W';
			if (sex == "Male")
				isMale = true;
			if (sex == "Female")
				isMale = false;
			if (sex == "Random")
				isMale = rand() % 2;
		}
	};

	class Dolphin : public Neutral
	{
	public:
		Dolphin(string sex)
		{
			hp_max = 100;
			hp = hp_max;
			food_max = 20;
			food = food_max;
			moves = 5;
			damage = 25;
			age = 0;
			type = 'D';
			if (sex == "Male")
				isMale = true;
			if (sex == "Female")
				isMale = false;
			if (sex == "Random")
				isMale = rand() % 2;
		}
	};


	class Ocean_master
	{

		vector<Whale> fish_whale;
		int whale_number;
		vector<Dolphin> fish_dolphin;
		int dolphin_number;
		vector<Killerwhale> fish_killerwhale;
		int killerwhale_number;
		vector<Shark> fish_shark;
		int shark_number;
		vector<Clownfish> fish_clownfish;
		int clownfish_number;
		vector<Fugu> fish_fugu;
		int fugu_number;
		vector<Plankton> fish_plankton;
		int plankton_number;
		Plankton* p_extra = new Plankton();
		Clownfish* cl_extra = new Clownfish("Random");
		Fugu* f_extra = new Fugu("Random");
		Dolphin* d_extra = new Dolphin("Random");
		Whale* w_extra = new Whale("Random");

		int* find_empty_cell(bool isPlankton);

		//PLANKTON

		void Plankton_move(Plankton* p_obj);

		void Plankton_replicate(Plankton* p_obj);

		void Plankton_age(Plankton* p_obj, int order);*/

		//PASSIVES

		void Passive_move(Passive* c_obj);

		void Passive_eat(Passive* c_obj);

		void Passive_replicate(Passive* c_obj);

		void Passive_age(Passive* c_obj, int order);*/

		//NEUTRALS

		void Neutral_move(Neutral* c_obj);

		void Neutral_eat(Neutral* c_obj);

		void Neutral_replicate(Neutral* c_obj);

		void Neutral_age(Neutral* c_obj, int order);*/

		//AGGRESSIVES

		void Aggressive_move(Aggressive* c_obj);

		void Aggressive_eat(Aggressive* c_obj);

		void Aggressive_replicate(Aggressive* c_obj);

		void Aggressive_age(Aggressive* c_obj, int order);*/

		//EVERYTHING ELSE

		Plankton& return_plankton(int x, int y);

		Clownfish& return_clownfish(int x, int y);

		Fugu& return_fugu(int x, int y);

		Dolphin& return_dolphin(int x, int y);

		Whale& return_whale(int x, int y);

		int empty_place(int x, int y, bool isPlankton); //checking what cell is available for moving into

	public:
		Ocean_field* ocean_table;
		Ocean_master(int width_inp, int height_inp)
		{
			srand(time(0));
			ocean_table = new Ocean_field(width_inp, height_inp);
			whale_number = 0;
			dolphin_number = 0;
			killerwhale_number = 0;
			shark_number = 0;
			clownfish_number = 0;
			fugu_number = 0;
			plankton_number = 0;
		}

		void Tick();

		void Show();

		void start_random_place(int w_c, int d_c, int k_c, int s_c, int c_c, int f_c, int p_c);

		void UpdateMap();
	};
}