#include "stdafx.h"
#ifdef __FreeBSD__
#include <md5.h>
#else
#include "../../libthecore/include/xmd5.h"
#endif

#include "utils.h"
#include "config.h"
#include "desc_client.h"
#include "desc_manager.h"
#include "char.h"
#include "char_manager.h"
#include "motion.h"
#include "packet.h"
#include "affect.h"
#include "pvp.h"
#include "start_position.h"
#include "party.h"
#include "guild_manager.h"
#include "p2p.h"
#include "dungeon.h"
#include "messenger_manager.h"
#include "war_map.h"
#include "questmanager.h"
#include "item_manager.h"
#include "monarch.h"
#include "mob_manager.h"
#include "dev_log.h"
#include "item.h"
#include "arena.h"
#include "buffer_manager.h"
#include "unique_item.h"
#include "threeway_war.h"
#include "log.h"
#include "../../common/VnumHelper.h"
#ifdef __AUCTION__
#include "auction_manager.h"
#endif

// ACMD(do_use_item)
// {
	// char arg1[256];
	// one_argument(argument, arg1, sizeof(arg1));
	// if (!*arg1)
	// {
		// ch->ChatPacket(CHAT_TYPE_INFO, "[do_use_item] Error 1: !*arg1");
		// return;
	// }		
	// int index;
	// str_to_number(index, arg1);		
	// ch->UseItem(TItemPos (INVENTORY, index));
// }

ACMD(do_sitdown)
{
	ch->Sitdown(1);
}

ACMD(do_standup)
{
	ch->Standup();
}

ACMD(do_reset_pickup_filter)
{
	ch->RemoveAffect(AFFECT_PICKUP_WEAPON_BLOCK);
	ch->RemoveAffect(AFFECT_PICKUP_ARMOR_BLOCK);
	ch->RemoveAffect(AFFECT_PICKUP_JEWELRY_BLOCK);
	ch->RemoveAffect(AFFECT_PICKUP_MATERIAL_BLOCK);
	ch->RemoveAffect(AFFECT_PICKUP_GHOSTSTONE_BLOCK);
	ch->RemoveAffect(AFFECT_PICKUP_SKILLBOOK_BLOCK);

	ch->ChatPacket(CHAT_TYPE_INFO, "[PickUpFilter] Alle Affects wurden gecleart. Relog ist empfehlenswert.");
	
}

ACMD(do_change_pickup_filter)
{
	// char arg1[256], arg2[256];
	// two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2));	
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));
	if (!*arg1)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[PickUpFilter] Error 1: !*arg1");
		return;
	}		
	// if (!*arg2)
	// {
		// ch->ChatPacket(CHAT_TYPE_INFO, "[PickUpFilter] Error 2: !*arg2");
		// return;
	// }	
	
	int index;
	// int status; // 0:Off, 1:On
	str_to_number(index, arg1);	
	// str_to_number(status, arg2);	
	
	switch (index)
	{
		case 1: // Weapon
			{
				if(ch->FindAffect(AFFECT_PICKUP_WEAPON_BLOCK))
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "[PickUpFilter] Du hebst nun wieder Waffen auf.");
					ch->RemoveAffect(AFFECT_PICKUP_WEAPON_BLOCK);
				}
				else
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "[PickUpFilter] Du hebst nun keine Waffen mehr auf.");
					ch->AddAffect(AFFECT_PICKUP_WEAPON_BLOCK, APPLY_NONE, 0, AFF_NONE, 60*60*24*365*60, 0, true, false);	
				}					
			}
			break;
		case 2: // Armor
			{
				if(ch->FindAffect(AFFECT_PICKUP_ARMOR_BLOCK))
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "[PickUpFilter] Du hebst nun wieder Rustungen auf.");
					ch->RemoveAffect(AFFECT_PICKUP_ARMOR_BLOCK);
				}
				else
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "[PickUpFilter] Du hebst nun keine Rustungen mehr auf.");
					ch->AddAffect(AFFECT_PICKUP_ARMOR_BLOCK, APPLY_NONE, 0, AFF_NONE, 60*60*24*365*60, 0, true, false);	
				}					
			}
			break;
		case 3: // Jewelry
			{
				if(ch->FindAffect(AFFECT_PICKUP_JEWELRY_BLOCK))
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "[PickUpFilter] Du hebst nun wieder Schmuck auf.");
					ch->RemoveAffect(AFFECT_PICKUP_JEWELRY_BLOCK);
				}
				else
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "[PickUpFilter] Du hebst nun keinen Schmuck mehr auf.");
					ch->AddAffect(AFFECT_PICKUP_JEWELRY_BLOCK, APPLY_NONE, 0, AFF_NONE, 60*60*24*365*60, 0, true, false);	
				}					
			}
			break;
		case 4: // Material
			{
				if(ch->FindAffect(AFFECT_PICKUP_MATERIAL_BLOCK))
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "[PickUpFilter] Du hebst nun wieder Upp-Items auf.");
					ch->RemoveAffect(AFFECT_PICKUP_MATERIAL_BLOCK);
				}
				else
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "[PickUpFilter] Du hebst nun keine Upp-Items mehr auf.");
					ch->AddAffect(AFFECT_PICKUP_MATERIAL_BLOCK, APPLY_NONE, 0, AFF_NONE, 60*60*24*365*60, 0, true, false);	
				}					
			}
			break;
		case 5: // Ghoststone
			{
				if(ch->FindAffect(AFFECT_PICKUP_GHOSTSTONE_BLOCK))
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "[PickUpFilter] Du hebst nun wieder Geiststeine auf.");
					ch->RemoveAffect(AFFECT_PICKUP_GHOSTSTONE_BLOCK);
				}
				else
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "[PickUpFilter] Du hebst nun keine Geiststeine mehr auf.");
					ch->AddAffect(AFFECT_PICKUP_GHOSTSTONE_BLOCK, APPLY_NONE, 0, AFF_NONE, 60*60*24*365*60, 0, true, false);	
				}					
			}
			break;		
		case 6: // Skillbook
			{
				if(ch->FindAffect(AFFECT_PICKUP_SKILLBOOK_BLOCK))
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "[PickUpFilter] Du hebst nun wieder Fertigkeitsbucher auf.");
					ch->RemoveAffect(AFFECT_PICKUP_SKILLBOOK_BLOCK);
				}
				else
				{
					ch->ChatPacket(CHAT_TYPE_INFO, "[PickUpFilter] Du hebst nun keine Fertigkeitsbucher mehr auf.");
					ch->AddAffect(AFFECT_PICKUP_SKILLBOOK_BLOCK, APPLY_NONE, 0, AFF_NONE, 60*60*24*365*60, 0, true, false);	
				}					
			}
			break;	
	}	
}

ACMD(do_timestamp_test)
{
	time_t ct = get_global_time();
	struct tm tm = *localtime(&ct);

	ch->ChatPacket(CHAT_TYPE_INFO,
			"%02d %02d %02d:%02d:%02d | ",
			tm.tm_mon + 1,
			tm.tm_mday,
			tm.tm_hour,
			tm.tm_min,
			tm.tm_sec);
}

ACMD(do_user_open_all_giftbox)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));
	if (!*arg1)
		return;	
	
	if (ch->IsObserverMode())
		return;

	if (ch->IsDead() || ch->IsStun())
		return;

	int slot;
	str_to_number(slot, arg1);
	
	LPITEM item = ch->GetInventoryItem(slot);
	if (NULL == item)
		return;
	int count_item = item->GetCount();
	if (count_item > 100)
		count_item = 100;
	
	std::vector <DWORD> dwVnums;
	std::vector <DWORD> dwCounts;
	std::vector <LPITEM> item_gets(0);
	int count = 0;	
	
	
	// ch->ChatPacket(CHAT_TYPE_INFO, "item_count: %d",count);
	if (item->GetType() == ITEM_GIFTBOX)
	{
		for (int i = 1; i <= count_item; ++i)
		{
			// ch->ChatPacket(CHAT_TYPE_INFO, "item_use: %d",i);
			ch->GiveItemFromSpecialItemGroup(item->GetVnum(), dwVnums, dwCounts, item_gets, count);
			item->SetCount(item->GetCount()-1);
		}				
	}


	
	// if (item->GetType() == ITEM_GIFTBOX)
	// {
		// for (int i = 1; i <= count; ++i)
		// {
			// // ch->ChatPacket(CHAT_TYPE_INFO, "item_use: %d",i);
			// ch->UseItem(TItemPos (INVENTORY, slot));
		// }				
	// }
	return;
}	
		
ACMD(do_user_bugreport)
{
	
	if(ch->GetQuestFlag("bugreport_reader.spamblock") > get_global_time())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[Spam-Schutz] Du kannst nur alle 10 Min. einen Bug-Report verfassen.");
		return;
	}
	
	ch->SetQuestFlag("bugreport_reader.spamblock",get_global_time()+600);
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
		return;
	DWORD reportIndex = number(1000000,9999999);
	char * query2 = (char*) malloc(sizeof(*query2));
	snprintf(query2, 1024, "INSERT INTO player.bugreport (id, playerName, time, bugReport, bugNumber) VALUES('%d', '%s', NOW(), '%s', '%d');", ch->GetAID(), ch->GetName(), arg1, reportIndex); //reportIndex);
	SQLMsg * msg2 = DBManager::instance().DirectQuery(query2);
	if(!msg2) {
		sys_err("[Bug-Report]: MySQL Query failed!");
		return;
	}
	free(query2);
	M2_DELETE(query2);	
	
	ch->ChatPacket(CHAT_TYPE_BIG_NOTICE, "Die Fehlermeldung wurde erfolgreich an den Server gesendet. Danke.");

}
ACMD(do_user_buy_switcher)
{
	int switcherBuyPrice = 6250000;
	if (ch->GetGold() < switcherBuyPrice)
		return;
	
	ch->AutoGiveItem(71084, 500);
	ch->PointChange(POINT_GOLD, -switcherBuyPrice, true);
	
}


ACMD(do_user_announce_switch_complete)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
		return;
	
	ch->ChatPacket(CHAT_TYPE_BIG_NOTICE, "Slot %s wurde fertig geswitcht!",arg1);
	
}

ACMD(do_user_horse_ride)
{
	if (ch->IsObserverMode())
		return;

	if (ch->IsDead() || ch->IsStun())
		return;

	if (ch->IsHorseRiding() == false)
	{
		// 말이 아닌 다른탈것을 타고있다.
		if (ch->GetMountVnum())
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "이미 탈것을 이용중입니다."));
			return;
		}

		if (ch->GetHorse() == NULL)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "말을 먼저 소환해주세요."));
			return;
		}

		ch->StartRiding();
	}
	else
	{
		ch->StopRiding();
	}
}

ACMD(do_new_user_horse_or_mount_ride)
{
	if (ch->IsObserverMode())
		return;

	if (ch->IsDead() || ch->IsStun())
		return;
	
	if (ch->IsHorseRiding() == false)
	{
		if (ch->GetHorse())
		{
			if(ch->horse_is_mount)
			{
				for (BYTE i=0; i<INVENTORY_MAX_NUM; ++i)
				{
					LPITEM item = ch->GetInventoryItem(i);
					if (NULL == item)
						continue;
					
					if (item->GetVnum() == 91200) {
						if(item->GetID() == ch->mount_seal_index)
						{
							ch->UseItem(TItemPos (INVENTORY, i));
							
						}
						return;
					}
				}				
			}
			ch->StartRiding();
			return;
		}
		else
		{
			for (BYTE i=0; i<INVENTORY_MAX_NUM; ++i)
			{
				LPITEM item = ch->GetInventoryItem(i);
				if (NULL == item)
					continue;
				
				if (item->GetVnum() == 91200) {
					int mount_index[34] = {20110,20111,20112,20113,20114,20115,20116,20117,20118,20119,20120,20121,20122,20123,20124,20125,20209,20210,20211,20212,20213,20214,20215,20219,20221,20222,20224,20225,20226,20227,20229,20230,20231,20232};
					int mount_skin_index = item->GetAttributeValue(0);
					int mount_skin = mount_index[mount_skin_index];
					DWORD mount_vnum = (DWORD)mount_skin;
					ch->HorseSummon(true, false, mount_vnum, "Reittier");
					ch->horse_is_mount = true;
					ch->mount_seal_index = item->GetID();
					
					//ch->UseItem(TItemPos (INVENTORY, i));
					return;
				}
			}
			if (ch->IsInOXMap())
				return;
			ch->HorseSummon(true,false,0,0);
			return;
		}		
		
		
	}
	
}

