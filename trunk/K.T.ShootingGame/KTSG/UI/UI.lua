--UI lua file
--���type�s��={1=button,2=text,3=combo box}
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
		item1 = "���K",
		item2 = "�B��",
		item3 = "thunder",
		item4 = "storm"}
}
