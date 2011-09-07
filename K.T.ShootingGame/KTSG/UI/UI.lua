--UI lua file
--北兜type絪腹={1=button,2=text,3=combo box, 4=slider}
--formate
--uinum = UI计秖
--ui1={
--		cmdnum=北兜计秖,
--		cmd1={cid=id絪腹(计), ctext=北兜, ctype=北兜摸(计), cpx=北兜x畒夹, cpy=北兜y畒夹,
--		cw=北兜糴, ch=北兜}
--		cmd2.....
--		}
--ui2={...
--		}
--箇砞礶size=1440*900
--ン畒夹㎝糴穦笆锣传
--
--狦北兜combo boxΑ
--		...,
--		cmd1={cid=id絪腹(计), ctext=北兜, ctype=北兜摸(计), cpx=北兜x畒夹, cpy=北兜y畒夹,
--		cw=北兜糴, ch=北兜, itemnum=ン计,
--		item1 = item,
--		item2 = hello
--		...
--		}
--狦北兜sliderΑ
--		...,
--		cmd1={cid=id絪腹(计), ctext=北兜, ctype=北兜摸(计), cpx=北兜x畒夹, cpy=北兜y畒夹,
--		cw=北兜糴, ch=北兜, cmin=slider程, cmax=slider程, cval=slider﹍
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
