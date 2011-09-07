pic = {
{100, "Media/picture/ball1.png"},
{101, "Media/picture/crate.jpg"},
{102, "Media/picture/main_warship.png"},
{103, "Media/picture/ray1.png"},
{104, "Media/picture/tower1.png"},
}

wav = {
{18, "Media/music/018.wav", 10}
}

i=0;

function count()
	local res = i;
	i=i+1;
	return res;
end

path1=
{
	type="beziercurve",
	offset={x=0,y=0},
	{time=count(),x=100,y=2000},
	{time=count(),x=100,y=1900},
	{time=count(),x=200,y=1700},
	{time=count(),x=300,y=1500},
	{time=count(),x=200,y=1300},
	{time=count(),x=100,y=1100},
	{time=count(),x=200,y=900},
	{time=count(),x=300,y=700},
	{time=count(),x=200,y=500},
	{time=count(),x=100,y=300},
	{time=count(),x=100,y=100},
	{time=count(),x=100,y=-300},
}

straight1=
{
	type="straight",
	velocity=200,
	polygon=
	{
		{x=0,y=0},
		{x=0,y=50},
	}
}

nway1=
{
	type="nway",
	num=3,
	RadiationAngle=40,
}

tower1=
{
	x=0,
	y=0,
	trajectory=nway1,
	Behavior=straight1,
	type="ray",
	atk=50,
	atkspeed=0.3,
	ballpic=103
}


plane1 =
{
	path = path1,
	tower=
	{
		tower1
	},
}

stage =
{
	{
		time=3.5,
		plane=plane1
	}
}

