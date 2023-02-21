
#include <iostream>

// static 함수
// 함수에도 static을 붙여서 객체가 생성되지 않더라도 호출이 가능한 함수를
// 만들수 있다.
// 일반 멤버(데이터, 함수)에 접근할 수 없다.
// 정적 멤버(데이터, 함수)에 접근할 수 있다.

// 범위기반 for문 read only

// scenemanager -> scene -> layer -> gameobject -> component
// 다차원배열자료들을 클래스로 나눠서 구조 설계

// 게임에 맞춰서 씬제작

//void PlayScene::Initialize()
//{
//	//override를 써서 자식쪽으로 오지만 부모쪽 함수로 지정가능
//	Scene::Initialize();
//}

// 레이어 layer
// 게임 화면( 배경, 플레이어, 몬스터 , 총알(효과) 등등)층층으로 구성
// 레이어 열거체 순서대로 생성

// Entity 클래스
// 멤버 변수 mName으로 이름을 생성하여 구분짓기
// mScenes[(UINT)eSceneType::Play]->SetName(L"Player");

// virtual override
// 부모 클래스와 똑같은 이름의 함수를 쓸때 자동적으로 가상함수화됨
// 명시적으로 표시하기위해 코드 표기

// 단축키
// ctrl + R -> 이름 바꾸기
// 주석 ctrl + k, c  해제 ctrl + k,u
// ctrl + . -> 빠른 작업 리펙토링
// ctrl + k, o -> 헤더 cpp전환

// 델타 타임
// 바로 전 프레임을 수행하는데 걸린 게임 시간
// 정해진 시간안에 똑같이 움직이게 하기
// cpu의 Hz를 사용해서 계산
// 3.2GHz는 32억번의 진동을 1초만에 수행한다
// 32억번의 프리퀀시(진동)을 카운트하면 1초가 지난다. 약간의 오차가 있다.


int main()
{
	return 0;
}