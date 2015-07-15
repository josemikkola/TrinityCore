#define USED_ONCE_ALREADY                 10000

void Apply(Player* player, Creature* creature, uint32 action, Item* item)
{
    if (!item)
        return;

    if (action >= 10000)
        action = action - 10000;

    std::string message = "";
    message += "Succesfully enchanted: ";
    switch (item->GetTemplate()->Quality)
    {
    case ITEM_QUALITY_POOR:
        message += "|cff9d9d9d[";
        break;
    case ITEM_QUALITY_NORMAL:
        message += "|cffffffff[";
        break;
    case ITEM_QUALITY_UNCOMMON:
        message += "|cff1eff00[";
        break;
    case ITEM_QUALITY_RARE:
        message += "|cff0070dd[";
        break;
    case ITEM_QUALITY_EPIC:
        message += "|cffa335ee[";
        break;
    case ITEM_QUALITY_LEGENDARY:
        message += "|cffff8000[";
        break;
    case ITEM_QUALITY_ARTIFACT:
        message += "|cffe6cc80[";
        break;
    case ITEM_QUALITY_HEIRLOOM:
        message += "|cffe6cc80[";
        break;
    }
    message += item->GetTemplate()->Name1;
    message += "]|r!";

    switch (action)
    {
    case 3717: // Socket Bracer.
    case 3723: // Socket Gloves.
    case 3729: // Socket Belt.
        player->ApplyEnchantment(item, PRISMATIC_ENCHANTMENT_SLOT, false);
        item->SetEnchantment(PRISMATIC_ENCHANTMENT_SLOT, action, 0, 0);
        player->ApplyEnchantment(item, PRISMATIC_ENCHANTMENT_SLOT, true);
        break;
    default:
        item->ClearEnchantment(PERM_ENCHANTMENT_SLOT);
        item->SetEnchantment(PERM_ENCHANTMENT_SLOT, action, 0, 0);
        break;
    }
    creature->Whisper(message.c_str(), LANG_UNIVERSAL, player);

};

bool RequiredEquipment(Player* player, uint32 action)
{
    switch (action)
    {
    case 2: // Main-Hand Weapon.
        if (!player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND))
            return false;
        if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND)->GetTemplate()->SubClass == ITEM_SUBCLASS_WEAPON_FISHING_POLE)
            return false;
        break;
    case 3: // Off-Hand Weapon.
        if (!player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND))
            return false;
        break;
    case 4: // Ranged Weapon.
        if (!player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED))
            return false;
        if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED)->GetTemplate()->SubClass == ITEM_SUBCLASS_WEAPON_WAND)
            return false;
        if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED)->GetTemplate()->SubClass == ITEM_SUBCLASS_WEAPON_THROWN)
            return false;
        break;
    case 5: // Head.
        if (!player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD))
            return false;
        break;
    case 6: // Shoulders.
        if (!player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS))
            return false;
        break;
    case 7: // Cloak.
        if (!player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK))
            return false;
        break;
    case 8: // Chest.
        if (!player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST))
            return false;
        break;
    case 9: // Bracers.
        if (!player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS))
            return false;
        break;
    case 10: // Waist.
        if (!player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST))
            return false;
        break;
    case 11: // Gloves.
        if (!player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS))
            return false;
        break;
    case 12: // Legs.
        if (!player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS))
            return false;
        break;
    case 13: // Feet.
        if (!player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET))
            return false;
        break;
    case 14: // Rings.
        if (!player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1) && !player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2))
            return false;
        break;
    }
    return true;
};


