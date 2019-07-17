#include "HanStorySystem.hpp"

void Load(EventManager& evt_mng)
{

	//국가 선택
	{
		EventMaker e("국가선택", EventPriority::Highest);

		e->content = "국가를 선택해 주세요. 국가마다 다양한 차이점이 있으니 신중하게 골라야 합니다.";

		e->CanStart = [&](Gamedata& data) {
			return data.dict["플레이어"] == "";
		};

		{
			EventSelectItemMaker s(e, "백제");
			s->content = "백제는 지리적 이점으로 다양한 동맹들을 가지고 있습니다.\
그리고 한반도의 농지의 많은부분을 차지하고 있습니다.";

			s->Effect = [&](Gamedata& data) {
				data.dict["플레이어"] = "백제";
				PlayerGive(7, 5, 4, 6, 3, 2);
			};
		}

		{
			EventSelectItemMaker s(e, "신라");
			s->content = "신라는 반도의 산맥을 끼고 있어서 방어에 유리합니다.";

			s->Effect = [&](Gamedata& data) {
				data.dict["플레이어"] = "백제";
				PlayerGive(4, 4, 3, 4, 6, 4);
			};
		}

		{
			EventSelectItemMaker s(e, "고구려");
			s->content = "고구려는 기름진 부여땅을 가지고 있으며 대규모로 말을 훈련할 수 있는 큰 평야를 가지고 있습니다.";

			s->Effect = [&](Gamedata& data) {
				data.dict["플레이어"] = "고구려";
				PlayerGive(6, 4, 4, 3, 7, 2);
			};
		}
	}

	//전쟁의 속삭임
	{
		EventMaker e("전쟁의 속삭임", EventPriority::Normal);

		e->content =
			"최근 왜구가 하나의 나라로 통일돼었고\n\
그 영향으로 왜구의 침략이 조직적이고 변화하였습니다.\n\
그에 비해 우리의 수군은 왜군이 쓸고지나간 자리의 \n\
눈 뜨고 지켜볼 수 밖에 없습니다.\n\
우리는 이를 막기위해 대책을 세워야 합니다.";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["임진왜란"] == "")
			{
				data.dict["임진왜란"] = "시작됨";
				return true;
			}
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "수군 장수들을 소집하라!");
			s->content =
				"수군장수를 소집합니다.\n\
자금-3";
			s->CanRun = [&](Gamedata& data) {
				return data.player.res.money >= 3;
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["임진왜란"] = "장수소집";
			};
		}
		{
			EventSelectItemMaker s(e, "해안가에 사람이 살지 못 하도록 해라!(해금령)");
			s->content =
				"해금령을 명령합니다.\n\
자금-1\n\
식량-2";
			s->CanRun = [&](Gamedata& data) {
				return (data.player.res.money >= 1 && data.player.res.food >= 2);
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["임진왜란"] = "전쟁돌입";
				data.dict["해금령"] = "예";
			};
		}
		{
			EventSelectItemMaker s(e, "허튼 소리 마라!");
			s->content =
				"아무 대비도 하지 않습니다.";
			s->Effect = [&](Gamedata& data) {
				data.dict["임진왜란"] = "전쟁돌입";
			};
		}
	}

	//장수소집
	{
		EventMaker e("소집된 수군 장수들", EventPriority::Normal);

		e->content =
			"수군장수들이 왜구에 대해 대책을 세우기 위해 한양에 모였습니다\n\
각자 자신의 의견을 주장하고 있습니다. 그러나 누가 지휘를 할지 판단을 하는건 당신입니다.";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["임진왜란"] == "장수소집")
			{
				data.dict["임진왜란"] = "전쟁돌입";
				return true;
			}
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "원균이 수군을 지휘하게 한다.");
			s->content =
				"그는 평소에 조정에 많은 세금을 바쳐왔습니다.\n\
그의 경제력은 믿을만합니다. 그러나 그의 전투력은 그렇지 않을 수도 있습니다.\n\
자금+3\n\
무력-3\n\
인력-1";
			s->CanRun = [&](Gamedata& data) {
				return data.player.res.milli >= 3 && data.player.res.human >= 1;
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["임진왜란"] = "전쟁돌입";
				data.player.res.money += 3;
				data.player.res.milli -= 3;
				data.player.res.human -= 1;
			};
		}
		{
			EventSelectItemMaker s(e, "이순신이 수군을 지휘하게 한다.");
			s->content =
				"그는 의롭기로 소문난 사람입니다. 그러나 그의 실력은 증명되지 않았습니다.\n\
자금-1\n\
무력+2\n\
인력+1";
			s->CanRun = [&](Gamedata& data) {
				return data.player.res.money >= 1;
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["임진왜란"] = "전쟁돌입";
				data.player.res.money -= 1;
				data.player.res.milli += 2;
				data.player.res.human += 1;
			};
		}
		{
			EventSelectItemMaker s(e, "적임자가 여기에 없는것 같다!");
			s->content =
				"그 누구에게도 맡길 수가 없다. 내가 직접 지휘하겠다.";
			s->Effect = [&](Gamedata& data) {
				data.dict["임진왜란"] = "전쟁돌입";
			};
		}
	}

	//전쟁돌입
	{
		EventMaker e("전쟁돌입", EventPriority::Normal);

		e->content =
			"왜구가 동래성에 상륙했다고 편지가 왔습니다. 왜구는 조선에게 길을 빌려 명을 치고자 하니 \n\
길만 빌려주면. 아무 피해도 입히지 않겠다고 약속했습니다.";

		e->CanStart = [&](Gamedata& data) {
			return data.dict["임진왜란"] == "전쟁돌입";
		};

		{
			EventSelectItemMaker s(e, "그들을 막아라! 간이 배 밖으로 나온게 분명하다!");
			s->content =
				"방어군을 파병합니다.\n\
무력-3\n\
인력-3\n\
식량-2\n\
돈-1";
			s->CanRun = [&](Gamedata& data) {
				return
					data.player.res.milli >= 3 &&
					data.player.res.human >= 3 &&
					data.player.res.food >= 2 &&
					data.player.res.money >= 1;
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["임진왜란"] = "왜와 전투";
				data.player.res.milli -= 3;
				data.player.res.human -= 3;
				data.player.res.food -= 2;
				data.player.res.money -= 1;
			};
		}
		{
			EventSelectItemMaker s(e, "길을 빌려주는 정도는 별 상관없지 않을까?\n\
피해도 안 입히겠다고 약속하지 않았는가?");
			s->content = "왜구에게 길을 빌려 줍니다.\n\
패배합니다.";

			s->Effect = [&](Gamedata& data) {
				data.dict["임진왜란"] = "끝";
			};
		}
		{
			EventSelectItemMaker s(e, "중국에서 내 몸을 지키겠다! 남은사람 끼리 알아서 해보아라!");
			s->content =
				"중국으로 대피합니다.\n\
";
			s->Effect = [&](Gamedata& data) {
				data.dict["임진왜란"] = "명의 개입";
			};
		}
	}
}

int main()
{
	EventManager evt_mng;

	Load(evt_mng);

	evt_mng.DefaultRun();
	
	return 0;
}