ACMD(do_user_horse_or_mount_ride)
{
	if (ch->IsObserverMode())
		return;

	if (ch->IsDead() || ch->IsStun())
		return;
	
	if (ch->IsHorseRiding() == false)
	{
		if (ch->GetHorse())
		{
			ch->StartRiding();
			return;
		}
		else
		{
			for (BYTE i=0; i<INVENTORY_MAX_NUM; ++i)
			{
				LPITEM item = ch->GetInventoryItem(i);
				if (NULL == item)
					continue;
				
				if (item->GetVnum() == 91200) {
					ch->UseItem(TItemPos (INVENTORY, i));
					return;
				}
			}
			if (ch->IsInOXMap())
				return;
			ch->StartRiding();
			return;
		}
	}
	else
	{
		ch->StopRiding();
	}
}

ACMD(do_user_enter_battlezone)
{
	if (ch->IsObserverMode())
		return;
	
	if(ch->GetMapIndex() == 361)
		return;

	if (ch->IsDead() || ch->IsStun())
		return;

	if (ch->GetLevel()<135)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Du musst lv.135 erreicht haben um die Kampfzone zu betreten!");
		return;		
	}
	if (ch->GetQuestFlag("battlezone.reenter_time") > get_global_time())
	{
		int iSecLeft = ch->GetQuestFlag("battlezone.reenter_time") - get_global_time();
		if (iSecLeft < 60)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "Du musst noch %d Sek. warten bis du die Kampfzone betreten kannst!",iSecLeft);
			return;
		}
		else
		{
			int iMinLeft = iSecLeft / 60;
			ch->ChatPacket(CHAT_TYPE_INFO, "Du musst noch %d Min. warten bis du die Kampfzone betreten kannst!",iMinLeft);
			return;			
		}	
	}
	if (ch->IsHorseRiding() || ch->GetMountVnum())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Du musst dein Reittier wegschicken um die Kampfzone zu betreten!");
		return;				
	}
	if (ch->GetParty())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Du musst deine Gruppe verlassen um die Kampfzone zu betreten!");
		return;			
	}
	if (!ch->CanWarp())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Du musst 10 Sek. warten bis du die Kampfzone betreten kannst!");
		return;			
	}
	if (ch->GetExchange())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Du musst den Handel beenden um die Kampfzone zu betreten!");
		return;			
	}	
	if (ch->IsOpenSafebox())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Du musst das Lager schlie?n um die Kampfzone zu betreten!");
		return;			
	}
	if (ch->IsCubeOpen())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Du musst das Crafting beenden um die Kampfzone zu betreten!");
		return;			
	}
	if (ch->GetShop())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Du musst den Laden verlassen um die Kampfzone zu betreten!");
		return;			
	}	
	if (ch->GetMyShop())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Du kannst die Kampfzone nicht betreten wahrend du einen Laden eroffnet hast.");
		return;			
	}	
	if (1 == quest::CQuestManager::instance().GetEventFlag("battlezone"))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Die Kampfzone ist immoment geschlossen...");
		return;		
	}
	
	int localBattlezonePos[7][2] = {
		{0,0},
		{180,346},
		{220,294},
		{189,194},
		{283,220},
		{327,238},
		{335,320}
	};
	
	int randomBattlezoneStartPos = number(1,6);
	long globalBattlezonePosX = (70000+localBattlezonePos[randomBattlezoneStartPos][0])*100;
	long globalBattlezonePosY = (70000+localBattlezonePos[randomBattlezoneStartPos][1])*100;
	
	
	//long mapIndexBattlezone = 361;
	//
	ch->SetQuestFlag("battlezone.respawn_time",180);
	ch->SetQuestFlag("battlezone.points",0);
	ch->WarpSet(globalBattlezonePosX,globalBattlezonePosY,0);
	//ch->SetWarpLocation((globalBattlezonePos+localBattlezonePos[randomBattlezoneStartPos][0])*100,(globalBattlezonePos+localBattlezonePos[randomBattlezoneStartPos][1])*100,mapIndexBattlezone);
	return;
}

ACMD(do_user_request_leave_battlezone)
{
	if(ch->GetMapIndex() == 361)
	{
		int chPoints = ch->GetQuestFlag("battlezone.points");
		if (chPoints == 0)
		{
			//ch->ChatPacket(CHAT_TYPE_INFO,"cmd:InstantEXIT");
			ch->ChatPacket(CHAT_TYPE_COMMAND,"battlezone instant_exit");
			return;
		}
		//ch->ChatPacket(CHAT_TYPE_INFO,"cmd:NormalEXIT");
		ch->ChatPacket(CHAT_TYPE_COMMAND,"battlezone request");
		return;
	}
}

ACMD(do_user_quick_exit_battlezone)
{
	if(ch->GetMapIndex() == 361)
	{
		ch->SetQuestFlag("battlezone.respawn_time",180);
		ch->SetQuestFlag("battlezone.points",0);
		ch->SetQuestFlag("battlezone.reenter_time",get_global_time()+60*5);
		ch->WarpSet(EMPIRE_START_X(ch->GetEmpire()), EMPIRE_START_Y(ch->GetEmpire()));
	}
}

ACMD(do_user_normal_leave_battlezone)
{
	if(ch->GetMapIndex() == 361)
	{
		ch->SetQuestFlag("battlezone.leave_time",get_global_time()+60*2);
		ch->ChatPacket(CHAT_TYPE_COMMAND,"battlezoneleavetimer %d",ch->GetQuestFlag("battlezone.leave_time"));
		SendNoticeMap("Ein Spieler versucht aus der Kampfzone zu entkommen! T?et ihn f? mehr Punkt(e)!", 361, true);
		ch->battlezone_SetMark();
		
	}
}

ACMD(do_user_final_leave_battlezone)
{
	if(ch->GetMapIndex() == 361)
	{
		
		int newHonorPoints 	= ch->GetQuestFlag("battlezone.honorpoints");
		int chPoints 		= ch->GetQuestFlag("battlezone.points");
		
		ch->SetQuestFlag("battlezone.honorpoints",newHonorPoints+chPoints);
		
		ch->SetQuestFlag("battlezone.success",chPoints);
		ch->SetQuestFlag("battlezone.respawn_time",180);
		ch->SetQuestFlag("battlezone.points",0);
		ch->SetQuestFlag("battlezone.reenter_time",get_global_time()+60*5);
		ch->WarpSet(EMPIRE_START_X(ch->GetEmpire()), EMPIRE_START_Y(ch->GetEmpire()));
		
	}
}

ACMD(do_dev_battlezone_reset_time)
{
	ch->SetQuestFlag("battlezone.reenter_time",0);
	ch->ChatPacket(CHAT_TYPE_INFO, "[Development] Die Wartezeit der Kampfzone wurde zur?kgesetzt!");
}

ACMD(do_set_pet_name)
{
	char arg1[256], arg2[256];
	two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2));	

	if (!*arg1)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[Pet-System] Fehler 1: !*arg1");
		return;
	}	
	
	DWORD itemIndex;

	if (isnhdigit(*arg1))
		str_to_number(itemIndex, arg1);	
	
	LPITEM item = ITEM_MANAGER::instance().Find(itemIndex);
	if (!item) 
	{
		// item wurde nicht gefunden = Abbruch!
		sys_err( "PetEggItem not found!" );
		return;
	}	
	
	LPITEM item2 = ch->AutoGiveItem(item->GetValue(0), 1);
	item2->SetSocket(0,1);
	
	//char szQuery1[1024];
	//snprintf(szQuery1, sizeof(szQuery1), "INSERT INTO pet_name_new VALUES(%d,'%s')", item->GetID(), arg2);
	//std::unique_ptr<SQLMsg> pmsg2(DBManager::instance().DirectQuery(szQuery1));
	
	
}

ACMD(do_user_horse_back)
{
	if (ch->GetHorse() != NULL)
	{
		ch->HorseSummon(false);
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "말을 돌려보냈습니다."));
	}
	else if (ch->IsHorseRiding() == true)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "말에서 먼저 내려야 합니다."));
	}
	else
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "말을 먼저 소환해주세요."));
	}
}

ACMD(do_user_horse_feed)
{
	// 개인상점을 연 상태에서는 말 먹이를 줄 수 없다.
	if (ch->GetMyShop())
		return;

	if (ch->GetHorse() == NULL)
	{
		if (ch->IsHorseRiding() == false)
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "말을 먼저 소환해주세요."));
		else
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "말을 탄 상태에서는 먹이를 줄 수 없습니다."));
		return;
	}

	DWORD dwFood = ch->GetHorseGrade() + 50054 - 1;

	if (ch->CountSpecifyItem(dwFood) > 0)
	{
		ch->RemoveSpecifyItem(dwFood, 1);
		ch->FeedHorse();
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "말에게 %s%s 주었습니다."),
				ITEM_MANAGER::instance().GetTable(dwFood)->szLocaleName,
				"");
	}
	else
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "%s 아이템이 필요합니다"), ITEM_MANAGER::instance().GetTable(dwFood)->szLocaleName);
	}
}

#define MAX_REASON_LEN		128

EVENTINFO(TimedEventInfo)
{
	DynamicCharacterPtr ch;
	int		subcmd;
	int         	left_second;
	char		szReason[MAX_REASON_LEN];

	TimedEventInfo()
	: ch()
	, subcmd( 0 )
	, left_second( 0 )
	{
		::memset( szReason, 0, MAX_REASON_LEN );
	}
};

struct SendDisconnectFunc
{
	void operator () (LPDESC d)
	{
		if (d->GetCharacter())
		{
			if (d->GetCharacter()->GetGMLevel() == GM_PLAYER)
				d->GetCharacter()->ChatPacket(CHAT_TYPE_COMMAND, "quit Shutdown(SendDisconnectFunc)");
		}
	}
};

struct DisconnectFunc
{
	void operator () (LPDESC d)
	{
		if (d->GetType() == DESC_TYPE_CONNECTOR)
			return;

		if (d->IsPhase(PHASE_P2P))
			return;

		if (d->GetCharacter())
			d->GetCharacter()->Disconnect("Shutdown(DisconnectFunc)");

		d->SetPhase(PHASE_CLOSE);
	}
};

EVENTINFO(shutdown_event_data)
{
	int seconds;

	shutdown_event_data()
	: seconds( 0 )
	{
	}
};

EVENTFUNC(shutdown_event)
{
	shutdown_event_data* info = dynamic_cast<shutdown_event_data*>( event->info );

	if ( info == NULL )
	{
		sys_err( "shutdown_event> <Factor> Null pointer" );
		return 0;
	}

	int * pSec = & (info->seconds);

	if (*pSec < 0)
	{
		sys_log(0, "shutdown_event sec %d", *pSec);

		if (--*pSec == -10)
		{
			const DESC_MANAGER::DESC_SET & c_set_desc = DESC_MANAGER::instance().GetClientSet();
			std::for_each(c_set_desc.begin(), c_set_desc.end(), DisconnectFunc());
			return passes_per_sec;
		}
		else if (*pSec < -10)
			return 0;

		return passes_per_sec;
	}
	else if (*pSec == 0)
	{
		const DESC_MANAGER::DESC_SET & c_set_desc = DESC_MANAGER::instance().GetClientSet();
		std::for_each(c_set_desc.begin(), c_set_desc.end(), SendDisconnectFunc());
		g_bNoMoreClient = true;
		--*pSec;
		return passes_per_sec;
	}
	else
	{
		char buf[64];
		snprintf(buf, sizeof(buf), LC_TEXT("셧다운이 %d초 남았습니다."), *pSec);
		SendNotice(buf);

		--*pSec;
		return passes_per_sec;
	}
}

void Shutdown(int iSec)
{
	if (g_bNoMoreClient)
	{
		thecore_shutdown();
		return;
	}

	CWarMapManager::instance().OnShutdown();

	char buf[64];
	snprintf(buf, sizeof(buf), LC_TEXT("%d초 후 게임이 셧다운 됩니다."), iSec);

	SendNotice(buf);

	shutdown_event_data* info = AllocEventInfo<shutdown_event_data>();
	info->seconds = iSec;

	event_create(shutdown_event, info, 1);
}

ACMD(do_shutdown)
{
	if (NULL == ch)
	{
		sys_err("Accept shutdown command from %s.", ch->GetName());
	}
	TPacketGGShutdown p;
	p.bHeader = HEADER_GG_SHUTDOWN;
	P2P_MANAGER::instance().Send(&p, sizeof(TPacketGGShutdown));

	Shutdown(10);
}

