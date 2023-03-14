//
// 충돌 오프셋 변경
// 충돌시 체크박스 색변경 구현
// 애니메이션 마다 충돌체 체크박스 크기 구현하기
// 
// 같은 레이어 충돌시 두번 충돌되는 버그 - 내일
// 
// 알파 블렌드
// 참고 _ http://egloos.zum.com/EireneHue/v/969409
// 투명한 효과를 줄때 사용
// ㄴ transparentBlt과 알파 블렌딩 둘중 하나 골라서 사용
// //알파 블렌딩
// BLENDFUNCTION func = {};
// func.BlendOp = AC_SRC_OVER;
// func.BlendFlags = 0;
// func.AlphaFormat = 0;
// func.SourceConstantAlpha = 127; // 알파값 - 낮을수록 투명
//
// AlphaBlend(hdc, pos.x, pos.y
//    , mSpriteSheet[mSpriteIndex].size.x* scale.x
//    , mSpriteSheet[mSpriteIndex].size.y* scale.y
//    , mSheetImage->GetHdc()
//    , mSpriteSheet[mSpriteIndex].leftTop.x, mSpriteSheet[mSpriteIndex].leftTop.y
//    , mSpriteSheet[mSpriteIndex].size.x, mSpriteSheet[mSpriteIndex].size.y
//    , func);
// 
// 알파 블렌딩 배경 지우기
// 포토샵으로 알파채널로 오브젝트 테두리를 딴뒤 흰색(255,255,255)으로
// 오브젝트만 칠한뒤 32비트 bmp포맷으로 저장
// 
// 페이드 인 아웃
// ㄴ 알파가 있는(32비트) 검은색이미지의 알파값조정해서 구현
// 
// 
// 리지드 바디 (rigid body)
// ㄴ 질량을 가진 물체
// ㄴ 중력, 마찰력(정지, 운동)등 에 영향을 받는 컴포넌트 
//