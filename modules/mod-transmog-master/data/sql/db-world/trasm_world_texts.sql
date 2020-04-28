SET @TEXT_ID := 601083;
DELETE FROM `npc_text` WHERE `ID` IN  (@TEXT_ID,@TEXT_ID+1);
INSERT INTO `npc_text` (`ID`, `text0_0`) VALUES
(@TEXT_ID, 'Transfiguracion te permite cambiar la apariencia de tus items sin cambiar sus estadisticas.\r\nItems usados para la transfiguracion dejaran de ser reembolsables, comerciables y se ligaran a ti.\r\nAl actualizar un menu actualizara el precio y su vista.\r\n\r\nNo todo se puede transfigurar entre si.\r\nExisten restricciones pero no estan limitadas a:\r\nSolo armaduras y armas pueden ser transfiguradas\r\nArmas de fuego,Arcos y Ballestas pueden transfigurarse entre si\r\nCañas de pescar no pueden transfigurarse\r\nDebes poder equipar los dos Items utilizados en el proceso.\r\n\r\nTransfiguraciones permaneceran en tus Items mientras los poseas.\r\nSi intentas poner el Item en tu banco de hermandad o enviarlo por correo a alguien mas, la transfiguracion se pierde.\r\n\r\nTambien puedes quitarte las transfiguraciones gratis en el transfigurador.'),
(@TEXT_ID+1, 'Puedes guardar tu propio conjunto de transfiguracion.\r\n\r\nPara guardar, primero deberas transfigurar tus items equipados.\r\nDespues cuando vallas al menu de organizar conjuntos y luego al menu de guardar conjuntos,\r\ntodos los items que has transfigurado se muestran para que veas que estas guardando.\r\nSi crees que tu conjunto esta bueno, puedes guardar el conjunto y nombrarlo como desees.\r\n\r\nPara usar un conjunto puedes clickear en conjuntos guardados en el menu de organizar conjuntos y luego seleecionar usar conjunto.\r\nSi el conjunto tiene una transfiguracion para item que ya esta transfigurado, la previa transfiguracion se pierde.\r\nTen en cuenta que se aplican las mismas restricciones de transfiguración al intentar usar un conjunto que en la transfiguración normal.\r\n\r\nPara eliminar un conjunto puedes ir al menu de conjuntos y seleccionar eliminar conjunto.');

SET @STRING_ENTRY := 11100;
DELETE FROM `acore_string` WHERE `entry` IN  (@STRING_ENTRY+0,@STRING_ENTRY+1,@STRING_ENTRY+2,@STRING_ENTRY+3,@STRING_ENTRY+4,@STRING_ENTRY+5,@STRING_ENTRY+6,@STRING_ENTRY+7,@STRING_ENTRY+8,@STRING_ENTRY+9,@STRING_ENTRY+10);
INSERT INTO `acore_string` (`entry`, `content_default`) VALUES
(@STRING_ENTRY+0, 'Item transfigurado.'),
(@STRING_ENTRY+1, 'La ranura del equipo esta vacia.'),
(@STRING_ENTRY+2, 'Objeto de origen seleccionado invalido.'),
(@STRING_ENTRY+3, 'Objeto de origen no existe.'),
(@STRING_ENTRY+4, 'Objeto de destino no existe.'),
(@STRING_ENTRY+5, 'Objetos seleccionados son invalidos.'),
(@STRING_ENTRY+6, 'No tienes el Dinero suficiente.'),
(@STRING_ENTRY+7, 'No tienes suficientes emblemas.'),
(@STRING_ENTRY+8, 'Transfiguraciones eliminadas.'),
(@STRING_ENTRY+9, 'No hay transfiguraciones.'),
(@STRING_ENTRY+10, 'Nombre no valido insertado.');