EVENTFUNC(timed_event)
{
	TimedEventInfo * info = dynamic_cast<TimedEventInfo *>( event->info );

	if ( info == NULL )
	{
		sys_err( "timed_event> <Factor> Null pointer" );
		return 0;
	}

	LPCHARACTER	ch = info->ch;
	if (ch == NULL) { // <Factor>
		return 0;
	}
	LPDESC d = ch->GetDesc();

	if (info->left_second <= 0)
	{
		ch->m_pkTimedEvent = NULL;

		switch (info->subcmd)
		{
			case SCMD_LOGOUT:
			case SCMD_QUIT:
			case SCMD_PHASE_SELECT:
				{
					TPacketNeedLoginLogInfo acc_info;
					acc_info.dwPlayerID = ch->GetDesc()->GetAccountTable().id;

					db_clientdesc->DBPacket( HEADER_GD_VALID_LOGOUT, 0, &acc_info, sizeof(acc_info) );

					LogManager::instance().DetailLoginLog( false, ch );
				}
				break;
		}

		switch (info->subcmd)
		{
			case SCMD_LOGOUT:
				if (d)
					d->SetPhase(PHASE_CLOSE);
				break;

			case SCMD_QUIT:
				ch->ChatPacket(CHAT_TYPE_COMMAND, "quit");
				break;

			case SCMD_PHASE_SELECT:
				{
					ch->Disconnect("timed_event - SCMD_PHASE_SELECT");

					if (d)
					{
						d->SetPhase(PHASE_SELECT);
					}
				}
				break;
		}

		return 0;
	}
	else
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "%d초 남았습니다."), info->left_second);
		--info->left_second;
	}

	return PASSES_PER_SEC(1);
}

ACMD(do_cmd)
{
	/* RECALL_DELAY
	   if (ch->m_pkRecallEvent != NULL)
	   {
	   ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "취소 되었습니다."));
	   event_cancel(&ch->m_pkRecallEvent);
	   return;
	   }
	// END_OF_RECALL_DELAY */

	if (ch->m_pkTimedEvent)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "취소 되었습니다."));
		event_cancel(&ch->m_pkTimedEvent);
		return;
	}

	switch (subcmd)
	{
		case SCMD_LOGOUT:
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "로그인 화면으로 돌아 갑니다. 잠시만 기다리세요."));
			break;

		case SCMD_QUIT:
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "게임을 종료 합니다. 잠시만 기다리세요."));
			break;

		case SCMD_PHASE_SELECT:
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "캐릭터를 전환 합니다. 잠시만 기다리세요."));
			break;
	}

	int nExitLimitTime = 10;

	if (ch->IsHack(false, true, nExitLimitTime) &&
		false == CThreeWayWar::instance().IsSungZiMapIndex(ch->GetMapIndex()) &&
	   	(!ch->GetWarMap() || ch->GetWarMap()->GetType() == GUILD_WAR_TYPE_FLAG))
	{
		return;
	}

	switch (subcmd)
	{
		case SCMD_LOGOUT:
		case SCMD_QUIT:
		case SCMD_PHASE_SELECT:
			{
				TimedEventInfo* info = AllocEventInfo<TimedEventInfo>();

				{
					if (ch->IsPosition(POS_FIGHTING))
						info->left_second = 10;
					else
						info->left_second = 3;
				}

				info->ch		= ch;
				info->subcmd		= subcmd;
				strlcpy(info->szReason, argument, sizeof(info->szReason));

				ch->m_pkTimedEvent	= event_create(timed_event, info, 1);
			}
			break;
	}
}

ACMD(do_mount)
{
	/*
	   char			arg1[256];
	   struct action_mount_param	param;

	// 이미 타고 있으면
	if (ch->GetMountingChr())
	{
	char arg2[256];
	two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	if (!*arg1 || !*arg2)
	return;

	param.x		= atoi(arg1);
	param.y		= atoi(arg2);
	param.vid	= ch->GetMountingChr()->GetVID();
	param.is_unmount = true;

	float distance = DISTANCE_SQRT(param.x - (DWORD) ch->GetX(), param.y - (DWORD) ch->GetY());

	if (distance > 600.0f)
	{
	ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "좀 더 가까이 가서 내리세요."));
	return;
	}

	action_enqueue(ch, ACTION_TYPE_MOUNT, &param, 0.0f, true);
	return;
	}

	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
	return;

	LPCHARACTER tch = CHARACTER_MANAGER::instance().Find(atoi(arg1));

	if (!tch->IsNPC() || !tch->IsMountable())
	{
	ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "거기에는 탈 수 없어요."));
	return;
	}

	float distance = DISTANCE_SQRT(tch->GetX() - ch->GetX(), tch->GetY() - ch->GetY());

	if (distance > 600.0f)
	{
	ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "좀 더 가까이 가서 타세요."));
	return;
	}

	param.vid		= tch->GetVID();
	param.is_unmount	= false;

	action_enqueue(ch, ACTION_TYPE_MOUNT, &param, 0.0f, true);
	 */
}

ACMD(do_fishing)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
		return;

	ch->SetRotation(atof(arg1));
	ch->fishing();
}

ACMD(do_console)
{
	ch->ChatPacket(CHAT_TYPE_COMMAND, "ConsoleEnable");
}

ACMD(do_restart)
{
	if (false == ch->IsDead())
	{
		ch->ChatPacket(CHAT_TYPE_COMMAND, "CloseRestartWindow");
		ch->StartRecoveryEvent();
		return;
	}

	if (NULL == ch->m_pkDeadEvent)
		return;

	int iTimeToDead = (event_time(ch->m_pkDeadEvent) / passes_per_sec);

	if (subcmd != SCMD_RESTART_TOWN && (!ch->GetWarMap() || ch->GetWarMap()->GetType() == GUILD_WAR_TYPE_FLAG))
	{
		if (!test_server)
		{
			if (ch->IsHack())
			{
				//성지 맵일경우에는 체크 하지 않는다.
				if (false == CThreeWayWar::instance().IsSungZiMapIndex(ch->GetMapIndex()))
				{
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "아직 재시작 할 수 없습니다. (%d초 남음)"), iTimeToDead - (180 - g_nPortalLimitTime));
					return;
				}
			}
#define eFRS_HERESEC	170
			if (iTimeToDead > eFRS_HERESEC)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "아직 재시작 할 수 없습니다. (%d초 남음)"), iTimeToDead - eFRS_HERESEC);
				return;
			}
		}
	}

	//PREVENT_HACK
	//DESC : 창고, 교환 창 후 포탈을 사용하는 버그에 이용될수 있어서
	//		쿨타임을 추가
	if (subcmd == SCMD_RESTART_TOWN)
	{
		if (ch->IsHack())
		{
			//길드맵, 성지맵에서는 체크 하지 않는다.
			if ((!ch->GetWarMap() || ch->GetWarMap()->GetType() == GUILD_WAR_TYPE_FLAG) ||
			   	false == CThreeWayWar::instance().IsSungZiMapIndex(ch->GetMapIndex()))
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "아직 재시작 할 수 없습니다. (%d초 남음)"), iTimeToDead - (180 - g_nPortalLimitTime));
				return;
			}
		}

#define eFRS_TOWNSEC	173
		if (iTimeToDead > eFRS_TOWNSEC)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "아직 마을에서 재시작 할 수 없습니다. (%d 초 남음)"), iTimeToDead - eFRS_TOWNSEC);
			return;
		}
	}
	//END_PREVENT_HACK

	ch->ChatPacket(CHAT_TYPE_COMMAND, "CloseRestartWindow");

	ch->GetDesc()->SetPhase(PHASE_GAME);
	ch->SetPosition(POS_STANDING);
	ch->StartRecoveryEvent();

	//FORKED_LOAD
	//DESC: 삼거리 전투시 부활을 할경우 맵의 입구가 아닌 삼거리 전투의 시작지점으로 이동하게 된다.
	if (1 == quest::CQuestManager::instance().GetEventFlag("threeway_war"))
	{
		if (subcmd == SCMD_RESTART_TOWN || subcmd == SCMD_RESTART_HERE)
		{
			if (true == CThreeWayWar::instance().IsThreeWayWarMapIndex(ch->GetMapIndex()) &&
					false == CThreeWayWar::instance().IsSungZiMapIndex(ch->GetMapIndex()))
			{
				ch->WarpSet(EMPIRE_START_X(ch->GetEmpire()), EMPIRE_START_Y(ch->GetEmpire()));

				ch->ReviveInvisible(5);
				ch->PointChange(POINT_HP, ch->GetMaxHP() - ch->GetHP());
				ch->PointChange(POINT_SP, ch->GetMaxSP() - ch->GetSP());

				return;
			}

			//성지
			if (true == CThreeWayWar::instance().IsSungZiMapIndex(ch->GetMapIndex()))
			{
				if (CThreeWayWar::instance().GetReviveTokenForPlayer(ch->GetPlayerID()) <= 0)
				{
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "성지에서 부활 기회를 모두 잃었습니다! 마을로 이동합니다!"));
					ch->WarpSet(EMPIRE_START_X(ch->GetEmpire()), EMPIRE_START_Y(ch->GetEmpire()));
				}
				else
				{
					ch->Show(ch->GetMapIndex(), GetSungziStartX(ch->GetEmpire()), GetSungziStartY(ch->GetEmpire()));
				}

				ch->PointChange(POINT_HP, ch->GetMaxHP() - ch->GetHP());
				ch->PointChange(POINT_SP, ch->GetMaxSP() - ch->GetSP());
				ch->ReviveInvisible(5);

				return;
			}
		}
	}
	//END_FORKED_LOAD

	if (ch->GetDungeon())
		ch->GetDungeon()->UseRevive(ch);

	if (ch->GetWarMap() && !ch->IsObserverMode())
	{
		CWarMap * pMap = ch->GetWarMap();
		DWORD dwGuildOpponent = pMap ? pMap->GetGuildOpponent(ch) : 0;

		if (dwGuildOpponent)
		{
			switch (subcmd)
			{
				case SCMD_RESTART_TOWN:
					sys_log(0, "do_restart: restart town");
					PIXEL_POSITION pos;

					if (CWarMapManager::instance().GetStartPosition(ch->GetMapIndex(), ch->GetGuild()->GetID() < dwGuildOpponent ? 0 : 1, pos))
						ch->Show(ch->GetMapIndex(), pos.x, pos.y);
					else
						ch->ExitToSavedLocation();

					ch->PointChange(POINT_HP, ch->GetMaxHP() - ch->GetHP());
					ch->PointChange(POINT_SP, ch->GetMaxSP() - ch->GetSP());
					ch->ReviveInvisible(5);
					break;

				case SCMD_RESTART_HERE:
					sys_log(0, "do_restart: restart here");
					ch->RestartAtSamePos();
					//ch->Show(ch->GetMapIndex(), ch->GetX(), ch->GetY());
					ch->PointChange(POINT_HP, ch->GetMaxHP() - ch->GetHP());
					ch->PointChange(POINT_SP, ch->GetMaxSP() - ch->GetSP());
					ch->ReviveInvisible(5);
					break;
			}

			return;
		}
	}
	switch (subcmd)
	{
		case SCMD_RESTART_TOWN:
			sys_log(0, "do_restart: restart town");
			PIXEL_POSITION pos;

			if (SECTREE_MANAGER::instance().GetRecallPositionByEmpire(ch->GetMapIndex(), ch->GetEmpire(), pos))
				ch->WarpSet(pos.x, pos.y);
			else
				ch->WarpSet(EMPIRE_START_X(ch->GetEmpire()), EMPIRE_START_Y(ch->GetEmpire()));
			ch->PointChange(POINT_HP, ch->GetMaxHP() - ch->GetHP());
			ch->PointChange(POINT_SP, ch->GetMaxSP() - ch->GetSP());
			ch->DeathPenalty(1);
			break;

		case SCMD_RESTART_HERE:
			sys_log(0, "do_restart: restart here");
			ch->RestartAtSamePos();
			//ch->Show(ch->GetMapIndex(), ch->GetX(), ch->GetY());
			ch->PointChange(POINT_HP, ch->GetMaxHP() - ch->GetHP());
			ch->PointChange(POINT_SP, ch->GetMaxSP() - ch->GetSP());
			ch->DeathPenalty(0);
			ch->ReviveInvisible(5);
			break;
	}
}

#define MAX_STAT g_iStatusPointSetMaxValue

ACMD(do_stat_reset)
{
	ch->PointChange(POINT_STAT_RESET_COUNT, 12 - ch->GetPoint(POINT_STAT_RESET_COUNT));
}

