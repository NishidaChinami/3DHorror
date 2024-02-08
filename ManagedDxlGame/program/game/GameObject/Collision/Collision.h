#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class Factory;
class GameObject;

using IntersectedCall = std::function<void(std::shared_ptr<GameObject>a, std::shared_ptr<GameObject>b)>;


//-------------------------------------------------------------------------------------------------//
//当たり判定を取るための二つのオブジェクトクラスを設定するクラス
//-------------------------------------------------------------------------------------------------//
class PairObject {
public:
	PairObject(){}
	//第1引数 当たり判定を足りたいクラスA
	//第2引数　当たり判定を足りたいクラスB
	//第3引数　当たり判定をとったあとの処理
	PairObject(std::shared_ptr<GameObject>a, std::shared_ptr<GameObject>b,IntersectedCall call)
		:a_(a)
		,b_(b)
		, m_intersected_call(call)
	{}
	~PairObject(){}
	//オブジャクトクラスポインタ
	std::shared_ptr<GameObject>a_;
	std::shared_ptr<GameObject>b_;

	//当たり判定を取ったあとの処理（std function）
	IntersectedCall m_intersected_call;


};

//-------------------------------------------------------------------------------------------------//
//当たり判定を取りたいクラスの組み合わせを保存する
// 当たり判定検知後の処理関数
//-------------------------------------------------------------------------------------------------//
class Collision
{
public:
	Collision(){}
	~Collision() {}

	//二つのクラスを保存するクラスのリスト
	std::list<PairObject>m_intersect_list;
	//ここにもう一個レイ用のクラスリストを作ればいいのでは？

	//クラス名と当たり判定確認後の処理を保存するマップ
	std::unordered_map<std::string, IntersectedCall>m_intersect_map;

	//第1引数 当たり判定を足りたいクラスA
	//第2引数　当たり判定を足りたいクラスB
	template<class A, class B>
	void registPairObject(std::shared_ptr<A> a, std::shared_ptr<B> b) {
		std::string ab_name = std::string(typeid(A).name()) + typeid(B).name();
		//衝突を確かめるクラスの組み合わせがすでに保存されてないか確認
		if (m_intersect_map.find(ab_name) == m_intersect_map.end())return;
		//保存されてなければ、マップに保存
		auto intersected_call = m_intersect_map[ab_name];
		m_intersect_list.emplace_back(PairObject(a, b, intersected_call));
	}
	//当たり判定を検知後の処理を保存
	template<class A, class B>
	void registIntersectedProcess(const IntersectedCall& func) {
		std::string ab_name = std::string(typeid(A).name()) + typeid(B).name();
		m_intersect_map.try_emplace(ab_name, func);
	}
};