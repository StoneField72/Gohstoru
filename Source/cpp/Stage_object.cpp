
#include "stage_object.h"
#include "Master.h"
#include "DxLib.h"
#include "DxLibUtil.h"
#include "Collision.h"


StageObject::StageObject(const char* filename, VECTOR position, VECTOR Scale, VECTOR rotation)
    : ObjectHandle(-1),
    textureHandle1(-1),
    textureHandle2(-1),
    ObjPosition(position),
    ObjScale(Scale),
    ObjRotation(rotation),
    Objsize(VGet(0.0f, 0.0f, 0.0f)),
    Treesize(VGet(0.0f, 0.0f, 0.0f))
{
    ObjectHandle = MV1LoadModel(filename);
}

StageObject::StageObject(const char* filename, const char* texturePath1, VECTOR position, VECTOR Scale, VECTOR rotation)
    : ObjectHandle(-1),
    textureHandle1(-1),
    textureHandle2(-1),
    ObjPosition(position),
    ObjScale(Scale),
    ObjRotation(rotation),
    Objsize(VGet(0.0f, 0.0f, 0.0f)),
    Treesize(VGet(0.0f, 0.0f, 0.0f))
{
    ObjectHandle = MV1LoadModel(filename);

    if (texturePath1 != nullptr)
    {
        textureHandle1 = LoadGraph(texturePath1);
        if (textureHandle1 != -1)
        {
            MV1SetTextureGraphHandle(ObjectHandle, 0, textureHandle1, true);
        }
    }
}

StageObject::StageObject(const char* filename, const char* texturePath1, const char* texturePath2, VECTOR position, VECTOR Scale, VECTOR rotation)
    : ObjectHandle(-1),
    textureHandle1(-1),
    textureHandle2(-1),
    ObjPosition(position),
    ObjScale(Scale),
    ObjRotation(rotation),
    Objsize(VGet(0.0f, 0.0f, 0.0f)),
    Treesize(VGet(0.0f, 0.0f, 0.0f))
{
    ObjectHandle = MV1LoadModel(filename);

    textureHandle1 = LoadGraph(texturePath1);
    if (textureHandle1 != -1)
    {
        MV1SetTextureGraphHandle(ObjectHandle, 0, textureHandle1, TRUE);
    }

    textureHandle2 = LoadGraph(texturePath2);
    if (textureHandle2 != -1)
    {
        MV1SetTextureGraphHandle(ObjectHandle, 1, textureHandle2, TRUE);
    }
    
    if (texturePath1 == "Resource/asset/NAT_Grass1_AS.jpg")
    {
        // ３Ｄモデルに含まれる０番目のバックカリングを無効にする
        MV1SetMeshBackCulling(ObjectHandle, 0, FALSE);
    }
}

StageObject::~StageObject()
{
    MV1DeleteModel(ObjectHandle);

    DeleteGraph(textureHandle1);
    DeleteGraph(textureHandle2);
}

void StageObject::Init()
{
    // メッシュ番号（通常は0がメイン）
    int meshIndex = 0;

    // 最小・最大座標を取得
    VECTOR minPos = MV1GetMeshMinPosition(ObjectHandle, meshIndex);
    VECTOR maxPos = MV1GetMeshMaxPosition(ObjectHandle, meshIndex);

    // 大きさを計算
    float sizeX = maxPos.x - minPos.x;
    float sizeY = maxPos.y - minPos.y;
    float sizeZ = maxPos.z - minPos.z;
    Objsize = VGet(sizeX * ObjScale.x, sizeY * ObjScale.y, sizeZ * ObjScale.z);

    Treesize = VGet(200.0f, 500.0f, 200.0f);

    if (ObjRotation.y == DX_PI_F / 2 || ObjRotation.y == (-DX_PI_F / 2))
    {
        float x = Objsize.x;
        Objsize.x = Objsize.z;
        Objsize.z = x;
    }

    this->SetScale(Objsize);
    this->SetPos(VSub(ObjPosition, VGet(0.0f, ObjPosition.y * 2, 0.0f)));

    MV1SetMaterialDifColor(ObjectHandle, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
    MV1SetMaterialEmiColor(ObjectHandle, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
    MV1SetEmiColorScale(ObjectHandle, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));

    MV1SetPosition(ObjectHandle, ObjPosition);
    MV1SetScale(ObjectHandle, ObjScale);
    MV1SetRotationXYZ(ObjectHandle, ObjRotation);
}


int StageObject::Update()
{
    GameObject* player = GetPlayerObject();

    VECTOR playerPos = player->GetPos();
    VECTOR playerSize = VGet(200.0f, 300.0f, 100.0f);

    //オブジェクトとプレイヤーの当たり判定
    if (Collision::CheckCollisionAABB(playerPos, playerSize, ObjPosition, Objsize)) 
    {
        //DrawFormatString(300, 30, GetColor(0, 0, 0), "当たった");
    }

    std::list<GameObject*> enemys = Master::objectManager->GetObjectsByTag("Enemy");
    for (GameObject* enemy : enemys)
    {
        if (this->GetTag() == "stage")
        {
            //プレイヤーから敵が見えているか
            if (Collision::CheckRayAABB(playerPos, enemy->GetPos(), ObjPosition, Objsize) == true)
            {
                enemy->SetInvisible(true);
                enemy->SetInThePic(false);
                //printfDx("オブジェクトに隠れている\n");
            }
        }

        if (this->GetTag() == "tree")
        {
            //プレイヤーから敵が見えているか
            if (Collision::CheckRayAABB(playerPos, enemy->GetPos(), ObjPosition, Treesize) == true)
            {
                enemy->SetInvisible(true);
                enemy->SetInThePic(false);
                //printfDx("木に隠れている\n");
            }
        }
    }

    //auto fighters = Master::objectManager->GetObjectsByTag("Enemy");
    //for (auto fighter : fighters)
    //{
    //    for (auto obj : Master::objectManager->GetObjectList())
    //    {
    //        if (obj->GetTag() == "Enemy")
    //        {
    //            if (this->GetTag() == "stage")
    //            {
    //                //プレイヤーから敵が見えているか
    //                if (Collision::CheckRayAABB(playerPos, obj->GetPos(), ObjPosition, Objsize) == true)
    //                {
    //                    obj->SetInvisible(true);
    //                    //DrawFormatString(300, 50, GetColor(0, 0, 0), "Invisible");
    //                }
    //            }
    //        }
    //    }
    //}

    return 0;
}


void StageObject::Draw()
{
    //SetUseZBuffer3D(TRUE);
    //SetWriteZBuffer3D(TRUE);

    //MV1SetMaterialSpcPower(ObjectHandle, 0, 10.0f);
    //MV1SetMaterialSpcPower(ObjectHandle, 1, 10.0f);

    //SetUseLighting(TRUE);

    SetUseLighting(false);
    MV1DrawModel(ObjectHandle); 
    SetUseLighting(true);

    //SetUseLighting(FALSE);
}


void StageObject::Uninit()
{
    MV1DeleteModel(ObjectHandle);

    DeleteGraph(textureHandle1);
    DeleteGraph(textureHandle2);
}