class npc_enchantments : public CreatureScript
{
public:
    npc_enchantments() : CreatureScript("npc_enchantments") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM(5, "|TInterface/PaperDoll/UI-PaperDoll-Slot-MainHand:20|t Main-Hand Weapon.", GOSSIP_SENDER_MAIN, 2);
        player->ADD_GOSSIP_ITEM(5, "|TInterface/PaperDoll/UI-PaperDoll-Slot-SecondaryHand:20|t Off-Hand Weapon.", GOSSIP_SENDER_MAIN, 3);
        player->ADD_GOSSIP_ITEM(5, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Ranged:20|t Ranged Weapon.", GOSSIP_SENDER_MAIN, 4);
        player->ADD_GOSSIP_ITEM(5, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Head:20|t Head.", GOSSIP_SENDER_MAIN, 5);
        player->ADD_GOSSIP_ITEM(5, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Shoulder:20|t Shoulders.", GOSSIP_SENDER_MAIN, 6);
        player->ADD_GOSSIP_ITEM(5, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Shirt:20|t Cloak.", GOSSIP_SENDER_MAIN, 7);
        player->ADD_GOSSIP_ITEM(5, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Chest:20|t Chest.", GOSSIP_SENDER_MAIN, 8);
        player->ADD_GOSSIP_ITEM(5, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Wrists:20|t Bracers.", GOSSIP_SENDER_MAIN, 9);
        player->ADD_GOSSIP_ITEM(5, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Waist:20|t Waist.", GOSSIP_SENDER_MAIN, 10);
        player->ADD_GOSSIP_ITEM(5, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Hands:20|t Gloves.", GOSSIP_SENDER_MAIN, 11);
        player->ADD_GOSSIP_ITEM(5, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Legs:20|t Legs.", GOSSIP_SENDER_MAIN, 12);
        player->ADD_GOSSIP_ITEM(5, "|TInterface/PaperDoll/UI-PaperDoll-Slot-Feet:20|t Feet.", GOSSIP_SENDER_MAIN, 13);
        if (player->HasSkill(SKILL_ENCHANTING) && player->GetSkillValue(SKILL_ENCHANTING) == 450)
            player->ADD_GOSSIP_ITEM(5, "|TInterface/PaperDoll/UI-PaperDoll-Slot-RFinger:20|t Rings.", GOSSIP_SENDER_MAIN, 14);
        player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        Item* item;
        player->PlayerTalkClass->ClearMenus();

        if (sender == GOSSIP_SENDER_MAIN)
        {
            if (!RequiredEquipment(player, action))
            {
                player->PlayerTalkClass->SendCloseGossip();
                return true;
            }

            switch (action)
            {
            case 2: // Main-Hand Weapon.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
                if (item->GetTemplate()->InventoryType == INVTYPE_2HWEAPON)
                {
                    if (item->GetTemplate()->SubClass == ITEM_SUBCLASS_WEAPON_STAFF)
                        player->ADD_GOSSIP_ITEM(5, "[STAFF] +81 Spell Power.", GOSSIP_SENDER_MAIN, 3854);
                    player->ADD_GOSSIP_ITEM(5, "[2H] +35 Agility.", GOSSIP_SENDER_MAIN, 2670);
                    player->ADD_GOSSIP_ITEM(5, "[2H] +110 Attack Power.", GOSSIP_SENDER_MAIN, 3827);
                }
                player->ADD_GOSSIP_ITEM(5, "+25 Agility.", GOSSIP_SENDER_MAIN, 1103);
                player->ADD_GOSSIP_ITEM(5, "+25 Hit +25 Crit.", GOSSIP_SENDER_MAIN, 3788);
                player->ADD_GOSSIP_ITEM(5, "+65 Attack Power.", GOSSIP_SENDER_MAIN, 3833);
                player->ADD_GOSSIP_ITEM(5, "+63 Spell Power.", GOSSIP_SENDER_MAIN, 3834);
                player->ADD_GOSSIP_ITEM(5, "+45 Spirit.", GOSSIP_SENDER_MAIN, 3844);
                player->ADD_GOSSIP_ITEM(5, "Blade Ward.", GOSSIP_SENDER_MAIN, 3869);
                player->ADD_GOSSIP_ITEM(5, "Blood Draining.", GOSSIP_SENDER_MAIN, 3870);
                player->ADD_GOSSIP_ITEM(5, "Berserking.", GOSSIP_SENDER_MAIN, 3789);
                player->ADD_GOSSIP_ITEM(5, "Black Magic.", GOSSIP_SENDER_MAIN, 3790);
                player->ADD_GOSSIP_ITEM(5, "Icebreaker.", GOSSIP_SENDER_MAIN, 3239);
                player->ADD_GOSSIP_ITEM(5, "Icy Chill.", GOSSIP_SENDER_MAIN, 1894);
                player->ADD_GOSSIP_ITEM(5, "Mongoose.", GOSSIP_SENDER_MAIN, 2673);
                player->ADD_GOSSIP_ITEM(5, "Executioner.", GOSSIP_SENDER_MAIN, 3225);
                player->ADD_GOSSIP_ITEM(5, "Titanium Weapon Chain.", GOSSIP_SENDER_MAIN, 3731);
                player->ADD_GOSSIP_ITEM(5, "Back!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
                break;

            case 3: // Off-Hand Weapon.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
                if (item->GetTemplate()->InventoryType == INVTYPE_SHIELD)
                {
                    player->ADD_GOSSIP_ITEM(5, "+20 Defense.", GOSSIP_SENDER_MAIN, 1952);
                    player->ADD_GOSSIP_ITEM(5, "+25 Intellect.", GOSSIP_SENDER_MAIN, 1128);
                    player->ADD_GOSSIP_ITEM(5, "+12 Resilience.", GOSSIP_SENDER_MAIN, 3229);
                    player->ADD_GOSSIP_ITEM(5, "Titanium Plating.", GOSSIP_SENDER_MAIN, 3849);
                    player->ADD_GOSSIP_ITEM(5, "+18 Stamina.", GOSSIP_SENDER_MAIN, 1071);
                    player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
                }
                if (item->GetTemplate()->InventoryType == INVTYPE_2HWEAPON)
                {
                    if (item->GetTemplate()->SubClass == ITEM_SUBCLASS_WEAPON_STAFF)
                        player->ADD_GOSSIP_ITEM(5, "[STAFF] +81 Spell Power.", GOSSIP_SENDER_MAIN, 3854 + USED_ONCE_ALREADY);
                    player->ADD_GOSSIP_ITEM(5, "[2H] +35 Agility.", GOSSIP_SENDER_MAIN, 2670 + USED_ONCE_ALREADY);
                    player->ADD_GOSSIP_ITEM(5, "[2H] +110 Attack Power.", GOSSIP_SENDER_MAIN, 3827 + USED_ONCE_ALREADY);
                }
                player->ADD_GOSSIP_ITEM(5, "+25 Agility.", GOSSIP_SENDER_MAIN, 1103 + USED_ONCE_ALREADY);
                player->ADD_GOSSIP_ITEM(5, "+25 Hit +25 Crit", GOSSIP_SENDER_MAIN, 3788 + USED_ONCE_ALREADY);
                player->ADD_GOSSIP_ITEM(5, "+65 Attack Power.", GOSSIP_SENDER_MAIN, 3833 + USED_ONCE_ALREADY);
                player->ADD_GOSSIP_ITEM(5, "+63 Spell Power.", GOSSIP_SENDER_MAIN, 3834 + USED_ONCE_ALREADY);
                player->ADD_GOSSIP_ITEM(5, "+45 Spirit.", GOSSIP_SENDER_MAIN, 3844 + USED_ONCE_ALREADY);
                player->ADD_GOSSIP_ITEM(5, "Blade Ward.", GOSSIP_SENDER_MAIN, 3869 + USED_ONCE_ALREADY);
                player->ADD_GOSSIP_ITEM(5, "Blood Draining.", GOSSIP_SENDER_MAIN, 3870 + USED_ONCE_ALREADY);
                player->ADD_GOSSIP_ITEM(5, "Berserking.", GOSSIP_SENDER_MAIN, 3789 + USED_ONCE_ALREADY);
                player->ADD_GOSSIP_ITEM(5, "Black Magic.", GOSSIP_SENDER_MAIN, 3790 + USED_ONCE_ALREADY);
                player->ADD_GOSSIP_ITEM(5, "Icebreaker.", GOSSIP_SENDER_MAIN, 3239 + USED_ONCE_ALREADY);
                player->ADD_GOSSIP_ITEM(5, "Icy Chill.", GOSSIP_SENDER_MAIN, 1894 + USED_ONCE_ALREADY);
                player->ADD_GOSSIP_ITEM(5, "Mongoose.", GOSSIP_SENDER_MAIN, 2673 + USED_ONCE_ALREADY);
                player->ADD_GOSSIP_ITEM(5, "Executioner.", GOSSIP_SENDER_MAIN, 3225 + USED_ONCE_ALREADY);
                player->ADD_GOSSIP_ITEM(5, "Titanium Weapon Chain.", GOSSIP_SENDER_MAIN, 3731 + USED_ONCE_ALREADY);
                player->ADD_GOSSIP_ITEM(5, "Back!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());

                break;

            case 4: // Ranged Weapon.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED);
                player->ADD_GOSSIP_ITEM(5, "+40 Ranged Critical Chance.", GOSSIP_SENDER_MAIN, 3608);
                player->ADD_GOSSIP_ITEM(5, "+30 Ranged Hit Chance.", GOSSIP_SENDER_MAIN, 2523);
                player->ADD_GOSSIP_ITEM(5, "+40 Ranged Haste.", GOSSIP_SENDER_MAIN, 3607);
                player->ADD_GOSSIP_ITEM(5, "+15 Damage.", GOSSIP_SENDER_MAIN, 3843);
                player->ADD_GOSSIP_ITEM(5, "Back!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
                break;

            case 5: // Head.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD);
                if (player->HasSkill(SKILL_ENGINEERING) && player->GetSkillValue(SKILL_ENGINEERING) == 450)
                    player->ADD_GOSSIP_ITEM(5, "Mind Amplification Dish.", GOSSIP_SENDER_MAIN, 4222);
                player->ADD_GOSSIP_ITEM(5, "+50 Attack Power, +20 Resilience.", GOSSIP_SENDER_MAIN, 3795);
                player->ADD_GOSSIP_ITEM(5, "+29 Spell Power, +20 Resilience.", GOSSIP_SENDER_MAIN, 3796);
                player->ADD_GOSSIP_ITEM(5, "+30 Spell Power, +10 MP5.", GOSSIP_SENDER_MAIN, 3819);
                player->ADD_GOSSIP_ITEM(5, "+30 Spell Power, +20 Critical Chance.", GOSSIP_SENDER_MAIN, 3820);
                player->ADD_GOSSIP_ITEM(5, "+30 Stamina, +25 Resilience.", GOSSIP_SENDER_MAIN, 3842);
                player->ADD_GOSSIP_ITEM(5, "+37 Stamina, +20 Defense.", GOSSIP_SENDER_MAIN, 3818);
                player->ADD_GOSSIP_ITEM(5, "+50 Attack Power, +20 Critical Chance.", GOSSIP_SENDER_MAIN, 3817);
                player->ADD_GOSSIP_ITEM(5, "Back!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
                break;

            case 6: // Shoulders.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS);
                if (player->HasSkill(SKILL_INSCRIPTION) && player->GetSkillValue(SKILL_INSCRIPTION) == 450)
                {
                    player->ADD_GOSSIP_ITEM(5, "[INSCRIPTION] +120 Attack Power, +15 Critical Chance.", GOSSIP_SENDER_MAIN, 3835);
                    player->ADD_GOSSIP_ITEM(5, "[INSCRIPTION] +70 Spell Power, +8 MP5.", GOSSIP_SENDER_MAIN, 3836);
                    player->ADD_GOSSIP_ITEM(5, "[INSCRIPTION] +60 Dodge, +15 Defense.", GOSSIP_SENDER_MAIN, 3837);
                    player->ADD_GOSSIP_ITEM(5, "[INSCRIPTION] +70 spell Power, +15 Critical Chance.", GOSSIP_SENDER_MAIN, 3838);
                }
                else
                {
                    player->ADD_GOSSIP_ITEM(5, "+40 Attack Power, +15 Critical Chance.", GOSSIP_SENDER_MAIN, 3808);
                    player->ADD_GOSSIP_ITEM(5, "+24 Spell Power, +8 MP5.", GOSSIP_SENDER_MAIN, 3809);
                    player->ADD_GOSSIP_ITEM(5, "+20 Dodge, +15 Defense.", GOSSIP_SENDER_MAIN, 3811);
                    player->ADD_GOSSIP_ITEM(5, "+24 Spell Power, +15 Critical Chance.", GOSSIP_SENDER_MAIN, 3810);
                }
                player->ADD_GOSSIP_ITEM(5, "+40 Attack Power, +15 Resilience.", GOSSIP_SENDER_MAIN, 3793);
                player->ADD_GOSSIP_ITEM(5, "+23 Spell Power, +15 Resilience.", GOSSIP_SENDER_MAIN, 3794);
                player->ADD_GOSSIP_ITEM(5, "+30 Stamina, +15 Resilience.", GOSSIP_SENDER_MAIN, 3852);
                player->ADD_GOSSIP_ITEM(5, "Back!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
                break;

            case 7: // Cloak.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK);
                if (player->HasSkill(SKILL_TAILORING) && player->GetSkillValue(SKILL_TAILORING) == 450)
                {
                    player->ADD_GOSSIP_ITEM(5, "Darkglow Embroidery.", GOSSIP_SENDER_MAIN, 3728);
                    player->ADD_GOSSIP_ITEM(5, "Lightweave Embroidery.", GOSSIP_SENDER_MAIN, 3722);
                    player->ADD_GOSSIP_ITEM(5, "Swordguard Embroidery.", GOSSIP_SENDER_MAIN, 3730);
                }
                if (player->HasSkill(SKILL_ENGINEERING) && player->GetSkillValue(SKILL_ENGINEERING) == 450)
                {
                    player->ADD_GOSSIP_ITEM(5, "Springy Arachnoweave.", GOSSIP_SENDER_MAIN, 3859);
                    player->ADD_GOSSIP_ITEM(5, "Flexweave Underlay.", GOSSIP_SENDER_MAIN, 3605);
                }
                else
                    player->ADD_GOSSIP_ITEM(5, "+22 Agility.", GOSSIP_SENDER_MAIN, 1099);
                player->ADD_GOSSIP_ITEM(5, "+10 Agility, Increased Stealth.", GOSSIP_SENDER_MAIN, 3256);
                player->ADD_GOSSIP_ITEM(5, "+10 Spirit, -2% Threat.", GOSSIP_SENDER_MAIN, 3296);
                player->ADD_GOSSIP_ITEM(5, "+16 Defense.", GOSSIP_SENDER_MAIN, 1951);
                player->ADD_GOSSIP_ITEM(5, "+35 Spell Penetration.", GOSSIP_SENDER_MAIN, 3243);
                player->ADD_GOSSIP_ITEM(5, "+225 Armor.", GOSSIP_SENDER_MAIN, 3294);
                player->ADD_GOSSIP_ITEM(5, "+23 Haste.", GOSSIP_SENDER_MAIN, 3831);
                player->ADD_GOSSIP_ITEM(5, "Back!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
                break;

            case 8: // Chest.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST);
                player->ADD_GOSSIP_ITEM(5, "+10 All Stats.", GOSSIP_SENDER_MAIN, 3832);
                player->ADD_GOSSIP_ITEM(5, "+275 Health.", GOSSIP_SENDER_MAIN, 3297);
                player->ADD_GOSSIP_ITEM(5, "+10 MP5.", GOSSIP_SENDER_MAIN, 2381);
                player->ADD_GOSSIP_ITEM(5, "+20 Resilience.", GOSSIP_SENDER_MAIN, 3245);
                player->ADD_GOSSIP_ITEM(5, "+22 Defense.", GOSSIP_SENDER_MAIN, 1953);
                player->ADD_GOSSIP_ITEM(5, "Back!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
                break;

            case 9: // Bracers.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS);
                if (player->HasSkill(SKILL_LEATHERWORKING) && player->GetSkillValue(SKILL_LEATHERWORKING) == 450)
                {
                    player->ADD_GOSSIP_ITEM(5, "[LEATHERWORKING] +130 Attack Power.", GOSSIP_SENDER_MAIN, 3756);
                    player->ADD_GOSSIP_ITEM(5, "[LEATHERWORKING] +102 Stamina.", GOSSIP_SENDER_MAIN, 3757);
                    player->ADD_GOSSIP_ITEM(5, "[LEATHERWORKING] +76 Spell Power.", GOSSIP_SENDER_MAIN, 3758);
                }
                else
                {
                    player->ADD_GOSSIP_ITEM(5, "+50 Attack Power.", GOSSIP_SENDER_MAIN, 3845);
                    player->ADD_GOSSIP_ITEM(5, "+40 Stamina.", GOSSIP_SENDER_MAIN, 3850);
                    player->ADD_GOSSIP_ITEM(5, "+30 Spell Power.", GOSSIP_SENDER_MAIN, 2332);
                }
                player->ADD_GOSSIP_ITEM(5, "+18 Spirit.", GOSSIP_SENDER_MAIN, 1147);
                player->ADD_GOSSIP_ITEM(5, "+15 Expertise.", GOSSIP_SENDER_MAIN, 3231);
                player->ADD_GOSSIP_ITEM(5, "+6 All Stats.", GOSSIP_SENDER_MAIN, 2661);
                player->ADD_GOSSIP_ITEM(5, "+16 Intellect.", GOSSIP_SENDER_MAIN, 1119);
                if (player->HasSkill(SKILL_BLACKSMITHING) && player->GetSkillValue(SKILL_BLACKSMITHING) == 450)
                    player->ADD_GOSSIP_ITEM(5, "Socket Bracer.", GOSSIP_SENDER_MAIN, 3717);
                player->ADD_GOSSIP_ITEM(5, "Back!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
                break;

            case 10: // Waist.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST);
                if (player->HasSkill(SKILL_ENGINEERING) && player->GetSkillValue(SKILL_ENGINEERING) == 450)
                {
                    player->ADD_GOSSIP_ITEM(5, "Electromagnetic Pulse Generator.", GOSSIP_SENDER_MAIN, 3599);
                    player->ADD_GOSSIP_ITEM(5, "Frag Belt.", GOSSIP_SENDER_MAIN, 3601);
                }
                player->ADD_GOSSIP_ITEM(5, "Eternal Belt Buckle.", GOSSIP_SENDER_MAIN, 3729);
                player->ADD_GOSSIP_ITEM(5, "Back!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
                break;

            case 11: // Gloves.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS);
                if (player->HasSkill(SKILL_ENGINEERING) && player->GetSkillValue(SKILL_ENGINEERING) == 450)
                {
                    player->ADD_GOSSIP_ITEM(5, "Reticulated Armor Webbing.", GOSSIP_SENDER_MAIN, 3860);
                    player->ADD_GOSSIP_ITEM(5, "Hyperspeed Accelerators.", GOSSIP_SENDER_MAIN, 3604);
                    player->ADD_GOSSIP_ITEM(5, "Hand-Mounted Pyro Rocket.", GOSSIP_SENDER_MAIN, 3603);
                }
                player->ADD_GOSSIP_ITEM(5, "+28 Spell Power.", GOSSIP_SENDER_MAIN, 3246);
                player->ADD_GOSSIP_ITEM(5, "+16 Critical Chance.", GOSSIP_SENDER_MAIN, 3249);
                player->ADD_GOSSIP_ITEM(5, "+10 Parry, +2% Threat.", GOSSIP_SENDER_MAIN, 3253);
                player->ADD_GOSSIP_ITEM(5, "+44 Attack Power.", GOSSIP_SENDER_MAIN, 1603);
                player->ADD_GOSSIP_ITEM(5, "+20 Agility.", GOSSIP_SENDER_MAIN, 3222);
                player->ADD_GOSSIP_ITEM(5, "+20 Hit Chance.", GOSSIP_SENDER_MAIN, 3234);
                player->ADD_GOSSIP_ITEM(5, "+15 Expertise.", GOSSIP_SENDER_MAIN, 3231 + USED_ONCE_ALREADY);
                if (player->HasSkill(SKILL_BLACKSMITHING) && player->GetSkillValue(SKILL_BLACKSMITHING) == 450)
                    player->ADD_GOSSIP_ITEM(5, "Socket Gloves.", GOSSIP_SENDER_MAIN, 3723);
                player->ADD_GOSSIP_ITEM(5, "Back!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
                break;

            case 12: // Legs.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS);
                player->ADD_GOSSIP_ITEM(5, "+40 Resilience, +28 Stamina.", GOSSIP_SENDER_MAIN, 3853);
                player->ADD_GOSSIP_ITEM(5, "+55 Stamina, +22 Agility.", GOSSIP_SENDER_MAIN, 3822);
                player->ADD_GOSSIP_ITEM(5, "+75 Attack Power, +22 Critical Chance.", GOSSIP_SENDER_MAIN, 3823);
                player->ADD_GOSSIP_ITEM(5, "+50 Spell Power, +20 Spirit.", GOSSIP_SENDER_MAIN, 3719);
                player->ADD_GOSSIP_ITEM(5, "+50 Spell Power, +30 Stamina.", GOSSIP_SENDER_MAIN, 3721);
                player->ADD_GOSSIP_ITEM(5, "Back!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
                break;

            case 13: // Feet
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET);
                if (player->HasSkill(SKILL_ENGINEERING) && player->GetSkillValue(SKILL_ENGINEERING) == 450)
                    player->ADD_GOSSIP_ITEM(5, "Nitro Boots", GOSSIP_SENDER_MAIN, 3606);
                player->ADD_GOSSIP_ITEM(5, "+32 Attack Power.", GOSSIP_SENDER_MAIN, 1597);
                player->ADD_GOSSIP_ITEM(5, "+15 Stamina, +8% Movement.", GOSSIP_SENDER_MAIN, 3232);
                player->ADD_GOSSIP_ITEM(5, "+16 Agility.", GOSSIP_SENDER_MAIN, 983);
                player->ADD_GOSSIP_ITEM(5, "+18 Spirit.", GOSSIP_SENDER_MAIN, 1147 + USED_ONCE_ALREADY);
                player->ADD_GOSSIP_ITEM(5, "+12 Hit Chance, +12 Critical Chance.", GOSSIP_SENDER_MAIN, 3826);
                player->ADD_GOSSIP_ITEM(5, "+22 Stamina.", GOSSIP_SENDER_MAIN, 1075);
                player->ADD_GOSSIP_ITEM(5, "Back!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
                break;

            case 14: // Rings
                player->ADD_GOSSIP_ITEM(5, "+40 Attack Power.", GOSSIP_SENDER_MAIN, 3839);
                player->ADD_GOSSIP_ITEM(5, "+28 Spell Power.", GOSSIP_SENDER_MAIN, 3840);
                player->ADD_GOSSIP_ITEM(5, "+30 Stamina.", GOSSIP_SENDER_MAIN, 3791);
                player->ADD_GOSSIP_ITEM(5, "Back!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
                break;

            case GOSSIP_ACTION_INFO_DEF:
                OnGossipHello(player, creature);
                break;

            case 3854: // [STAFF] +81 Spell Power.
            case 2670: // [2H] +35 Agility.
            case 3827: // [2H] +110 Attack Power."
            case 1103: // +25 Agility.
            case 3788: // +25 Hit +25 Crit.
            case 3833: // +65 Attack Power.
            case 3834: // +63 Spell Power.
            case 3844: // +45 Spirit.
            case 3869: // Blade Ward.
            case 3870: // Blood Draining.
            case 3789: // Berserking.
            case 3790: // Black Magic.
            case 3239: // Icebreaker.
            case 1894: // Icy Chill.
            case 2673: // Mongoose.
            case 3225: // Executioner.
            case 3731: // Titanium Weapon Chain.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
                Apply(player, creature, action, item);
                OnGossipHello(player, creature);
                break;

            case 1952: // +20 Defense.
            case 1128: // +25 Intellect.
            case 3229: // +12 Resilience.
            case 3849: // Titanium Plating.
            case 1071: // +18 Stamina.
            case 3854 + USED_ONCE_ALREADY: // [STAFF] +81 Spell Power.
            case 2670 + USED_ONCE_ALREADY: // [2H] +35 Agility.
            case 3827 + USED_ONCE_ALREADY: // [2H] +110 Attack Power.
            case 1103 + USED_ONCE_ALREADY: // +25 Agility.
            case 3788 + USED_ONCE_ALREADY: // +25 Hit +25 Crit.
            case 3833 + USED_ONCE_ALREADY: // +65 Attack Power.
            case 3834 + USED_ONCE_ALREADY: // +63 Spell Power.
            case 3844 + USED_ONCE_ALREADY: // +45 Spirit.
            case 3869 + USED_ONCE_ALREADY: // Blade Ward.
            case 3870 + USED_ONCE_ALREADY: // Blood Draining.
            case 3789 + USED_ONCE_ALREADY: // Berserking.
            case 3790 + USED_ONCE_ALREADY: // Black Magic.
            case 3239 + USED_ONCE_ALREADY: // Icebreaker.
            case 1894 + USED_ONCE_ALREADY: // Icy Chill.
            case 2673 + USED_ONCE_ALREADY: // Mongoose.
            case 3225 + USED_ONCE_ALREADY: // Executioner.
            case 3731 + USED_ONCE_ALREADY: // Titanium Weapon Chain.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
                Apply(player, creature, action, item);
                OnGossipHello(player, creature);
                break;

            case 3608: // +40 Ranged Critical Chance.
            case 2523: // +30 Ranged Hit Chance.
            case 3607: // +40 Ranged Haste.
            case 3843: // +15 Damage.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED);
                Apply(player, creature, action, item);
                OnGossipHello(player, creature);
                break;

            case 4222: // Mind Amplification Dish.
            case 3795: // +50 Attack Power, +20 Resilience.
            case 3796: // +29 Spell Power, +20 Resilience.
            case 3819: // +30 Spell Power, +10 MP5.
            case 3820: // +30 Spell Power, +20 Critical Chance.
            case 3842: // +30 Stamina, +25 Resilience.
            case 3818: // +37 Stamina, +20 Defense.
            case 3817: // +50 Attack Power, +20 Critical Chance.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD);
                Apply(player, creature, action, item);
                OnGossipHello(player, creature);
                break;

            case 3835: // [INSCRIPTION] +120 Attack Power, +15 Critical Chance.
            case 3836: // [INSCRIPTION] +70 Spell Power, +8 MP5."
            case 3837: // [INSCRIPTION] +60 Dodge, +15 Defense.
            case 3838: // [INSCRIPTION] +70 spell Power, +15 Critical Chance.
            case 3808: // +40 Attack Power, +15 Critical Chance."
            case 3809: // +24 Spell Power, +8 MP5.
            case 3811: // +20 Dodge, +15 Defense.
            case 3810: // +24 Spell Power, +15 Critical Chance.
            case 3793: // +40 Attack Power, +15 Resilience.
            case 3794: // +23 Spell Power, +15 Resilience.
            case 3852: // +30 Stamina, +15 Resilience.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS);
                Apply(player, creature, action, item);
                OnGossipHello(player, creature);
                break;

            case 3728: // Darkglow Embroidery.
            case 3722: // Lightweave Embroidery.
            case 3730: // Swordguard Embroidery.
            case 3859: // Springy Arachnoweave.
            case 3605: // Flexweave Underlay.
            case 1099: // +22 Agility.
            case 3256: // +10 Agility, Increased Stealth.
            case 3296: // +10 Spirit, -2% Threat.
            case 1951: // +16 Defense.
            case 3243: // +35 Spell Penetration.
            case 3294: // +225 Armor."
            case 3831: // +23 Haste.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK);
                Apply(player, creature, action, item);
                OnGossipHello(player, creature);
                break;

            case 3832: // +10 All Stats.
            case 3297: // +275 Health.
            case 2381: // +10 MP5.
            case 3245: // +20 Resilience.
            case 1953: // +22 Defense.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST);
                Apply(player, creature, action, item);
                OnGossipHello(player, creature);
                break;

            case 3756: // [LEATHERWORKING] +130 Attack Power.
            case 3757: // [LEATHERWORKING] +102 Stamina.
            case 3758: // [LEATHERWORKING] +76 Spell Power.
            case 3845: // +50 Attack Power.
            case 3850: // +40 Stamina.
            case 2332: // +30 Spell Power.
            case 1147: // +18 Spirit.
            case 3231: // +15 Expertise.
            case 2661: // +6 All Stats.
            case 1119: // +16 Intellect.
            case 3717: // Socket Bracer.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS);
                Apply(player, creature, action, item);
                OnGossipHello(player, creature);
                break;

            case 3599: // Electromagnetic Pulse Generator.
            case 3601: // Frag Belt.
            case 3729: // Eternal Belt Buckle.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST);
                Apply(player, creature, action, item);
                OnGossipHello(player, creature);
                break;

            case 3860: // Reticulated Armor Webbing.
            case 3604: // Hyperspeed Accelerators.
            case 3603: // Hand-Mounted Pyro Rocket.
            case 3246: // +28 Spell Power.
            case 3249: // +16 Critical Chance.
            case 3253: // +10 Parry, +2% Threat.
            case 1603: // +44 Attack Power.
            case 3222: // +20 Agility.
            case 3234: // +20 Hit Chance.
            case 3231 + USED_ONCE_ALREADY: // +15 Expertise.
            case 3723: // Socket Gloves.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS);
                Apply(player, creature, action, item);
                OnGossipHello(player, creature);
                break;

            case 3853: // +40 Resilience, +28 Stamina. 
            case 3822: // +55 Stamina, +22 Agility. 
            case 3823: // +75 Attack Power, +22 Critical Chance. 
            case 3719: // +50 Spell Power, +20 Spirit. 
            case 3721: // +50 Spell Power, +30 Stamina. 
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS);
                Apply(player, creature, action, item);
                OnGossipHello(player, creature);
                break;

            case 3606: // Nitro Boots 
            case 1597: // +32 Attack Power.
            case 3232: // +15 Stamina.
            case 983: // +16 Agility.
            case 1147 + USED_ONCE_ALREADY: // +18 Spirit.
            case 3826: // +12 Hit Chance, +12 Critical Chance.
            case 1075: // +22 Stamina.
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET);
                Apply(player, creature, action, item);
                OnGossipHello(player, creature);
                break;

            case 3839: // +40 Attack Power.
            case 3840: // +28 Spell Power.
            case 3791: // +30 Stamina.
                Item* one;
                Item* two;
                one = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1);
                two = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2);
                Apply(player, creature, action, one);
                Apply(player, creature, action, two);
                OnGossipHello(player, creature);
                break;

            default:
                player->PlayerTalkClass->SendCloseGossip();
                creature->Whisper("This ain't implented yet, yo! (404, error).", LANG_UNIVERSAL, player);
                break;
            }
        }
        return true;
    }
};

void AddSC_npc_enchantments()
{
    new npc_enchantments();
}