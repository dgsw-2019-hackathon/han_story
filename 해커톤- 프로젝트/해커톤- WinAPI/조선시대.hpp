
void 조선시대(EventManager& evt_mng)
{
	{
		EventMaker e("위화도회군", EventPriority::Normal);

		e->content =
			"우왕과 최영은 요동 정벌이라는 무리한 요구를 하고 있습니다.\n\
이성계는 사불가론을 들며 반대하였지만 결국 우왕은 단행하였습니다.\n\
위화도에 도착하였습니다.지금 한창 장마철이므로 활은 아교가 풀어지고, 많은 군사들은 역병을 앓을 것입니다";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["위화도회군"] == "" && data.dict["고려탄생"] == "조선건국")
			{
				data.dict["위화도회군"] = "시작됨";
				return true;
			}
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "군대를 개경으로 돌리자!");
			s->content =
				"군대를 돌려 개경으로 돌려 쿠데타를 일으킵니다.\n\
식량-";

			s->Effect = [&](Gamedata& data) {
				data.dict["위화도회군"] = "돌입";
			};
		}

		{
			EventSelectItemMaker s(e, "요동을 정벌하러 가자!");
			s->content =
				"요동을 정벌하러 갑니다\n\
군사력--";
			s->Effect = [&](Gamedata& data) {
				data.dict["위화도회군"] = "종료";
				data.player.res.milli -= 10000;
			};
		}
	}

	//위화도 회군
	{
		EventMaker e("위화도회군", EventPriority::Normal);

		e->content =
			"개경에 도착하였습니다. 이제 무엇을 할지는 당신의 선택입니다.";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["위화도회군"] == "돌입")
			{
				data.dict["위화도회군"] = "종료";
				return true;
			}
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "우왕을 죽이고 쿠데타를 일으킨다.");
			s->content = "쿠데타를 일으킵니다. 이성계는 조선을 빠르게 건국하게 됩니다.\n\
자금-\n\
인력-\n\
신앙+\n\
군사력+";


			s->Effect = [&](Gamedata& data) {
				data.dict["위화도회군"] = "종료";
				data.dict["플레이어"] = "조선";
				data.dict["시대"] = "조선시대";
				data.player.res.money -= 1;
				data.player.res.milli += 2;
				data.player.res.human -= 1;
				data.player.res.faith += 1;
			};
		}

		{
			EventSelectItemMaker s(e, "도저히 칠 수 없었다고 우왕에게 고한다.");
			s->content = "우왕은 크게 노하며 이성계의 관직을 박탈합니다.\n\
신앙-";


			s->Effect = [&](Gamedata& data) {
				data.dict["위화도회군"] = "종료";
				data.player.res.faith -= 10000;
			};
		}
	}

	{
		EventMaker e("훈민정음창제", EventPriority::Normal);
		e->content =
			"하루종일 먹고살기 위해 일을 하는 백성들이 한자를 배우기엔 어려웠지만,\n\
새로운 문자를 만들자니 귀족들의 반발이 너무 거세었다";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "조선시대") return false;
			if (data.dict["훈민정음창제"] == "")
			{
				data.dict["훈민정음창제"] = "시작됨";
				return true;
			}
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "기존의 한자를 계속 사용!");
			s->content =
				"백성들은 계속 문자를 모르고 살게되고,\n\
훗날에도 우리나라는 발전하지 못합니다\n\
신앙-";

			s->Effect = [&](Gamedata& data) {
				data.player.res.faith -= 10000;
			};
		}

		{
			EventSelectItemMaker s(e, "훈민정음을 만드는거다!");
			s->content =
				"훈민정음을 창제를 시작합니다\n\
자금-신앙+인력+";
			s->Effect = [&](Gamedata& data) {
				data.dict["훈민정음창제"] = "창제";
				data.player.res.money -= 2;
				data.player.res.money += 1;
				data.player.res.faith += 2;
			};
		}
	}

	//훈민정음 창제
	{
		EventMaker e("훈민정음창제", EventPriority::Normal);

		e->content =
			"당신(세종)의 눈건강이 나빠져 더 이상 훈민정음을 창제하긴 힘듭니다\n\
다른 사람에게 맡기세요";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "조선시대") return false;
			if (data.dict["훈민정음창제"] == "창제")
			{
				data.dict["훈민정음창제"] = "종료";
				return true;
			}
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "집현전 학자들한테 맡긴다.");
			s->content = "집현전 학자들이 세종이 원하는 바를\n\
이뤄낼지는 의문입니다. 하지만 실력이 매우 뛰어난 학자들이죠.\n\
자금-\n\
인력-\n\
신앙+";


			s->Effect = [&](Gamedata& data) {
				data.dict["훈민정음창제"] = "종료";
				data.player.res.money -= 1;
				data.player.res.human -= 1;
				data.player.res.faith += 1;
			};
		}

		{
			EventSelectItemMaker s(e, "내가 직접 만들겠다");
			s->content = "좀더 정확하게 만들수 있겠지만,세종의 건강이 악화될 수 있습니다.\n\
신앙-";


			s->Effect = [&](Gamedata& data) {
				data.dict["훈민정음창제"] = "종료";
				data.player.res.faith -= 10000;
			};
		}
	}
	{
		EventMaker e("환국", EventPriority::Low);
		e->content =
			"조선의 궁궐에서 환국이 일어났습니다. 의정부에는 새로운 관리가 등용되었습니다.";

		e->CanStart = [&](Gamedata& data) {
			return evt_mng.RandomInt(0, 4) == 0;
		};


		{
			EventSelectItemMaker s(e, "그놈이 그놈이다.");
			s->content =
				"외교력+";
			s->Effect = [&](Gamedata& data) {
				data.player.res.diplo += 2;
			};
		}
	}
	{
		EventMaker e("사화", EventPriority::Low);
		e->content =
			"조선의 궁궐에서 사화이 일어났습니다. 썩 유쾌하지 않은 기분입니다.";

		e->CanStart = [&](Gamedata& data) {
			return evt_mng.RandomInt(0, 6) == 0;
		};


		{
			EventSelectItemMaker s(e, "젠장");
			s->content =
				"외교력-";
			s->Effect = [&](Gamedata& data) {
				data.player.res.diplo -= 2;
			};
		}
	}


	//전쟁의 속삭임
	{
		EventMaker e("전쟁의 속삭임", EventPriority::Highest);

		e->content =
			"최근 왜구가 하나의 나라로 통일돼었고\n\
그 영향으로 왜구의 침략이 조직적이고 변화하였습니다.\n\
그에 비해 우리의 수군은 왜군이 쓸고지나간 자리의 \n\
눈 뜨고 지켜볼 수 밖에 없습니다.\n\
우리는 이를 막기위해 대책을 세워야 합니다.";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["임진왜란"] == "" && evt_mng.RandomInt(0, 6) == 0)
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
자금-";

			s->Effect = [&](Gamedata& data) {
				data.dict["임진왜란"] = "장수소집";
			};
		}
		{
			EventSelectItemMaker s(e, "해안가에 사람이 살지 못 하도록 해라!(해금령)");
			s->content =
				"해금령을 명령합니다.\n\
자금-\n\
식량-";

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
자금+\n\
무력-\n\
인력-";

			s->Effect = [&](Gamedata& data) {
				data.dict["임진왜란"] = "전쟁돌입";
				data.player.res.money += 7;
				data.player.res.milli -= 3;
				data.player.res.human -= 1;
			};
		}
		{
			EventSelectItemMaker s(e, "이순신이 수군을 지휘하게 한다.");
			s->content =
				"그는 의롭기로 소문난 사람입니다. 그러나 그의 실력은 증명되지 않았습니다.\n\
자금-\n\
무력+\n\
인력+";

			s->Effect = [&](Gamedata& data) {
				data.dict["임진왜란"] = "전쟁돌입";
				data.player.res.money -= 1;
				data.player.res.milli += 8;
				data.player.res.human += 7;
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
무력-\n\
인력-\n\
식량-\n\
돈-";

			s->Effect = [&](Gamedata& data) {
				data.dict["임진왜란"] = "왜와 전투";
				data.player.res.milli -= 5;
				data.player.res.human -= 4;
				data.player.res.food -= 3;
				data.player.res.money -= 2;
			};
		}
		{
			EventSelectItemMaker s(e, "길을 빌려주는 정도는 별 상관없지 않을까?\n\
피해도 안 입히겠다고 약속하지 않았는가?");
			s->content = "왜구에게 길을 빌려 줍니다.\n\
패배합니다.";

			s->Effect = [&](Gamedata& data) {
				data.dict["임진왜란"] = "끝";
				data.player.res.milli = -1;
				data.player.res.faith = 0;
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
	{
		EventMaker e("명나라의 대군", EventPriority::Low);
		e->content =
			"명나라의 군대가 황해를 건너 곧 한반도에 상륙합니다.\n 그들은 굶주린 우리의 백성을 한테 다음과 같이 합니다.";

		e->CanStart = [&](Gamedata& data) {
			return data.dict["임진왜란"] == "명의 개입";
		};


		{
			EventSelectItemMaker s(e, "그들에게 쌀을 나누어 주어라");
			s->content =
				"인력++";
			s->Effect = [&](Gamedata& data) {
				data.player.res.human += 6;
				data.dict["임진왜란"] = "왜와 전투";
			};
		}
	}
	{
		EventMaker e("왜와 전투", EventPriority::Low);
		e->content = "왜군이 한반도를 돌아다니며 어지럽히고 있습니다. 어서 그들을 해치워야합니다.";

		e->CanStart = [&](Gamedata& data) {
			return data.dict["임진왜란"] == "왜와 전투";
		};


		{
			EventSelectItemMaker s(e, "싸워라");
			s->content = "전투에 따라 인력과 군사력이 소모됩니다.\n";
			s->Effect = [&](Gamedata& data) {
				data.player.res.human -= evt_mng.RandomInt(0, 3);
				data.player.res.milli -= evt_mng.RandomInt(0, 3);
				if (evt_mng.RandomInt(0, 5)) data.dict["임진왜란"] = "승리";
			};
		}
		{
			EventSelectItemMaker s(e, "항복.");
			s->content =
				"패배합니다.";
			s->Effect = [&](Gamedata& data) {
				data.dict["임진왜란"] = "끝";
				data.player.res.milli = -1;
				data.player.res.faith = 0;
			};
		}
	}
	{
		EventMaker e("임진왜란의 끝", EventPriority::Low);
		e->content = "왜군은 다시 그들의 집으로 돌아갔습니다. 우리는 이 일을 기억하고 다시는 이런일이 일어나지 않도록 해야합니다.";

		e->CanStart = [&](Gamedata& data) {
			return data.dict["임진왜란"] == "승리";
		};

		{
			EventSelectItemMaker s(e, "드디어.");
			s->content = "군사력+\n신앙++\n식량-\n인력-";
			s->Effect = [&](Gamedata& data) {
				data.dict["임진왜란"] = "끝";
				data.dict["근대사"] = "병자호란";
				data.player.res.milli += 3;
				data.player.res.faith += 12;
				data.player.res.food -= 3;
				data.player.res.human -= 3;
			};
		}
	}
	{
		EventMaker e("병자호란", EventPriority::Low);
		e->content = "여진족은 오랫동안 북쪽의 야만인이였습니다. 그러나 그들은 스스로를 청이라 부르며 우리에게 전쟁을 시작했습니다.";

		e->CanStart = [&](Gamedata& data) {
			return data.dict["임진왜란"] == "승리";
		};

		{
			EventSelectItemMaker s(e, "어쩔수 없군.");
			s->content = "(삼궤구고두례를 합니다)\n외교력-\n신앙+";
			s->Effect = [&](Gamedata& data) {
				data.dict["근대사"] = "오페르트";
				data.player.res.diplo -= 3;
				data.player.res.faith += 3;
			};
		}
	}
	{
		EventMaker e("오페르트 도굴 사건", EventPriority::Low);
		e->content = "남연군의 묘가 도굴 되었습니다. .";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["임진왜란"] == "오페르트")
			{
				if (data.dict["해금령"] == "예")
				{
					data.dict["근대사"] = "한일합방";
					return false;
				}
				return true;
			}
			else
			{
				return false;
			}
			
		};

		{
			EventSelectItemMaker s(e, "망나니 같으니!");
			s->content = "외교력-\n신앙+";
			s->Effect = [&](Gamedata& data) {
				data.player.res.diplo -= 3;
				data.player.res.faith += 3;
				data.dict["근대사"] = "한일합방";
			};
		}
	}
	{
		EventMaker e("을사늑약", EventPriority::Low);
		e->content = "일본이 우리나라의 외교권을 박탈하는 조약을 강제체결했습니다.";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["해금령"] == "한일합방")
			{
				return false;
			}
			return false;
		};

		{
			EventSelectItemMaker s(e, "젠장!");
			s->content = "1949년으로 타임워프 합니다.";
			s->Effect = [&](Gamedata& data) {
				data.dict["시대"] = "근대시대";
				data.dict["플레이어"] = "대한민국";
			};
		}
	}
}
