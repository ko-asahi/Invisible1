// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Interaction/AILevelDialogueMappingAsset.h"

const UDataTable* UAILevelDialogueMappingAsset::ResolveTableByLevel(FName InLevelName) const
{
	// 遍历映射表，查找当前关卡的文本库
	for (const FLevelDialogueTableMapping& Mapping : LevelMappings)
	{
		if (Mapping.LevelName.IsNone())
		{
			continue;
		}
		if (Mapping.LevelName == InLevelName)
		{
			if (UDataTable* Table = Mapping.DialogueTable.LoadSynchronous())
			{
				return Table;
			}
		}
	}

	// 回退默认库
	if (UDataTable* DefaultTable = DefaultDialogueTable.LoadSynchronous())
	{
		return DefaultTable;
	}
    
	//没有可用文本库
	return nullptr;
}