ACMD(do_stat_minus)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
		return;

	if (ch->IsPolymorphed())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "둔갑 중에는 능력을 올릴 수 없습니다."));
		return;
	}

	if (ch->GetPoint(POINT_STAT_RESET_COUNT) <= 0)
		return;

	if (!strcmp(arg1, "st"))
	{
		if (ch->GetRealPoint(POINT_ST) <= JobInitialPoints[ch->GetJob()].st)
			return;

		ch->SetRealPoint(POINT_ST, ch->GetRealPoint(POINT_ST) - 1);
		ch->SetPoint(POINT_ST, ch->GetPoint(POINT_ST) - 1);
		ch->ComputePoints();
		ch->PointChange(POINT_ST, 0);
	}
	else if (!strcmp(arg1, "dx"))
	{
		if (ch->GetRealPoint(POINT_DX) <= JobInitialPoints[ch->GetJob()].dx)
			return;

		ch->SetRealPoint(POINT_DX, ch->GetRealPoint(POINT_DX) - 1);
		ch->SetPoint(POINT_DX, ch->GetPoint(POINT_DX) - 1);
		ch->ComputePoints();
		ch->PointChange(POINT_DX, 0);
	}
	else if (!strcmp(arg1, "ht"))
	{
		if (ch->GetRealPoint(POINT_HT) <= JobInitialPoints[ch->GetJob()].ht)
			return;

		ch->SetRealPoint(POINT_HT, ch->GetRealPoint(POINT_HT) - 1);
		ch->SetPoint(POINT_HT, ch->GetPoint(POINT_HT) - 1);
		ch->ComputePoints();
		ch->PointChange(POINT_HT, 0);
		ch->PointChange(POINT_MAX_HP, 0);
	}
	else if (!strcmp(arg1, "iq"))
	{
		if (ch->GetRealPoint(POINT_IQ) <= JobInitialPoints[ch->GetJob()].iq)
			return;

		ch->SetRealPoint(POINT_IQ, ch->GetRealPoint(POINT_IQ) - 1);
		ch->SetPoint(POINT_IQ, ch->GetPoint(POINT_IQ) - 1);
		ch->ComputePoints();
		ch->PointChange(POINT_IQ, 0);
		ch->PointChange(POINT_MAX_SP, 0);
	}
	else
		return;

	ch->PointChange(POINT_STAT, +1);
	ch->PointChange(POINT_STAT_RESET_COUNT, -1);
	ch->ComputePoints();
}

ACMD(do_stat)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
		return;

	if (ch->IsPolymorphed())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "둔갑 중에는 능력을 올릴 수 없습니다."));
		return;
	}

	if (ch->GetPoint(POINT_STAT) <= 0)
		return;

	BYTE idx = 0;

	if (!strcmp(arg1, "st"))
		idx = POINT_ST;
	else if (!strcmp(arg1, "dx"))
		idx = POINT_DX;
	else if (!strcmp(arg1, "ht"))
		idx = POINT_HT;
	else if (!strcmp(arg1, "iq"))
		idx = POINT_IQ;
	else
		return;

	// ch->ChatPacket(CHAT_TYPE_INFO, "%s GRP(%d) idx(%u), MAX_STAT(%d), expr(%d)", __FUNCTION__, ch->GetRealPoint(idx), idx, MAX_STAT, ch->GetRealPoint(idx) >= MAX_STAT);
	if (ch->GetRealPoint(idx) >= MAX_STAT)
		return;

	ch->SetRealPoint(idx, ch->GetRealPoint(idx) + 1);
	ch->SetPoint(idx, ch->GetPoint(idx) + 1);
	ch->ComputePoints();
	ch->PointChange(idx, 0);

	if (idx == POINT_IQ)
	{
		ch->PointChange(POINT_MAX_HP, 0);
	}
	else if (idx == POINT_HT)
	{
		ch->PointChange(POINT_MAX_SP, 0);
	}

	ch->PointChange(POINT_STAT, -1);
	ch->ComputePoints();
}

ACMD(do_pvp)
{
	if (ch->GetArena() != NULL || CArenaManager::instance().IsArenaMap(ch->GetMapIndex()) == true)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "대련장에서 사용하실 수 없습니다."));
		return;
	}

	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	DWORD vid = 0;
	str_to_number(vid, arg1);
	LPCHARACTER pkVictim = CHARACTER_MANAGER::instance().Find(vid);

	if (!pkVictim)
		return;

	if (pkVictim->IsNPC())
		return;
	#ifdef ENABLE_MESSENGER_BLOCK
	if (MessengerManager::instance().IsBlocked_Target(ch->GetName(), pkVictim->GetName()))
	{
		//ben blokladım hacı
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "%s blokkk"), pkVictim->GetName());
		return;
	}
	if (MessengerManager::instance().IsBlocked_Target(ch->GetName(), pkVictim->GetName()))
	{
		//o blokladı hacı
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "%s blokkk_me"), pkVictim->GetName());
		return;
	}
	#endif
	if (pkVictim->GetArena() != NULL)
	{
		pkVictim->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(pkVictim->GetLanguage(), "상대방이 대련중입니다."));
		return;
	}

	CPVPManager::instance().Insert(ch, pkVictim);
}

ACMD(do_guildskillup)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
		return;

	if (!ch->GetGuild())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<길드> 길드에 속해있지 않습니다."));
		return;
	}

	CGuild* g = ch->GetGuild();
	TGuildMember* gm = g->GetMember(ch->GetPlayerID());
	if (gm->grade == GUILD_LEADER_GRADE)
	{
		DWORD vnum = 0;
		str_to_number(vnum, arg1);
		g->SkillLevelUp(vnum);
	}
	else
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<길드> 길드 스킬 레벨을 변경할 권한이 없습니다."));
	}
}

ACMD(do_skillup)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
		return;

	DWORD vnum = 0;
	str_to_number(vnum, arg1);

	if (true == ch->CanUseSkill(vnum))
	{
		ch->SkillLevelUp(vnum);
	}
	else
	{
		switch(vnum)
		{
			case SKILL_HORSE_WILDATTACK:
			case SKILL_HORSE_CHARGE:
			case SKILL_HORSE_ESCAPE:
			case SKILL_HORSE_WILDATTACK_RANGE:

			case SKILL_7_A_ANTI_TANHWAN:
			case SKILL_7_B_ANTI_AMSEOP:
			case SKILL_7_C_ANTI_SWAERYUNG:
			case SKILL_7_D_ANTI_YONGBI:

			case SKILL_8_A_ANTI_GIGONGCHAM:
			case SKILL_8_B_ANTI_YEONSA:
			case SKILL_8_C_ANTI_MAHWAN:
			case SKILL_8_D_ANTI_BYEURAK:

			case SKILL_ADD_HP:
			case SKILL_RESIST_PENETRATE:
				ch->SkillLevelUp(vnum);
				break;
		}
	}
}

//
// @version	05/06/20 Bang2ni - 커맨드 처리 Delegate to CHARACTER class
//
ACMD(do_safebox_close)
{
	ch->CloseSafebox();
}

//
// @version	05/06/20 Bang2ni - 커맨드 처리 Delegate to CHARACTER class
//
ACMD(do_safebox_password)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));
	ch->ReqSafeboxLoad(arg1);
}

ACMD(do_safebox_change_password)
{
	char arg1[256];
	char arg2[256];

	two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	if (!*arg1 || strlen(arg1)>6)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<창고> 잘못된 암호를 입력하셨습니다."));
		return;
	}

	if (!*arg2 || strlen(arg2)>6)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<창고> 잘못된 암호를 입력하셨습니다."));
		return;
	}

	TSafeboxChangePasswordPacket p;

	p.dwID = ch->GetDesc()->GetAccountTable().id;
	strlcpy(p.szOldPassword, arg1, sizeof(p.szOldPassword));
	strlcpy(p.szNewPassword, arg2, sizeof(p.szNewPassword));

	db_clientdesc->DBPacket(HEADER_GD_SAFEBOX_CHANGE_PASSWORD, ch->GetDesc()->GetHandle(), &p, sizeof(p));
}

ACMD(do_mall_password)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1 || strlen(arg1) > 6)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<창고> 잘못된 암호를 입력하셨습니다."));
		return;
	}

	int iPulse = thecore_pulse();

	if (ch->GetMall())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<창고> 창고가 이미 열려있습니다."));
		return;
	}

	if (iPulse - ch->GetMallLoadTime() < passes_per_sec * 10) // 10초에 한번만 요청 가능
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<창고> 창고를 닫은지 10초 안에는 열 수 없습니다."));
		return;
	}

	ch->SetMallLoadTime(iPulse);

	TSafeboxLoadPacket p;
	p.dwID = ch->GetDesc()->GetAccountTable().id;
	strlcpy(p.szLogin, ch->GetDesc()->GetAccountTable().login, sizeof(p.szLogin));
	strlcpy(p.szPassword, arg1, sizeof(p.szPassword));

	db_clientdesc->DBPacket(HEADER_GD_MALL_LOAD, ch->GetDesc()->GetHandle(), &p, sizeof(p));
}

ACMD(do_mall_close)
{
	if (ch->GetMall())
	{
		ch->SetMallLoadTime(thecore_pulse());
		ch->CloseMall();
		ch->Save();
	}
}

ACMD(do_ungroup)
{
	if (!ch->GetParty())
		return;

	if (!CPartyManager::instance().IsEnablePCParty())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<파티> 서버 문제로 파티 관련 처리를 할 수 없습니다."));
		return;
	}

	if (ch->GetDungeon())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<파티> 던전 안에서는 파티에서 나갈 수 없습니다."));
		return;
	}

	LPPARTY pParty = ch->GetParty();

	if (pParty->GetMemberCount() == 2)
	{
		// party disband
		CPartyManager::instance().DeleteParty(pParty);
	}
	else
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<파티> 파티에서 나가셨습니다."));
		//pParty->SendPartyRemoveOneToAll(ch);
		pParty->Quit(ch->GetPlayerID());
		//pParty->SendPartyRemoveAllToOne(ch);
	}
}

ACMD(do_close_shop)
{
	if (ch->GetMyShop())
	{
		ch->CloseMyShop();
		return;
	}
}

ACMD(do_set_walk_mode)
{
	ch->SetNowWalking(true);
	ch->SetWalking(true);
}

ACMD(do_set_run_mode)
{
	ch->SetNowWalking(false);
	ch->SetWalking(false);
}

ACMD(do_channel_switch)
{

	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));
	if (!*arg1)
		return;
		
	int new_ch;
	str_to_number(new_ch, arg1);
	if( new_ch <1 || new_ch >4)
		return;
	if (!ch->IsPC())
		return;
	ch->ChannelSwitch(new_ch);
}

ACMD(do_war)
{
	//내 길드 정보를 얻어오고
	CGuild * g = ch->GetGuild();

	if (!g)
		return;

	//전쟁중인지 체크한번!
	if (g->UnderAnyWar())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<길드> 이미 다른 전쟁에 참전 중 입니다."));
		return;
	}

	//파라메터를 두배로 나누고
	char arg1[256], arg2[256];
	DWORD type = GUILD_WAR_TYPE_FIELD; //fixme102 base int modded uint
	two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	if (!*arg1)
		return;

	if (*arg2)
	{
		str_to_number(type, arg2);

		if (type >= GUILD_WAR_TYPE_MAX_NUM)
			type = GUILD_WAR_TYPE_FIELD;
	}

	//길드의 마스터 아이디를 얻어온뒤
	DWORD gm_pid = g->GetMasterPID();

	//마스터인지 체크(길전은 길드장만이 가능)
	if (gm_pid != ch->GetPlayerID())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<길드> 길드전에 대한 권한이 없습니다."));
		return;
	}

	//상대 길드를 얻어오고
	CGuild * opp_g = CGuildManager::instance().FindGuildByName(arg1);

	if (!opp_g)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<길드> 그런 길드가 없습니다."));
		return;
	}

	//상대길드와의 상태 체크
	switch (g->GetGuildWarState(opp_g->GetID()))
	{
		case GUILD_WAR_NONE:
			{
				if (opp_g->UnderAnyWar())
				{
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<길드> 상대방 길드가 이미 전쟁 중 입니다."));
					return;
				}

				int iWarPrice = KOR_aGuildWarInfo[type].iWarPrice;

				if (g->GetGuildMoney() < iWarPrice)
				{
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<길드> 전비가 부족하여 길드전을 할 수 없습니다."));
					return;
				}

				if (opp_g->GetGuildMoney() < iWarPrice)
				{
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<길드> 상대방 길드의 전비가 부족하여 길드전을 할 수 없습니다."));
					return;
				}
			}
			break;

		case GUILD_WAR_SEND_DECLARE:
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "이미 선전포고 중인 길드입니다."));
				return;
			}
			break;

		case GUILD_WAR_RECV_DECLARE:
			{
				if (opp_g->UnderAnyWar())
				{
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<길드> 상대방 길드가 이미 전쟁 중 입니다."));
					g->RequestRefuseWar(opp_g->GetID());
					return;
				}
			}
			break;

		case GUILD_WAR_RESERVE:
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<길드> 이미 전쟁이 예약된 길드 입니다."));
				return;
			}
			break;

		case GUILD_WAR_END:
			return;

		default:
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<길드> 이미 전쟁 중인 길드입니다."));
			g->RequestRefuseWar(opp_g->GetID());
			return;
	}

	if (!g->CanStartWar(type))
	{
		// 길드전을 할 수 있는 조건을 만족하지않는다.
		if (g->GetLadderPoint() == 0)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<길드> 레더 점수가 모자라서 길드전을 할 수 없습니다."));
			sys_log(0, "GuildWar.StartError.NEED_LADDER_POINT");
		}
		else if (g->GetMemberCount() < GUILD_WAR_MIN_MEMBER_COUNT)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<길드> 길드전을 하기 위해선 최소한 %d명이 있어야 합니다."), GUILD_WAR_MIN_MEMBER_COUNT);
			sys_log(0, "GuildWar.StartError.NEED_MINIMUM_MEMBER[%d]", GUILD_WAR_MIN_MEMBER_COUNT);
		}
		else
		{
			sys_log(0, "GuildWar.StartError.UNKNOWN_ERROR");
		}
		return;
	}

	// 필드전 체크만 하고 세세한 체크는 상대방이 승낙할때 한다.
	if (!opp_g->CanStartWar(GUILD_WAR_TYPE_FIELD))
	{
		if (opp_g->GetLadderPoint() == 0)
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<길드> 상대방 길드의 레더 점수가 모자라서 길드전을 할 수 없습니다."));
		else if (opp_g->GetMemberCount() < GUILD_WAR_MIN_MEMBER_COUNT)
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<길드> 상대방 길드의 길드원 수가 부족하여 길드전을 할 수 없습니다."));
		return;
	}

	do
	{
		if (g->GetMasterCharacter() != NULL)
			break;

		CCI *pCCI = P2P_MANAGER::instance().FindByPID(g->GetMasterPID());

		if (pCCI != NULL)
			break;

		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<길드> 상대방 길드의 길드장이 접속중이 아닙니다."));
		g->RequestRefuseWar(opp_g->GetID());
		return;

	} while (false);

	do
	{
		if (opp_g->GetMasterCharacter() != NULL)
			break;

		CCI *pCCI = P2P_MANAGER::instance().FindByPID(opp_g->GetMasterPID());

		if (pCCI != NULL)
			break;

		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<길드> 상대방 길드의 길드장이 접속중이 아닙니다."));
		g->RequestRefuseWar(opp_g->GetID());
		return;

	} while (false);

	g->RequestDeclareWar(opp_g->GetID(), type);
}

