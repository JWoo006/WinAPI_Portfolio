
// 어플리케이션 백버퍼 클리어 함수로 구현

// window API는 bmp포맷만 지원하므로 알파값을 넣을수없다.
// 특정색(예: 마젠타(RGB(255,0,255)색)을 지정하여 그색을 제외하고
// 이미지 로딩하게끔 설계
// #pragma comment(lib, "Msimg32.lib") 추가
//TransparentBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0
//	, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

// 애니메이션
// 일정한 간격으로 떨어져있는 스프라이트 시트준비
// 이벤트(함수)로 애니메이션 분기를 결정하고 분기에따라 함수가 호출하게끔 설계
// 이벤트는 함수 포인터(functianal)로 설계