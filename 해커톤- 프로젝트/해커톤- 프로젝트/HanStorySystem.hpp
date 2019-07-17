#include <unordered_set>
#include <unordered_map>
#include <string>
#include <functional>
#include <list>
#include <stdexcept>
#include <iostream>
#include <random>
#include <stdlib.h>

using namespace std;

extern class EventManager;
static EventManager* mainEventmgr = nullptr;

struct Resource { //자원 구조체
	int food =  10; //삭량 자원
	int human = 10;//인력 자원
	int money = 10;//돈   자원
	int faith = 10;//신앙 자원
	int milli = 10;//무력 자원
	int diplo = 10;//외교 자원
};

void ShowResource(const Resource& r) {
	
	cout << "식량:";
	if (r.food < 5) { cout << "없음"; }
	else if (r.food < 10) { cout << "부족"; }
	else if (r.food < 15) { cout << "보통"; }
	else { cout << "풍족"; }
	cout << "   ";
	cout << "인력:";
	if (r.human < 5) { cout << "없음"; }
	else if (r.human < 10) { cout << "부족"; }
	else if (r.human < 15) { cout << "보통"; }
	else { cout << "풍족"; }
	cout << "   ";
	cout << "돈　:";
	if (r.money < 5) { cout << "없음"; }
	else if (r.money < 10) { cout << "부족"; }
	else if (r.money < 15) { cout << "보통"; }
	else { cout << "풍족"; }
	cout << "   ";
	cout << "외교:";
	if (r.diplo < 5) { cout << "없음"; }
	else if (r.diplo < 10) { cout << "부족"; }
	else if (r.diplo < 15) { cout << "보통"; }
	else { cout << "풍족"; }
	cout << "   ";
	cout << "무력:";
	if (r.milli < 5) { cout << "없음"; }
	else if (r.milli < 10) { cout << "부족"; }
	else if (r.milli < 15) { cout << "보통"; }
	else { cout << "풍족"; }
	cout << "   ";
	cout << "신앙:";
	if (r.faith < 5) { cout << "없음"; }
	else if (r.faith < 10) { cout << "부족"; }
	else if (r.faith < 15) { cout << "보통"; }
	else { cout << "풍족"; }
	cout << "   " << endl;
}

class Item {
public:
	const string name; //아이템 이름

	const int cost;
	Resource effect;//아이템 효과;

	std::vector<string> childItem;

	Item(const string first, const int cost, const Resource effect, const std::vector<string> childItem) : name(first), cost(cost), effect(effect), childItem(childItem) {
		
	}
};

struct Player //플레이어 구조체
{ 
	list<Item> inventory;//아이템 목록
	Resource res; //자원
	int rank = 0; //랭크 포인트
};



struct Gamedata
{
	Player player;
	unordered_map<string, string> dict;
	unordered_map<string, int> delay;
};

static bool AlwaysTrue(Gamedata&) { return true; } //항상 참

class EventSelectItem //이벤트 선택지 구조체
{
public:
	string name = "null";//이벤트 선택지의 이름
	string content = "null";//이벤트 선택지의 내용
	function<bool(Gamedata&)> CanVisible = AlwaysTrue; //표시 가능한지 알려주는 함수
	function<bool(Gamedata&)> CanRun = AlwaysTrue; //실행 가능한지 알려주는 함수
	function<void(Gamedata&)> Effect; //선택하면 적용되는 효과 함수

	EventSelectItem() = delete;
	EventSelectItem(string _name = "제목 없음") :name(_name) {

	}
};

enum class EventPriority //이벤트 우선순위
{
	None,   //없음
	Lowest, //매우 낮음
	Low,    //낮음
	Normal, //중간
	High,   //높음
	Highest, //매우 높음
};

class Event //이벤트 구조체
{
public:
	function<bool(Gamedata&)> CanStart = AlwaysTrue; //시작 가능한지 알려주는 함수
	string name; //이벤트의 제목
	string content; //이벤트에 표시될 내용
	vector<EventSelectItem> item;  //이벤트의 선택지
	EventPriority prio = EventPriority::Normal; //이벤트의 우선순위

