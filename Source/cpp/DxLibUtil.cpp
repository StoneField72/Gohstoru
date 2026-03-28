

#include "DxLibUtil.h"

struct LogEntry
{
	std::string text;
	int startTime;     // 表示開始時刻（ミリ秒）
	int alpha;         // 現在の透明度（0〜255）
};

std::vector<LogEntry> displayedLogs; // 表示中のログ
std::vector<std::string> pendingLogs; // まだ表示してないログ
int lastLogTime = 0;
const int LOG_INTERVAL = 1000; // 1秒ごとに1行表示

void AddLog(const std::string& message)
{
	pendingLogs.push_back(message);
}

void AddScore(int amount, int LogType)
{
	// スコア変化をログに記録
	char buffer[64];

	switch (LogType)
	{
	case 0://最終スコア
		sprintf_s(buffer, "写真のスコア:%d", amount);
		break;

	case 1://
		sprintf_s(buffer, "よく写っている:%d", amount);
		break;

	case 2:
		sprintf_s(buffer, "　　写っている:%d", amount);
		break;

	case 3:
		sprintf_s(buffer, "少し写っている:%d", amount);
		break;

	case 4:
		sprintf_s(buffer, "ボーナス:+%d", amount);
		break;
	default:
		break;
	}
	
	AddLog(std::string(buffer));
}

void UpdateLogs()
{
	int now = GetNowCount();

	// 一定時間ごとに1行ずつ表示
	if (!pendingLogs.empty() && now - lastLogTime >= LOG_INTERVAL)
	{
		LogEntry entry;
		entry.text = pendingLogs.front();
		entry.startTime = now;
		entry.alpha = 255;

		displayedLogs.push_back(entry);
		pendingLogs.erase(pendingLogs.begin());
		lastLogTime = now;
	}

	// フェード処理
	for (auto& entry : displayedLogs)
	{
		int elapsed = now - entry.startTime;
		if (elapsed > 1500) // 表示から3秒後にフェード開始
		{
			entry.alpha -= 5;
			if (entry.alpha < 0) entry.alpha = 0;
		}
	}

	// 消えたログを削除
	displayedLogs.erase(
		std::remove_if(displayedLogs.begin(), displayedLogs.end(),
			[](const LogEntry& e) { return e.alpha == 0; }),
		displayedLogs.end()
	);
}

void DrawLogs()
{
	int y = 200;
	for (const auto& entry : displayedLogs)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, entry.alpha);
		DrawString(SCREEN_SIZE_X - 250, y, entry.text.c_str(), GetColor(255, 255, 255));
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		y += 20;
	}

	UpdateLogs();
}

void ClearAllLogs()
{
	displayedLogs.clear();
	pendingLogs.clear();
}

VECTOR DxLibLerp(VECTOR& start, VECTOR& end, float t)
{
	VECTOR ret;

	ret = VAdd(start, VScale(VSub(end, start), t));

	return ret;
}


GameObject* GetEnemyObject(GameObject* parent)
{
	auto fighters = Master::objectManager->GetObjectsByTag("Enemy");
	for (auto fighter : fighters)
	{
		for (auto obj : Master::objectManager->GetObjectList())
		{
			if (obj->GetTag() == "Enemy")
			{
				return obj;
			}
		}
	}

	return nullptr;
}


GameObject* GetPlayerObject()
{
	auto fighters = Master::objectManager->GetObjectsByTag("player");
	for (auto fighter : fighters)
	{
		for (auto obj : Master::objectManager->GetObjectList())
		{
			if (obj->GetTag() == "player")
			{
				return obj;
			}
		}
	}

	return nullptr;
}


GameObject* GetStageObject(GameObject* parent)
{
	auto fighters = Master::objectManager->GetObjectsByTag("stage");
	for (auto fighter : fighters)
	{
		for (auto obj : Master::objectManager->GetObjectList())
		{
			if (obj->GetTag() == "stage")
			{
				return obj;
			}
		}
	}

	return nullptr;
}
