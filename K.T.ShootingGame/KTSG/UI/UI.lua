--UI lua file
--控制項type編號={1=button,2=text,3=combo box}
--formate
--uinum = UI的數量
--ui1={
--		cmdnum=控制項數量,
--		cmd1={cid=id編號(數字), ctext=控制項的字, ctype=控制項類型(數字), cpx=控制項x座標, cpy=控制項y座標,
--		cw=控制項寬度, ch=控制項長度}
--		cmd2.....
--		}
--ui2={...
--		}
--預設畫面size=1440*900
--物件座標和長寬會自動轉換
--
--如果控制項為combo box格式為
--		...,
--		cmd1={cid=id編號(數字), ctext=控制項的字, ctype=控制項類型(數字), cpx=控制項x座標, cpy=控制項y座標,
--		cw=控制項寬度, ch=控制項長度, itemnum=物件數,
--		item1 = item的字,
--		item2 = hello
--		...
--		}
uinum = 2
ui1={
		cmdnum=2,
		cmd1={cid=1, ctext="yaya", ctype=1, cpx=1000, cpy=400,
		cw=200, ch=100},
		cmd2={cid=2, ctext="hello", ctype=2, cpx=1000, cpy=550,
		cw=200, ch=100}
}

ui2={
		cmdnum=1,
		cmd1={cid=1, ctext="yes", ctype=3, cpx=1000, cpy=710,
		cw=200, ch=50, itemnum = 4,
		item1 = "火焰",
		item2 = "冰凍",
		item3 = "thunder",
		item4 = "storm"}
}
