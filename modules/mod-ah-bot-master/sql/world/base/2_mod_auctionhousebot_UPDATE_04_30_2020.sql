--Config AH1
DELETE FROM `mod_auctionhousebot` WHERE `auctionhouse` IN (2,6,7);

INSERT INTO `mod_auctionhousebot` (`auctionhouse`, `name`, `minitems`, `maxitems`, `percentgreytradegoods`, `percentwhitetradegoods`, `percentgreentradegoods`, `percentbluetradegoods`, `percentpurpletradegoods`, `percentorangetradegoods`, `percentyellowtradegoods`, `percentgreyitems`, `percentwhiteitems`, `percentgreenitems`, `percentblueitems`, `percentpurpleitems`, `percentorangeitems`, `percentyellowitems`, `minpricegrey`, `maxpricegrey`, `minpricewhite`, `maxpricewhite`, `minpricegreen`, `maxpricegreen`, `minpriceblue`, `maxpriceblue`, `minpricepurple`, `maxpricepurple`, `minpriceorange`, `maxpriceorange`, `minpriceyellow`, `maxpriceyellow`, `minbidpricegrey`, `maxbidpricegrey`, `minbidpricewhite`, `maxbidpricewhite`, `minbidpricegreen`, `maxbidpricegreen`, `minbidpriceblue`, `maxbidpriceblue`, `minbidpricepurple`, `maxbidpricepurple`, `minbidpriceorange`, `maxbidpriceorange`, `minbidpriceyellow`, `maxbidpriceyellow`, `maxstackgrey`, `maxstackwhite`, `maxstackgreen`, `maxstackblue`, `maxstackpurple`, `maxstackorange`, `maxstackyellow`, `buyerpricegrey`, `buyerpricewhite`, `buyerpricegreen`, `buyerpriceblue`, `buyerpricepurple`, `buyerpriceorange`, `buyerpriceyellow`, `buyerbiddinginterval`, `buyerbidsperinterval`)
VALUES
('2','Alliance','600','600','0','65','40','35','20','0','0','0','28','40','20','35','0','0','100','150','2150','4050','1800','3400','4250','5750','9250','10550','33250','55550','55250','66550','70','100','70','100','80','100','75','100','80','100','80','100','80','100','0','2','5','5','5','1','1','1','13','25','32','45','60','22','1','1'),
('6','Horde','600','600','0','65','40','35','20','0','0','0','28','40','20','35','0','0','100','150','2150','4050','1800','3400','4250','5750','9250','10550','33250','55550','55250','66550','70','100','70','100','80','100','75','100','80','100','80','100','80','100','0','2','5','5','5','1','1','1','13','25','32','45','60','22','1','1'),
('7','Neutral','700','700','0','65','40','35','20','0','0','0','28','40','20','35','0','0','100','150','2150','4050','1800','3400','4250','5750','9250','10550','33250','55550','55250','66550','70','100','70','100','80','100','75','100','80','100','80','100','80','100','0','10','10','10','10','1','1','1','13','25','32','45','60','22','1','1');