ACMD(do_nowar)
{
	CGuild* g = ch->GetGuild();
	if (!g)
		return;

	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
		return;

	DWORD gm_pid = g->GetMasterPID();

	if (gm_pid != ch->GetPlayerID())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<길드> 길드전에 대한 권한이 없습니다."));
		return;
	}

	CGuild* opp_g = CGuildManager::instance().FindGuildByName(arg1);

	if (!opp_g)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "<길드> 그런 길드가 없습니다."));
		return;
	}

	g->RequestRefuseWar(opp_g->GetID());
}

ACMD(do_detaillog)
{
	ch->DetailLog();
}

ACMD(do_monsterlog)
{
	ch->ToggleMonsterLog();
}

ACMD(do_pkmode)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
		return;

	BYTE mode = 0;
	str_to_number(mode, arg1);

	if (mode == PK_MODE_PROTECT)
		return;

	if (ch->GetLevel() < PK_PROTECT_LEVEL && mode != 0)
		return;

	ch->SetPKMode(mode);
}

ACMD(do_messenger_auth)
{
	if (ch->GetArena())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "대련장에서 사용하실 수 없습니다."));
		return;
	}

	char arg1[256], arg2[256];
	two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	if (!*arg1 || !*arg2)
		return;

	char answer = LOWER(*arg1);
	// @fixme130 AuthToAdd void -> bool
	bool bIsDenied = answer != 'y';
	bool bIsAdded = MessengerManager::instance().AuthToAdd(ch->GetName(), arg2, bIsDenied); // DENY
	if (bIsAdded && bIsDenied)
	{
		LPCHARACTER tch = CHARACTER_MANAGER::instance().FindPC(arg2);

		if (tch)
			tch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(tch->GetLanguage(), "%s 님으로 부터 친구 등록을 거부 당했습니다."), ch->GetName());
	}

}

ACMD(do_setblockmode)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (*arg1)
	{
		BYTE flag = 0;
		str_to_number(flag, arg1);
		ch->SetBlockMode(flag);
	}
}

ACMD(do_unmount)
{
	if (true == ch->UnEquipSpecialRideUniqueItem())
	{
		ch->RemoveAffect(AFFECT_MOUNT);
		ch->RemoveAffect(AFFECT_MOUNT_BONUS);

		if (ch->IsHorseRiding())
		{
			ch->StopRiding();
		}
	}
	else
	{
		ch->ChatPacket( CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "인벤토리가 꽉 차서 내릴 수 없습니다."));
	}

}

ACMD(do_observer_exit)
{
	if (ch->IsObserverMode())
	{
		if (ch->GetWarMap())
			ch->SetWarMap(NULL);

		if (ch->GetArena() != NULL || ch->GetArenaObserverMode() == true)
		{
			ch->SetArenaObserverMode(false);

			if (ch->GetArena() != NULL)
				ch->GetArena()->RemoveObserver(ch->GetPlayerID());

			ch->SetArena(NULL);
			ch->WarpSet(ARENA_RETURN_POINT_X(ch->GetEmpire()), ARENA_RETURN_POINT_Y(ch->GetEmpire()));
		}
		else
		{
			ch->ExitToSavedLocation();
		}
		ch->SetObserverMode(false);
	}
}

ACMD(do_view_equip)
{
	if (ch->GetGMLevel() <= GM_PLAYER)
		return;

	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (*arg1)
	{
		DWORD vid = 0;
		str_to_number(vid, arg1);
		LPCHARACTER tch = CHARACTER_MANAGER::instance().Find(vid);

		if (!tch)
			return;

		if (!tch->IsPC())
			return;
		/*
		   int iSPCost = ch->GetMaxSP() / 3;

		   if (ch->GetSP() < iSPCost)
		   {
		   ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "정신력이 부족하여 다른 사람의 장비를 볼 수 없습니다."));
		   return;
		   }
		   ch->PointChange(POINT_SP, -iSPCost);
		 */
		tch->SendEquipment(ch);
	}
}

ACMD(do_party_request)
{
	if (ch->GetArena())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "대련장에서 사용하실 수 없습니다."));
		return;
	}

	if (ch->GetParty())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "이미 파티에 속해 있으므로 가입신청을 할 수 없습니다."));
		return;
	}

	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
		return;

	DWORD vid = 0;
	str_to_number(vid, arg1);
	LPCHARACTER tch = CHARACTER_MANAGER::instance().Find(vid);

	if (tch)
		if (!ch->RequestToParty(tch))
			ch->ChatPacket(CHAT_TYPE_COMMAND, "PartyRequestDenied");
}

ACMD(do_party_request_accept)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
		return;

	DWORD vid = 0;
	str_to_number(vid, arg1);
	LPCHARACTER tch = CHARACTER_MANAGER::instance().Find(vid);

	if (tch)
		ch->AcceptToParty(tch);
}

ACMD(do_party_request_deny)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
		return;

	DWORD vid = 0;
	str_to_number(vid, arg1);
	LPCHARACTER tch = CHARACTER_MANAGER::instance().Find(vid);

	if (tch)
		ch->DenyToParty(tch);
}

ACMD(do_monarch_warpto)
{
	if (!CMonarch::instance().IsMonarch(ch->GetPlayerID(), ch->GetEmpire()))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "군주만이 사용 가능한 기능입니다"));
		return;
	}

	//군주 쿨타임 검사
	if (!ch->IsMCOK(CHARACTER::MI_WARP))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "%d 초간 쿨타임이 적용중입니다."), ch->GetMCLTime(CHARACTER::MI_WARP));
		return;
	}

	//군주 몹 소환 비용
	const int WarpPrice = 10000;

	//군주 국고 검사
	if (!CMonarch::instance().IsMoneyOk(WarpPrice, ch->GetEmpire()))
	{
		int NationMoney = CMonarch::instance().GetMoney(ch->GetEmpire());
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "국고에 돈이 부족합니다. 현재 : %u 필요금액 : %u"), NationMoney, WarpPrice);
		return;
	}

	int x = 0, y = 0;
	char arg1[256];

	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "사용법: warpto <character name>"));
		return;
	}

	LPCHARACTER tch = CHARACTER_MANAGER::instance().FindPC(arg1);

	if (!tch)
	{
		CCI * pkCCI = P2P_MANAGER::instance().Find(arg1);

		if (pkCCI)
		{
			if (pkCCI->bEmpire != ch->GetEmpire())
			{
				ch->ChatPacket (CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "타제국 유저에게는 이동할수 없습니다"));
				return;
			}

			if (pkCCI->bChannel != g_bChannel)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "해당 유저는 %d 채널에 있습니다. (현재 채널 %d)"), pkCCI->bChannel, g_bChannel);
				return;
			}
			if (!IsMonarchWarpZone(pkCCI->lMapIndex))
			{
				ch->ChatPacket (CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "해당 지역으로 이동할 수 없습니다."));
				return;
			}

			PIXEL_POSITION pos;

			if (!SECTREE_MANAGER::instance().GetCenterPositionOfMap(pkCCI->lMapIndex, pos))
				ch->ChatPacket(CHAT_TYPE_INFO, "Cannot find map (index %d)", pkCCI->lMapIndex);
			else
			{
				//ch->ChatPacket(CHAT_TYPE_INFO, "You warp to (%d, %d)", pos.x, pos.y);
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "%s 에게로 이동합니다"), arg1);
				ch->WarpSet(pos.x, pos.y);

				//군주 돈 삭감
				CMonarch::instance().SendtoDBDecMoney(WarpPrice, ch->GetEmpire(), ch);

				//쿨타임 초기화
				ch->SetMC(CHARACTER::MI_WARP);
			}
		}
		else if (NULL == CHARACTER_MANAGER::instance().FindPC(arg1))
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "There is no one by that name");
		}

		return;
	}
	else
	{
		if (tch->GetEmpire() != ch->GetEmpire())
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "타제국 유저에게는 이동할수 없습니다"));
			return;
		}
		if (!IsMonarchWarpZone(tch->GetMapIndex()))
		{
			ch->ChatPacket (CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "해당 지역으로 이동할 수 없습니다."));
			return;
		}
		x = tch->GetX();
		y = tch->GetY();
	}

	ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "%s 에게로 이동합니다"), arg1);
	ch->WarpSet(x, y);
	ch->Stop();

	//군주 돈 삭감
	CMonarch::instance().SendtoDBDecMoney(WarpPrice, ch->GetEmpire(), ch);

	//쿨타임 초기화
	ch->SetMC(CHARACTER::MI_WARP);
}

ACMD(do_monarch_transfer)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "사용법: transfer <name>"));
		return;
	}

	if (!CMonarch::instance().IsMonarch(ch->GetPlayerID(), ch->GetEmpire()))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "군주만이 사용 가능한 기능입니다"));
		return;
	}

	//군주 쿨타임 검사
	if (!ch->IsMCOK(CHARACTER::MI_TRANSFER))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "%d 초간 쿨타임이 적용중입니다."), ch->GetMCLTime(CHARACTER::MI_TRANSFER));
		return;
	}

	//군주 워프 비용
	const int WarpPrice = 10000;

	//군주 국고 검사
	if (!CMonarch::instance().IsMoneyOk(WarpPrice, ch->GetEmpire()))
	{
		int NationMoney = CMonarch::instance().GetMoney(ch->GetEmpire());
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "국고에 돈이 부족합니다. 현재 : %u 필요금액 : %u"), NationMoney, WarpPrice);
		return;
	}


	LPCHARACTER tch = CHARACTER_MANAGER::instance().FindPC(arg1);

	if (!tch)
	{
		CCI * pkCCI = P2P_MANAGER::instance().Find(arg1);

		if (pkCCI)
		{
			if (pkCCI->bEmpire != ch->GetEmpire())
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "다른 제국 유저는 소환할 수 없습니다."));
				return;
			}
			if (pkCCI->bChannel != g_bChannel)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "%s 님은 %d 채널에 접속 중 입니다. (현재 채널: %d)"), arg1, pkCCI->bChannel, g_bChannel);
				return;
			}
			if (!IsMonarchWarpZone(pkCCI->lMapIndex))
			{
				ch->ChatPacket (CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "해당 지역으로 이동할 수 없습니다."));
				return;
			}
			if (!IsMonarchWarpZone(ch->GetMapIndex()))
			{
				ch->ChatPacket (CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "해당 지역으로 소환할 수 없습니다."));
				return;
			}

			TPacketGGTransfer pgg;

			pgg.bHeader = HEADER_GG_TRANSFER;
			strlcpy(pgg.szName, arg1, sizeof(pgg.szName));
			pgg.lX = ch->GetX();
			pgg.lY = ch->GetY();

			P2P_MANAGER::instance().Send(&pgg, sizeof(TPacketGGTransfer));
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "%s 님을 소환하였습니다."), arg1);

			//군주 돈 삭감
			CMonarch::instance().SendtoDBDecMoney(WarpPrice, ch->GetEmpire(), ch);
			//쿨타임 초기화
			ch->SetMC(CHARACTER::MI_TRANSFER);
		}
		else
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "입력하신 이름을 가진 사용자가 없습니다."));
		}

		return;
	}


	if (ch == tch)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "자신을 소환할 수 없습니다."));
		return;
	}

	if (tch->GetEmpire() != ch->GetEmpire())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "다른 제국 유저는 소환할 수 없습니다."));
		return;
	}
	if (!IsMonarchWarpZone(tch->GetMapIndex()))
	{
		ch->ChatPacket (CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "해당 지역으로 이동할 수 없습니다."));
		return;
	}
	if (!IsMonarchWarpZone(ch->GetMapIndex()))
	{
		ch->ChatPacket (CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "해당 지역으로 소환할 수 없습니다."));
		return;
	}

	//tch->Show(ch->GetMapIndex(), ch->GetX(), ch->GetY(), ch->GetZ());
	tch->WarpSet(ch->GetX(), ch->GetY(), ch->GetMapIndex());

	//군주 돈 삭감
	CMonarch::instance().SendtoDBDecMoney(WarpPrice, ch->GetEmpire(), ch);
	//쿨타임 초기화
	ch->SetMC(CHARACTER::MI_TRANSFER);
}

