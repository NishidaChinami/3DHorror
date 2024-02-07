#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class GameCamera;
class Stage;
class Mediator;
//-------------------------------------------------------------------------------------------------//
//�X�e�[�W�̕`��N���X
//�X�e�[�W�̃��b�V����`�悷��
//-------------------------------------------------------------------------------------------------//
class BackGroudStage
{
public:
	//�X�e�[�W�̓����蔻��N���X�ƃ��f�B�G�[�^�[�N���X���R���X�g���N�^�̈����Ɏ���
	BackGroudStage(const std::shared_ptr<Stage>&stage, const std::shared_ptr<Mediator>& mediator);
	~BackGroudStage();

	//�I���W�i�����b�V������R�s�[���b�V�����ĕǂ̃��b�V���𐶐�����֐�
	void MeshCreate();
	//���C���X�e�[�W�̕`��
	void MainStageDraw(std::shared_ptr<GameCamera>gamecamera);
	//�`���[�g���A���X�e�[�W�̕`��
	void TutorialStageDraw(std::shared_ptr<GameCamera>gamecamera);
	//�`���[�g���A���X�e�[�W�̕ǂ̍���
	static const int SIZE = 1600;
	//------------Getter/Setter------------------------//
	tnl::Vector3 getSkyEmissive() {return m_skybox->getMtrlEmissive();}
	void setSkyEmissive(tnl::Vector3 param) { m_skybox->setMtrlEmissive({ param.x,param.y,param.z }); }
	const std::vector<Shared<dxe::Mesh>>& getMesh()const { return m_tutorial_mesh_vector; }
private:

	//���b�V����ۑ�����x�N�^�[
	std::vector<Shared<dxe::Mesh>> m_main_mesh_vector;
	std::vector<Shared<dxe::Mesh>> m_tutorial_mesh_vector;

	//�X�e�[�W�̃I���W�i�����b�V��
	std::vector<Shared<dxe::Mesh>> m_main_original_mesh;
	std::vector<Shared<dxe::Mesh>> m_tutorial_original_mesh;

	//�`���[�g���A���}�b�v��csv�n���h��
	std::vector<std::vector<int>> m_tutorial_csv;
	//�|���S���^�C�v�ƃe�N�X�`���[��ۑ�����csv�̃��[�h�p�x�N�^�[
	std::vector<std::vector<tnl::CsvCell>> m_mesh_csv;
	//�G�~�b�V�u�J���[
	tnl::Vector3 m_skybox_emmisive = { 0.36,0.42,0.42 };

	//------------���N���X�̎Q�Ɨp�|�C���^------------------------//
	std::shared_ptr<Stage>m_stage;
	std::shared_ptr<Mediator>m_mediator;
	//�X�J�C�{�b�N�X�̃|�C���^
	Shared<dxe::Mesh> m_skybox = nullptr;
};



