modded class MissionServer
{
    void MissionServer()
    {
        // Additional initialization (if needed) ...
    }

    override void OnEvent(EventType eventTypeId, Param params)
    {
        super.OnEvent(eventTypeId, params);

        ChatMessageEventParams chatParams = ChatMessageEventParams.Cast(params);
        if (!chatParams)
            return;

        // Process only chat message events
        if (eventTypeId == ChatMessageEventTypeID)
        {
            string chatText = chatParams.param3;
            PlayerBase senderPlayer = PlayerBase.Cast(chatParams.param1);
            if (!senderPlayer)
                return;

            // We're using only the !aduty command to both enable and disable admin tools.
            if (chatText.IndexOf("!aduty") == 0)
            {
                if (!IsPlayerAdmin(senderPlayer))
                {
                    Print("Command denied: You are not an admin.");
                    return;
                }

                // Toggle admin features:
                // If god mode is enabled then admin features are ON.
                if (senderPlayer.COTHasGodMode())
                {
                    // Disable admin features: god mode, unlimited ammo, and AI ignore.
                    senderPlayer.COTSetGodMode(false);
                    senderPlayer.COTSetUnlimitedAmmo(false);
                    senderPlayer.COTSetCannotBeTargetedByAI(false);
                    // Remove the admin gear items from the player's inventory.
                    RemoveGearSetFromAdmin(senderPlayer);
                    Print("Disabled admin features for " + senderPlayer.GetIdentity().GetName());
                }
                else
                {
                    // Enable admin features.
                    senderPlayer.COTSetGodMode(true);
                    senderPlayer.COTSetUnlimitedAmmo(true);
                    senderPlayer.COTSetCannotBeTargetedByAI(true);
                    // Give the gear set to the admin player.
                    GiveGearSetToAdmin(senderPlayer);
                    Print("Enabled admin features for " + senderPlayer.GetIdentity().GetName());
                }
            }
        }
    }

    // Replace this with your actual admin-check logic.
    bool IsPlayerAdmin(Man player)
    {
        return true;
    }

    // This function adds the gear set items to the admin player's inventory.
    void GiveGearSetToAdmin(PlayerBase adminPlayer)
    {
        if (!adminPlayer) return;

        TStringArray gearItems = new TStringArray;
        gearItems.Insert("ovg_tacticalshirt_ADMIN");
        gearItems.Insert("ovg_tacticalpants_ADMIN");
        gearItems.Insert("ovg_balaclava_ADMIN");
        gearItems.Insert("ovg_tacticalgloves_ADMIN");
        gearItems.Insert("ovg_falconbelt_ADMIN");
        gearItems.Insert("ovg_heavyvest_MK3_ADMIN");
        gearItems.Insert("ovg_assault_Backpack_ADMIN");
        gearItems.Insert("ovg_tacticalhelmet_ADMIN");
        gearItems.Insert("ovg_boots_ADMIN");
        gearItems.Insert("OVG_Staff_Large_AdminTag_blue");

        for (int i = 0; i < gearItems.Count(); i++)
        {
            string itemClassName = gearItems[i];
            EntityAI gearItem = adminPlayer.GetInventory().CreateInInventory(itemClassName);
            if (gearItem)
            {
                Print("Gave gear item: " + itemClassName + " to admin: " + adminPlayer.GetIdentity().GetName());
            }
            else
            {
                Print("Failed to give gear item: " + itemClassName + " to admin: " + adminPlayer.GetIdentity().GetName());
            }
        }
    }

    // This function will remove the gear set items from the admin player's inventory.
    void RemoveGearSetFromAdmin(PlayerBase adminPlayer)
    {
        if (!adminPlayer) return;
    
        TStringArray gearItems = new TStringArray;
        gearItems.Insert("ovg_tacticalshirt_ADMIN");
        gearItems.Insert("ovg_tacticalpants_ADMIN");
        gearItems.Insert("ovg_balaclava_ADMIN");
        gearItems.Insert("ovg_tacticalgloves_ADMIN");
        gearItems.Insert("ovg_falconbelt_ADMIN");
        gearItems.Insert("ovg_heavyvest_MK3_ADMIN");
        gearItems.Insert("ovg_assault_Backpack_ADMIN");
        gearItems.Insert("ovg_tacticalhelmet_ADMIN");
        gearItems.Insert("ovg_boots_ADMIN");
        gearItems.Insert("OVG_Staff_Large_AdminTag_blue");
    
        array<EntityAI> itemsToDelete = new array<EntityAI>();
    
        // Get all items the player has, including equipped and in containers
        InventoryTraversalType type = InventoryTraversalType.PREORDER;
        InventoryLocation loc = new InventoryLocation();
        array<EntityAI> allItems = new array<EntityAI>();
    
        adminPlayer.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, allItems);
    
        for (int i = 0; i < allItems.Count(); i++)
        {
            EntityAI item = allItems[i];
            if (item && gearItems.Find(item.GetType()) != -1)
            {
                itemsToDelete.Insert(item);
            }
        }
    
        for (int j = 0; j < itemsToDelete.Count(); j++)
        {
            EntityAI toDelete = itemsToDelete[j];
            if (toDelete)
            {
                adminPlayer.GetInventory().DropEntity(InventoryMode.SERVER, toDelete);
                toDelete.Delete();
                Print("Removed gear item: " + toDelete.GetType() + " from admin: " + adminPlayer.GetIdentity().GetName());
            }
        }
    }
};