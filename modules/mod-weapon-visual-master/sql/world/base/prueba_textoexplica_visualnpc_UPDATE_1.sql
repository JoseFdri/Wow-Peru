DELETE FROM `npc_text` WHERE `ID` = 64646;
-- \r\n parrafo x2 = dobleparrafo y espacio
SET @TEXT_ID := 64646;
REPLACE INTO `npc_text` (`ID`, `text0_0`) VALUES
(@TEXT_ID, 'El |cffff8000Resplandor de armas|r, te dejara usar cualquier efecto visual de encantamientos en tus armas (Solo efecto visual).\r\n\r\n|cffef0000Restriccion:|r\r\nSi tu arma ya tiene un efecto visual proveniente del arma y no de un encantamiento, no podras usar ningun resplandor de arma, en esa arma especifica.\r\n\r\n|cff71d5ffSe puede usar un efecto visual en mi arma si esta Transfigurada?|r\r\nSi, si tu arma no infiere con la restriccion, asi este transfigurada, podra usar un efecto visual de la lista.\r\n\r\n|cff71d5ffSe puede usar un efecto visual en mi arma si tiene algun encantamiento con efecto visual?|r\r\nSi, si tu arma no infiere con la restriccion, asi tenga un encantamiento con efecto visual, podras usar un efecto visual de la lista.\r\n\r\nHora de relucir $N.'),


