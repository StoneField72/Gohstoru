#pragma once

#include "DxLib.h"
#include <string>
#include "Animator.h"

//É}ÉNÉçíËã`
#define SAFE_DELETE(p) if (p) { delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY(p) if (p) { delete[] p; p = nullptr; }


class GameObject
{
protected:
	std::string m_tag;
	unsigned int m_layer;
	bool m_isActive;
	bool m_isDontDestroy;

	bool Invisible;
	bool InthePicture;
	int  PhotoScore;
	bool Select;

	bool Openeble;

	int m_team;
	VECTOR m_pos;
	VECTOR m_dir;
	VECTOR m_scale;
	float m_speed;
	Animator m_animator;

public:
	GameObject() = default;
	virtual ~GameObject() = default;

	void SetTag(const std::string& tag) { m_tag = tag; }
	void SetLayer(const unsigned int layer) { m_layer = layer; }
	void SetActive(const bool b) { m_isActive = b; }
	void SetDontDestroy(const bool b) { m_isDontDestroy = b; }

	void SetInvisible(const bool b) { Invisible = b; }
	void SetInThePic(const bool b) { InthePicture = b; }
	void SetScore(const int s) { PhotoScore = s; }
	void SetSelect(const bool b) { Select = b; }

	void SetTeam(int t) { m_team = t; }
	void SetPos(const VECTOR& position) { m_pos = position; }
	void SetDir(const VECTOR& direction) { m_dir = direction; }
	void SetSpeed(const float spd) { m_speed = spd; }
	void SetScale(const VECTOR scl) { m_scale = scl; }

	std::string GetTag(void) const { return m_tag; }
	unsigned int GetLayer(void) const { return m_layer; }
	bool IsActive(void) const { return m_isActive; }
	bool IsDontDestroy(void) const { return m_isDontDestroy; }

	bool GetInvisible(void) const { return Invisible; }
	bool GetInThePic(void) const { return InthePicture; }
	int GetScore(void) const { return PhotoScore; }
	bool GetSelect(void) const { return Select; }

	bool GetOpeneble(void) const { return Openeble; }

	int GetTeam(void) const { return m_team; }
	VECTOR GetPos(void) const { return m_pos; }
	VECTOR GetDir(void) const { return m_dir; }
	float GetSpeed(void) const { return m_speed; }
	VECTOR GetScale(void) const { return m_scale; }
	Animator* GetAnimator(void) { return &m_animator; }

	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual int Update(void) = 0;
	virtual void Draw(void) = 0;
};