	Event() = delete;

	Event(string _name = "제목 없음", EventPriority _prio = EventPriority::Normal) :name(_name), prio(_prio) {

	}


};

class EventManager
{
	list<Event> event;
public:
	Gamedata gamedata;
	mt19937_64 rand;
	vector<Item> allItem;

	EventManager()
	{
		std::random_device rd;
		rand = mt19937_64(rd());
		mainEventmgr = this;
	}

	bool RandomPercent(const float& percent)
	{
		return ((rand() % 10001) / 100.f) < percent;
	}

	int RandomInt(const int& min, const int& max)
	{
		return rand() % (max - min + 1) + min;
	}

	void AddEvent(const Event e)
	{
		event.push_back(e);
	}

	const Event GetNewEvent()
	{
		EventPriority p = EventPriority::None;

		Event _return("null");
		for (auto& e : event)
		{
			if (e.prio > p && e.CanStart(gamedata))
			{
				p = e.prio;
				_return = e;
			}
		}
		if (p != EventPriority::None)
		{
			return _return;
		}

		throw out_of_range("EventManager Throw: 가능한 이벤트가 없습니다");
	}

	bool RandomAverageTurn(const string name, const int delay)
	{
		if (gamedata.delay.find(name) == gamedata.delay.end())
		{
			gamedata.delay[name] = 5 * delay;
			return false;
		}
		else
		{
			gamedata.delay[name] -= RandomInt(1, 9);
			if (gamedata.delay[name] <= 0)
			{
				gamedata.delay.erase(name);
				return  true;
			}
			else return false;
		}
	}
	

