//
// �浹 ������ ����
// �浹�� üũ�ڽ� ������ ����
// �ִϸ��̼� ���� �浹ü üũ�ڽ� ũ�� �����ϱ�
// 
// ���� ���̾� �浹�� �ι� �浹�Ǵ� ���� - ����
// 
// ���� ����
// ���� _ http://egloos.zum.com/EireneHue/v/969409
// ������ ȿ���� �ٶ� ���
// �� transparentBlt�� ���� ���� ���� �ϳ� ��� ���
// //���� ����
// BLENDFUNCTION func = {};
// func.BlendOp = AC_SRC_OVER;
// func.BlendFlags = 0;
// func.AlphaFormat = 0;
// func.SourceConstantAlpha = 127; // ���İ� - �������� ����
//
// AlphaBlend(hdc, pos.x, pos.y
//    , mSpriteSheet[mSpriteIndex].size.x* scale.x
//    , mSpriteSheet[mSpriteIndex].size.y* scale.y
//    , mSheetImage->GetHdc()
//    , mSpriteSheet[mSpriteIndex].leftTop.x, mSpriteSheet[mSpriteIndex].leftTop.y
//    , mSpriteSheet[mSpriteIndex].size.x, mSpriteSheet[mSpriteIndex].size.y
//    , func);
// 
// ���� ���� ��� �����
// ���伥���� ����ä�η� ������Ʈ �׵θ��� ���� ���(255,255,255)����
// ������Ʈ�� ĥ�ѵ� 32��Ʈ bmp�������� ����
// 
// ���̵� �� �ƿ�
// �� ���İ� �ִ�(32��Ʈ) �������̹����� ���İ������ؼ� ����
// 
// 
// ������ �ٵ� (rigid body)
// �� ������ ���� ��ü
// �� �߷�, ������(����, �)�� �� ������ �޴� ������Ʈ 
//