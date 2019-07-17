// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "../해커톤- 프로젝트/HanStorySystem.hpp"
#include "삼국시대&남북국시대.hpp"
#include "조선시대.hpp"
#include "고려시대.hpp"
#include "근대시대.hpp"

void Load(EventManager& evt_mng)
{
	evt_mng.allItem.push_back(Item("낡은 검", 2, Resource{ 0, 0, 0, 0, 1, 0 }, vector<string>{}));
	evt_mng.allItem.push_back(Item("토기", 2, Resource{ 1, 0, 0, 0, 0, 0 }, vector<string>{}));
	evt_mng.allItem.push_back(Item("청동 거울", 2, Resource{ 0, 0, 0, 1, 0, 0 }, vector<string>{}));
	evt_mng.allItem.push_back(Item("일반 검", 2, Resource{ 0, 0, 0, 0, 2, 0 }, vector<string>{"낡은 검", "낡은 검"}));
	evt_mng.allItem.push_back(Item("인권", 2, Resource{ 0, 0, 0, 0, 1, 1 }, vector<string>{"낡은 검", "청동 거울"}));
	evt_mng.allItem.push_back(Item("낫", 2, Resource{ 2, 0, 0, 0, 0, 0 }, vector<string>{"토기", "토기"}));
	evt_mng.allItem.push_back(Item("판사의 망치", 2, Resource{ 2, 3, 1, 4, 0, 0 }, vector<string>{"청동 거울", "청동 거울", "청동 거울", "일반 검", "일반 검", "낡은 검"}));
	evt_mng.allItem.push_back(Item("최무선의 화포", 2, Resource{ 0, 2, 0, 0, 7, 1 }, vector<string>{"인권", "일반 검", "일반 검", "낡은 검", "낡은 검", "낡은 검"}));
	evt_mng.allItem.push_back(Item("마차", 2, Resource{3, 0, 3, 1, 0, 3 }, vector<string>{"인권", "인권", "낫", "청동 거울", "청동거울"}));
	evt_mng.allItem.push_back(Item("트랙터", 2, Resource{20, 1, 4, 0, 1, 0 }, vector<string>{"마차", "낫", "토기" ,"토기" ,"토기"}));
	evt_mng.allItem.push_back(Item("헌번", 2, Resource{ 2, 5, 0, 10, 0, 8 }, vector<string>{"판사의 망치", "인권", "인권", "낫"}));
	evt_mng.allItem.push_back(Item("이순신의 거북선", 2, Resource{ 0, 1, 5, 1, 10, 2 }, vector<string>{"최무선의 화포", "마차"}));
	evt_mng.allItem.push_back(Item("광개토대왕의 대검", 2, Resource{ 0, 5, 0, 12, 25, 8 }, vector<string>{"구매불가"}));
	evt_mng.allItem.push_back(Item("이순신의 거북선", 2, Resource{ 0, 15, 0, 35, 1, 4 }, vector<string>{"구매불가"}));
	evt_mng.allItem.push_back(Item("이상한 돌(우라늄 원석)", 2, Resource{ 0, 0, 30, 0, 5, 5 }, vector<string>{"구매불가"}));

	
	삼국시대(evt_mng);
	남북국시대(evt_mng);
	고려시대(evt_mng);
	조선시대(evt_mng);
	근대시대(evt_mng);
	
	//
//	//국가 선택
	{
		EventMaker e("시대선택", EventPriority::Highest);

		e->content = "시대를 선택해주세요. 삼국시대부터 근대시대까지 다양한 시대가 있습니다.";

		e->CanStart = [&](Gamedata& data) {
			return data.dict["시대"] == "";
		};

		{
			EventSelectItemMaker s(e, "삼국시대");
			s->content = "삼국시대는 한반도에 신라, 백제, 고구려 이 세개의 국가가 한반도으 패권을 다투던 시대입니다. 삼국시대의 각 국가는 삼한과 부여에 뿌리를 두고 있습니다.";

			s->Effect = [&](Gamedata& data) {
				data.dict["시대"] = "삼국시대";
			};
		}

		{
			EventSelectItemMaker s(e, "남북국시대");
			s->content = "남북국시대는 한반도에 북국과 남국이 존재하던 시대입니다. 남쪽에는 신라가 북쪽에는 발해가 존재합니다. 한반도의 균형은 유지되었지만 서쪽의 유목민들의 움직임이 심상치 않습니다...";

			s->Effect = [&](Gamedata& data) {
				data.dict["플레이어"] = "통일신라";
				data.dict["시대"] = "남북국시대";
			};
		}

		{
			EventSelectItemMaker s(e, "고려시대");
			s->content = "고려시대는 변화의 시대 입니다. 후삼국이 경쟁하며 한 국가로 통일이 되었고 무신이 정변을 일으키고 몽골이 침략까지 하는 시대 였습니다. 우리는 송나라와 거란에 버금가는 열강이지만 서쪽의 몽골도 대비해야 합니다.";

			s->Effect = [&](Gamedata& data) {
				data.dict["플레이어"] = "고려";
				data.dict["시대"] = "고려시대";
			};
		}

		{
			EventSelectItemMaker s(e, "조선시대");
			s->content = "조선시대는 외세의 침략에 맞서서 성장하는 시대입니다. 이성계가 조선시대에 시작을 열었고 세종대왕이 훈민정음을 창제하는 영광스러운 시간도 있었지만 일본이 침략을 하고 여진족이 침략을 하는 어두운 시간도 있었습니다.";

			s->Effect = [&](Gamedata& data) {
				data.dict["플레이어"] = "조선";
				data.dict["시대"] = "조선";
			};
		}

		{
			EventSelectItemMaker s(e, "근대시대");
			s->content = "근대시대에서느 6.25라는 커다란 전쟁을 겪게 됩니다. 이 전쟁은 나라의 국운을 걸은 전쟁이며 패배한다면 한반도에는 더 이상 민주주의를 볼 수 없을것입니다";

			s->Effect = [&](Gamedata& data) {
				data.dict["플레이어"] = "대한민국";
				data.dict["시대"] = "근대시대";
			};
		}
	}

}