	void DefaultRun()
	{
		try
		{
			bool Loop = true;
			while (Loop)
			{
				system("cls");
				auto& e = GetNewEvent();
				cout << "\n=== " << e.name << " ===" << endl << e.content << endl << endl;

				while (true)
				{
					cout << "[" << gamedata.dict["플레이어"] << "]";
					ShowResource(gamedata.player.res);
					size_t i = 1;
					for (const auto& s : e.item)
					{
						if (s.CanVisible(gamedata))
						{
							cout << i << ". " << s.name;
							cout << endl;
						}
						++i;
					}

					if (i == 1)
					{
						cin.ignore();
					}
					else
					{
						cout << endl << "숫자를 적어 선택해주세요 : ";
						cin >> i;

						auto& sec = e.item.at(i - 1);

						cout << endl << sec.content << endl;

						//if (sec.CanRun(gamedata))
						{
							cout << "이것으로 결정하겠습니까? (y/n) : ";
							char c;
							while (true)
							{
								cin >> c;
								if (c == 'y' || c == 'n') break;
							}
							if (c == 'y')
							{
								sec.Effect(gamedata);
								if (gamedata.player.res.diplo < 0)
								{
									if (-gamedata.player.res.diplo <= gamedata.player.res.faith)
									{
										gamedata.player.res.faith += gamedata.player.res.diplo;
										gamedata.player.res.diplo = 0;
									}
									else
									{
										cout << "당신의 국가는 멸망했습니다.\n그 누구도 당신의 외침을 들으려 하지 않습니다. 외교적인 노력의 부족함이 낳은 결과입니다...";
										Loop = false;
										break;
									}
								}
								if (gamedata.player.res.milli < 0)
								{
									if (-gamedata.player.res.milli <= gamedata.player.res.faith)
									{
										gamedata.player.res.faith += gamedata.player.res.milli;
										gamedata.player.res.milli = 0;
									}
									else
									{
										cout << "당신의 국가는 멸망했습니다.\n당신의 군대는 싸우려 하지 않고 후퇴에 후퇴를 거듭한 끝에 당신의 궁성에 도달했습니다.\n군사적 노력의 부족함이 낳은 결과입니다...";
										Loop = false;
										break;
									}
								}
								if (gamedata.player.res.food < 0)
								{
									if (-gamedata.player.res.food <= gamedata.player.res.faith)
									{
										gamedata.player.res.faith += gamedata.player.res.food;
										gamedata.player.res.food = 0;
									}
									else
									{
										cout << "당신의 국가는 멸망했습니다.\n당신의 식량창고에는 단 한 톨의 쌀도 남지 않았으며 궁성의 관리들은 전부 도망 쳤습니다.\n식량이 없이는 어떤 국가도 존속할 수 없습니다.";
										Loop = false;
										break;
									}
								}
								if (gamedata.player.res.human < 0)
								{
									if (-gamedata.player.res.human <= gamedata.player.res.faith)
									{
										gamedata.player.res.faith += gamedata.player.res.human;
										gamedata.player.res.human = 0;
									}
									else
									{
										cout << "당신의 국가는 멸망했습니다.\n아무도 성에 남아 있지 않습니다. 더 이상 부족이라고도 부끄러운 수준입니다. \n 사람이 있어야 국가도 있는법입니다.";
										Loop = false;
										break;
									}
								}
								if (gamedata.player.res.money < 0)
								{
									if (-gamedata.player.res.money <= gamedata.player.res.faith)
									{
										gamedata.player.res.faith += gamedata.player.res.money;
										gamedata.player.res.money = 0;
									}
									else
							                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            		{
										cout << "당신의 국가는 멸망했습니다.\n더 이상 관리에게 지급해줄 돈이 없고 관리는 이에 질려 모두 궁성을 떠났습니다.\n돈이 없다면 아무것도 할 수 없습니다.";
										Loop = false;
										break;
									}
								}
								if (gamedata.player.res.faith < 0)
								{
									cout << "당신의 국가는 멸망했습니다.\n당신은 국가의 통치자이지만 그 누구도 당신의 결정을 신뢰하지도 않고 따르지 않습니다.\n신앙이 없다면 우리의 통치는 억압과 다름 없습니다.";
									Loop = false;
									break;
								}
								break;
							}
						}
						cout << endl;

						cin.ignore();
					}
				}
			}
		}
		catch (exception e)
		{
			cout << e.what() << endl;
		}
	}
};




class EventMaker {
	Event e;
public:

	EventMaker(string first, EventPriority second) : e(first, second)  {
		
	}

	[[nodiscard]] Event* operator-> () {
		return &e;
	}

	Event* _Ptr() {
		return &e;
	}
	
	~EventMaker()
	{
		mainEventmgr->AddEvent(e);
	}
};

class EventSelectItemMaker {
	EventSelectItem s;
	Event* e;
public:

	EventSelectItemMaker(EventMaker& first, string second) : s(second) {
		e = first._Ptr();
	}

	[[nodiscard]] EventSelectItem* operator-> () {
		return &s;
	}

	~EventSelectItemMaker()
	{
		e->item.push_back(s);
	}
};

void PlayerGive(int food, int human, int money, int diplo, int milli, int faith)
{
	mainEventmgr->gamedata.player.res.food += food;
	mainEventmgr->gamedata.player.res.human += human;
	mainEventmgr->gamedata.player.res.money += money;
	mainEventmgr->gamedata.player.res.diplo += diplo;
	mainEventmgr->gamedata.player.res.milli += milli;
	mainEventmgr->gamedata.player.res.faith += faith;
}

void PlayerUse(int food, int human, int money, int diplo, int milli, int faith)
{
	mainEventmgr->gamedata.player.res.food -= food;
	mainEventmgr->gamedata.player.res.human -= human;
	mainEventmgr->gamedata.player.res.money -= money;
	mainEventmgr->gamedata.player.res.diplo -= diplo;
	mainEventmgr->gamedata.player.res.milli -= milli;
	mainEventmgr->gamedata.player.res.faith -= faith;
}