ACMD(do_monarch_info)
{
	if (CMonarch::instance().IsMonarch(ch->GetPlayerID(), ch->GetEmpire()))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "나의 군주 정보"));
		TMonarchInfo * p = CMonarch::instance().GetMonarch();
		for (int n = 1; n < 4; ++n)
		{
			if (n == ch->GetEmpire())
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "[%s군주] : %s  보유금액 %lld "), EMPIRE_NAME(n), p->name[n], p->money[n]);
			else
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "[%s군주] : %s  "), EMPIRE_NAME(n), p->name[n]);

		}
	}
	else
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "군주 정보"));
		TMonarchInfo * p = CMonarch::instance().GetMonarch();
		for (int n = 1; n < 4; ++n)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "[%s군주] : %s  "), EMPIRE_NAME(n), p->name[n]);

		}
	}

}

ACMD(do_elect)
{
	db_clientdesc->DBPacketHeader(HEADER_GD_COME_TO_VOTE, ch->GetDesc()->GetHandle(), 0);
}

// LUA_ADD_GOTO_INFO
struct GotoInfo
{
	std::string 	st_name;

	BYTE 	empire;
	int 	mapIndex;
	DWORD 	x, y;

	GotoInfo()
	{
		st_name 	= "";
		empire 		= 0;
		mapIndex 	= 0;

		x = 0;
		y = 0;
	}

	GotoInfo(const GotoInfo& c_src)
	{
		__copy__(c_src);
	}

	void operator = (const GotoInfo& c_src)
	{
		__copy__(c_src);
	}

	void __copy__(const GotoInfo& c_src)
	{
		st_name 	= c_src.st_name;
		empire 		= c_src.empire;
		mapIndex 	= c_src.mapIndex;

		x = c_src.x;
		y = c_src.y;
	}
};

ACMD(do_monarch_tax)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Usage: monarch_tax <1-50>");
		return;
	}

	// 군주 검사
	if (!ch->IsMonarch())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "군주만이 사용할수 있는 기능입니다"));
		return;
	}

	// 세금설정
	int tax = 0;
	str_to_number(tax,  arg1);

	if (tax < 1 || tax > 50)
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "1-50 사이의 수치를 선택해주세요"));

	quest::CQuestManager::instance().SetEventFlag("trade_tax", tax);

	// 군주에게 메세지 하나
	ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "세금이 %d %로 설정되었습니다"));

	// 공지
	char szMsg[1024];

	snprintf(szMsg, sizeof(szMsg), "군주의 명으로 세금이 %d %% 로 변경되었습니다", tax);
	BroadcastNotice(szMsg);

	snprintf(szMsg, sizeof(szMsg), "앞으로는 거래 금액의 %d %% 가 국고로 들어가게됩니다.", tax);
	BroadcastNotice(szMsg);

	// 쿨타임 초기화
	ch->SetMC(CHARACTER::MI_TAX);
}

static const DWORD cs_dwMonarchMobVnums[] =
{
	191, //	산견신
	192, //	저신
	193, //	웅신
	194, //	호신
	391, //	미정
	392, //	은정
	393, //	세랑
	394, //	진희
	491, //	맹환
	492, //	보우
	493, //	구패
	494, //	추흔
	591, //	비류단대장
	691, //	웅귀 족장
	791, //	밀교교주
	1304, // 누렁범귀
	1901, // 구미호
	2091, // 여왕거미
	2191, // 거대사막거북
	2206, // 화염왕i
	0,
};

ACMD(do_monarch_mob)
{
	char arg1[256];
	LPCHARACTER	tch;

	one_argument(argument, arg1, sizeof(arg1));

	if (!ch->IsMonarch())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "군주만이 사용할수 있는 기능입니다"));
		return;
	}

	if (!*arg1)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Usage: mmob <mob name>");
		return;
	}

#ifdef ENABLE_MONARCH_MOB_CMD_MAP_CHECK // @warme006
	BYTE pcEmpire = ch->GetEmpire();
	BYTE mapEmpire = SECTREE_MANAGER::instance().GetEmpireFromMapIndex(ch->GetMapIndex());
	if (mapEmpire != pcEmpire && mapEmpire != 0)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "자국 영토에서만 사용할 수 있는 기능입니다"));
		return;
	}
#endif

	// 군주 몹 소환 비용
	const int SummonPrice = 5000000;

	// 군주 쿨타임 검사
	if (!ch->IsMCOK(CHARACTER::MI_SUMMON))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "%d 초간 쿨타임이 적용중입니다."), ch->GetMCLTime(CHARACTER::MI_SUMMON));
		return;
	}

	// 군주 국고 검사
	if (!CMonarch::instance().IsMoneyOk(SummonPrice, ch->GetEmpire()))
	{
		int NationMoney = CMonarch::instance().GetMoney(ch->GetEmpire());
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "국고에 돈이 부족합니다. 현재 : %u 필요금액 : %u"), NationMoney, SummonPrice);
		return;
	}

	const CMob * pkMob;
	DWORD vnum = 0;

	if (isdigit(*arg1))
	{
		str_to_number(vnum, arg1);

		if ((pkMob = CMobManager::instance().Get(vnum)) == NULL)
			vnum = 0;
	}
	else
	{
		pkMob = CMobManager::Instance().Get(arg1, true);

		if (pkMob)
			vnum = pkMob->m_table.dwVnum;
	}

	DWORD count;

	// 소환 가능 몹 검사
	for (count = 0; cs_dwMonarchMobVnums[count] != 0; ++count)
		if (cs_dwMonarchMobVnums[count] == vnum)
			break;

	if (0 == cs_dwMonarchMobVnums[count])
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "소환할수 없는 몬스터 입니다. 소환가능한 몬스터는 홈페이지를 참조하세요"));
		return;
	}

	tch = CHARACTER_MANAGER::instance().SpawnMobRange(vnum,
			ch->GetMapIndex(),
			ch->GetX() - number(200, 750),
			ch->GetY() - number(200, 750),
			ch->GetX() + number(200, 750),
			ch->GetY() + number(200, 750),
			true,
			pkMob->m_table.bType == CHAR_TYPE_STONE,
			true);

	if (tch)
	{
		// 군주 돈 삭감
		CMonarch::instance().SendtoDBDecMoney(SummonPrice, ch->GetEmpire(), ch);

		// 쿨타임 초기화
		ch->SetMC(CHARACTER::MI_SUMMON);
	}
}

static const char* FN_point_string(LPCHARACTER ch, int apply_number)
{
	switch (apply_number)
	{
		case POINT_MAX_HP:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "최대 생명력 +%d");
		case POINT_MAX_SP:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "최대 정신력 +%d");
		case POINT_HT:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "체력 +%d");
		case POINT_IQ:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "지능 +%d");
		case POINT_ST:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "근력 +%d");
		case POINT_DX:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "민첩 +%d");
		case POINT_ATT_SPEED:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "공격속도 +%d");
		case POINT_MOV_SPEED:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "이동속도 %d");
		case POINT_CASTING_SPEED:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "쿨타임 -%d");
		case POINT_HP_REGEN:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "생명력 회복 +%d");
		case POINT_SP_REGEN:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "정신력 회복 +%d");
		case POINT_POISON_PCT:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "독공격 %d");
#ifdef ENABLE_WOLFMAN_CHARACTER
		case POINT_BLEEDING_PCT:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "독공격 %d");
#endif
		case POINT_STUN_PCT:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "스턴 +%d");
		case POINT_SLOW_PCT:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "슬로우 +%d");
		case POINT_CRITICAL_PCT:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "%d%% 확률로 치명타 공격");
		case POINT_RESIST_CRITICAL:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "상대의 치명타 확률 %d%% 감소");
		case POINT_PENETRATE_PCT:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "%d%% 확률로 관통 공격");
		case POINT_RESIST_PENETRATE: return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "상대의 관통 공격 확률 %d%% 감소");
		case POINT_ATTBONUS_HUMAN:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "인간류 몬스터 타격치 +%d%%");
		case POINT_ATTBONUS_ANIMAL:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "동물류 몬스터 타격치 +%d%%");
		case POINT_ATTBONUS_ORC:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "웅귀족 타격치 +%d%%");
		case POINT_ATTBONUS_MILGYO:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "밀교류 타격치 +%d%%");
		case POINT_ATTBONUS_UNDEAD:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "시체류 타격치 +%d%%");
		case POINT_ATTBONUS_DEVIL:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "악마류 타격치 +%d%%");
		case POINT_STEAL_HP:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "타격치 %d%% 를 생명력으로 흡수");
		case POINT_STEAL_SP:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "타력치 %d%% 를 정신력으로 흡수");
		case POINT_MANA_BURN_PCT:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "%d%% 확률로 타격시 상대 전신력 소모");
		case POINT_DAMAGE_SP_RECOVER:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "%d%% 확률로 피해시 정신력 회복");
		case POINT_BLOCK:			return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "물리타격시 블럭 확률 %d%%");
		case POINT_DODGE:			return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "활 공격 회피 확률 %d%%");
		case POINT_RESIST_SWORD:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "한손검 방어 %d%%");
		case POINT_RESIST_TWOHAND:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "양손검 방어 %d%%");
		case POINT_RESIST_DAGGER:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "두손검 방어 %d%%");
		case POINT_RESIST_BELL:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "방울 방어 %d%%");
		case POINT_RESIST_FAN:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "부채 방어 %d%%");
		case POINT_RESIST_BOW:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "활공격 저항 %d%%");
#ifdef ENABLE_WOLFMAN_CHARACTER
		case POINT_RESIST_CLAW:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "두손검 방어 %d%%");
#endif
		case POINT_RESIST_FIRE:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "화염 저항 %d%%");
		case POINT_RESIST_ELEC:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "전기 저항 %d%%");
		case POINT_RESIST_MAGIC:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "마법 저항 %d%%");
		case POINT_RESIST_WIND:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "바람 저항 %d%%");
		case POINT_RESIST_ICE:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "냉기 저항 %d%%");
		case POINT_RESIST_EARTH:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "대지 저항 %d%%");
		case POINT_RESIST_DARK:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "어둠 저항 %d%%");
		case POINT_REFLECT_MELEE:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "직접 타격치 반사 확률 : %d%%");
		case POINT_REFLECT_CURSE:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "저주 되돌리기 확률 %d%%");
		case POINT_POISON_REDUCE:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "독 저항 %d%%");
#ifdef ENABLE_WOLFMAN_CHARACTER
		case POINT_BLEEDING_REDUCE:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "독 저항 %d%%");
#endif
		case POINT_KILL_SP_RECOVER:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "%d%% 확률로 적퇴치시 정신력 회복");
		case POINT_EXP_DOUBLE_BONUS:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "%d%% 확률로 적퇴치시 경험치 추가 상승");
		case POINT_GOLD_DOUBLE_BONUS:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "%d%% 확률로 적퇴치시 돈 2배 드롭");
		case POINT_ITEM_DROP_BONUS:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "%d%% 확률로 적퇴치시 아이템 2배 드롭");
		case POINT_POTION_BONUS:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "물약 사용시 %d%% 성능 증가");
		case POINT_KILL_HP_RECOVERY:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "%d%% 확률로 적퇴치시 생명력 회복");
//		case POINT_IMMUNE_STUN:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "기절하지 않음 %d%%");
//		case POINT_IMMUNE_SLOW:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "느려지지 않음 %d%%");
//		case POINT_IMMUNE_FALL:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "넘어지지 않음 %d%%");
//		case POINT_SKILL:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "");
//		case POINT_BOW_DISTANCE:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "");
		case POINT_ATT_GRADE_BONUS:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "공격력 +%d");
		case POINT_DEF_GRADE_BONUS:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "방어력 +%d");
		case POINT_MAGIC_ATT_GRADE:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "마법 공격력 +%d");
		case POINT_MAGIC_DEF_GRADE:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "마법 방어력 +%d");
