void 고려시대(EventManager& evt_mng) {

	{
		EventMaker e("새로운 시대 탄생", EventPriority::Normal);

		e->content =
			"오랜시간 동안 호족간의 대립과 왕권의 약화 관리들의 부패로\n\
			신라는 세개의 국가로 분할 되었습니다.\n\
하지만 한반도는 오랫동안 나누어졌었고 반드시 통합되어야 합니다\n\
어떠한 방법으로 후삼국을 통일 할 것입니까?";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "고려시대") return false;
			if (data.dict["고려탄생"] == "")
			{
				data.dict["고려탄생"] = "시작됨";
				return true;
			}
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "신라와 손을 잡고 후백제를 물리친다.");
			s->content =
				"신라가 후백제에게 공격받아도와줍니다.\n\
자금-\n\
인력-";
			s->CanRun = [&](Gamedata& data) {
				return (data.player.res.money >= 2 && data.player.res.human >= 4);
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["고려탄생"] = "제도편성";
				data.player.res.money -= 2;
				data.player.res.human -= 4;
			};
		}
		{
			EventSelectItemMaker s(e, "군대를 모으고 여러 호족들을 고려편으로 돌립니다.");
			s->content =
				"군대를 모으고 호족들을 자신의 편으로 돌립니다..\n\
자금-\n\
식량-\n\
신앙+";
			s->CanRun = [&](Gamedata& data) {
				return (data.player.res.money >= 1 && data.player.res.food >= 2);
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["고려탄생"] = "제도편성";
				data.player.res.money -= 1;
				data.player.res.food -= 2;
				data.player.res.faith += 2;
			};
		}
	}

	{
		EventMaker e("새로운 제도편성", EventPriority::Normal);

		e->content =
			"호족들의 친분을 쌓아야 더 안정된 나라가 될수있습니다.\n\
호족들과 어떻게 친분을 쌓을 것입니까?";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "고려시대") return false;
			if (data.dict["고려탄생"] == "제도편성")
			{
				data.dict["고려탄생"] = "법 탄생";
				return true;
			}
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "사심관 제도를 실시합니다.");
			s->content =
				"지방 유력 가문이 본래의 그 지역을 다스리게 하는 사심관 제도를 실시합니다.\n\
자금+\n\
인력+\n\
외교력-";
			s->CanRun = [&](Gamedata& data) {
				return data.player.res.diplo >= 2;
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["고려탄생"] = "과거제도";
				data.player.res.human += 2;
				data.player.res.money += 1;
				data.player.res.diplo -= 2;
			};
		}
		{
			EventSelectItemMaker s(e, "사성정책을 실시합니다.");
			s->content =
				"호족들에게 관직과 토지를 주었으며 성씨를 내려 주었습니다.\n\
인력+\n\
신앙+\n\
자금-";
			s->CanRun = [&](Gamedata& data) {
				return data.player.res.money >= 2;
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["고려탄생"] = "과거제도";
				data.player.res.money -= 1;
				data.player.res.human += 1;
				data.player.res.faith += 2;
			};
		}
		{
			EventSelectItemMaker s(e, "혼인제도를 시행합니다.");
			s->content =
				"끊임 없는 정략결혼을 합니다..\n\
인력-\n\
식량+";
			s->CanRun = [&](Gamedata& data) {
				return data.player.res.human >= 2;
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["고려탄생"] = "과거제도";
				data.player.res.human -= 1;
				data.player.res.food += 2;
			};
		}
		{
			EventSelectItemMaker s(e, "아무제도도 시행하지 않습니다.");
			s->content =
				"굳이 제도를 시행하지 않아도 된다고 생각합니다.\n\
외교력-\n\
인력-";
			s->CanRun = [&](Gamedata& data) {
				return (data.player.res.diplo >= 2 && data.player.res.human >= 2);
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["고려탄생"] = "과거제도";
				data.player.res.diplo -= 2;
				data.player.res.human -= 2;
			};
		}
	}

	//고려시대에 과거제도
	{
		EventMaker e("고려시대에 과거제도", EventPriority::Normal);

		e->content =
			"중국에서 귀화한 쌍기가 새로운 제도를 추천하였습니다.";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "고려시대") return false;
			if (data.dict["고려탄생"] == "과거제도")
			{
				data.dict["고려탄생"] = "제도돌입";
				return true;
			}
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "쌍기의 의견을 적극 찬성한다.");
			s->content =
				"나라에서 시험을 치러 능력있는 관리를 선발할수있습니다.\n\
자금-\n\
인력+";
			s->CanRun = [&](Gamedata& data) {
				return data.player.res.money >= 2;
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["고려탄생"] = "국자감";
				data.player.res.human += 4;
				data.player.res.money -= 2;
			};
		}
		{
			EventSelectItemMaker s(e, "쌍기의 의견을 반대합니다.");
			s->content =
				"현행을 유지합니다.\n\
인력-\n\
군사력+";
			s->CanRun = [&](Gamedata& data) {
				return data.player.res.human >= 2;
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["고려탄생"] = "국자감";
				data.player.res.milli += 1;
				data.player.res.human -= 2;
			};
		}
		{
			EventSelectItemMaker s(e, "나만의 제도를 만들어 시행하겠다!");
			s->content =
				"지금의 제도랑 쌍기의 제도가 마음에 들지않습니다.\n\
제가 마음에 드는 사람들을 뽑는 제도를 만들것입니다.\n\
인력-\n\
신앙-";
			s->CanRun = [&](Gamedata& data) {
				return (data.player.res.human >= 2 && data.player.res.faith >= 3);
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["고려탄생"] = "국자감";
				data.player.res.human -= 2;
				data.player.res.faith -= 3;
			};
		}
	}

	//고려의 국자감
	{
		EventMaker e("고려의 국자감", EventPriority::Normal);

		e->content =
			"고려의 수준을 향샹시키기위해 국자감을 지을것인가요?.";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "고려시대") return false;
			if (data.dict["고려탄생"] == "국자감")
			{
				data.dict["고려탄생"] = "국자감 만듬";
				return true;
			}
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "국자감을 설치할것입니다.");
			s->content =
				"더욱더 사람들의 지적능력을 높일 수 있습니다.\n\
자금-\n\
외교력+\n\
군사력+";
			s->CanRun = [&](Gamedata& data) {
				return data.player.res.money >= 2;
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["고려탄생"] = "서경천도";
				data.player.res.milli += 3;
				data.player.res.diplo += 3;
				data.player.res.money -= 2;
			};
		}
		{
			EventSelectItemMaker s(e, "국자감을 설치하지 않습니다.");
			s->content =
				"현행을 유지합니다.";

			s->Effect = [&](Gamedata& data) {
				data.dict["고려탄생"] = "서경천도";
			};
		}
	}

	//서경천도운동
	{
		EventMaker e("서경천도운동", EventPriority::Normal);

		e->content =
			"이벤트 문제입니다!\n\
서경천도운동을 이르킨 인물은 누구입니까?";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "고려시대") return false;
			if (data.dict["고려탄생"] == "서경천도")
			{
				data.dict["고려탄생"] = "서경천도운동";
				return true;
			}
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "묘청이 일으켰습니다.");
			s->content =
				"진짜 묘청이 일으켰다고 생각하십니까?\n틀리면 나라가 흔들릴것입니다";

			s->Effect = [&](Gamedata& data) {
				data.dict["고려탄생"] = "서희담판";
				data.player.res.food += 5;
				data.player.res.human += 5;
				data.player.res.money += 5;
				data.player.res.diplo += 5;
				data.player.res.milli += 5;
				data.player.res.faith += 5;
			};
		}
		{
			EventSelectItemMaker s(e, "김부식이 일으켰습니다.");
			s->content =
				"진짜 김부식이 일으켰다고 생각하십니까?\n틀리면 나라가 흔들릴것입니다";

			s->CanRun = [&](Gamedata& data) {
				return (data.player.res.food >= 5 && data.player.res.human >= 5 && data.player.res.money >= 5 && data.player.res.faith >= 5 && data.player.res.milli >= 5 && data.player.res.diplo >=5);
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["고려탄생"] = "서희담판";
				data.player.res.food -= 5;
				data.player.res.human -= 5;
				data.player.res.money -= 5;
				data.player.res.diplo -= 5;
				data.player.res.milli -= 5;
				data.player.res.faith -= 5;
			};
		}
		{
			EventSelectItemMaker s(e, "인종이 일으켰습니다.");
			s->content =
				"진짜 인종이 일으켰다고 생각하십니까?\n틀리면 나라가 흔들릴것입니다";
			s->CanRun = [&](Gamedata& data) {
				return (data.player.res.food >= 5 && data.player.res.human >= 5 && data.player.res.money >= 5 && data.player.res.faith >= 5 && data.player.res.milli >= 5 && data.player.res.diplo >= 5);
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["고려탄생"] = "서희담판";
				data.player.res.food -= 5;
				data.player.res.human -= 5;
				data.player.res.money -= 5;
				data.player.res.diplo -= 5;
				data.player.res.milli -= 5;
				data.player.res.faith -= 5;
			};
		}
	}

	//서희담판
	{
		EventMaker e("거란과의 전쟁", EventPriority::Normal);

		e->content =
			"거란이 우리나라를 차지하려고 합니다.\n\
어떻게 행동하실겁니까?";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "고려시대") return false;
			if (data.dict["고려탄생"] == "서희담판")
			{
				data.dict["고려탄생"] = "서희의 담판";
				return true;
			}
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "서희라는 신하를 보내 외교담판을 할것입니다.");
			s->content =
				"서희라는 신하는 매우 영리하여 저희에게 최선의 방법을 찾아낼것입니다.\n\
외교력++\n\
군사력+\n\
자금-";
			s->CanRun = [&](Gamedata& data) {
				return data.player.res.money >= 1;
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["고려탄생"] = "무신정변";
				data.player.res.milli += 1;
				data.player.res.diplo += 7;
				data.player.res.money -= 1;
			};
		}
		{
			EventSelectItemMaker s(e, "군사를 모아 거란과 전쟁을 합니다.");
			s->content =
				"군대를 모아 거란과 전쟁을 하여 이겨보려고 합니다.\n\
하지만 거란족의 수가 너무 많습니다.\n\
외교력-\n\
군사력-\n\
식량-";

			s->CanRun = [&](Gamedata& data) {
				return (data.player.res.diplo >= 4 && data.player.res.milli >=2 && data.player.res.food >= 1);
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["고려탄생"] = "무신정변";
				data.player.res.milli -= 2;
				data.player.res.diplo -= 4;
				data.player.res.food -= 1;
			};
		}
		{
			EventSelectItemMaker s(e, "그냥 가만히 있습니다.");
			s->content =
				"거란이 침략하였습니다.\n\
식량--\n\
인력--\n\
자금--\n\
신앙--\n\
군사력--\n\
외교력--";

			s->CanRun = [&](Gamedata& data) {
				return (data.player.res.food >= 10000 && data.player.res.human >= 10000 && data.player.res.money >= 10000 && data.player.res.faith >= 10000 && data.player.res.milli >= 10000 && data.player.res.diplo >= 10000);
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["고려탄생"] = "무신정변";
				data.player.res.food -= 10000;
				data.player.res.human -= 10000;
				data.player.res.money -= 10000;
				data.player.res.diplo -= 10000;
				data.player.res.milli -= 10000;
				data.player.res.faith -= 10000;
			};
		}
	}

	//무신정변
	{
		EventMaker e("무신정변", EventPriority::Normal);

		e->content =
			"무신들이 정변을 일으켰습니다.\n\
왜 무신들이 정변을 일으켰다고 생각하십니까?";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "고려시대") return false;
			if (data.dict["고려탄생"] == "무신정변")
			{
				data.dict["고려탄생"] = "무신정변이 일어남";
				return true;
			}
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "문신과의 차별대우에 불만을 품었습니다.");
			s->content =
				"대체로 무신은 학문을 하는 문신에 비해 업신여김을 받았고, 높은 관리가 되거나 능력을 펼칠 수 있는 자리에 오르기 힘들었습니다.\n\
외교력-\n\
군사력+";
			s->CanRun = [&](Gamedata& data) {
				return data.player.res.diplo >= 1;
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["고려탄생"] = "조선건국";
				data.player.res.milli += 2;
				data.player.res.diplo -= 1;
			};
		}
		{
			EventSelectItemMaker s(e, "나이많은 무신이 젊은 문신에게 굴욕을 겪었기때문입니다.");
			s->content =
				"무술을 잘 하는 정중부는 왕을 보호하는 일을 하고 있었는데 \n\
그때 젊은 문신인 김돈중이 장난삼아 촛불로 정중부의 수염을 태웠었습니다.\n\
외교력-\n\
군사력+";

			s->CanRun = [&](Gamedata& data) {
				return (data.player.res.diplo >= 2);
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["고려탄생"] = "조선건국";
				data.player.res.milli += 2;
				data.player.res.diplo -= 2;
			};
		}
		{
			EventSelectItemMaker s(e, "무신 이소응이 젊은 문신에게 뺨을 맞는 사건이 발생하였기 때문입니다.");
			s->content =
				"의종이 무신끼리의 시합을 붙혔는데 대장군인 이소응이 젊은 무신에게 졌습니다.\n\
이때 젊은 문신이 대장군의 실력이 형편없다며 이소응의 뺨을 때리게 되었습니다.\n\
외교력-\n\
군사력+";

			s->CanRun = [&](Gamedata& data) {
				return data.player.res.diplo >= 2;
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["고려탄생"] = "조선건국";
				data.player.res.milli += 2;
				data.player.res.diplo -= 2;
			};
		}
	}

}
