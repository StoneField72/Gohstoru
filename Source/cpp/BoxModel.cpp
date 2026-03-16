

#include "BoxModel.h"


BoxModel::BoxModel()
{
    m_boxMap.clear();
}

BoxModel::~BoxModel()
{
    m_boxMap.clear();
}

void BoxModel::AddBox(std::string tag, DxLibBox& box, std::string parentName)
{
    //親のタグが指定されているなら
    if (!parentName.empty()) 
    {
        //登録されているmapからDxLibBoxを取得
        DxLibBox* tempBox = GetBox(parentName);
        if (tempBox != nullptr)
        {
            //取得に成功したら親を登録
            box.SetParent(tempBox->GetMatrix());
        }
    }

    //  <first, second>
    //map<キー, 要素>
    //mapはキーがなければ要素をpush、キーが見つかれば要素を上書きする
    m_boxMap[tag] = box;
}

DxLibBox* BoxModel::GetBox(std::string tag)
{
    auto it = m_boxMap.find(tag);

    //タグで指定した要素が見つからないならnullptrを返す
    if (it == m_boxMap.end())
    {
        nullptr;
    }

    //要素のポインタを返す
    return &(it->second);
}

void BoxModel::Init(void)
{
    m_boxMap.clear();
}

void BoxModel::Uninit(void)
{
    m_boxMap.clear();
}

void BoxModel::Update(void)
{
    for (auto &box : m_boxMap) 
    {
        (box.second).Transform();//親子付け
    }
}

void BoxModel::Draw(void)
{
    for (auto& box : m_boxMap)
    {
        (box.second).Draw();
    }
}