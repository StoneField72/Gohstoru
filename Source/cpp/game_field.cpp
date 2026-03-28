
#include "game_field.h"
#include "Master.h"

Field::Field()
{

}

Field::~Field()
{
    
}

void Field::Init()
{
    //モデルの読み込み
    skyhandle = MV1LoadModel("Resource/asset/sky/Stage00_sky.mv1");
    MV1SetPosition(skyhandle, VGet(0.0f, -16000.0f, 0.0f));
    MV1SetScale(skyhandle, VGet(2.0f, 2.0f, 2.0f));

    floorhandle = LoadGraph("Resource/asset/GR_Moss1_AS.png");
    floornormalhandle = LoadGraph("Resource/asset/GR_Moss1_N.png");

    //木
    woodtexhandle = LoadGraph("Resource/asset/diffuse.png");
    for (int i = 0; i < 60; i++)
    {
        woodhandle[i] = MV1LoadModel("Resource/asset/Tree.mv1");
        MV1SetTextureGraphHandle(woodhandle[i], 0, woodtexhandle, TRUE); // 0はテクスチャ番号
        MV1SetScale(woodhandle[i], VGet(1.0f, 1.0f, 1.0f));

        if (i >= 0 && i < 15)
        {
            if (i % 2 == 0)
            {
                MV1SetPosition(woodhandle[i], VGet(6000.0f, -200.0f, -4800.0f + (i * 840)));
                MV1SetRotationXYZ(woodhandle[i], VGet(0.0f, DX_PI_F + (i * 70.0f), 0.0f));
            }
            else
            {
                MV1SetPosition(woodhandle[i], VGet(7000.0f, -200.0f, -4800.0f + (i * 840)));
                MV1SetRotationXYZ(woodhandle[i], VGet(0.0f, DX_PI_F + (i * 70.0f), 0.0f));
            }
        }
        else if (i >= 15 && i < 30)
        {
            if (i % 2 == 0)
            {
                MV1SetPosition(woodhandle[i], VGet(-7000.0f, -200.0f, -5500.0f + ((i - 15) * 840)));
                MV1SetRotationXYZ(woodhandle[i], VGet(0.0f, DX_PI_F + (i * 70.0f), 0.0f));
            }
            else
            {
                MV1SetPosition(woodhandle[i], VGet(-6000.0f, -200.0f, -5500.0f + ((i - 15) * 840)));
                MV1SetRotationXYZ(woodhandle[i], VGet(0.0f, DX_PI_F + (i * 70.0f), 0.0f));
            }
        }
        else if (i >= 30 && i < 45)
        {
            if (i % 2 == 0)
            {
                MV1SetPosition(woodhandle[i], VGet(-4800.0f + ((i - 30) * 840), -200.0f, 6000.0f));
                MV1SetRotationXYZ(woodhandle[i], VGet(0.0f, DX_PI_F + (i * 70.0f), 0.0f));
            }
            else
            {
                MV1SetPosition(woodhandle[i], VGet(-4800.0f + ((i - 30) * 840), -200.0f, 7000.0f));
                MV1SetRotationXYZ(woodhandle[i], VGet(0.0f, DX_PI_F + (i * 70.0f), 0.0f));
            }
           
        }
        else if (i >= 45 && i < 60)
        {
            if (i % 2 == 0)
            {
                MV1SetPosition(woodhandle[i], VGet(-5500.0f + ((i - 45) * 840), -200.0f, -7000.0f));
                MV1SetRotationXYZ(woodhandle[i], VGet(0.0f, DX_PI_F + (i * 70.0f), 0.0f));
            }
            else
            {
                MV1SetPosition(woodhandle[i], VGet(-5500.0f + ((i - 45) * 840), -200.0f, -6000.0f));
                MV1SetRotationXYZ(woodhandle[i], VGet(0.0f, DX_PI_F + (i * 70.0f), 0.0f));
            }
        }
    }

    grasstexhandle1 = LoadGraph("Resource/asset/NAT_Grass1_AS.jpg");
    grasstexhandle2 = LoadGraph("Resource/asset/NAT_Grass1_N.jpg");

    for (int i = 0; i < 100; i++)
    {
        grasshandle[i] = MV1LoadModel("Resource/asset/Grass.mv1");

        MV1SetTextureGraphHandle(grasshandle[i], 0, grasstexhandle1, TRUE); // 0はテクスチャ番号
        MV1SetTextureGraphHandle(grasshandle[i], 1, grasstexhandle2, TRUE); // 1はテクスチャ番号

        // 3Dモデルに含まれる0番目のバックカリングを無効にする
        MV1SetMeshBackCulling(grasshandle[i], 0, FALSE);

        MV1SetScale(grasshandle[i], VGet(2.0f, 2.0f, 2.0f));
        MV1SetPosition(grasshandle[i], VGet((GetRand(9900) - 5000), -200.0f, (GetRand(9900) - 5000)));
        MV1SetRotationXYZ(grasshandle[i], VGet(0.0f, DX_PI_F + GetRand(180), 0.0f));
    }

    SetTextureAddressModeUV(DX_TEXADDRESS_WRAP, DX_TEXADDRESS_WRAP);

    const float MAP_SIZE = 20000;
    TopLeft = VGet(-MAP_SIZE / 2, -200.0f, MAP_SIZE / 2);
    diameter = MAP_SIZE;

    // ポリゴンの頂点のデータをセット
    {
        //左上
        Vertex[0].pos = VGet(TopLeft.x, TopLeft.y, TopLeft.z);
        Vertex[0].norm = VGet(0.0f, 1.0f, 0.0f);
        Vertex[0].dif = GetColorU8(255, 255, 255, 255);
        Vertex[0].spc = GetColorU8(0, 0, 0, 0);
        Vertex[0].u = 0.0f;
        Vertex[0].v = 0.0f;
        Vertex[0].su = 0.0f;
        Vertex[0].sv = 0.0f;

        //右上
        Vertex[1].pos = VGet(TopLeft.x + diameter, TopLeft.y, TopLeft.z);
        Vertex[1].norm = VGet(0.0f, 1.0f, 0.0f);
        Vertex[1].dif = GetColorU8(255, 255, 255, 255);
        Vertex[1].spc = GetColorU8(0, 0, 0, 0);
        Vertex[1].u = 8.0f;
        Vertex[1].v = 0.0f;
        Vertex[1].su = 8.0f;
        Vertex[1].sv = 0.0f;

        //左下
        Vertex[2].pos = VGet(TopLeft.x, TopLeft.y, TopLeft.z - diameter);
        Vertex[2].norm = VGet(0.0f, 1.0f, 0.0f);
        Vertex[2].dif = GetColorU8(255, 255, 255, 255);
        Vertex[2].spc = GetColorU8(0, 0, 0, 0);
        Vertex[2].u = 0.0f;
        Vertex[2].v = 8.0f;
        Vertex[2].su = 0.0f;
        Vertex[2].sv = 8.0f;

        //右下
        Vertex[3].pos = VGet(TopLeft.x + diameter, TopLeft.y, TopLeft.z - diameter);
        Vertex[3].norm = VGet(0.0f, 1.0f, 0.0f);
        Vertex[3].dif = GetColorU8(255, 255, 255, 255);
        Vertex[3].spc = GetColorU8(0, 0, 0, 0);
        Vertex[3].u = 8.0f;
        Vertex[3].v = 8.0f;
        Vertex[3].su = 8.0f;
        Vertex[3].sv = 8.0f;
    }

    // ２ポリゴン分のインデックスデータをセット
    Index[0] = 0;
    Index[1] = 1;
    Index[2] = 2;
    Index[3] = 3;
    Index[4] = 2;
    Index[5] = 1;

    //法線を求める
    VECTOR vec = VCross(VSub(Vertex[0].pos, Vertex[1].pos), VSub(Vertex[0].pos, Vertex[2].pos));
    Vertex[0].norm = VNorm(vec);
    Vertex[1].norm = Vertex[0].norm;
    Vertex[2].norm = Vertex[0].norm;
    Vertex[3].norm = Vertex[0].norm;
}