//		case POINT_CURSE_PCT:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "");
		case POINT_MAX_STAMINA:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "최대 지구력 +%d");
		case POINT_ATTBONUS_WARRIOR:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "무사에게 강함 +%d%%");
		case POINT_ATTBONUS_ASSASSIN:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "자객에게 강함 +%d%%");
		case POINT_ATTBONUS_SURA:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "수라에게 강함 +%d%%");
		case POINT_ATTBONUS_SHAMAN:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "무당에게 강함 +%d%%");
#ifdef ENABLE_WOLFMAN_CHARACTER
		case POINT_ATTBONUS_WOLFMAN:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "무당에게 강함 +%d%%");
#endif
		case POINT_ATTBONUS_MONSTER:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "몬스터에게 강함 +%d%%");
		case POINT_MALL_ATTBONUS:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "공격력 +%d%%");
		case POINT_MALL_DEFBONUS:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "방어력 +%d%%");
		case POINT_MALL_EXPBONUS:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "경험치 %d%%");
		case POINT_MALL_ITEMBONUS:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "아이템 드롭율 %.1f배");
		case POINT_MALL_GOLDBONUS:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "돈 드롭율 %.1f배");
		case POINT_MAX_HP_PCT:			return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "최대 생명력 +%d%%");
		case POINT_MAX_SP_PCT:			return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "최대 정신력 +%d%%");
		case POINT_SKILL_DAMAGE_BONUS:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "스킬 데미지 %d%%");
		case POINT_NORMAL_HIT_DAMAGE_BONUS:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "평타 데미지 %d%%");
		case POINT_SKILL_DEFEND_BONUS:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "스킬 데미지 저항 %d%%");
		case POINT_NORMAL_HIT_DEFEND_BONUS:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "평타 데미지 저항 %d%%");
//		case POINT_PC_BANG_EXP_BONUS:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "");
//		case POINT_PC_BANG_DROP_BONUS:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "");
//		case POINT_EXTRACT_HP_PCT:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "");
		case POINT_RESIST_WARRIOR:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "무사공격에 %d%% 저항");
		case POINT_RESIST_ASSASSIN:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "자객공격에 %d%% 저항");
		case POINT_RESIST_SURA:		return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "수라공격에 %d%% 저항");
		case POINT_RESIST_SHAMAN:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "무당공격에 %d%% 저항");
#ifdef ENABLE_WOLFMAN_CHARACTER
		case POINT_RESIST_WOLFMAN:	return LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "무당공격에 %d%% 저항");
#endif
		default:					return NULL;
	}
}

static bool FN_hair_affect_string(LPCHARACTER ch, char *buf, size_t bufsiz)
{
	if (NULL == ch || NULL == buf)
		return false;

	CAffect* aff = NULL;
	time_t expire = 0;
	struct tm ltm;
	int	year, mon, day;
	int	offset = 0;

	aff = ch->FindAffect(AFFECT_HAIR);

	if (NULL == aff)
		return false;

	expire = ch->GetQuestFlag("hair.limit_time");

	if (expire < get_global_time())
		return false;

	// set apply string
	offset = snprintf(buf, bufsiz, FN_point_string(ch, aff->bApplyOn), aff->lApplyValue);

	if (offset < 0 || offset >= (int) bufsiz)
		offset = bufsiz - 1;

	localtime_r(&expire, &ltm);

	year	= ltm.tm_year + 1900;
	mon		= ltm.tm_mon + 1;
	day		= ltm.tm_mday;

	snprintf(buf + offset, bufsiz - offset, LC_TEXT(" (만료일 : %d년 %d월 %d일)"), year, mon, day);

	return true;
}

ACMD(do_costume)
{
	char buf[512];
	const size_t bufferSize = sizeof(buf);

	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	CItem* pBody = ch->GetWear(WEAR_COSTUME_BODY);
	CItem* pHair = ch->GetWear(WEAR_COSTUME_HAIR);

	ch->ChatPacket(CHAT_TYPE_INFO, "COSTUME status:");

	if (pHair)
	{
		const char* itemName = pHair->GetName();
		ch->ChatPacket(CHAT_TYPE_INFO, "  HAIR : %s", itemName);

		for (int i = 0; i < pHair->GetAttributeCount(); ++i)
		{
			const TPlayerItemAttribute& attr = pHair->GetAttribute(i);
			if (0 < attr.bType)
			{
				snprintf(buf, bufferSize, FN_point_string(ch, attr.bType), attr.sValue);
				ch->ChatPacket(CHAT_TYPE_INFO, "     %s", buf);
			}
		}

		if (pHair->IsEquipped() && arg1[0] == 'h')
			ch->UnequipItem(pHair);
	}

	if (pBody)
	{
		const char* itemName = pBody->GetName();
		ch->ChatPacket(CHAT_TYPE_INFO, "  BODY : %s", itemName);

		if (pBody->IsEquipped() && arg1[0] == 'b')
			ch->UnequipItem(pBody);
	}
}

ACMD(do_hair)
{
	char buf[256];

	if (false == FN_hair_affect_string(ch, buf, sizeof(buf)))
		return;

	ch->ChatPacket(CHAT_TYPE_INFO, buf);
}

ACMD(do_inventory)
{
	int	index = 0;
	int	count		= 1;

	char arg1[256];
	char arg2[256];

	LPITEM	item;

	two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	if (!*arg1)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Usage: inventory <start_index> <count>");
		return;
	}

	if (!*arg2)
	{
		index = 0;
		str_to_number(count, arg1);
	}
	else
	{
		str_to_number(index, arg1); index = MIN(index, INVENTORY_MAX_NUM);
		str_to_number(count, arg2); count = MIN(count, INVENTORY_MAX_NUM);
	}

	for (int i = 0; i < count; ++i)
	{
		if (index >= INVENTORY_MAX_NUM)
			break;

		item = ch->GetInventoryItem(index);

		ch->ChatPacket(CHAT_TYPE_INFO, "inventory [%d] = %s",
						index, item ? item->GetName() : "<NONE>");
		++index;
	}
}

//gift notify quest command
ACMD(do_gift)
{
	ch->ChatPacket(CHAT_TYPE_COMMAND, "gift");
}

ACMD(do_cube)
{
	if (!ch->CanDoCube())
		return;

	dev_log(LOG_DEB0, "CUBE COMMAND <%s>: %s", ch->GetName(), argument);
	int cube_index = 0, inven_index = 0;
	// before SpecialInventory Nov2020 Exterminatus
	// const char *line;

	// char arg1[256], arg2[256], arg3[256];

	// line = two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2));
	// one_argument(line, arg3, sizeof(arg3));
#ifdef ENABLE_SPECIAL_STORAGE
	int inven_type = 0;
	
	char arg1[256], arg2[256], arg3[256], arg4[256];
	two_arguments (two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2)), arg3, sizeof(arg3), arg4, sizeof(arg4));
#else
	const char *line;
	char arg1[256], arg2[256], arg3[256];

	line = two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2));
	one_argument(line, arg3, sizeof(arg3));
#endif
	if (0 == arg1[0])
	{
		// print usage
		ch->ChatPacket(CHAT_TYPE_INFO, "Usage: cube open");
		ch->ChatPacket(CHAT_TYPE_INFO, "       cube close");
		ch->ChatPacket(CHAT_TYPE_INFO, "       cube add <inveltory_index>");
		ch->ChatPacket(CHAT_TYPE_INFO, "       cube delete <cube_index>");
		ch->ChatPacket(CHAT_TYPE_INFO, "       cube list");
		ch->ChatPacket(CHAT_TYPE_INFO, "       cube cancel");
		ch->ChatPacket(CHAT_TYPE_INFO, "       cube make [all]");
		return;
	}

	const std::string& strArg1 = std::string(arg1);

	// r_info (request information)
	// /cube r_info     ==> (Client -> Server) 현재 NPC가 만들 수 있는 레시피 요청
	//					    (Server -> Client) /cube r_list npcVNUM resultCOUNT 123,1/125,1/128,1/130,5
	//
	// /cube r_info 3   ==> (Client -> Server) 현재 NPC가 만들수 있는 레시피 중 3번째 아이템을 만드는 데 필요한 정보를 요청
	// /cube r_info 3 5 ==> (Client -> Server) 현재 NPC가 만들수 있는 레시피 중 3번째 아이템부터 이후 5개의 아이템을 만드는 데 필요한 재료 정보를 요청
	//					   (Server -> Client) /cube m_info startIndex count 125,1|126,2|127,2|123,5&555,5&555,4/120000@125,1|126,2|127,2|123,5&555,5&555,4/120000
	//
	if (strArg1 == "r_info")
	{
		if (0 == arg2[0])
			Cube_request_result_list(ch);
		else
		{
			if (isdigit(*arg2))
			{
				int listIndex = 0, requestCount = 1;
				str_to_number(listIndex, arg2);

				if (0 != arg3[0] && isdigit(*arg3))
					str_to_number(requestCount, arg3);

				Cube_request_material_info(ch, listIndex, requestCount);
			}
		}

		return;
	}

	switch (LOWER(arg1[0]))
	{
		case 'o':	// open
			Cube_open(ch);
			break;

		case 'c':	// close
			Cube_close(ch);
			break;

		case 'l':	// list
			Cube_show_list(ch);
			break;

		case 'a':	// add cue_index inven_index
			{
				// if (0 == arg2[0] || !isdigit(*arg2) ||
					// 0 == arg3[0] || !isdigit(*arg3))
					// return;
#ifdef ENABLE_SPECIAL_STORAGE
				if (0 == arg2[0] || !isdigit(*arg2) || 0 == arg3[0] || !isdigit(*arg3) || 0 == arg4[0] || !isdigit(*arg4))
#else
				if (0 == arg2[0] || !isdigit(*arg2) || 0 == arg3[0] || !isdigit(*arg3))
#endif
				str_to_number(cube_index, arg2);
				str_to_number(inven_index, arg3);
				// Cube_add_item (ch, cube_index, inven_index);
#ifdef ENABLE_SPECIAL_STORAGE
				str_to_number(inven_type, arg4);
				Cube_add_item (ch, cube_index, inven_index, inven_type);
#else
				Cube_add_item (ch, cube_index, inven_index);
#endif
			}
			break;

		case 'd':	// delete
			{
				if (0 == arg2[0] || !isdigit(*arg2))
					return;

				str_to_number(cube_index, arg2);
				Cube_delete_item (ch, cube_index);
			}
			break;

		case 'm':	// make
			if (0 != arg2[0])
			{
				while (true == Cube_make(ch))
					dev_log (LOG_DEB0, "cube make success");
			}
			else
				Cube_make(ch);
			break;

		default:
			return;
	}
}

ACMD(do_costvisible)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	DWORD type = 0;
	str_to_number(type, arg1);
	if (type == 0)
	{
		if (ch->GetQuestFlag("cost.change") > 0)
		{
			ch->SetQuestFlag("cost.change", 0);
//			ch->ChatPacket(CHAT_TYPE_INFO, "R?tungskost? sichtbar...");
//			ch->ChatPacket(CHAT_TYPE_INFO, "Undress and dress costume...");
			ch->ComputePoints();
		}
		else
		{
			ch->SetQuestFlag("cost.change", 1);
//			ch->ChatPacket(CHAT_TYPE_INFO, "R?tungskost? unsichtbar..");
//			ch->ChatPacket(CHAT_TYPE_INFO, "Undress and dress costume...");
			ch->ComputePoints();
		}
	}
	else
	{
		if (ch->GetQuestFlag("costweap.change") > 0)
		{
			ch->SetQuestFlag("costweap.change", 0);
//			ch->ChatPacket(CHAT_TYPE_INFO, "Waffenkost? sichtbar..");
//			ch->ChatPacket(CHAT_TYPE_INFO, "Undress and dress costume...");
			ch->ComputePoints();
		}
		else
		{
			ch->SetQuestFlag("costweap.change", 1);
//			ch->ChatPacket(CHAT_TYPE_INFO, "Waffenkost? unsichtbar..");
//			ch->ChatPacket(CHAT_TYPE_INFO, "Undress and dress costume...");
			ch->ComputePoints();
		}
	}
	ch->UpdatePacket();
}

