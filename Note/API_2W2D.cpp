
// ��üũ
// �Ҹ��ڿ��� delete , layer Ŭ������ �����Ҵ��� ���ؼ� ����
// 
// �̹���, ���� - ������ ����
// ���ҽ� ����
// ����Ƽ�� Resources.Load����
// �پ��� ������ Ÿ���� ���� <template>���
// 
//
// STL map
// �ΰ��� �����͸� �ִ´�. -> std::map<int, char> mMap;
// ù��° �����ʹ� Ű��, �ι�° �����ʹ� ����Ǵ� �������̴�.
// Ű���� �������� �ڽź��� ������ �������� ũ�� ������
// ���� Ʈ������� �ڷᱸ���̴�. ������ ������ �߿� �ϳ��� Ž���ؾ��Ҷ� ���
// Ž���� ����ȭ�Ǿ��ִ�.

//
// �迭�� Ʈ�� ������ �׿� �ڷᱸ���鵵 ƴƴ�� ��������
//
// �߻� Ŭ���� - ���������Լ��� �ϳ��� �����ϰ��ִٸ� �߻�Ŭ������ ��
//  = 0; <- ������ �������̵� �޾Ƽ� ����϶�� �� ���������Լ�   
// virtual HRESULT Load(const std::wstring& path) = 0;
// ������ ��Ӹ� �޾Ƽ� ���

// iterator
// ���������� �����ؼ� �����͸� �����ؼ� �����ü� �ְ� ���ִ� Ŭ�����̴�.
// Ŭ���� �����Ϳ� ���� ������ �������� ������(�ڵ�� �����)
// list�� iterator
// vector�� �迭ó�� �ε����� ������ ���������� �װ� �ȵǴ� list��
// std::list<int>::iterator iter
// list���� �̳�Ŭ���� iterator�� ��ü�� ���� �����Ͽ� ��ȸ�Ҽ��ִ�.

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

//���� ����ȯ (Dynamic Casting)
// �θ� Ŭ������ �����Ϳ��� �ڽ� Ŭ������ 
// �����ͷ� �ٿ� ĳ���� ���ִ� ������

// ������ ������ , �����


// stock ������Ʈ
// �⺻���� �����Ǵ� ��(������)�� �귯��(�Ͼ��)

// selectobject(HDC, HGDIOBJ);
// �� �Լ��� ��ȯ���� HGDIOBJ�� ������ ���� ���������Ʈ

//HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
////Rectangle(mHdc, -1, -1, 1601, 901);
//
//HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 255));
//HPEN oldPen = (HPEN)SelectObject(hdc, pen);
//
//Rectangle(hdc, mPos.x, mPos.y, mPos.x + 100, mPos.y + 100);
//
//// �޸� ���� ���� �ʰ� ó��
//SelectObject(hdc, oldPen);
//DeleteObject(pen);
//SelectObject(hdc, oldBrush);
//DeleteObject(brush);