SET
@Entry = 190010,
@Name = "Transfigurador Magdalena";
DELETE FROM `creature_template` WHERE `entry` = 190010;

INSERT INTO `creature_template` (`entry`, `modelid1`, `modelid2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(@Entry, 19646, 0, @Name, "WoW Magdalena", NULL, 0, 80, 80, 2, 35, 1, 1.2, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 3, 1, 0, 0, 1, 0, 0, 'npc_transmogrifier');

--aura
INSERT INTO creature_template_addon (entry, mount, bytes1, bytes2, emote, path_id, auras) VALUES (190010, 0, 0, 0, 0, 0, "30540");