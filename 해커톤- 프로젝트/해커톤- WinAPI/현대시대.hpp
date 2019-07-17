

void 근대시대(EventManager& evt_mng)
{
	{
		EventMaker e("한국전쟁",  EventPriority::Normal);

		e->content =
			"대한민국 정부가 세워진지 2년도 안된 지금,\n\
남과 북으로 나눠진 대한민국에서 \n\
1952년 6월 25일 북한이 남한을 침입하였습니다.\n\
한 민족으로서 부끄럽기도 하고, 슬프기도 하지만 \n\
지금 북의 남침을 막지 못 한다면 \n\
영원히 우리 영토를 볼 수 없을수도 있습니다.\n\
우리는 이를 막기위해 대책을 세워야 합니다.";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "근대시대") return false;
			if (data.dict["한국전쟁"] == "")
			{
				data.dict["한국전쟁"] = "시작됨";
				return true;
			}
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "모든 군사를 최전선에 보냅시다!");
			s->content =
"군사들을 최전선에 보냅니다.\n\
자금-3";
			s->CanRun = [&](Gamedata& data) {
				return data.player.res.money >= 3;
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["한국전쟁"] = "최전방 배치";
				data.player.res.money -= 3;
			};
		}
		{
			EventSelectItemMaker s(e, "군사를 적절히 배치해야 안정적입니다!");
			s->content =
"군을 안정적으로 배치합니다.\n\
자금-1\n\
식량-2";
			s->CanRun = [&](Gamedata& data) {
				return (data.player.res.money >= 1 && data.player.res.food >= 2);
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["한국전쟁"] = "전쟁돌입";
				data.player.res.money -= 1;
				data.player.res.food -= 2;
			};
		}
		{
			EventSelectItemMaker s(e, "군 수뇌부들이 놀고 먹고 있는데 우리가 뭘 한들 바뀌겠습니까?");
			s->content =
				"급박하게 전쟁 준비를 하게 되어 \n\
인명 피해가 심해질 것 입니다.\n\
무력 -2\n\
인력 -4\n\
[실제로 남침을 당했을때 우리나라 군 수뇌부들은 육군본부 \n\
장교클럽에 모여서 놀고 먹었다고 한다.\n\
게다가 전방 사단의 경우는 전력의 대부분이 외박, 아니면 휴가였다고 한다.]";
			s->Effect = [&](Gamedata& data) {
				data.dict["한국전쟁"] = "전쟁돌입";
				data.player.res.milli -= 2;
				data.player.res.human -= 4;
			};
		}
	}

	//전쟁의 시작(반격)
	{
		EventMaker e("전쟁의 시작(반격)", EventPriority::Normal);

		e->content =
			"북한군이 38선을 넘어 우리의 영토를 향해 전진하고 있습니다.\n\
대한민국은 북한군에 대해 어떠한 조치를 해야 할 것입니다.\n\
더이상의 전진을 막던지, 또는  굳건히 영토에 남아 방어를 할것인지.\n\
";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "근대시대") return false;
			if (data.dict["한국전쟁"] == "최전방 배치")
			{
				data.dict["한국전쟁"] = "전쟁돌입";
				return true;
			}
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "최전방에 있는 군들에게 북에 대한 반격을 명령합니다.");
			s->content =
				"우리의 군은 준비가 덜 되었지만, \n\
위급한 상황일수록 더 강한 힘을 끌어 올 수도 있습니다.\n\
하지만 피해규모는 가히 상상할수 없을것입니다.\n\
낮은 확률로 반격을 성공합니다.\n\
자금+2\n\
무력-4\n\
인력-3";
			s->CanRun = [&](Gamedata& data) {
				return data.player.res.milli >= 3 && data.player.res.human >= 1;
			};

			s->Effect = [&](Gamedata& data) {

				if (evt_mng.RandomPercent(20))
				{
					data.dict["한국전쟁"] = "승리";
				}
				else
				{
					data.dict["한국전쟁"] = "전쟁돌입";
				}

				data.player.res.money += 2;
				data.player.res.milli -= 4;
				data.player.res.human -= 3;
			};
		}
		{
			EventSelectItemMaker s(e, "최전방에 있는 군들에게 북에 대한 방어를 명령합니다.");
			s->content =
				"우리 군을 좀더 준비시키고, \n\
최전방에서 방어를 할 수 있도록 합니다.\n\
하지만 조금 높은 확률로 방어가 뚤릴 수 있습니다.\n\
자금-3\n\
무력-1\n\
인력-1";
			s->CanRun = [&](Gamedata& data) {
				return data.player.res.money >= 1;
			};

			s->Effect = [&](Gamedata& data) {

				if (evt_mng.RandomPercent(35))
				{
					data.dict["한국전쟁"] = "승리";
				}
				else
				{
					data.dict["한국전쟁"] = "전쟁돌입";
				}

				data.player.res.money -= 3;
				data.player.res.milli -= 1;
				data.player.res.human -= 1;
			};
		}
	}

	//전쟁돌입
	{
		EventMaker e("전쟁돌입", EventPriority::Normal);

		e->content =
			"우리나라는 끊임없이 쳐들어오는 북한을 힘겹게 막아내고 있습니다. \n\
하지만 우리 군만으로는 이 전쟁을 끝내기 어려워 보입니다.";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "근대시대") return false;
			return data.dict["한국전쟁"] == "전쟁돌입";
		};

		{
			EventSelectItemMaker s(e, "미국에 원군을 요청합니다.");
			s->content =
				"미국에 원군을 요청하여 승리의 확률을 높인다.\n\
무력+4\n\
외교-2\n\
돈-2";
			s->CanRun = [&](Gamedata& data) {
				return 
					data.player.res.human >= 3 &&
					data.player.res.diplo >= 2 &&
					data.player.res.money >= 2;
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["한국전쟁"] = "승리";
				data.player.res.milli += 4;
				data.player.res.diplo -= 2;
				data.player.res.money -= 2;
			};
		}
		{
			EventSelectItemMaker s(e, "딴나라 힘은 필요 없고 우리 군만으로 충분합니다.");
			s->content = "지원요청을 하지 않습니다.\n\
높은 확률로 전쟁에서 패배합니다.";

			s->Effect = [&](Gamedata& data) {
				if (evt_mng.RandomPercent(70))
				{
					data.dict["한국전쟁"] = "패배";
				}
				else
				{
					data.dict["한국전쟁"] = "승리";
				}
			};
		}
	}	
} 