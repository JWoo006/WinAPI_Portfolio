// 릭제거
//  auto - 자료형 추론해서 알아서 맞춰줌
//for (auto pair : mResources)
//{
//	delete pair.second;
//	pair.second = nullptr;
//}
// 
// 씬 전환
// 업데이트와 렌더는 현재 사용중인 현재씬만 하도록 설계
// 타이틀 씬 클래스 생성후 씬매니저에 초기화 등록후 업데이트에 키입력시 호출되게끔
// 
// default 키워드
// class Foo
//{
//	public:
//		Foo(const Foo& other) = default;
//		Foo& operator=(const Foo& rhs) = default;
//};
// default 키워드를 사용하면 컴파일러가 만들어준 기본 복사 생성자 
// 및 기본 대입 연산자를 사용하겠다는 뜻
//
// delete 키워드
// delete 키워드는 컴파일러가 자동으로 만들어주는 것을 막는 것
// 
// 리소스 추출
// 
// 컴포넌트 구현 설계
// 제작할 컴포넌트
// 1. 위치 정보를 가지고 있는 Transform 컴포넌트
// 2. 화면에 그려주는 역할을 맡아줄(Render) SpriteRenderer 컴포넌트(이미지 1장)
// 3. 충돌을 구현하기 위한 Collider 컴포넌트
// 4. 애니메이션 처리를 해주기 위한 Animator 컴포넌트
// 5. 사운드 재생을 위한 Audio 컴포넌트
// 6. Script 컴포넌트 - 같은 동작을 하는 
// 
// Transform
// pos와 size 데이터를 가지고있다.
//

