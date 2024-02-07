#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Factory;
class GameObject;

using IntersectedCall = std::function<void(std::shared_ptr<GameObject>a, std::shared_ptr<GameObject>b)>;


//-------------------------------------------------------------------------------------------------//
//�����蔻�����邽�߂̓�̃I�u�W�F�N�g�N���X��ݒ肷��N���X
//-------------------------------------------------------------------------------------------------//
class PairObject {
public:
	PairObject(){}
	//��1���� �����蔻��𑫂肽���N���XA
	//��2�����@�����蔻��𑫂肽���N���XB
	//��3�����@�����蔻����Ƃ������Ƃ̏���
	PairObject(std::shared_ptr<GameObject>a, std::shared_ptr<GameObject>b,IntersectedCall call)
		:a_(a)
		,b_(b)
		,intersected_call_(call)
	{}
	~PairObject(){}
	//�I�u�W���N�g�N���X�|�C���^
	std::shared_ptr<GameObject>a_;
	std::shared_ptr<GameObject>b_;

	//�����蔻�����������Ƃ̏����istd function�j
	IntersectedCall intersected_call_;


};

//-------------------------------------------------------------------------------------------------//
//�����蔻�����肽���N���X�̑g�ݍ��킹��ۑ�����
// �����蔻�茟�m��̏����֐�
//-------------------------------------------------------------------------------------------------//
class Collision
{
public:
	Collision(){}
	~Collision() {}

	//��̃N���X��ۑ�����N���X�̃��X�g
	std::list<PairObject>intersect_list_;
	//�����ɂ�������C�p�̃N���X���X�g�����΂����̂ł́H

	//�N���X���Ɠ����蔻��m�F��̏�����ۑ�����}�b�v
	std::unordered_map<std::string, IntersectedCall>intersect_map_;

	//��1���� �����蔻��𑫂肽���N���XA
	//��2�����@�����蔻��𑫂肽���N���XB
	template<class A, class B>
	void registPairObject(std::shared_ptr<A> a, std::shared_ptr<B> b) {
		std::string ab_name = std::string(typeid(A).name()) + typeid(B).name();
		//�Փ˂��m���߂�N���X�̑g�ݍ��킹�����łɕۑ�����ĂȂ����m�F
		if (intersect_map_.find(ab_name) == intersect_map_.end())return;
		//�ۑ�����ĂȂ���΁A�}�b�v�ɕۑ�
		auto intersected_call = intersect_map_[ab_name];
		intersect_list_.emplace_back(PairObject(a, b, intersected_call));
	}
	//�����蔻������m��̏�����ۑ�
	template<class A, class B>
	void registIntersectedProcess(const IntersectedCall& func) {
		std::string ab_name = std::string(typeid(A).name()) + typeid(B).name();
		intersect_map_.try_emplace(ab_name, func);
	}

private:
	
};