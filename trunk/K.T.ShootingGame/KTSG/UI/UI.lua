--UI lua file
--���type�s��={1=button,2=text,3=combo box, 4=slider}
--formate
--uinum = UI���ƶq
--ui1={
--		cmdnum=����ƶq,
--		cmd1={cid=id�s��(�Ʀr), ctext=������r, ctype=�������(�Ʀr), cpx=���x�y��, cpy=���y�y��,
--		cw=����e��, ch=�������}
--		cmd2.....
--		}
--ui2={...
--		}
--�w�]�e��size=1440*900
--����y�ЩM���e�|�۰��ഫ
--
--�p�G�����combo box�榡��
--		...,
--		cmd1={cid=id�s��(�Ʀr), ctext=������r, ctype=�������(�Ʀr), cpx=���x�y��, cpy=���y�y��,
--		cw=����e��, ch=�������, itemnum=�����,
--		item1 = item���r,
--		item2 = hello
--		...
--		}
--�p�G�����slider�榡��
--		...,
--		cmd1={cid=id�s��(�Ʀr), ctext=������r, ctype=�������(�Ʀr), cpx=���x�y��, cpy=���y�y��,
--		cw=����e��, ch=�������, cmin=slider���̤p��, cmax=slider���̤j��, cval=slider����l��
--		...
--		}
uinum = 2

ui1={	--main menu
		cmdnum=3,
		cmd1={cid=1, ctext="Start Game", ctype=1, cpx=590, cpy=450, cw=260, ch=80},
		cmd2={cid=2, ctext="Option", ctype=1, cpx=590, cpy=600, cw=260, ch=80},
		cmd3={cid=3, ctext="Exit", ctype=1, cpx=590, cpy=750, cw=260, ch=80}
}

ui2={	--option menu
		cmdnum=15,
		cmd1={cid=4, ctext="volume", ctype=2, cpx=300, cpy=200, cw=100, ch = 50},
		cmd2={cid=5, ctext="", ctype=4, cpx=400, cpy=200, cw=640, ch = 50, cmin=0, cmax=100, cval=50},

		cmd3={cid=6, ctext="Up", ctype=2, cpx=350, cpy=300, cw=80, ch=50},
		cmd4={cid=7, ctext="Up", ctype=1, cpx=480, cpy=300, cw=80, ch=50},

		cmd5={cid=8, ctext="Down", ctype=2, cpx=350, cpy=400, cw=80, ch=50},
		cmd6={cid=9, ctext="Down", ctype=1, cpx=480, cpy=400, cw=80, ch=50},

		cmd7={cid=10, ctext="Skill", ctype=2, cpx=350, cpy=500, cw=80, ch=50},
		cmd8={cid=11, ctext="Skill", ctype=1, cpx=480, cpy=500, cw=80, ch=50},

		cmd9={cid=12, ctext="Left", ctype=2, cpx=950, cpy=300, cw=80, ch=50},
		cmd10={cid=13, ctext="Left", ctype=1, cpx=1080, cpy=300, cw=80, ch=50},

		cmd11={cid=14, ctext="Right", ctype=2, cpx=950, cpy=400, cw=80, ch=50},
		cmd12={cid=15, ctext="Right", ctype=1, cpx=1080, cpy=400, cw=80, ch=50},

		cmd13={cid=16, ctext="time", ctype=2, cpx=950, cpy=500, cw=80, ch=50},
		cmd14={cid=17, ctext="time", ctype=1, cpx=1080, cpy=500, cw=80, ch=50},

		cmd15={cid=18, ctext="Exit", ctype=1, cpx=50, cpy=100, cw=120, ch=70}
}