ACMD(do_in_game_mall)
{
	char country_code[3];

	switch (LC_GetLocalType())
	{
		case LC_GERMANY:	country_code[0] = 'd'; country_code[1] = 'e'; country_code[2] = '\0'; break;
		case LC_FRANCE:		country_code[0] = 'f'; country_code[1] = 'r'; country_code[2] = '\0'; break;
		case LC_ITALY:		country_code[0] = 'i'; country_code[1] = 't'; country_code[2] = '\0'; break;
		case LC_SPAIN:		country_code[0] = 'e'; country_code[1] = 's'; country_code[2] = '\0'; break;
		case LC_UK:			country_code[0] = 'e'; country_code[1] = 'n'; country_code[2] = '\0'; break;
		case LC_TURKEY:		country_code[0] = 't'; country_code[1] = 'r'; country_code[2] = '\0'; break;
		case LC_POLAND:		country_code[0] = 'p'; country_code[1] = 'l'; country_code[2] = '\0'; break;
		case LC_PORTUGAL:	country_code[0] = 'p'; country_code[1] = 't'; country_code[2] = '\0'; break;
		case LC_GREEK:		country_code[0] = 'g'; country_code[1] = 'r'; country_code[2] = '\0'; break;
		case LC_RUSSIA:		country_code[0] = 'r'; country_code[1] = 'u'; country_code[2] = '\0'; break;
		case LC_DENMARK:	country_code[0] = 'd'; country_code[1] = 'k'; country_code[2] = '\0'; break;
		case LC_BULGARIA:	country_code[0] = 'b'; country_code[1] = 'g'; country_code[2] = '\0'; break;
		case LC_CROATIA:	country_code[0] = 'h'; country_code[1] = 'r'; country_code[2] = '\0'; break;
		case LC_MEXICO:		country_code[0] = 'm'; country_code[1] = 'x'; country_code[2] = '\0'; break;
		case LC_ARABIA:		country_code[0] = 'a'; country_code[1] = 'e'; country_code[2] = '\0'; break;
		case LC_CZECH:		country_code[0] = 'c'; country_code[1] = 'z'; country_code[2] = '\0'; break;
		case LC_ROMANIA:	country_code[0] = 'r'; country_code[1] = 'o'; country_code[2] = '\0'; break;
		case LC_HUNGARY:	country_code[0] = 'h'; country_code[1] = 'u'; country_code[2] = '\0'; break;
		case LC_NETHERLANDS: country_code[0] = 'n'; country_code[1] = 'l'; country_code[2] = '\0'; break;
		case LC_USA:		country_code[0] = 'u'; country_code[1] = 's'; country_code[2] = '\0'; break;
		case LC_CANADA:	country_code[0] = 'c'; country_code[1] = 'a'; country_code[2] = '\0'; break;
		default:
			if (test_server == true)
			{
				country_code[0] = 'd'; country_code[1] = 'e'; country_code[2] = '\0';
			}
			break;
	}

	char buf[512+1];
	char sas[33];
	MD5_CTX ctx;
	const char sas_key[] = "GF9001";

	snprintf(buf, sizeof(buf), "%u%u%s", ch->GetPlayerID(), ch->GetAID(), sas_key);

	MD5Init(&ctx);
	MD5Update(&ctx, (const unsigned char *) buf, strlen(buf));
	
#ifdef __FreeBSD__
	MD5End(&ctx, sas);
#else
	static const char hex[] = "0123456789abcdef";
	unsigned char digest[16];
	MD5Final(digest, &ctx);
	int i;
	for (i = 0; i < 16; ++i) {
		sas[i+i] = hex[digest[i] >> 4];
		sas[i+i+1] = hex[digest[i] & 0x0f];
	}
	sas[i+i] = '\0';
#endif

	snprintf(buf, sizeof(buf), "mall %s/securelogin/%u/ongame/%d/",g_strWebMallURL.c_str(), ch->GetDesc()->GetAccountTable().id, g_server_id);

	ch->ChatPacket(CHAT_TYPE_COMMAND, buf);
}

// 주사위
ACMD(do_dice)
{
	char arg1[256], arg2[256];
	int start = 1, end = 100;

	two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	if (*arg1 && *arg2)
	{
		start = atoi(arg1);
		end = atoi(arg2);
	}
	else if (*arg1 && !*arg2)
	{
		start = 1;
		end = atoi(arg1);
	}

	end = MAX(start, end);
	start = MIN(start, end);

	int n = number(start, end);

	if (ch->GetParty())
		ch->GetParty()->ChatPacketToAllMember(CHAT_TYPE_INFO, LC_TEXT("%s님이 주사위를 굴려 %d가 나왔습니다. (%d-%d)"), ch->GetName(), n, start, end);
	else
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "당신이 주사위를 굴려 %d가 나왔습니다. (%d-%d)"), n, start, end);
}

#ifdef ENABLE_NEWSTUFF
ACMD(do_click_safebox)
{
	ch->SetSafeboxOpenPosition();
	ch->ChatPacket(CHAT_TYPE_COMMAND, "ShowMeSafeboxPassword");
}
ACMD(do_force_logout)
{
	LPDESC pDesc=DESC_MANAGER::instance().FindByCharacterName(ch->GetName());
	if (!pDesc)
		return;
	pDesc->DelayedDisconnect(0);
}
#endif

ACMD(do_click_mall)
{
	ch->ChatPacket(CHAT_TYPE_COMMAND, "ShowMeMallPassword");
}

ACMD(do_ride)
{
    dev_log(LOG_DEB0, "[DO_RIDE] start");
    if (ch->IsDead() || ch->IsStun())
	return;

    // 내리기
    {
	if (ch->IsHorseRiding())
	{
	    dev_log(LOG_DEB0, "[DO_RIDE] stop riding");
	    ch->StopRiding();
	    return;
	}

	if (ch->GetMountVnum())
	{
	    dev_log(LOG_DEB0, "[DO_RIDE] unmount");
	    do_unmount(ch, NULL, 0, 0);
	    return;
	}
    }

    // 타기
    {
	if (ch->GetHorse() != NULL)
	{
	    dev_log(LOG_DEB0, "[DO_RIDE] start riding");
	    ch->StartRiding();
	    return;
	}

	for (BYTE i=0; i<INVENTORY_MAX_NUM; ++i)
	{
	    LPITEM item = ch->GetInventoryItem(i);
	    if (NULL == item)
		continue;

	    // 유니크 탈것 아이템
		if (item->IsRideItem())
		{
			if (NULL==ch->GetWear(WEAR_UNIQUE1) || NULL==ch->GetWear(WEAR_UNIQUE2))
			{
				dev_log(LOG_DEB0, "[DO_RIDE] USE UNIQUE ITEM");
				//ch->EquipItem(item);
				ch->UseItem(TItemPos (INVENTORY, i));
				return;
			}
		}

	    // 일반 탈것 아이템
	    // TODO : 탈것용 SubType 추가
	    switch (item->GetVnum())
	    {
		case 71114:	// 저신이용권
		case 71116:	// 산견신이용권
		case 71118:	// 투지범이용권
		case 71120:	// 사자왕이용권
		    dev_log(LOG_DEB0, "[DO_RIDE] USE QUEST ITEM");
		    ch->UseItem(TItemPos (INVENTORY, i));
		    return;
	    }

		// GF mantis #113524, 52001~52090 번 탈것
		if( (item->GetVnum() > 52000) && (item->GetVnum() < 52091) )	{
			dev_log(LOG_DEB0, "[DO_RIDE] USE QUEST ITEM");
			ch->UseItem(TItemPos (INVENTORY, i));
		    return;
		}
	}
    }


    // 타거나 내릴 수 없을때
    ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT_CONVERT_LANGUAGE(ch->GetLanguage(), "말을 먼저 소환해주세요."));
}

#ifdef __AUCTION__
// temp_auction
ACMD(do_get_item_id_list)
{
	for (int i = 0; i < INVENTORY_MAX_NUM; i++)
	{
		LPITEM item = ch->GetInventoryItem(i);
		if (item != NULL)
			ch->ChatPacket(CHAT_TYPE_INFO, "name : %s id : %d", item->GetProto()->szName, item->GetID());
	}
}

// temp_auction

ACMD(do_enroll_auction)
{
	char arg1[256];
	char arg2[256];
	char arg3[256];
	char arg4[256];
	two_arguments (two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2)), arg3, sizeof(arg3), arg4, sizeof(arg4));

	DWORD item_id = strtoul(arg1, NULL, 10);
	BYTE empire = strtoul(arg2, NULL, 10);
	int bidPrice = strtol(arg3, NULL, 10);
	int immidiatePurchasePrice = strtol(arg4, NULL, 10);

	LPITEM item = ITEM_MANAGER::instance().Find(item_id);
	if (item == NULL)
		return;

	AuctionManager::instance().enroll_auction(ch, item, empire, bidPrice, immidiatePurchasePrice);
}

ACMD(do_enroll_wish)
{
	char arg1[256];
	char arg2[256];
	char arg3[256];
	one_argument (two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2)), arg3, sizeof(arg3));

	DWORD item_num = strtoul(arg1, NULL, 10);
	BYTE empire = strtoul(arg2, NULL, 10);
	int wishPrice = strtol(arg3, NULL, 10);

	AuctionManager::instance().enroll_wish(ch, item_num, empire, wishPrice);
}

ACMD(do_enroll_sale)
{
	char arg1[256];
	char arg2[256];
	char arg3[256];
	one_argument (two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2)), arg3, sizeof(arg3));

	DWORD item_id = strtoul(arg1, NULL, 10);
	DWORD wisher_id = strtoul(arg2, NULL, 10);
	int salePrice = strtol(arg3, NULL, 10);

	LPITEM item = ITEM_MANAGER::instance().Find(item_id);
	if (item == NULL)
		return;

	AuctionManager::instance().enroll_sale(ch, item, wisher_id, salePrice);
}

// temp_auction
// packet으로 통신하게 하고, 이건 삭제해야한다.
ACMD(do_get_auction_list)
{
	char arg1[256];
	char arg2[256];
	char arg3[256];
	two_arguments (one_argument (argument, arg1, sizeof(arg1)), arg2, sizeof(arg2), arg3, sizeof(arg3));

	AuctionManager::instance().get_auction_list (ch, strtoul(arg1, NULL, 10), strtoul(arg2, NULL, 10), strtoul(arg3, NULL, 10));
}
//
//ACMD(do_get_wish_list)
//{
//	char arg1[256];
//	char arg2[256];
//	char arg3[256];
//	two_arguments (one_argument (argument, arg1, sizeof(arg1)), arg2, sizeof(arg2), arg3, sizeof(arg3));
//
//	AuctionManager::instance().get_wish_list (ch, strtoul(arg1, NULL, 10), strtoul(arg2, NULL, 10), strtoul(arg3, NULL, 10));
//}
ACMD (do_get_my_auction_list)
{
	char arg1[256];
	char arg2[256];
	two_arguments (argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	AuctionManager::instance().get_my_auction_list (ch, strtoul(arg1, NULL, 10), strtoul(arg2, NULL, 10));
}

ACMD (do_get_my_purchase_list)
{
	char arg1[256];
	char arg2[256];
	two_arguments (argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	AuctionManager::instance().get_my_purchase_list (ch, strtoul(arg1, NULL, 10), strtoul(arg2, NULL, 10));
}

ACMD (do_auction_bid)
{
	char arg1[256];
	char arg2[256];
	two_arguments (argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	AuctionManager::instance().bid (ch, strtoul(arg1, NULL, 10), strtoul(arg2, NULL, 10));
}

ACMD (do_auction_impur)
{
	char arg1[256];
	one_argument (argument, arg1, sizeof(arg1));

	AuctionManager::instance().immediate_purchase (ch, strtoul(arg1, NULL, 10));
}

ACMD (do_get_auctioned_item)
{
	char arg1[256];
	char arg2[256];
	two_arguments (argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	AuctionManager::instance().get_auctioned_item (ch, strtoul(arg1, NULL, 10), strtoul(arg2, NULL, 10));
}

ACMD (do_buy_sold_item)
{
	char arg1[256];
	char arg2[256];
	one_argument (argument, arg1, sizeof(arg1));

	AuctionManager::instance().get_auctioned_item (ch, strtoul(arg1, NULL, 10), strtoul(arg2, NULL, 10));
}

ACMD (do_cancel_auction)
{
	char arg1[256];
	one_argument (argument, arg1, sizeof(arg1));

	AuctionManager::instance().cancel_auction (ch, strtoul(arg1, NULL, 10));
}

ACMD (do_cancel_wish)
{
	char arg1[256];
	one_argument (argument, arg1, sizeof(arg1));

	AuctionManager::instance().cancel_wish (ch, strtoul(arg1, NULL, 10));
}

ACMD (do_cancel_sale)
{
	char arg1[256];
	one_argument (argument, arg1, sizeof(arg1));

	AuctionManager::instance().cancel_sale (ch, strtoul(arg1, NULL, 10));
}

ACMD (do_rebid)
{
	char arg1[256];
	char arg2[256];
	two_arguments (argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	AuctionManager::instance().rebid (ch, strtoul(arg1, NULL, 10), strtoul(arg2, NULL, 10));
}

ACMD (do_bid_cancel)
{
	char arg1[256];
	char arg2[256];
	two_arguments (argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	AuctionManager::instance().bid_cancel (ch, strtoul(arg1, NULL, 10));
}
#endif
