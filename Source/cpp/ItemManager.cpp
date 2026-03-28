#include "ItemManager.h"
#include "DxLibUtil.h"


ItemManager::ItemManager(VECTOR position, VECTOR rotation)
{
    BoxHandle = -1;
    BoxTexHandle = -1;
    BoxOpenedHandle = -1;

    ObjRotation = rotation;
    ObjPosition = position;

    Open = false;
    OpenCount = 200.0f;

    this->SetInvisible(false);
}

ItemManager::~ItemManager()
{

}

void ItemManager::Init()
{
    BoxHandle = MV1LoadModel("Resource/asset/BOX/Box.mv1");
    BoxTexHandle = LoadGraph("Resource/asset/BOX/Boxes_on_pallet1.png");
    BoxOpenedHandle = MV1LoadModel("Resource/asset/BOX/BoxOpened.mv1");

    MV1SetTextureGraphHandle(BoxHandle, 0, BoxTexHandle, true);
    MV1SetTextureGraphHandle(BoxOpenedHandle, 0, BoxTexHandle, true);

    MV1SetPosition(BoxHandle, ObjPosition);
    MV1SetPosition(BoxOpenedHandle, ObjPosition);

    MV1SetRotationXYZ(BoxHandle, ObjRotation);
    MV1SetRotationXYZ(BoxOpenedHandle, ObjRotation);

    MV1SetScale(BoxHandle, VGet(2.0f, 2.0f, 2.0f));
    MV1SetScale(BoxOpenedHandle, VGet(2.0f, 2.0f, 2.0f));
}

void ItemManager::Uninit()
{
    MV1DeleteModel(BoxHandle);
    DeleteGraph(BoxTexHandle);
    MV1DeleteModel(BoxOpenedHandle);
}

int ItemManager::Update()
{
    // プレイヤーと宝箱の座標（VECTOR型） 
    VECTOR playerPos = GetPlayerObject()->GetPos();

    // プレイヤーの視線ベクトル（正規化されていると仮定） 
    VECTOR playerDir = GetPlayerObject()->GetDir();

    // 宝箱への方向ベクトルを計算
    VECTOR toChest = VSub(VAdd(ObjPosition, VGet(0.0f, 200.0f, 0.0f)), playerPos);
    toChest = VNorm(toChest); 

    // 距離を計算 
    float distance = VSize(VSub(ObjPosition, playerPos));
    // 向きの判定（内積を使って角度をチェック）
    //  
    float dot = VDot(playerDir, toChest); 

    // 条件：距離が近く、かつ視線が宝箱の方向を向いている 
    const float OPEN_DISTANCE = 500.0f;

    // 距離のしきい値（単位：DxLibの座標系）
    const float ANGLE_THRESHOLD = 0.5f; 


    if (Open == false)
    {
        // cos(30度) 
        if (distance < OPEN_DISTANCE && dot > ANGLE_THRESHOLD)
        {
            this->Openeble = true;

            if (CheckHitKey(KEY_INPUT_F) && Master::shot->GetGameTime() > 0)
            {
                // 宝箱を開ける処理 
                Open = true;
                this->SetInvisible(true);

                AddLog("宝箱を開けた");
            }
        }
        else
        {
            this->Openeble = false;
        }
    }
    else
    {
        if (OpenCount == 0)
        {
            this->SetActive(FALSE);
        }
        else
        {
            OpenCount -= 1.0f;
        }
        
        this->Openeble = false;
    }

    return 0;
}

void ItemManager::Draw()
{
    SetUseLighting(false);
    
    if (Open)
    {
        if (OpenCount <= 100)
        {
            MV1SetOpacityRate(BoxOpenedHandle, OpenCount / 100);
        }

        MV1DrawModel(BoxOpenedHandle);
    }
    else
    {
        MV1DrawModel(BoxHandle);
    }
    
    SetUseLighting(true);
}