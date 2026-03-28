#pragma once

#include "DxLibBox.h"
#include <map>
#include <string>


class BoxModel
{
private:
	std::map<std::string, DxLibBox> m_boxMap;


public:
	BoxModel();
	virtual ~BoxModel();

	void AddBox(std::string tag, DxLibBox& box, std::string parentName = "");//Box‚Ì’Ç‰Á
	DxLibBox* GetBox(std::string tag);//Box‚ÌŽæ“¾

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};