void Field::Uninit()
{
    MV1DeleteModel(skyhandle);
    DeleteGraph(floorhandle);
    DeleteGraph(floornormalhandle);

    DeleteGraph(woodtexhandle);
    DeleteGraph(grasstexhandle1);
    DeleteGraph(grasstexhandle2);
    for (int i = 0; i < 60; i++)
    {
        MV1DeleteModel(woodhandle[i]);
    }

    for (int i = 0; i < 100; i++)
    {
        MV1DeleteModel(grasshandle[i]);
    }
}

int Field::Update()
{
    static float rot = 0.0f;
    MV1SetRotationXYZ(skyhandle, VGet(0.0f, rot, 0.0f));
    rot += 0.0003f;

    return 0;
}

void Field::Draw()
{
    SetFogEnable(FALSE);
    MV1DrawModel(skyhandle);
    SetFogEnable(TRUE);

    if (m_team == 0)
    {
        // ２ポリゴンの描画
        DrawPolygonIndexed3D(Vertex, 4, Index, 2, floorhandle, false);
    }
    else
    {
        VERTEX3DSHADER vertex[4];
        for (int i = 0; i < 4; i++)
        {
            vertex[i].pos = Vertex[i].pos;
            vertex[i].norm = Vertex[i].norm;
            vertex[i].dif = Vertex[i].dif;
            vertex[i].spc = Vertex[i].spc;
            vertex[i].u = Vertex[i].u;
            vertex[i].v = Vertex[i].v;
            vertex[i].su = Vertex[i].su;
            vertex[i].sv = Vertex[i].sv;
        }

        // 使用するテクスチャを０番にセット
        SetUseTextureToShader(0, floorhandle);
        SetUseTextureToShader(1, floornormalhandle);

        DrawPolygonIndexed3DToShader(vertex, 4, Index, 2);
    }

    for (int i = 0; i < 60; i++)
    {
        MV1DrawModel(woodhandle[i]);
    }

    for (int i = 0; i < 100; i++)
    {
        MV1DrawModel(grasshandle[i]);
    }
}
