
// 릭체크
// 소멸자에서 delete , layer 클래스는 동적할당을 안해서 냅둠
// 
// 이미지, 사운드 - 데이터 관리
// 리소스 관리
// 유니티의 Resources.Load참조
// 다양한 데이터 타입을 위해 <template>사용
// 
//
// STL map
// 두개의 데이터를 넣는다. -> std::map<int, char> mMap;
// 첫번째 데이터는 키값, 두번째 데이터는 저장되는 데이터이다.
// 키값을 기준으로 자신보다 작으면 왼쪽으로 크면 오른쪽
// 이진 트리모양의 자료구조이다. 수많은 데이터 중에 하나만 탐색해야할때 사용
// 탐색에 최적화되어있다.

//
// 배열과 트리 구조는 그외 자료구조들도 틈틈이 공부하자
//
// 추상 클래스 - 순수가상함수가 하나라도 포함하고있다면 추상클래스가 됨
//  = 0; <- 무조건 오버라이드 받아서 사용하라는 뜻 순수가상함수   
// virtual HRESULT Load(const std::wstring& path) = 0;
// 무조건 상속만 받아서 사용

// iterator
// 간접적으로 접근해서 데이터를 접근해서 가져올수 있게 해주는 클래스이다.
// 클래스 데이터에 직접 접근을 막기위해 존재함(핸들과 비슷함)
// list의 iterator
// vector는 배열처럼 인덱스로 접근이 가능하지만 그게 안되는 list는
// std::list<int>::iterator iter
// list안의 이너클래스 iterator의 객체를 만들어서 접근하여 순회할수있다.

#include <iostream>
#include <list>

int main()
{

	std::list<int>	list;

	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);

	std::list<int>::iterator iter = list.begin();

	return 0;
}

//동적 형변환 (Dynamic Casting)
// 부모 클래스의 포인터에서 자식 클래스의 
// 포인터로 다운 캐스팅 해주는 연산자

// 파일의 절대경로 , 상대경로


// stock 오브젝트
// 기본으로 생성되는 펜(검은색)과 브러쉬(하얀색)

// selectobject(HDC, HGDIOBJ);
// 위 함수의 반환값은 HGDIOBJ로 기존에 쓰던 스톡오브젝트

//HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
////Rectangle(mHdc, -1, -1, 1601, 901);
//
//HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 255));
//HPEN oldPen = (HPEN)SelectObject(hdc, pen);
//
//Rectangle(hdc, mPos.x, mPos.y, mPos.x + 100, mPos.y + 100);
//
//// 메모리 릭이 남지 않게 처리
//SelectObject(hdc, oldPen);
//DeleteObject(pen);
//SelectObject(hdc, oldBrush);
//DeleteObject(brush);