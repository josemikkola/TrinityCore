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
