
void 삼국시대(EventManager& evt_mng) {

	{
		EventMaker e("국가선택", EventPriority::High);
		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "삼국시대") return false;
			data.dict["플레이어"] = "신라";
			return data.dict["플레이어"] == "";
		};
	}

	{
		EventMaker e("삼국통일", EventPriority::High);
		e->content =
			"어느날 당신은 어린시절 스승한테 한 약속이 떠올랐습니다. 내가 왕이된다면 삼국을 통일하여 어지러운 한반도를 평온하게 만들겠다고...\n\
당신이 왕이 된 지금 우리는 결단을 내려야합니다!";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "삼국시대") return false;

			if (data.dict["삼국통일"] != "")
				return false;

			return  evt_mng.RandomAverageTurn("삼국통일", 5);

		};

		{
			EventSelectItemMaker s(e, "당나라에 도움을 요청하라!");
			s->content =
				"당나라에 삼국통일을 도와달라는 밀서를 보냅니다.\n\
인력-\n\
돈-\n\
외교+";
			s->Effect = [&](Gamedata& data) {
				data.dict["삼국통일"] = "밀서전달";
				data.player.res.human -= 1;
				data.player.res.money -= 2;
				data.player.res.diplo += 2;
			};
		}

		{
			EventSelectItemMaker s(e, "일단 한 국가는 우리의 힘으로 이겨보자!");
			s->content =
				"한 국가는 우리의 힘으로 이길 준비를 합니다.";
			s->Effect = [&](Gamedata& data) {
				data.dict["삼국통일"] = "전쟁시작";
				data.player.res.food -= 2;
				data.player.res.human -= 2;
				data.player.res.money -= 2;
				data.player.res.milli += 5;
			};
		}

		{
			EventSelectItemMaker s(e, "지금은 이르다...");
			s->content =
				"아무것도 하지 않는다.";
			s->Effect = [&](Gamedata& data) {
			};
		}
	}

	{
		EventMaker e("밀서전달", EventPriority::High);
		e->content =
			"당신은 밀서를 보낼 사람을 골라야합니다.\n\
어떻게 또는 누구를 선정할까요?";
		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "삼국시대") return false;
			if (data.dict["삼국통일"] == "밀서전달")
				return true;
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "신하들과 회의를 통해 정하자!");
			s->content =
				"회의를 열기위해 신하들에게 밀서를 보낸다는 사실을 공개하고 모집합니다.\n\
군사력--";
			s->Effect = [&](Gamedata& data) {
				data.player.res.milli -= 10000;
			};
		}

		{
			EventSelectItemMaker s(e, "이벌찬(1등급 관직)에게 부탁하여 믿을만한 사람 한명을 보내자!");
			s->content =
				"도움을 요청하기 위해 이벌찬에게만 밀서를 보낸다는 사실을 공개하고\n\
이벌찬의 심복중 믿을만한 한사람을 추천해달라고 한다.\n\
인력-\n\
돈-\n\
외교+";
			s->Effect = [&](Gamedata& data) {
				data.player.res.human -= 1;
				data.player.res.money -= 2;
				data.player.res.diplo += 2;
				data.dict["삼국통일"] = "밀서전달완료";
			};
		}

		{
			EventSelectItemMaker s(e, "그냥 내가 믿을 만한 사람에게 맡기자!");
			s->content =
				"믿을만한 심복에게 밀서를 보낸다는 사실을 공개하고 일을 맡깁니다.\n\
돈-\n\
외교+";
			s->Effect = [&](Gamedata& data) {
				data.player.res.money -= 3;
				data.player.res.diplo += 2;
				data.dict["삼국통일"] = "밀서전달완료";
			};
		}
	}

	{
		EventMaker e("밀서 전달 완료", EventPriority::Normal);
		e->content =
			"당나라에 밀서 전달을 완료했습니다.\n\
어느나라부터 공격할까요?";
		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "삼국시대") return false;
			if (data.dict["삼국통일"] == "밀서전달완료")
				return true;
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "고구려");
			s->content = "당나라와 위 아래 동시 공격을 합니다.\n\
돈-\n\
인력-\n\
군사력-";
			s->Effect = [&](Gamedata& data) {
				data.player.res.human -= 3;
				data.player.res.money -= 2;
				data.player.res.milli -= 1;
				data.dict["삼국통일"] = "고구려공격완료";
			};
		}

		{
			EventSelectItemMaker s(e, "백제");
			s->content = "당나라 군대가 바다로 넘어와 양 옆 동시 공격을 합니다.\n\
돈-\n\
인력-\n\
군사력-";
			s->Effect = [&](Gamedata& data) {
				data.player.res.human -= 2;
				data.player.res.money -= 3;
				data.player.res.milli -= 1;
				data.dict["삼국통일"] = "백제공격완료";
			};
		}
	}

	{
		EventMaker e("전쟁 시작", EventPriority::Normal);
		e->content =
			"백제와 고구려중 어느 나라를 공격할까요?";
		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "삼국시대") return false;
			if (data.dict["삼국통일"] == "전쟁시작")
				return true;
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "고구려 공격");
			s->content =
				"고구려를 공격합니다\n\
식량- ~ --\n\
인구- ~ --\n\
돈-\n\
군사력-";
			s->Effect = [&](Gamedata& data) {
				if (evt_mng.RandomPercent(70))
					data.player.res.food -= 2;
				else
					data.player.res.food -= 5;
				if (evt_mng.RandomPercent(70))
					data.player.res.human -= 2;
				else
					data.player.res.human -= 5;
				data.player.res.money -= 2;
				data.player.res.milli -= 1;
				data.dict["삼국통일"] = "백제공격완료";
			};
		}

		{
			EventSelectItemMaker s(e, "백제 공격");
			s->content =
				"백제를 공격합니다\n\
식량- ~ -\n\
인구- ~ -\n\
돈-\n\
군사력-";
			s->Effect = [&](Gamedata& data) {
				if (evt_mng.RandomPercent(80))
					data.player.res.food -= 3;
				else
					data.player.res.food -= 4;
				if (evt_mng.RandomPercent(80))
					data.player.res.human -= 3;
				else
					data.player.res.human -= 4;
				data.player.res.money -= 2;
				data.player.res.milli -= 1;
				data.dict["삼국통일"] = "백제공격완료";
			};
		}
	}

	{
		EventMaker e("백제 공격", EventPriority::Normal);
		e->content =
			"이제 삼국 통일을 위해 백제만이 남았습니다!\n\
하지만 당나라가 약간 걸리네요";
		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "삼국시대") return false;
			if (data.dict["삼국통일"] == "고구려공격완료")
				return true;
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "백제 공격");
			s->content = "당의 도움을 받지 않고 백제를 공격합니다\n\
식량-\n\
인력+\n\
돈-\n\
군사력-";
			s->Effect = [&](Gamedata& data) {
				data.player.res.food -= 2;
				data.player.res.human += 1;
				data.player.res.money -= 1;
				data.player.res.milli -= 3;
				if (evt_mng.RandomPercent(50))
					data.dict["삼국통일"] = "삼국완벽통합";
				else
					data.dict["삼국통일"] = "당과의전쟁";
			};
		}

		{
			EventSelectItemMaker s(e, "백제 연합 공격");
			s->content = "당과 협력하여 벡제를 공격합니다\n\
식량-\n\
인력-\n\
돈-\n\
외교-";
			s->Effect = [&](Gamedata& data) {
				data.player.res.food -= 2;
				data.player.res.human += 1;
				data.player.res.money -= 1;
				data.player.res.diplo -= 3;
				data.dict["삼국통일"] = "당과의전쟁";
			};
		}
	}

	{
		EventMaker e("고구려 공격", EventPriority::Normal);
		e->content =
			"이제 삼국 통일을 위해 고구려만이 남았습니다!\n\
하지만 당나라가 약간 걸리네요";
		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "삼국시대") return false;
			if (data.dict["삼국통일"] == "백제공격완료") 
				return true;
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "고구려 공격");
			s->content = "당의 도움을 받지 않고 고구려를 공격합니다\n\
식량-\n\
인력+\n\
돈-\n\
군사력-";
			s->Effect = [&](Gamedata& data) {
				data.player.res.food -= 2;
				data.player.res.human += 1;
				data.player.res.money -= 1;
				data.player.res.milli -= 3;
				if (evt_mng.RandomPercent(50))
					data.dict["삼국통일"] = "삼국완벽통합";
				else
					data.dict["삼국통일"] = "당과의전쟁";
			};
		}

		{
			EventSelectItemMaker s(e, "고구려 연합 공격");
			s->content = "당과 협력하여 고구려를 공격합니다\n\
식량-\n\
인력-\n\
돈-\n\
외교-";
			s->Effect = [&](Gamedata& data) {
				data.player.res.food -= 2;
				data.player.res.human += 1;
				data.player.res.money -= 1;
				data.player.res.diplo -= 3;
				data.dict["삼국통일"] = "당과의전쟁";
			};
		}
	}

	{
		EventMaker e("당과의 전쟁", EventPriority::Normal);
		e->content =
			"삼국 통일을 당의 도움을 받아 끝내니 이제는 당이 우리를 노립니다.\n\
하지만 이 소식을 듣고 멸망한 백제, 고구려의 백성들이 우리를 도와준다고 하네요.\n\
열심히 맞서 싸워봅시다!\n\
식량++\n\
인력++\n\
돈++\n\
외교--\n\
군사력+";
		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "삼국시대") return false;
			if (data.dict["삼국통일"] == "당과의전쟁") {
				data.player.res.food += 5;
				data.player.res.human += 5;
				data.player.res.money += 5;
				data.player.res.diplo -= 5;
				data.player.res.milli += 2;
				return true;
			}
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "당과의 전투!");
			s->content = "당과 전투를 시작합시다!";
			s->Effect = [&](Gamedata& data) {
				if (evt_mng.RandomPercent(60))
					data.dict["삼국통일"] = "삼국완벽통합";
				else
					data.dict["삼국통일"] = "삼국일부통합";
			};
		}

		{
			EventMaker e("삼국 완벽 통합!", EventPriority::High);
			e->content = "드디어 당신은 삼국을 완벽하게 통합하였습니다!\n\
다음 시대로 넘어갑니다!";
			e->CanStart = [&](Gamedata& data) {
				if (data.dict["시대"] != "삼국시대") return false;
				if (data.dict["삼국통일"] == "삼국완벽통합") {
					data.dict["시대"] = "남북국시대";
					data.dict["플레이어"] = "통일신라";
					return true;
				}
				else
					return false;
			};
		}
	}

	{
		EventMaker e("삼국 일부 통합", EventPriority::High);
		e->content = "당에 져서 한반도의 일부만을 가지게 되었지만\n\
어쨌든 당신이 소망하던 삼국 통일의 꿈을 이뤘습니다!\n\
모든 자원 / 2\n\
다음 시대로 넘어갑니다!";
		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "삼국시대") return false;
			if (data.dict["삼국통일"] == "삼국일부통합") {
				data.dict["시대"] = "남북국시대";
				data.dict["플레이어"] = "통일신라";
				data.player.res.food /= 2;
				data.player.res.human /= 2;
				data.player.res.money /= 2;
				data.player.res.diplo /= 2;
				data.player.res.milli /= 2;
				data.player.res.faith /= 2;
				return true;
			}
			else
				return false;
		};
	}
}
void 남북국시대(EventManager& evt_mng) {
	{
		EventMaker e("국가선택", EventPriority::High);
		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "남북국시대") return false;
			data.dict["플레이어"] = "통일신라";
			return data.dict["플레이어"] == "";
		};
	}

	{
		EventMaker e("한 청년", EventPriority::High);
		e->content = "평화로운 어느날\n\
한 무관이 와서 해적의 실상을 보고합니다\n\
하지만 이런 평화로운 시대에 해적이 있을것 같지도 않습니다\n\
게다가 문신들은 저 자를 무시하라고 하네요\n\
이 청년을 어떻게 할까요?";
		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "남북국시대") return false;
			if (data.dict["청해진"] == "")
				return true;
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "저놈을 처형시켜라!!");
			s->content = "저 청년을 바로 처형시킵니다\n\
군사력+\n\
인력-";
			s->Effect = [&](Gamedata& data) {
				data.player.res.milli += 1;
				data.player.res.human -= 4;
				data.dict["청해진"] = "처형";
			};
		}

		{
			EventSelectItemMaker s(e, "(무시한다)");
			s->content = "저 청년에게 벌을 주지는 않지만\n\
말을 귀기울여 듣지도 않습니다\n\
신앙-";
			s->Effect = [&](Gamedata& data) {
				data.player.res.faith -= 3;
				data.dict["청해진"] = "무시";
			};
		}

		{
			EventSelectItemMaker s(e, "들어보도록 하지...");
			s->content = "항의를 무릅쓰고\n\
저 청년의 말을 귀기울여 들어봅니다\n\
군사력+";
			s->Effect = [&](Gamedata& data) {
				data.player.res.milli += 3;
				data.dict["청해진"] = "경청";
			};
		}
	}
	{
		EventMaker e("처형", EventPriority::High);
		e->content = "1년후...\n\
해적들이 주변 민가를 털고 세력이 커져\n\
우리 국민들은 바다로 나갈 수 없게 되었습니다...";
		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "남북국시대") return false;
			if (data.dict["청해진"] == "처형") {
				data.player.res.human -= 10000;
				return true;
			}
			else
				return false;
		};
	}

	{
		EventMaker e("무시", EventPriority::High);
		e->content = "1년후...\n\
해적들이 주변 민가를 털고 세력이 커졌으나\n\
그 청년이 겨우겨우 막고 있다고 합니다\n\
그의 말을 들어볼걸 그랬네요...\n\
신앙-\n\
인력-\n\
돈--";
		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "남북국시대") return false;
			if (data.dict["청해진"] == "무시") {
				data.player.res.faith -= 3;
				data.player.res.human -= 3;
				data.player.res.money -= 5;
				data.dict["청해진"] = "끝";
				return true;
			}
			else
				return false;
		};
	}

	{
		EventMaker e("경청", EventPriority::High);
		e->content = "나는 그의 말을 경청했고\n\
사태는 생각보다 심각했습니다\n\
그의 말에 따라 청해진을 설치했고, 몇달 뒤 이제 해적의 만행을 없어졌습니다.\n\
게다가 해적이 사라진 뒤에는 청해진이 해상 무역의 중심지가 되었습니다\n\
장보고의 말을 들어보길 잘했네요\n\
신앙++\n\
돈+\n\
군사력++";
		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "남북국시대") return false;
			if (data.dict["청해진"] == "경청") {
				data.dict["청해진"] = "끝";
				data.player.res.faith += 5;
				data.player.res.money += 3;
				data.player.res.milli += 5;
				return true;
			}
			else
				return false;
		};
	}
	{
		EventMaker e("발해", EventPriority::Normal);
		e->content = "고구려의 땅에 새로운 국가가 생겼다고 합니다. 그 국가의 이름은 발해라고 합니다.";
		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "남북국시대") return false;
			if (data.dict["발해"] == "" && evt_mng.RandomInt(0, 2) == 0) {
				data.dict["발해"] = "끝";
				return true;
			}
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "해동성국이라고 부르면 되는건가?");

			s->Effect = [&](Gamedata& data) {
				data.dict["외교적 결례"] = "";
			};
		}
		{
			EventSelectItemMaker s(e, "돼지곰국이라고 부르면 되는건가?");

			s->Effect = [&](Gamedata& data) {
				data.dict["외교적 결례"] = "예";
			};
		}
	}
	{
		EventMaker e("발해", EventPriority::Normal);
		e->content = "고구려의 땅에 새로운 국가가 생겼다고 합니다. 그 국가의 이름은 발해라고 합니다.";
		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "남북국시대") return false;
			if (data.dict["발해"] == "" && evt_mng.RandomInt(0, 2) == 0) {
				data.dict["발해"] = "끝";
				return true;
			}
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "홍길동이 발해를 건국했지...");

			s->Effect = [&](Gamedata& data) {
				data.dict["외교적 결례"] = "예";
			};
		}
		{
			EventSelectItemMaker s(e, "대조영이 발해를 건국했지...");

			s->Effect = [&](Gamedata& data) {
				data.dict["외교적 결례"] = "";
			};
		}
	}
	{
		EventMaker e("외교적 결례", EventPriority::Highest);
		e->content = "당신의 방자하게도 외교적 결례를 일으켰습니다.";
		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "남북국시대") return false;
			if (data.dict["외교적 결례"] == "예") {
				return true;
			}
			else
				return false;
		};

		{
			EventSelectItemMaker s(e, "미안.");

			s->content = "외교--";

			s->Effect = [&](Gamedata& data) {
				data.player.res.diplo -= 8;
				data.dict["외교적 결례"] = "";
			};
		}
	}

	{
		EventMaker e("남국에서 온 상인", EventPriority::Low);
		e->content =
			"남국의 상인이 당신을 만나길 원합니다. 그는 후추와 종이를 거래하길 원합니다.";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "삼국시대" && data.dict["시대"] != "남북국시대" && data.dict["시대"] != "고려시대" && data.dict["시대"] != "조선시대") return false;
			
			return evt_mng.RandomInt(0, 3) == 0;

		};

		{
			EventSelectItemMaker s(e, "이 거래는 우리 모두에게 이득이 될것이다.");
			s->content =
				"식량+\n외교력+\n돈+";
			s->Effect = [&](Gamedata& data) {
				data.player.res.food += 1;
				data.player.res.diplo += 1;
				data.player.res.money += 1;
			};
		}
	}

	{
		EventMaker e("홍수", EventPriority::Normal);
		e->content =
			"수도 근처의 곡창지대에서 큰 홍수가 났습니다. 우리는 무엇을 해야 할 까요?";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "삼국시대" && data.dict["시대"] != "남북국시대" && data.dict["시대"] != "고려시대" && data.dict["시대"] != "조선시대") return false;

			return evt_mng.RandomInt(0, 6) == 0;

		};

		{
			EventSelectItemMaker s(e, "구조대를 보내고 백성들이 굶지않게 식량을 나누어 주어라.");
			s->content =
				"인력-\n식량--\n외교력+\n돈-";
			s->Effect = [&](Gamedata& data) {
				data.player.res.human -= 1;
				data.player.res.food -= 5;
				data.player.res.diplo += 3;
				data.player.res.money -= 3;
			};
		}
		{
			EventSelectItemMaker s(e, "신께서 노하신게 분명하다! 어서 제사를 준비해라!");
			s->content =
				"인력--\n식량--\n신앙++++";
			s->Effect = [&](Gamedata& data) {
				data.player.res.human -= 7;
				data.player.res.food -= 7;
				data.player.res.faith += 18;
			};
		}
		{
			EventSelectItemMaker s(e, "백성들이 죽든 말든 나랑 무슨 상관이냐!");
			s->content =
				"인력--\n식량-\n외교력-";
			s->Effect = [&](Gamedata& data) {
				data.player.res.human -= 5;
				data.player.res.food -= 5;
				data.player.res.diplo -= 2;
			};
		}
	}

	{
		EventMaker e("조세", EventPriority::Lowest);
		e->content =
			"전국에서 우리가 명령한대로 조세가 수도로 모이고 있습니다. .";

		{
			EventSelectItemMaker s(e, "조세가 없다면 국가는 유지 될수 없지.");
			s->content =
				"식량++";
			s->Effect = [&](Gamedata& data) {
				data.player.res.food += 10;
			};
			s->CanVisible = [&](Gamedata& data) {
				return data.dict["시대"] != "근대시대";
			};
		}
		{
			EventSelectItemMaker s(e, "조세가 없다면 국가는 유지 될수 없지.");
			s->content =
				"돈++";
			s->Effect = [&](Gamedata& data) {
				data.player.res.money += 10;
			};
			s->CanVisible = [&](Gamedata& data) {
				return data.dict["시대"] == "근대시대";
			};
		}
	}
	{
		EventMaker e("풍년", EventPriority::Normal);
		e->content =
			"풍년입니다. 이때에는 평년보다 더 많은 식량이 산출 됩니다";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "삼국시대" && data.dict["시대"] != "남북국시대" && data.dict["시대"] != "고려시대" && data.dict["시대"] != "조선시대") return false;

			return evt_mng.RandomInt(0, 3) == 0;

		};
		{
			EventSelectItemMaker s(e, "모두 곡창에 넣어라!");
			s->content =
				"식량++";
			s->Effect = [&](Gamedata& data) {
				data.player.res.food += 10;
			};
		}
		{
			EventSelectItemMaker s(e, "풍작을 도와주신 천지신명님께 감사제사를 드려라!");
			s->content =
				"식량+\n신앙+";
			s->Effect = [&](Gamedata& data) {
				data.player.res.food += 5;
				data.player.res.faith += 4;
			};
		}
	}
	{
		EventMaker e("가뭄", EventPriority::Low);
		e->content =
			"가뭄입니다. 백성들이 굶주리고 있습니다. 부디 자비롭게 대처하십시오";

		e->CanStart = [&](Gamedata& data) {
			if (data.dict["시대"] != "삼국시대" && data.dict["시대"] != "남북국시대" && data.dict["시대"] != "고려시대" && data.dict["시대"] != "조선시대") return false;

			return evt_mng.RandomInt(0, 4) == 0;

		};
		{
			EventSelectItemMaker s(e, "곡창을 열어라!");
			s->content =
				"식량-/인력-";
			s->Effect = [&](Gamedata& data) {
				data.player.res.food -= 3;
				data.player.res.human -= 3;
			};
		}
		{
			EventSelectItemMaker s(e, "그래서...?");
			s->content =
				"인력--";
			s->Effect = [&](Gamedata& data) {
				data.player.res.human -= 7;
			};
		}
	}
	{
		EventMaker e("축제", EventPriority::High);
		e->content =
			"오늘은 축제날입니다. ";

		{
			e->CanStart = [&](Gamedata& data) {
				if (data.dict["시대"] != "삼국시대" && data.dict["시대"] != "남북국시대" && data.dict["시대"] != "고려시대" && data.dict["시대"] != "조선시대") return false;

				return evt_mng.RandomInt(0, 12) == 0;

			};

			EventSelectItemMaker s(e, "왕족들만 초대하라.");
			s->content =
				"돈-\n신앙+\n외교력+";
			s->Effect = [&](Gamedata& data) {
				data.player.res.money -= 4;
				data.player.res.faith += 5;
				data.player.res.diplo += 2;
			};
		}
		{
			EventSelectItemMaker s(e, "외국의 장관들도 초대하라.");
			s->content =
				"돈--\n신앙+\n외교력++";
			s->Effect = [&](Gamedata& data) {
				data.player.res.money -= 8;
				data.player.res.faith += 5;
				data.player.res.diplo += 7;
			};
		}
		{
			EventSelectItemMaker s(e, "관리들도 초대하라.");
			s->content =
				"돈---\n신앙++\n외교력++";
			s->Effect = [&](Gamedata& data) {
				data.player.res.money -= 12;
				data.player.res.faith += 9;
				data.player.res.diplo += 7;
			};
		}
		{
			EventSelectItemMaker s(e, "백성들도 초대하라.");
			s->content =
				"돈----\n신앙++++\n외교력++\n인력+";
			s->Effect = [&](Gamedata& data) {
				data.player.res.money -= 16;
				data.player.res.faith += 18;
				data.player.res.diplo += 7;
				data.player.res.human += 4;
			};
		}
	}

	{
		EventMaker e("호족의 성장", EventPriority::Normal);
		e->content =
			"최근 호족은 이례적인 성장을 하고 있씁니다. 그들의 경제적 위상은 올라갔으며 그들은 그에 걸맞은 권력을 원합니다.";
		e->CanStart = [&](Gamedata& data) {
			return data.dict["시대"] != "근대시대" && data.dict["시대"] != "조선시대" && evt_mng.RandomInt(0, 9) == 0 && data.dict["호족의 불복"] == "";
		};

		{
			EventSelectItemMaker s(e, "호족이 원한다면 그 정도 권력은 주어야 한다.");
			s->content =
				"식량-\n돈-";
			s->Effect = [&](Gamedata& data) {
				data.player.res.food -= 3;
				data.player.res.money -= 3;
				data.dict["고려탄생"] = "조선건국";
				data.dict["시대"] = "고려시대";
				//data.dict["호족의 불복"] == "끝";
			};
		}
		{
			EventSelectItemMaker s(e, "무엄하다!");
			s->content =
				"(호족의 불복종) 이벤트가 시작됩니다.";
			s->Effect = [&](Gamedata& data) {
				data.dict["호족의 불복"] = "시작";
			};
		}
	}
	{
		EventMaker e("호족의 불복", EventPriority::High);
		e->content =
			"호족은 수도에서 보낸 관리에게 조세를 바치지 않거나 적게 바치고 있으며 심지어 일부는 반란을 일으키는것 같습니다.";
		e->CanStart = [&](Gamedata& data) {
			return data.dict["시대"] != "근대시대" && data.dict["시대"] != "조선시대" && data.dict["호족의 불복"] == "시작";
		};

		{
			EventSelectItemMaker s(e, "그들을 죽여라.");
			s->content =
				"군사력--\n외교력-";
			s->Effect = [&](Gamedata& data) {
				data.player.res.milli -= 6;
				data.player.res.diplo -= 3;
				if (evt_mng.RandomInt(0, 6) == 0 || data.dict["시대"] == "남북국시대")
					data.dict["호족의 불복"] == "반란";
				else
					data.dict["호족의 불복"] == "";
			};
		}
		{
			EventSelectItemMaker s(e, "그들과 회유하기위해 유력 호족의 자식들과 혼인한다.");
			s->content =
				"외교-";
			s->Effect = [&](Gamedata& data) {
				data.player.res.diplo -= 2;
				data.dict["호족의 불복"] = "끝";
				data.dict["고려탄생"] = "무신정변";
				data.dict["시대"] = "고려시대";
			};
		}
		{
			EventSelectItemMaker s(e, "항복.");
			s->content =
				"패배합니다";
			s->Effect = [&](Gamedata& data) {
				data.player.res.diplo = -1;
				data.player.res.faith = 0;
			};
		}
	}
	{
		EventMaker e("호족의 반란", EventPriority::Normal);
		e->content =
			"호족은 우리에게 반기를 들고 새로운 국가를 세우려고 합니다! 그들을 막지 못 한다면 우리는 패배할 것 입니다.";
		e->CanStart = [&](Gamedata& data) {
			return data.dict["시대"] != "근대시대" && data.dict["시대"] != "조선시대" && data.dict["호족의 불복"] == "반란";
		};

		{
			EventSelectItemMaker s(e, "이건 명백이 왕을 거역하는 짓이다. 저들을 모두 감옥에 쳐넣어라!");
			s->content =
				"군사력---\n외교력+";
			s->Effect = [&](Gamedata& data) {
				data.player.res.milli -= 11;
				data.player.res.diplo += 3;
				data.dict["호족의 불복"] = "끝";
				data.dict["고려탄생"] = "무신정변";
				data.dict["시대"] = "고려시대";
			};
		}
		{
			EventSelectItemMaker s(e, "항복.");
			s->content = "나라를 적에게 바칩니다.";

			s->CanVisible = [&](Gamedata& data) {
				return data.dict["시대"] == "남북국시대";
			};

			s->Effect = [&](Gamedata& data) {
				data.dict["고려의 탄생"] = "예";
			};
		}
		{
			EventSelectItemMaker s(e, "항복.");
			s->content =
				"당신은 이제 고려를 플레이 합니다.";
			s->Effect = [&](Gamedata& data) {
				data.dict["플레이어"] = "고려";
			};
			s->CanVisible = [&](Gamedata& data) {
				return data.dict["시대"] != "남북국시대";
			};
		}
	}
	{
		EventMaker e("고려시대의 개막", EventPriority::Highest);
		e->content =
			"신라의 시대는 막을 내리고 고려의 시대가 시작되었습니다! 고려는 신라에 이은 2번째 통일국가 입니다!";

		e->CanStart = [&](Gamedata& data) {
			return data.dict["고려의 탄생"] == "예";
		};


		{
			EventSelectItemMaker s(e, "고려황제 만세! 만세");
			s->Effect = [&](Gamedata& data) {
				data.dict["플레이어"] = "고려";
				data.dict["시대"] = "고려시대";
				data.dict["고려탄생"] = "무신정변";
			};
		}
	}
	{
		EventMaker e("병영의 포화", EventPriority::Low);
		e->content =
			"지금 병영은 입대를 하길 원하는 사람으로 가득찼습니다! 그들을 빨리 배치시켜야 합니다";

		e->CanStart = [&](Gamedata& data) {
			return evt_mng.RandomInt(0, 3) == 0;
		};


		{
			EventSelectItemMaker s(e, "더 큰 군대는 더 큰 국가를 의미한다");
			s->content =
				"인력++\n군사력++";
			s->Effect = [&](Gamedata& data) {
				data.player.res.milli += 7;
				data.player.res.human += 6;
			};
		}
	}
	{
		EventMaker e("우수한 외교관", EventPriority::Low);
		e->content =
			"우리의 외교관이 타국의 위기를 모면시켰습니다. 다른 국가들이 우리를 보는 시선이 달라졌습니다.";

		e->CanStart = [&](Gamedata& data) {
			return evt_mng.RandomInt(0, 3) == 0;
		};

		{
			EventSelectItemMaker s(e, "마땅히 받아야할 대우다.");
			s->content =
				"외교력++";
			s->Effect = [&](Gamedata& data) {
				data.player.res.diplo += 8;
			};
		}
	}
}
